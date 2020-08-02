<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

	require_once "errorFunctions.inc";
	require_once "stringFunctions.inc";
	require_once "commFunctions.inc";
		
	require_once "classes/Server/Socket.class.inc";
	require_once "classes/Server/SocketClient.class.inc";
	require_once "classes/Server/SocketServer.class.inc";	
	require_once "classes/Server/WebMudClient.class.inc";
	require_once "classes/Server/WebMudServer.class.inc";
	
	require_once "classes/Server/PolicyServer.class.inc";
	
	require_once "classes/Server/WebSocketHandshake.class.inc";
	
	// Client types //
	define("GC_ANY", 0);
	define("GC_TELNET", 1);
	define("GC_WEBSOCKET", 2);
	define("GC_FLASH", 3);
	
	// Connection timeout for activity-less connections (in seconds) //
	define("CONN_TIMEOUT", 1200);
	
	// Telnet codes //	    
	define("TELNET_ECHO", 1);
	define("TELNET_ETX", 3);
	define("TELNET_EOT", 4);	
	define("TELNET_MXP", 91);
	
	define("TELNET_EOR", 239);
	define("TELNET_SE", 240);
	define("TELNET_GA", 249);	
	define("TELNET_SB", 250);
	
	define("TELNET_WILL", 251);
	define("TELNET_WONT", 252);
	define("TELNET_DO", 253);
	define("TELNET_DONT", 254);
	define("TELNET_IAC", 255);
	
	define("TELNET_ATCP", 200);	
	
	define("ATCP_START", "\xFF\xFA\xC8");
	define("ATCP_STOP", "\xFF\xF0");
	
	// Telnet color code replacements //
	$TELNET_COLORS = array(
		"[0m" => "</b></span>", 				// Reset
		"[00m" => "</b></span>", 				// Reset
		"[1m" => "<b>", 						// Bold (bright) on 
		"[3m" => "",							// Italics on
		"[4m" => "", 							// Underline on
		"[7m" => "<span class='tnc_inverse'>",	// Reverse video
		"[9m" => "",							// Strikethrough on
		"[22m" => "</b>",						// Bold off
		"[23m" => "",							// Italics off
		"[24m" => "",							// Underline off
		"[29m" => "",							// Strikethrough off
		"[30m" => "<span class='tnc_black'>",
		"[31m" => "<span class='tnc_red'>",
		"[32m" => "<span class='tnc_green'>",
		"[33m" => "<span class='tnc_yellow'>",
		"[34m" => "<span class='tnc_blue'>",
		"[35m" => "<span class='tnc_magenta'>",
		"[36m" => "<span class='tnc_cyan'>",
		"[37m" => "<span class='tnc_white'>",
		"[39m" => "<span class='tnc_default'>",
		"[40m" => "<span class='tnc_bg_black'>",
		"[41m" => "<span class='tnc_bg_red'>",
		"[42m" => "<span class='tnc_bg_green'>",
		"[43m" => "<span class='tnc_bg_yellow'>",
		"[44m" => "<span class='tnc_bg_blue'>",
		"[45m" => "<span class='tnc_bg_magenta'>",
		"[46m" => "<span class='tnc_bg_cyan'>",
		"[47m" => "<span class='tnc_bg_white'>",
		"[49m" => "<span class='tnc_bg_default'>"
	);
	
	// Directory on the filesystem to store logs generated (needs write (755) permissions) //
	define("LOG_DIR", "/var/www/phudbase/wm_server/player_logs/");
	
	// HREF for log directory //
	//define("LOG_HREF", "http://localhost/phudbase/wm_server/player_logs/");
	define("LOG_HREF", "http://phudbase.com/wm_server/player_logs/");
	
	// Standard header and footer for logs generated //
	define("LOG_HEADER", "
	<html>
	<head>
	<style>
		html, body {
			background: #000;
			color: #fff;
			margin: 10px;
			height: 100%;
			min-height: 100%;
			font-family: monospace;
			font-size: 13px;
		}
		
		p, h2, pre {
			margin: 0px; 
			padding: 5px; 
		}
		
		A:link, A:visited, A:active {
			color: #476a40;
			text-decoration: none;
		}
		
		A:hover {
			color: #fff; 
		}
		
		h1 {
			font-size: 30px;
			margin: 0;
			padding: 0;	
		}
		
		h2 {color: #327CE3;}
		
		input {
			background: #242424;
			border: 1px solid #476a40;
			color: #fff;
		}
		
		td {vertical-align: top;}
		
		.clear {clear: both; height: 5px;}

		.tnc_default {color: inherit;}
		.tnc_bg_default {background: #transparent;}
		
		.tnc_black {color: #464646;}
		.tnc_red {color: red;}
		.tnc_green {color: green;}
		.tnc_yellow {color: yellow;}
		.tnc_blue {color: blue;}
		.tnc_magenta {color: magenta;}
		.tnc_cyan {color: cyan;}
		.tnc_white {color: white;}
		
		.tnc_bg_black {background-color: #242424;}
		.tnc_bg_red {background-color: maroon;}
		.tnc_bg_green {background-color: green;}
		.tnc_bg_yellow {background-color: olive;}
		.tnc_bg_blue {background-color: navy;}
		.tnc_bg_magenta {background-color: purple;}
		.tnc_bg_cyan {background-color: teal;}
		.tnc_bg_white {background-background-color: silver;}
	</style>
	</head>
	<body>	
	");
	
	define("LOG_FOOTER", "</body></html>");
?>