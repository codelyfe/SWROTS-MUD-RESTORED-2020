<?php
class PolicyServer extends SocketServer
{	
	function on_read($client = -1, $data = "")
	{		
		if (substr_count($data, "<policy-file-request/>") > 0)
		{
			$cObj = $this->getClientObject($client);
					
			echo "Policy file requested, sent.\n";
			
			$p = '<' . '?xml version="1.0"?' . '>
					<!DOCTYPE cross-domain-policy SYSTEM "http://www.macromedia.com/xml/dtds/cross-domain-policy.dtd">
					<cross-domain-policy>
					   <site-control permitted-cross-domain-policies="all"/>
					   <allow-access-from domain="*" to-ports="*"/>
					</cross-domain-policy>';
	
			socket_write($cObj->getSocket(), $p, strlen($p));	

			socket_close($cObj->getSocket());
			
			$this->removeClientObject($client);
		}
	}
}

?>