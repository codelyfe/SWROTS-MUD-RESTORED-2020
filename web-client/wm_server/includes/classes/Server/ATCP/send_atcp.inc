<?php

	// IAC SB ATCP	255 250 200	Start sequence
	// IAC SE	255 240	Stop sequence

	$message = chr(TELNET_IAC) . chr(TELNET_SB) . chr(TELNET_ATCP) 
				. $data .
			   chr(TELNET_IAC) . chr(TELNET_SE); 

	@socket_write($cObj->getMudConnection(), $message);
	
	
?>