<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

class WebMudServer extends SocketServer
{		
	private $policy_server;
	
	function create()
	{
		parent::create();
		
		// Establish a Policy Server for Flash clients (optional) //
		$this->policy_server = new PolicyServer(HOST, PORT_POLICY);		
		$this->policy_server->create();
		
	}
	
	function process()
	{			
		while (true)
		{			
			// Let the primary socket server listen/read/write as necessary //
			parent::process();			
			
			// Check each client connected for a good mud connection, then check 
			// THAT connection for new data, disconnects, etc. //			
			$clients = $this->getClients();
			if (is_array($clients))
			{
				foreach ($clients as $key => $client)
				{		
					if ($client->connectedMUD())
					{					
						$mc = $client->getMudConnection();					
						
						// If it's a good socket //
						if (is_resource($mc))
						{		
							$input = "";
							
							//$input = @socket_read($mc, 16384, PHP_BINARY_READ);
							$flag = @socket_recv($mc,$input,1024,MSG_DONTWAIT);
							
							if ($flag === 0)
							{	
								// We lost the connection //
								$this->on_wm_disconnect($client->getID());
								
								if ($input == "" && $client->getBuffer() == "")
									break;
								
							} elseif ($input != "") 
				            {
				            	$cbuf = $client->addToBuffer($input);		            			
				            } else
				            {
				            	$cbuf = $client->getBuffer();
				            	$client->bumpReadCount();
				            }
				            
//				            if (strrpos($cbuf, "\r\n") == strlen($cbuf) - 2 ||
//				            	strrpos($cbuf, "\n\r") == strlen($cbuf) - 2 ||				            	
//				            	strrpos($cbuf, chr(TELNET_EOR)) == strlen($cbuf) - 1 ||
//								strrpos($cbuf, chr(TELNET_IAC) . chr(TELNET_GA)) == strlen($cbuf) - 2) |
//								($cbuf != "" && $client->getReadCount() >= 3))
							if ($cbuf[strlen($cbuf) - 1] == "\r" ||
				            	$cbuf[strlen($cbuf) - 1] == "\n" ||				            	
				            	$cbuf[strlen($cbuf) - 1] == chr(TELNET_EOR) ||
								$cbuf[strlen($cbuf) - 2] . $cbuf[strlen($cbuf) - 1] == chr(TELNET_IAC) . chr(TELNET_GA) || 
								$cbuf != "" && $input == "")
			            	{
			           			$client->clearBuffer();
			           			
			            		// Trigger the method for receiving data FROM the MUD //
								$this->on_wm_receive($client->getID(), $cbuf);		            	
				            }
						} 
					}
				}	
			}
			
			// If we have a policy server, process //
			if (is_object($this->policy_server))
				$this->policy_server->process();

				
			// Things get weird without a little pause... //
			usleep(10000);
		}				
	}
		
	function on_read($client = -1, $data = "")
	{				
		$cObj = $this->getClientObject($client);
		
		// Only parse the input if the client has completed the handshake (for WebSocket clients) or is a Telnet client //		
		if (!$cObj->hasHandshake())
		{				
			//echo "Received: $data\n";
			
			// Check for WebSocket handshake request //
			if (substr_count($data, "HTTP") > 0 && substr_count($data, "Origin") > 0)
			{
				if (substr_count($data, "Sec-WebSocket") > 0)
				{
                	$upgrade = (string)new WebSocketHandshake($data);
				} else {
					list($resource,$host,$origin) = $this->getHeaders($data);
				
					if ($resource == "")
					{
						$resource = WS_RESOURCE;
						$host = WS_HOST;
						$origin = WS_ORIGIN;
					}
					
					$upgrade = "HTTP/1.1 101 Web Socket Protocol Handshake\r\n" .
			           "Upgrade: WebSocket\r\n" .
			           "Connection: Upgrade\r\n" .
			           "WebSocket-Origin: $origin\r\n" .
			           "WebSocket-Location: ws://" . $host . $resource . "\r\n\r\n";
				}
				
				socket_write($cObj->getSocket(), $upgrade, strlen($upgrade));
						
				// Let on_read know to ignore the rest of the input, but to start paying attention // 
				$cObj->handshake = true;
							
				echo "Good handshake for client [$client]\n";			
			} elseif ($data == "PHUD:SET_CLIENT FLASH")
			{
				// Let on_read know to ignore the rest of the input, but to start paying attention // 
				$cObj->handshake = true;
				$cObj->setClientType(GC_FLASH);
							
				echo "Good Flash handshake for client [$client]\n";
			}		
			
		} else {
			
			// Trim the nasty from WebSocket data (a 0xFF byte appended to every message) //
			if ($cObj->getClientType() == GC_WEBSOCKET)			
				$data = substr($data, 0, strlen($data) - 1);
			
			// Check for PHudBase commands, first //
			if ($data == "PHUD:STARTLOGGING" && $cObj->connectedMUD())
			{
				$cObj->startLogging();
				
				$cObj->send(json_encode(array("sysmessage" => "<span style='color: red; font-weight: bolder;'>Log started...</span><br>")));
				
				return true;
			}
			
			if ($data == "PHUD:STOPLOGGING")
			{					
				// Write the log to a file //
				$file = 'client-log-' . microtime(true) . '.html';
				
				$fp = fopen(LOG_DIR . "$file" , 'w');
				fwrite($fp, LOG_HEADER . $cObj->getLog() . LOG_FOOTER);
				fclose($fp);
				
				// Send a link to the log //					
				$cObj->send(json_encode(
					array("sysmessage" => "<span style='color: red; font-weight: bolder;'>Your log is ready at "
									 . "<a href='" . LOG_HREF . "$file' target='_blank'>"
									 . LOG_HREF . "$file</a></span><br>")));
				
				// Terminate logging for the client //
				$cObj->stopLogging();
				
				return true;
			}
			
			// If the client hasn't connected to the MUD yet, try to now //
			// Otherwise, tunnel the data to the MUD //
			if (substr_count($data, "PHUD:CONNECT") && !is_resource($cObj->getMudConnection()))
			{
				list($host, $port) = explode(" ", ltrim($data, "PHUD:CONNECT "));

				echo "Attempting to connect client [$client] to $host on $port...\n";
				
				$cObj->send(json_encode(array("message"=>"Attempting connection to $host:$port...<br>")));
				
				$conn = socket_create(AF_INET, SOCK_STREAM, 0);
							
				if (socket_connect($conn, $host, $port))
				{
					socket_set_nonblock($conn);
										
					$cObj->setMudConnection($conn);
					$cObj->send(json_encode(array("conn_status" => "connected")));
									
					echo "Connected [$client] to $host\n";
					
					$cObj->send(json_encode(array("message"=>"Connected!<br>")));
				} else {
					$cObj->send(json_encode(array("message"=>"Could not connect to $host on port $port<br>")));
				}

				return true;
			}
			
			// Otherwise send it to the MUD //
			$conn = $cObj->getMudConnection();
			
			if (is_resource($conn))
			{
				socket_write($conn, $data . "\r\n", strlen($data . "\r\n"));	
			}
		}
	}
	
	// on_read for the MUD connection -- the MUD sent data for us to respond to //
	function on_wm_receive($client = -1, $data = "")
	{
		echo "Received:\n$data\n";
				
		$cObj = $this->getClientObject($client);
		
		if (!$cObj->isNoNegotiate())
			$this->handle_wm_negotiation($client, $data);

		if (is_object($cObj))
		{
			$data = $this->handle_ATCP($client, $data);
			
			$data = $this->handle_MXP($client, $data);
			
			// Convert < and > so we don't lose output //
			$data = str_replace("<", "&lt;", $data);
			$data = str_replace(">", "&gt;", $data);
			
			// Convert MXP_OPEN and MXP_CLOSE to preserve MXP tags //
			$data = str_replace("MXP_OPEN", "<", $data);
			$data = str_replace("MXP_CLOSE", ">", $data);
			
			// Process Telnet data //
			$data = stripTelnet($data);
			
			// Convert to UTF-8 for processing //
			$buf = utf8_encode($buf);

			// Are we logging for the client? //
			if ($cObj->isLogging())
				$cObj->addLog($data);
			
			// Kick it to the client //
			$cObj->send(json_encode(array("message" => $data)));
		}		
	}
	
	// on_connect for the MUD -- negotiate as necessary //
	function handle_wm_negotiation($client = -1, $input)
	{
		$cObj = $this->getClientObject($client);

		// Handle ATCP //
		if (substr_count($input, chr(TELNET_IAC) . chr(TELNET_WILL) . chr(TELNET_ATCP)) > 0)
		{
			echo "ATCP on for client [$client]\n";
			@socket_write($cObj->getMudConnection(),chr(TELNET_IAC) . chr(TELNET_DO) . chr(TELNET_ATCP));
						
			// Also send what we WILL do //
			//hello <client "key"> <client version> \n <supported module list>
			$this->send_ATCP($client, "hello PhudClient 1.0\nchar_vitals 1\nmap_display 1");
		}
		
		// Handle MXP //
		if (substr_count($input, chr(TELNET_IAC) . chr(TELNET_WILL) . chr(TELNET_MXP)) > 0)			
		{
			echo "MXP on for client [$client]\n";
			@socket_write($cObj->getMudConnection(),chr(TELNET_IAC) . chr(TELNET_DO) . chr(TELNET_MXP));						
		} else {
			echo "Negotiating MXP on for client [$client]\n";
			@socket_write($cObj->getMudConnection(),chr(TELNET_IAC) . chr(TELNET_WILL) . chr(TELNET_MXP));
		}
		   	
		$cObj->setNoNegotiate();
	}
	
	function on_wm_disconnect($client = -1)
	{
		$cObj = $this->getClientObject($client);
		
		$cObj->setDisconnectedMUD();
		
		$cObj->send(json_encode(array("conn_status" => "disconnected")));	
	}
	
	// Find and handle any ATCP commands, then strip them and return the data //
	function handle_ATCP($client = -1, $data)
	{
		$cObj = $this->getClientObject($client);	
		
		// "Live load" the ATCP handling //
		include "ATCP/handle_atcp.inc";
		
		return $data;
	}
	
	// Send an ATCP message //
	function send_ATCP($client = -1, $data)
	{
		$cObj = $this->getClientObject($client);	
		
		// "Live load" the ATCP handling //
		include "ATCP/send_atcp.inc";

		return $data;
	}
	
	// Handle MXP elements //
	function handle_MXP($client = -1, $data)
	{
		$cObj = $this->getClientObject($client);
		
		// "Live load" the MXP handling //
		include "MXP/handle_mxp.inc";
		
		return $data;
	}
}
?>