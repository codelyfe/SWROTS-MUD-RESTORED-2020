<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/

	// Useful for testing user-supplied character names or any data you don't want to have non-alphanums
	function nameHasBadChars($name)
	{
		return !(ctype_alnum($name));
	}
		
	// Strip endline/endstring //
	function stripEnds($string)
	{
		$string = str_replace("\n", "", $string);
		$string = str_replace("\r", "", $string);
		$string = str_replace("\0", "", $string);
		
		return $string;
	}
	
	// Splits the first word off of a string. If it can't be split, returns false //
	function splitOnce($string, $sep)
	{
		$split = explode($sep, $string, 2);
		
		if (count($split) > 1)
			return $split;
		else
			return false;
	}
	
	// Replaces ' and " with html entities //
	function stripQuotes($string, $form_input=false)
	{	
		$search = array(
		    '@<script[^>]*?>.*?</script>@si',   // Strip out javascript		    
		    '@<style[^>]*?>.*?</style>@siU',    // Strip style tags properly
		    '@<![\s\S]*?--[ \t\n\r]*>@'         // Strip multi-line comments
		);
		 
		$string = preg_replace($search, '', $string);	
		
		if (!$form_input)
		{
			$string = str_replace("'", "`", $string);		
			$string = str_replace("\"", "&quot;", $string);
		} else {					
			$string = str_replace("\"", "&quot;", $string);
		}
		
		return $string;
	}
	
	function stripTelnet($string)
	{ 
	    // Replace tabs to preserve them in HTML //
	    $string = str_replace(chr(9), "     ", $string);

		// Replace color codes, etc. with defined HTML replacements //
	    global $TELNET_COLORS;
	     
	    // Split combo codes into separate codes (ex. "[0;37m" to "[0m [37m")	   
	    $string = preg_replace("/" . "\[(\d+);" . "/i", "[$1m\x1B[", $string);
	    $string = preg_replace("/" . "\[(\d+);" . "/i", "[$1m\x1B[", $string);
	    
	    foreach ($TELNET_COLORS as $key => $value)
	    {
	    	$string = str_replace(chr(27) . $key, $value, $string);
	    }    
	    
	    // Remove rogue ESC's //
	    $string = str_replace(chr(27), "", $string);
	    
		// Convert CR/LFs and such to HTML breaks //
		$string = str_replace("\r\n", "<br>", $string);
		$string = str_replace("\n\r", "<br>", $string);    	    
	    $string = str_replace("\r", "<br>", $string);	 
	    $string = str_replace("\n", "<br>", $string);
	    $string = str_replace(chr(TELNET_IAC) . chr(TELNET_GA), "<br>", $string);  // IAC GA //  
	    
	    // Strip any other nasties //
	    $string = preg_replace("/[^[:print:]|\s]/","",$string);   
   	
		return $string;  
   	
		return $string;
	}
	
	function unstripQuotes($string, $sb = false)
	{
		if ($sb)
		{
			$string = ltrim($string, "<p>");
			$string = rtrim($string, "</p>");
		}
		$string = str_replace("`", "'", $string);
		$string = str_replace("&quot;", '"', $string);
		
		return $string;
	}	
	
	// Clean up HTML entities //
	function stripHTML($message)
	{		
		$message = str_replace("<", "&lt;", $message);
		$message = str_replace(">", "&gt;", $message);
		
		return $message;
	}
		
	function ordinal_suffix($value, $sup = 0)
	{
		// Function written by Marcus L. Griswold (vujsa)
		// Can be found at http://www.handyphp.com
		// Do not remove this header!
	
	    is_numeric($value) or trigger_error("<b>\"$value\"</b> is not a number!, The value must be a number in the function <b>ordinal_suffix()</b>", E_USER_ERROR);
	    if(substr($value, -2, 2) == 11 || substr($value, -2, 2) == 12 || substr($value, -2, 2) == 13){
	        $suffix = "th";
	    }
	    else if (substr($value, -1, 1) == 1){
	        $suffix = "st";
	    }
	    else if (substr($value, -1, 1) == 2){
	        $suffix = "nd";
	    }
	    else if (substr($value, -1, 1) == 3){
	        $suffix = "rd";
	    }
	    else {
	        $suffix = "th";
	    }
	    if($sup){
	        $suffix = "<sup>" . $suffix . "</sup>";
	    }
	    return $value . $suffix;
	}
	
	function asorti($arr) {
	   $arr2 = $arr;
	   foreach($arr2 as $key => $val) {
	      $arr2[$key] = strtolower($val);
	   }
	 
	   asort($arr2);
	   foreach($arr2 as $key => $val) {
	      $arr2[$key] = $arr[$key];
	   }
	
	   return $arr2;
	} 

	function convertURLs($text) 
	{
		$text = preg_replace("/([a-zA-Z]+:\/\/[a-z0-9\_\.\-]+"."[a-z]{2,6}[a-zA-Z0-9\/\*\-\_\?\&\%\=\,\+\.]+)/"," <a href=\"$1\" target=\"_blank\">$1</a>", $text);
		$text = preg_replace("/[^a-z]+[^:\/\/](www\." . "[^\.]+[\w][\.|\/][a-zA-Z0-9\/\*\-\_\?\&\%\=\,\+\.]+)/"," <a href=\"\" target=\"\">$1</a>", $text);
		$text = preg_replace("/([\s|\,\>])([a-zA-Z][a-zA-Z0-9\_\.\-]*[a-z" . "A-Z]*\@[a-zA-Z][a-zA-Z0-9\_\.\-]*[a-zA-Z]{2,6})" . "([A-Za-z0-9\!\?\@\#\$\%\^\&\*\(\)\_\-\=\+]*)" . "([\s|\.|\,\<])/i", "$1<a href=\"mailto:$2$3\">$2</a>$4",$text);
		return $text;
	}

	
?>