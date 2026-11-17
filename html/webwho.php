<HTML>
<BODY bgcolor="black" text="white" bgproperties="fixed">
<HEAD>
<META HTTP-EQUIV="Refresh" CONTENT="45; URL=webwho.php">
</HEAD>
<br><br>

<PRE>
<?
  $file = "WEBWHO";
  $fcontents = file($file);
  for ($i=0;$i<=sizeof($fcontents);$i++)
  {
    file_get_contents($fcontents[$i]);
  }
?>
</PRE>

</BODY>
</HTML>
