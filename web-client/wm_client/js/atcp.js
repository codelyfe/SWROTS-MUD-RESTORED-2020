// Process any ATCP messages //
function handle_ATCP(data)
{
	if (data.ATCP_Char_Name)
	{
				
	}
	
	if (data.ATCP_Client_Map)
	{	
			
	}
	
	if (data.ATCP_Char_Vitals)
	{
		
	}
	
	if (data.ATCP_Room_Num)
	{

	}
	
	if (data.ATCP_Room_Exits)
	{	
		m_nw.innerHTML = m_n.innerHTML = m_ne.innerHTML = m_e.innerHTML = m_se.innerHTML = m_s.innerHTML = m_sw.innerHTML 
			= m_w.innerHTML = m_in.innerHTML = m_out.innerHTML = m_up.innerHTML = m_down.innerHTML = "";
		
		for (var i in data.ATCP_Room_Exits)
		{					
			document.getElementById("m_" + data.ATCP_Room_Exits[i]).innerHTML = data.ATCP_Room_Exits[i].toUpperCase();
		}
	}
	
	if (data.ATCP_Disconnect)
	{
		if (data.ATCP_Disconnect == "true")
		{
			ow_Write("DISCONNECTED FROM MUD");
			m_conn_div.style.background = "red";	
			stopped = true;
		}
	}
}