<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

class Socket
{
	private $socket;
	private $address;
	private $port;
	private $blocking;
	
	function __construct($address = "localhost", $port=12345, $blocking=true)
	{
		$this->address = $address;
		$this->port = $port;
		$this->blocking = $blocking;
	}
	
	function open()
	{
		// Create a TCP Stream socket
		$this->socket = socket_create(AF_INET, SOCK_STREAM, 0);
		
		socket_connect($this->socket, $this->address, $this->port);

		if (!$blocking)
			socket_set_nonblock($this->socket);
			
		sleep(5);
	}
	
	function close()
	{
		
	}
	
	function getSocket()
	{
		return $this->socket;
	}
	
	function getAddress()
	{
		return $this->address;
	}
	
	function getPort()
	{
		return $this->port;
	}
	
	function getBlocking()
	{
		return $this->blocking;
	}
	
	function write($buf)
	{
		socket_write($this->socket, $buf, strlen($buf));
	}
}
?>