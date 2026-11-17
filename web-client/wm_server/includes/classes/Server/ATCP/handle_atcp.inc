<?php 
	
		// Match ALL ATCP calls and handle if we have any //
		if (preg_match_all("/" . ATCP_START . "([[:print:]|\n|\r\n|\r]+)" . ATCP_STOP . "/is",$data,$results))
		{
			foreach ($results as $key => $result)
			{
				foreach ($result as $rkey => $match)
				{
					if ($key == 0)
					{
						// Clear the ATCP out of our data //
						$data = str_replace($match, "", $data);
					} else {	
						//echo "Matched: $match\n";	
												
						// Handle Client.Goodbye //
						if (substr_count($mact, "Client.Goodbye"))
							$cObj->send(json_encode(array("ATCP_Disconnect" => "true")));					
						
						// Handle Room.Exits //
						if (substr_count($match,"Room.Exits") > 0)
						{
							$exit_string = ltrim($match, "Room.Exits ");
							
							// Room.Exits ne,se,sw,w,nw,u,i //
							$exits = explode(",", utf8_encode($exit_string));
									
							$cObj->send(json_encode(array("ATCP_Room_Exits" => $exits)));
						}
						
						// Handle Char.Vitals //
						if (substr_count($match,"Char.Vitals") > 0)
						{
							// H:2668/2668 M:3244/3244 E:12240/12240 W:15120/15120 NL:%d XP:%d XPD:%d			
							$vitals = explode(" ", ltrim($match, "Char.Vitals\n"));
				
							$h_string = $vitals[0];
							$m_string = $vitals[1];
							$e_string = $vitals[2];
							$w_string = $vitals[3];			
							$nl_string = $vitals[4];
							
							// For ToP only //
							$xp_string = $vitals[5];
							$xpd_string = $vitals[6];
							
							$h_raw = explode("/", ltrim($h_string, "H:"));
							$h_pct = ($h_raw[0]/$h_raw[1])*100;
							
							$m_raw = explode("/", ltrim($m_string, "M:"));
							$m_pct = ($m_raw[0]/$m_raw[1])*100;
							
							$e_raw = explode("/", ltrim($e_string, "E:"));
							$e_pct = ($e_raw[0]/$e_raw[1])*100;
							
							$w_raw = explode("/", ltrim($w_string, "W:"));
							$w_pct = ($w_raw[0]/$w_raw[1])*100;
							
							$nl_raw = explode("/", ltrim($nl_string, "NL:"));
							$nl_pct = floor(($nl_raw[0]/$nl_raw[1])*100);
							
							$char_vitals = array(array("H: $h_raw[0]/$h_raw[1]", "$h_pct%"),
												 array("M: $m_raw[0]/$m_raw[1]", "$m_pct%"),
												 array("E: $e_raw[0]/$e_raw[1]", "$e_pct%"),
												 array("W: $w_raw[0]/$w_raw[1]", "$w_pct%"),
												 array("NL: $nl_pct%", "$nl_pct%")
												);
							
							$cObj->send(json_encode(array("ATCP_Char_Vitals" => $char_vitals)));
						}
						
						// Handle Client.Map //
						if (substr_count($match,"Client.Map") > 0)
						{							
							$url = ltrim($match, "Client.Map ");			
				
							preg_match("/map=(\d+)\&/i",$url,$match);	
							$map = $match[1];
							
							preg_match("/building=(\d+)\&/i",$url,$match);	
							$bldg = $match[1];
														
							$loc = substr($url, strrpos($url, "level=") + 6, strlen($url));
								
							$coords = explode(" ", $loc);
							
							$z = $coords[0]*40;
							$x = 18 + ($coords[1]*40); 
							$y = 18 + ($coords[2]*40);
							
							$xs = 70-$x;
							$ys = 60-$y;
							
							$map = "MAP:$map" . "BLDG:$bldg" . "Z:$z";
							
							//echo "URL: $url\nMap: $map\nX:$x XS:$xs Y:$y YS: $ys\n";
							
							if ($map == $cObj->getLastMap())
							{					
								$exec = "document.getElementById('map_inner').style.backgroundPosition ='$xs" . "px $ys" . "px';";	
							} else {
								$cObj->setLastMap($map);
								
								$url = str_replace(" ", "%20", $url);
								
								$exec = "document.getElementById('map_inner').style.backgroundImage = 'url(http://$url)';"
									  . "document.getElementById('map_inner').style.backgroundPosition ='$xs" . "px $ys" . "px';";			  
							}		
				
							$cObj->send(json_encode(array("ATCP_Client_Map" => $exec)));		
						}			
						
					}
				}
			}
		}
?>