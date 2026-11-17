<?php
	/*******************************************************************************************************************
	 * 
	 * This work is licensed under the Creative Commons Attribution 3.0 United States License. 
	 * To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ or 
	 * send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
	 * 
	 *******************************************************************************************************************/
	
	// Will catch non-fatal errors, dump the error trace, and prevent process death //
	function error_handler_exception($errno, $errstr, $errfile, $errline ) 
	{
	   throw new ErrorException($errstr, 0, $errno, $errfile, $errline);	    
	}
		
	set_error_handler('error_handler_exception', E_ERROR | E_WARN | E_USER_ERROR | E_RECOVERABLE_ERROR);
?>