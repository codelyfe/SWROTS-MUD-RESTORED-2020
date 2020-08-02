#!/php -q
<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

/*

	Run from command line:
	> php -q server.php

*/

	require_once "includes/global.inc";
	
	/*
	 * Standard host and port settings
	 * Keep in mind that on a live host, you'll want to bind to the outbound IP or host name, not localhost or 127.0.0.1, etc.
	 */	
	define("HOST", "127.0.0.1");	
	define("PORT", "12346");	
	define("PORT_POLICY", "843"); // Leave this be: may require running ./server.php as root //
	
	/*
	 * The following defines are for the WebSocket Handshake, and should be set according to your server.
	 * If you're testing locally (based on the HOST and PORT above), yours should look like the values below.
	 * 
	 * If you're deploying the application on a live server, the values would like more like:
	 * 	RESOURCE: /wm_server/server.php (as in example.com/wm_server/server.php)
	 * 	HOST: example.com:12346
	 * 	ORIGIN: example.com
	 */
	
	define("WS_RESOURCE", "/wm_server/server.php");
	define("WS_HOST", "127.0.0.1:12346");
	define("WS_ORIGIN", "http://127.0.0.1");
		
	// Establish the WebMud server //	
	$server = new WebMudServer(HOST, PORT, GC_WEBSOCKET, 512);	
		
	$server->create();
	$server->set_client_class("WebMudClient");
			
	// Process reads/writes over the game server //
	$server->process();
	
	
?>
