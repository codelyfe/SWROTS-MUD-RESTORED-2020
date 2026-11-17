<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

	// Apply Formatting //
	function formatMessage($message, $messageType, $clientType)
	{
		$message = ucfirst($message);
		
		// Determine output format //
		if ($messageType == "notify") // Notification
		{
			$message = "<font color='#cccccc'>$message</font>";
		}
		
		if ($messageType == "sysmessage") // Directed System Message
		{
			$message = "<font color='red'>$message</font>";
		}
		
		if ($messageType == "room") // Say
		{
			$message = "<font color='#cbd3ff'>$message</font>";
		}
		
		if ($messageType == "action") // Action
		{			
			$message = "<font color='#b8b81d'>$message</font>";			
		}
		
		if ($messageType == "caction") // Player Action
		{		
			$message = "<font color='#ffffff'>$message</font>";			
		}
	
		
		return $message;
	}
	
	// Checks for embedded system calls in messages and acts/removes them, then does final prep for delivery by JSON (if WebSocket) //	
	function stripSysCalls($message, $c, $clientType)
	{	
			
		$message = str_replace("_-SYSTEM: CHAT-_", "", $message);
		
		$message = str_replace("`", "'", $message);

		$message = str_replace("\n", "", $message);
		
		
		if ($clientType == GC_WEBSOCKET)
			return json_encode(array("message"=>$message));
		else 
		{
			// It's telnet or flash, strip ALL HTML after replacing <br>'s with \n's //
			$message = str_replace("<br>", "\n", $message);
			$message = strip_tags($message);
			
			return "\r\n" . trim($message);
		}
		
	}
	
	// Wraps message sent to characters in a JS function call to allow evals //
	function ow_Write($message, $from=0)
	{
		$message = str_replace("\n", "", $message);
				
		return "window.top.ow_Write(\"$message\");";
	}
	
	// Update player's location on the map //
	function map_Update(Character $c, Room $r)
	{
		if (is_object($c->getConnection()) && $c->getConnection()->getClientType() == GC_WEBSOCKET)
		{
			$c->sendDirect(json_encode(array("oldroom" => "room{$r->getEID()}")));
			$c->sendDirect(json_encode(array("newroom" => "room{$c->getRoom()->getEID()}")));
		}
	}
	
	// Reload player's map (for the demo, all rooms) //
	function map_Refresh(Character $c)
	{
		if (is_object($c->getConnection()) && $c->getConnection()->getClientType() == GC_WEBSOCKET)
		{
			global $rooms;
			
			$data = "<table>";
			
			// Work from top left to lower right //
			for ($y = 1; $y >= -1; $y--)
			{
				$data .= "<tr>";
				for ($x = -1; $x <= 1; $x++)
				{
					$r = $rooms[$x][$y];
					
					$data .= "<td id='room{$r->getEID()}' style='background:#aaa; border: 2px solid #000; width: 25px; height: 25px;'></td>";
				}	
				$data .= "</tr>";
			}
			
			$data .= "</table>";
			
			// Use sendDirect so it doesn't get wrapped in a message for general output //
			$c->sendDirect(json_encode(array("mapdata" => $data)));
			
			map_Update($c, $c->getRoom());
		}
	}
	
	// Update the room contents area //
	function rc_Update($c)
	{
		if (is_object($c->getConnection()) && $c->getConnection()->getClientType() == GC_WEBSOCKET)
		{
			$message = $c->getRoom()->getPlayerListTable($c->getEID());
	
			$c->sendDirect(json_encode(array("rcdata" => $message)));
		}
	}
	
?>