<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

class SocketClient
{
	public $id;
	public $socket;
	public $handshake;
	public $set_handshake;
	
	function __construct($id, $socket)
	{
		$this->id = $id;
		$this->socket = $socket;
		$this->handshake = false;
	}
	
	function getID()
	{
		return $this->id;
	}
	
	function getSocket()
	{
		return $this->socket;
	}
	
	function write($buf)
	{
		if ($buf != "") // New messages to send //
	    {
			if (is_resource($this->socket)) 
			{
				socket_write($this->socket, $buf . "\r\n");	        
		    }			
	    }
	}
	
	// Alias for write_to() //
	function send($buf)
	{
		$this->write_to($buf);
	}
	
	function close()
	{
		return socket_close($this->socket);
	}
	
	function hasHandshake()
	{
		return $this->handshake == true;		
	}
}
?>