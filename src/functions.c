#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "mud.h"        


char *strrep(char *src, char *sch,char *rep)
{
  int lensrc,lensch,lenrep;
  char newsrc[MAX_STRING_LENGTH];
  int x,y,in_p;
  bool searching;
    lensrc = strlen(src);
    lensch = strlen(sch);
    lenrep = strlen(rep);
    searching = FALSE;
    for(x=0,in_p=0;x<lensrc;x++,in_p++)
    {
    	if(src[x] == sch[0])
    	{
            searching = TRUE;
    	    for(y=0;y<lensch;y++)
    	        if(src[x+y] != sch[y])
    	            searching = FALSE;
    	    if(searching)
    	    {
    	        for(y=0;y<lenrep;y++,in_p++)
    	            newsrc[in_p] = rep[y];
    	        x+=lensch;
                searching = FALSE;
    	    }
        }
        newsrc[in_p] = src[x];
    }
    newsrc[in_p] = '\0';
  return str_dup( newsrc );
}

char *strlinwrp(char *src, int length)
{
  int srclen,in_p,x,last_line;
  char newstr[MAX_STRING_LENGTH];
  bool looking;
    if(!length)
      length = 60;
    srclen = strlen(src);
    in_p = 0;
// STRFREE(newstr); Commented out - was just defined!
    looking = FALSE;
    for(x=0,last_line=0;x<srclen;x++,last_line++)
    {
        if(src[x] == '\r' || src[x] == '\n')
        {
            last_line = 0;
            looking = FALSE;
        }
        else if(last_line%length == 0 && x != 0)
            looking = TRUE;
        if(looking)
        {
          if(src[x] == ' ')
          {
            newstr[in_p++] = '\r';
            newstr[in_p++] = '\n';
            looking = FALSE;
            last_line = 0;
            if(src[x+1] == ' ')
              x++;
            continue;
          }
        }
        newstr[in_p++] = src[x];
    }
    newstr[in_p++] = '\r';
    newstr[in_p++] = '\n';
    newstr[in_p++] = '\0';
  return str_dup( newstr );
}

char *remand( char *src )
{
  /* This function will remove all & and ^ color codes out of a string */
  char *newarg;
    newarg = str_dup(src);
    newarg = strrep(newarg,"&x","");
    newarg = strrep(newarg,"&r","");
    newarg = strrep(newarg,"&g","");
    newarg = strrep(newarg,"&O","");
    newarg = strrep(newarg,"&b","");
    newarg = strrep(newarg,"&p","");
    newarg = strrep(newarg,"&c","");
    newarg = strrep(newarg,"&w","");
    newarg = strrep(newarg,"&z","");
    newarg = strrep(newarg,"&R","");
    newarg = strrep(newarg,"&G","");
    newarg = strrep(newarg,"&Y","");
    newarg = strrep(newarg,"&B","");
    newarg = strrep(newarg,"&P","");
    newarg = strrep(newarg,"&C","");
    newarg = strrep(newarg,"&W","");
    newarg = strrep(newarg,"^x","");
    newarg = strrep(newarg,"^z","");
    newarg = strrep(newarg,"^r","");
    newarg = strrep(newarg,"^R","");
    newarg = strrep(newarg,"^g","");
    newarg = strrep(newarg,"^G","");
    newarg = strrep(newarg,"^O","");
    newarg = strrep(newarg,"^Y","");
    newarg = strrep(newarg,"^b","");
    newarg = strrep(newarg,"^B","");
    newarg = strrep(newarg,"^p","");
    newarg = strrep(newarg,"^P","");
    newarg = strrep(newarg,"^c","");
    newarg = strrep(newarg,"^C","");
    newarg = strrep(newarg,"^w","");
    newarg = strrep(newarg,"^W","");
  return str_dup(newarg);
}

char *rembg( char *src )
{
  /* This function will remove all ^ color codes out of a string */
  char *newarg;
    newarg = str_dup(src);
    newarg = strrep(newarg,"^x","");
    newarg = strrep(newarg,"^z","");
    newarg = strrep(newarg,"^r","");
    newarg = strrep(newarg,"^R","");
    newarg = strrep(newarg,"^g","");
    newarg = strrep(newarg,"^G","");
    newarg = strrep(newarg,"^O","");
    newarg = strrep(newarg,"^Y","");
    newarg = strrep(newarg,"^b","");
    newarg = strrep(newarg,"^B","");
    newarg = strrep(newarg,"^p","");
    newarg = strrep(newarg,"^P","");
    newarg = strrep(newarg,"^c","");
    newarg = strrep(newarg,"^C","");
    newarg = strrep(newarg,"^w","");
    newarg = strrep(newarg,"^W","");
  return str_dup(newarg);
}

char *htmlcolor( char *src )
{
  char *newarg;
  /* This function will format color codes into <font color> strings */
  if(strlen(src) == 0)
  {
    bug("Htmlcolor: emptry string!");
    return "(err)";
  }

    newarg = str_dup(src);
    newarg = strrep(newarg,"<","&lt;"); 
    newarg = strrep(newarg,">","&gt;");
    newarg = strrep(newarg,"&x","</font><font color='#333333'>");
    newarg = strrep(newarg,"&r","</font><font color='#660000'>");
    newarg = strrep(newarg,"&g","</font><font color='#006600'>");
    newarg = strrep(newarg,"&O","</font><font color='#666600'>");
    newarg = strrep(newarg,"&b","</font><font color='#000066'>");
    newarg = strrep(newarg,"&p","</font><font color='#660066'>");
    newarg = strrep(newarg,"&c","</font><font color='#666699'>");
    newarg = strrep(newarg,"&w","</font><font color='#FFFFFF'>");
    newarg = strrep(newarg,"&z","</font><font color='#666666'>");
    newarg = strrep(newarg,"&R","</font><font color='#AA0000'>");
    newarg = strrep(newarg,"&G","</font><font color='#00AA00'>");
    newarg = strrep(newarg,"&Y","</font><font color='#999900'>");
    newarg = strrep(newarg,"&B","</font><font color='#0000AA'>");
    newarg = strrep(newarg,"&P","</font><font color='#AA00AA'>");
    newarg = strrep(newarg,"&C","</font><font color='#9999CC'>");
    newarg = strrep(newarg,"&W","</font><font color='#CCCCCC'>");
    newarg = strrep(newarg,"\r","");
 return str_dup(newarg);
}
 
/*char *chrmax( char *src, int length )
{
  
  int srclen,in_p,i,count;
  char newstr[MAX_STRING_LENGTH];
  bool looking;
  srclen = strlen(src);
  in_p=0; STRFREE(newstr); count=0;
  looking=FALSE;
  for(i=0,in_p=0;i<srclen;i++,in_p++)
  {
    
      if (count >= length){
        newstr[in_p] = '\0';
    	return str_dup( newstr );
      } 
    
    if (src[i] == '&'){
    	looking = TRUE;
  
    	if (src[i++] == '&')
    	  count++;
    	  i--;
    }
    if (looking){
    	  looking = FALSE;
    	    newstr[in_p] = src[i];
    	    in_p++;
    	    i++;
 	    newstr[in_p] = src[i];
    }
    else {
    	newstr[in_p] = src[i];
    	count++;

    }
  }
  if (count < length){
    for(i=0;i<length-count-1;i++,in_p++){
      newstr[in_p] = ' ';
    }
  }
  newstr[in_p] = '\0';
  return str_dup( newstr );
}
*/

char *chrmax( char *src, int length )
{
  int i,len;
  static char ret[MAX_STRING_LENGTH];
  ret[0] = '\0';
  for(len=i=0;len<length;++i)
  {
    if((src[i] != '&') || (src[i] != '^'))
      ++len;
    if((src[i] == '&') || (src[i] == '^'))
      {
      	if ((src[i] == '&') && (src[i+1] == '&'))
      	  ++len;
      	else if ((src[i] == '^') && (src[i+1] == '^'))
      	  ++len;
      	else
      	  len-=2;
      }
    ret[i] = src[i];
  }
  return ret;
}
int strlen_color (char *argument)
{
    char  *str;
    int    i, length;

    str = argument;
    if (argument == NULL)
        return 0;

    for (length=i=0; i < strlen (argument); ++i)
    {
        if ((str [i] != '&') && (str [i] != '^'))
            ++length;
        if ((str [i] == '&') || (str [i] == '^'))
          {
            if ((str[i] == '&') && (str[i+1] == '&'))
                length=2+length;
            else if ((str[i] == '^') && (str[i+1] == '^'))
                length=2+length;
            else
                --length;
          }
    }

    return length;
}

char *format_str(char *src, int len){
  int sp1, sx;
  static char add_len[MAX_STRING_LENGTH];
  add_len[0] = '\0';
  sp1 = strlen_color(src);
  if (sp1 < len){
    for (sx=14; sx >= sp1; sx--)
      strcat( add_len, " ");
    strcat( src, add_len );
    return src;
  }
  else
    return chrmax( src, len );
}

