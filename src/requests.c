#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mud.h"

int REQ;

void init_request_pipe( )
{
#ifdef REQUESTS
  if ( (REQ = open( REQUEST_PIPE, O_RDONLY | O_NONBLOCK )) == -1 )
  {
    bug ( "REQUEST pipe not found", 0 );
    exit(1);
  }
#endif
}

void check_requests( )
{
#ifdef REQUESTS
  char buf[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];
  int  c;
  if ( read( REQ, buf, sizeof( buf ) ) != -1 )
  {
     close( REQ );
     init_request_pipe();
     for ( c = 0; c < MAX_STRING_LENGTH; c++ )
	if ( buf[c] == '\n' || buf[c] == '\r' )
	{
	   buf[c] = '\0';
	   break;
	}
     sprintf( buf2, "REQUEST: %s", buf );
     log_string( buf2 );
     if ( strcmp( buf, "who" ) == 0 )
	do_who( NULL, "" );
     else
     if ( strcmp( buf, "webwho" ) == 0 )
	do_who( NULL, "www" );
  }
#endif
}
