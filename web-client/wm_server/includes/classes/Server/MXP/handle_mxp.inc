<?php

	/*	
	 * [4z<VERSION>
	 * [4z<SUPPORT>
	 * [4z<!ELEMENT RNum ATT="id" FLAG="RoomNum" EMPTY>
	 * [4z<!ELEMENT RName FLAG="RoomName">
	 * [4z<!ELEMENT RDesc FLAG="RoomDesc">
	 * [4z<!ELEMENT RExits FLAG="RoomExit">
	 * [4z<!ELEMENT Prompt FLAG="Prompt">	 
	*/

	// ++++++++ Capture and handle the "send" tag ++++++++ //
	$data = preg_replace("/(" . chr(27) . "\[\dz)" . "<SEND HREF=\"([A-Za-z0-9\s]+)\">/is",
						 "MXP_OPENa style=\"color: inherit;\" href=\"javascript:void(0);\" onclick=\"sendDirect('$2');\"MXP_CLOSE",
						 //"MXP_OPENa style=\"color: inherit;\" href=\"javascript:sendDirect('$2');\"MXP_CLOSE",
						 $data);	
						 
	$data = preg_replace("/(" . chr(27) . "\[\dz)" . "<\/SEND>/is", "MXP_OPEN/aMXP_CLOSE", $data);
	// +++++++++++++++++++++++++++++++++++++++++++++++++++ //
	
	// ++++++++ Capture and handle the "color" tag ++++++++ //	
	$data = preg_replace("/(" . chr(27) . "\[\dz)" . "<COLOR (\#*[A-Za-z0-9\s]+)>/is",						 
						 "MXP_OPENspan style=\"color: $2;\"MXP_CLOSE",
						 $data);	
						 
	$data = preg_replace("/(" . chr(27) . "\[\dz)" . "<\/COLOR>/is", "MXP_OPEN/spanMXP_CLOSE", $data);
	// +++++++++++++++++++++++++++++++++++++++++++++++++++ //
	
	// Clear ALL MXP tags //
	$data = preg_replace("/" . chr(27) . "\[\dz<[[:print:]]+>/is", "",$data);
	
?>