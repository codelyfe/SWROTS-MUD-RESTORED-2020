<?php 
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<script>document.domain = document.domain</script>
	<title>PHudBase-WebMud Client</title>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>	
	
	<link type="text/css" media="screen" rel="stylesheet" href="css/colorbox.css"/>
	<!--[if lt IE 7]>
	<link type="text/css" media="screen" rel="stylesheet" href="css/colorbox-ie.css" title="example"/>
	<![endif]-->	
	<link rel="stylesheet" type="text/css" href="css/styles.css"/>	
	<link rel="stylesheet" type="text/css" href="css/telnet.css"/>
			
	<script type="text/javascript" src="js/jquery.pack.js"></script>
	<script type="text/javascript" src="js/jquery.colorbox-min.js"></script>
	<script type="text/javascript" src="js/jquery.tools.min.js"></script>
		
	<script type="text/javascript" src="js/swfobject.js"></script>
	<script type="text/javascript" src="js/FABridge.js"></script>
	<script type="text/javascript" src="js/web_socket.js"></script>
		
	<script type="text/javascript" src="js/client.js"></script>	
	<script type="text/javascript" src="js/atcp.js"></script>	
	
	<script type="text/javascript">
		$(document).ready(function() {
			$("#about").colorbox({width: "600px", inline:true, href:"#m_about"});
			$("#help").colorbox({width: "600px", inline:true, href:"#m_help"});

			$("#interface").height($(window).height() - 20);

			$("#output, #scroller, #right").height($("#interface").height() - 100);
        	
			$(window).resize(function() {
				$("#interface").height($(window).height() - 20);

				$("#output, #scroller, #right").height($("#interface").height() - 100);
			});
			
		});
	</script>
</head>
<body>	
	<div id="interface">
        <div id="c_header">
        	<div id="header">
            	<h1>PHudBase-WebMud Client Demo</h1>
            </div>
		</div>           
		<div id="c_wrap"> 
            <div id="c_output">            	
            	<div id="output">            		
<strong>Welcome to the PHudBase-WebMud Client Demo!</strong><br><br>
Enter your favorite MUDs Server and Port and we'll get you hooked up.<br><br>
Let me know at jfitzdela (@) gmail.com if something doesn't work like you'd expect.<br><br>
Happy MUDding!<br><br>		
<div id='login_area' style='width: 400px; background: #222; border: 1px solid #777; margin: 5px; padding: 5px;'><form onsubmit='if (sendDirect("PHUD:CONNECT " + document.getElementById("mhost").value + " " + document.getElementById("mport").value)) {postLogin();} return false;'>
Host: <input type='text' id='mhost' size='15' value=''> Port: <input type='text' id='mport' size='5' value=''> <input type='submit' value='Connect'>
</form>
</div>
            	</div>
            </div>
            <div id="c_right">
            	<div id="movement">
					<table>
					<tr>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='nw'; send();">NW</td>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='n'; send();">N</td>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='ne'; send();">NE</td>
					</tr>
					<tr>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='w'; send();">W</td>
						<td style='text-align: center; vertical-align: middle; background: transparent; cursor: default;'></td>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='e'; send();">E</td>
					</tr>
					<tr>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='sw'; send();">SW</td>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='s'; send();">S</td>
						<td style='text-align: center; vertical-align: middle;' onclick="document.forms[0].data.value='se'; send();">SE</td>
					</tr>
					</table>
				</div>
				
				<div class="clear"></div>
				
				<h3>PHudBase Connection</h3>
				<div id="connection_ws"></div>
				
				<h3>MUD Connection</h3>
				<div id="connection_mud"></div>			
				
				<div class="clear"></div>
				<div class="clear"></div>
				<div class="clear"></div>
				
				<div id="autoscroll">Auto-scrolling Paused</div>	
            </div>
            
            <div class="clear"></div>
            
            <div id="c_footer">
            	<form id="data_form" style="display: none; text-align: center;" onsubmit="send(); return false;">
            		<input id="user_input" type="text" value="">            		
            	</input>
            </div>
		</div>
	</div>
        
	<div style="display: none;">
		<div id='m_about' style='padding: 5px; background: #000;'>
			<h2>About PHudBase-WebMud</h2>
			<p>
				PHudBase is a PHP-based, plugin-free socket-serving powerhouse.
			</p>
			<p>
				PHudBase-WebMud is a server (to be installed alongside an existing MUD) with a packaged 
				client to enable HTML 5 WebSocket access to your MUD without touching your codebase.			
			</p>
			<p>
				This means that your users can connect and play directly from your website without the 
				need for a Flash or Java applet, and because it's open-source, you can modify the client 
				and/or the server to your needs.
			</p>
			<p>
				The server sends data back to the client via JSON (ex. {"message":"John kicks some ass."}) and does 
				the conversion from Telnet for you, to include converting definable colors.
			</p>
			<p>
				You can also define <strong>any kind of custom message</strong>  
				you want to, from sending map data to separating chat from the actions and beyond.  This is the 
				<strong>only</strong> modification you would need to make to your code -- adding a way to recognize 
				PHudBase-WebMud users (by client-set option or automatic message from PHudBase) -- and it isn't 
				required to give your clients a browser-based gaming experience.
			</p>
			<p>
				Further discussion on the how's and why's of PHudBase-WebMud should be taken to the 
				<a href="http://groups.google.com/group/phudbase-developers" target="_blank">Google Group</a>.
			</p>
		</div>		
	</div>
</body>
</html>