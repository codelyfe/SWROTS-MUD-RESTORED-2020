<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/
	
class SocketServer
{
	private $socket;
	
	private $address;
	private $port;
	private $max_clients;
	
	private $clients;
	
	private $output;
	
	private $handler;
	
	private $client_type;
	
	private $client_class;
	
	private $policy_file;
	
	// Construct the initial server object //
	function __construct($address = "localhost", $port=12345, $c_type=GC_TELNET, $max_clients=256)
	{
		set_time_limit (0);
		$this->address = $address;
		$this->port = $port;
		$this->max_clients = $max_clients;
		
		$this->clients = array();
		$this->read = array();
		
		$this->output = "";
		
		$this->handler = false;
		
		$this->client_type = $c_type;
		
		$this->set_client_class();
		
		// Policy file for flash clients //
		$policy_file =
				   '<'.'?xml version="1.0" encoding="UTF-8"?'.'>'.
				    '<cross-domain-policy xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.adobe.com/xml/schemas/PolicyFileSocket.xsd">'.
				        '<allow-access-from domain="*" to-ports="*" secure="false" />'.
				        '<site-control permitted-cross-domain-policies="master-only" />'.
				    '</cross-domain-policy>'; 
		
	}
	
	// Create the server instance //
	function create()
	{
		// Create a TCP Stream socket
		$this->socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
		
		// Set the REUSE option before binding //
		if(!socket_set_option($this->socket,SOL_SOCKET,SO_REUSEADDR,1))
		{
			print(socket_strerror(socket_last_error($this->socket)));
			die();
		}
		
		$time = time();
		$bound = false;
		
		// Bind the socket to an address/port
		while ($time + 10 > time() && !$bound)
		{
			print ("Attempting to bind to port {$this->port}...\n");
			$bound = socket_bind($this->socket, $this->address, $this->port);
			if ($bound)
				break;
			else		
				sleep(1);
		}

		if (!$bound)
		{
			print ("Could not bind...\n");
			die();
		}
		
		// Start listening for connections
		if (socket_listen($this->socket))
			print ("Socket server started at address {$this->address} on port {$this->port}\n");
			
		// Make it non-blocking //
		socket_set_nonblock($this->socket);
	}
	
	// Orderly server shutdown //
	function shutdown()
	{
		// Close the client sockets //
		for ($i = 0; $i < $this->max_clients; $i++) // for each client
		{
			if (is_resource($clients[$i]->socket)) {
		        socket_write($clients[$i]->socket, "Server is going down!\n");
		        socket_close($clients[$i]->socket);
		        unset($clients[$i]);
		        print("Forced disconnect of Client $i");
		    } 
		}
		
		socket_close($this->socket);
	}
	
	// Listen for and accept new connections //
	function listen()
	{
		$client_class = $this->client_class;
		
		$this->read = array($this->socket);
			
		    // Setup clients listen socket for reading		  
		    for ($i = 0; $i < $this->max_clients; $i++)
		    {
		        if (is_resource($this->clients[$i]->socket))
		            $this->read[$i + 1] = $this->clients[$i]->socket ;
		    }
		    
			// Set up a non-blocking call to socket_select()
		    $ready = socket_select($this->read, $write = NULL, $except = NULL, 0); // For blocking: $tv_sec = NULL);
		    
		    
			/* if a new connection is being made add it to the client array */
		    if (in_array($this->socket, $this->read))
		    {
		        for ($i = 0; $i < $this->max_clients; $i++)
		        {
					if (!is_object($this->clients[$i]))
					{
						$this->clients[$i] = new $client_class($i, socket_accept($this->socket));
						print("Client $i connected.\n");						
											
						// Call on_connect -- should be overridden for any extended functionality //
						$this->on_connect($i);
						
						break;
					} elseif ($i == $this->max_clients - 1)
						print ("Too many clients connected.");	                
		        }
		        
		        if (--$ready <= 0)
		            return;
		    } // end if in_array
	}
	
	// Default handling for a new client successfully connected //
	function on_connect($clientID)
	{
		return true;
	}

	// Default handling for a client disconnecting //
	function on_disconnect($clientID)
	{
		return true;
	}
	
	// Write to all clients //
	function write_all($buf, $fromClient = -1)
	{		
		if ($buf != "") // New messages to send //
	    {
	    	echo "[$fromClient] sends: $buf\n";
		    for ($i = 0; $i < $this->max_clients; $i++) // for each client
			{
				if (is_resource($this->clients[$i]->socket)) 
				{
			        socket_write($this->clients[$i]->socket, $buf . "\r\n");			       	        
			    } 
			}
	    }
	}
	
	// Write to all clients except the one specified //
	function write_all_except($cID, $buf)
	{
		if ($buf != "") // New messages to send //
	    {
		    for ($i = 0; $i < $this->max_clients; $i++) // for each client
			{
				if ($i != $cID && is_resource($this->clients[$i]->socket)) 
				{
			        socket_write($this->clients[$i]->socket, $buf . "\r\n");	        
			    } 
			}
	    }
	}
	
	// Write to specific client //
	function write_client($cID, $buf)
	{
		if ($buf != "") // New messages to send //
	    {
			if (is_resource($this->clients[$cID]->socket)) 
			{
		        socket_write($this->clients[$cID]->socket, $buf . "\r\n");	        
		    }			
	    }
	}
	
	// Read incoming data
	function read_incoming()
	{
		for ($i = 0; $i < $this->max_clients; $i++) // for each client
	    {    	
	        if (in_array($this->clients[$i]->socket, $this->read))
	        {
	            //$input = socket_read($this->clients[$i]->socket, 2048, PHP_BINARY_READ);
	           	@socket_recv($this->clients[$i]->socket, $input, 2048, MSG_DONTWAIT);
	           	
	            if ($input == null) 
	            {
	                // Zero length string meaning disconnected
	                echo "Disconnecting $i: bad read.\n";
	                $this->on_disconnect($i);
	                unset ($this->clients[$i]);
	                break;
	            } else {	            
	            	$input = trim($input);
	           
					$this->on_read($i, $input);	            
	            }
	        }	        
	    }
	}
	
	// Handle data successfully read //
	function on_read($client, $data)
	{
		print ("Client $client sent: $data\n");					

		if ($data == 'exit') 
		{
			// requested disconnect
			socket_close($this->clients[$client]->socket);			
			unset($this->clients[$client]);
			print ("Client $client requested disconnect.\n");
			return;
		} 
			            
		if ($data == 'shutdown')
		{
			print ("Client $client requested server shutdown.\n");
			$this->shutdown();
			return;
		}
			            
		$this->append_buffer("Client $client said, \"$data\"\n");
	}

	// Add data to the buffer that will be written to all //
	function append_buffer($data)
	{
		$this->output .= $data;
	}
	
	// Handle incoming/outgoing traffic //
	function process_looped()
	{
		// Loop continuously
		while (true) {
			// Look for new clients //
			$this->listen();			
			
		    // If a client is trying to send data, handle it now //			
		    $this->read_incoming();
		    
			// Write data bound for all clients //
			$this->write_all($this->output);		    
			
		    $this->output = "";
		    
		} // end while
	}

	// Handle incoming/outgoing traffic ONCE //
	function process()
	{
		// Look for new clients //
		$this->listen();			
		
	    // If a client is trying to send data, handle it now //			
	    $this->read_incoming();
	    
		// Write data bound for all clients //
		$this->write_all($this->output);		    
		
	    $this->output = "";
	}
	
	// Get the client type (Telnet, WebSocket, Flash) //
	function getClientType()
	{
		return $this->client_type;
	}
	
	// Set the Class to be used for client instances //
	function set_client_class($cc = "SocketClient")
	{
		$this->client_class = $cc;
	}
	
	// Return the client object //
	function getClientObject($id)
	{
		if (is_object($this->clients[$id]))
			return $this->clients[$id];
		else 
			return false;
	}
	
	function setClientObject($id, $cObj)
	{
		$this->clients[$id] = $cObj;
	}
	
	function removeClientObject($id)
	{		
		unset ($this->clients[$id]);
	}

	function getClients()
	{
		return $this->clients;
	}
	
	function getHeaders($req)
	{	
		/*
	 	GET /phudbase/wm_server/server.php HTTP/1.1
		Upgrade: WebSocket
		Connection: Upgrade
		Host: pbtest.com:12346
		Origin: http://pbtest.com	  
	 	*/
	
		$req = str_replace("GET ", "", $req);
		$req = str_replace(" HTTP/1.1", "", $req);
		$req = str_replace("Upgrade: WebSocket\r\n", "", $req);
		$req = str_replace("Connection: Upgrade\r\n", "", $req);
		$req = str_replace("Host: ", "", $req);
		$req = str_replace("Origin: ", "", $req);
		
		$parts = split("\r\n", $req);
		
		$res = $parts[0];
		$host = $parts[1];
		$ori = $parts[2];	
		
		return array($res,$host,$ori);
	}
}

if (!defined('MSG_DONTWAIT')) {
   define('MSG_DONTWAIT', 0x40);
   return 1;
}
?>