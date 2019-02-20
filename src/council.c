#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
/* #include <stdlib.h> */
#include <time.h>
#include "mud.h"

JEDI_DATA * first_jedi;
JEDI_DATA * last_jedi;

SENATE2_DATA * first_senate;
SENATE2_DATA * last_senate;

static	OBJ_DATA *	rgObjNest	[MAX_NEST];

void	fread_jedi	args( ( JEDI_DATA *clan, FILE *fp ) );
bool	load_jedi_file	args( ( char *clanfile ) );
void	write_jedi_list	args( ( void ) );
void	fread_senate	args( ( SENATE2_DATA *clan, FILE *fp ) );
bool	load_senate_file	args( ( char *clanfile ) );
void	write_senate_list	args( ( void ) );

/*
 * Get pointer to clan structure from clan name.
 */
JEDI_DATA *get_jedi( char *name )
{
    JEDI_DATA *clan;
    
    for ( clan = first_jedi; clan; clan = clan->next )
       if ( !str_cmp( name, clan->name ) )
         return clan;
    return NULL;
};

SENATE2_DATA * get_senate( char *name )
{
    SENATE2_DATA *clan;
    
    for ( clan = first_senate; clan; clan = clan->next )
       if ( !str_cmp( name, clan->name ) )
         return clan;
    return NULL;
}

void do_remsenate(CHAR_DATA *ch, char *argument){
  SENATE2_DATA *clan;

  if ( argument[0] == '\0' )
  {
	send_to_char( "&wRemove which senate seat?\n\r", ch );
	return;
  }  
  if ((clan = get_senate(argument)) == NULL)
  {
  	send_to_char("No such senate.\n\r", ch);
  	return;
  }
  UNLINK( clan, first_senate, last_senate, next, prev );
  STRFREE( clan->name );
    DISPOSE( clan );
  write_senate_list();  
}

void do_remcouncil(CHAR_DATA *ch, char *argument)
{
  JEDI_DATA *clan;

  if( argument[0] == '\0' )
  {
	send_to_char( "&wNo such council.\n\r", ch );
	return;
  }  
  if ((clan = get_jedi(argument)) == NULL)
  {
  	send_to_char("No such council.\n\r", ch);
  	return;
  }
  UNLINK( clan, first_jedi, last_jedi, next, prev );
  STRFREE( clan->name );
    DISPOSE( clan );
  write_jedi_list();  
}

void write_senate_list( )
{
    SENATE2_DATA *tclan;
    FILE *fpout;
    char filename[256];

    sprintf( filename, "%s%s", SENATE_DIR, SENATE_LIST );
    fpout = fopen( filename, "w" );
    if ( !fpout )
    {
	bug( "FATAL: cannot open senate.lst for writing!\n\r", 0 );
 	return;
    }	  
    for ( tclan = first_senate; tclan; tclan = tclan->next )
	fprintf( fpout, "%s\n", tclan->filename );
    fprintf( fpout, "$\n" );
    fclose( fpout );
}

void write_jedi_list( )
{
    JEDI_DATA *tclan;
    FILE *fpout;
    char filename[256];

    sprintf( filename, "%s%s", JEDI_DIR, JEDI_LIST );
    fpout = fopen( filename, "w" );
    if ( !fpout )
    {
	bug( "FATAL: cannot open CLAN.lst for writing!\n\r", 0 );
 	return;
    }	  
    for ( tclan = first_jedi; tclan; tclan = tclan->next )
	fprintf( fpout, "%s\n", tclan->filename );
    fprintf( fpout, "$\n" );
    fclose( fpout );
}

void save_jedi( JEDI_DATA *clan )
{
    FILE *fp;
    char filename[256];
    char buf[MAX_STRING_LENGTH];

    if ( !clan )
    {
	bug( "save_clan: null clan pointer!", 0 );
	return;
    }
        
    if ( !clan->filename || clan->filename[0] == '\0' )
    {
	sprintf( buf, "save_clan: %s has no filename", clan->name );
	bug( buf, 0 );
	return;
    }
 
    sprintf( filename, "%s%s", JEDI_DIR, clan->filename );
    
    if ( ( fp = fopen( filename, "w" ) ) == NULL )
    {
    	bug( "save_clan: fopen", 0 );
    	perror( filename );
    }
    else
    {
	fprintf( fp, "#CLAN\n" );
	fprintf( fp, "Name         %s~\n",	clan->name		);
	fprintf( fp, "Filename     %s~\n",	clan->filename		);
	fprintf( fp, "Leader       %s~\n",	clan->leader		);
	fprintf( fp, "NumberOne    %s~\n",	clan->number1		);
	fprintf( fp, "NumberTwo    %s~\n",	clan->number2		);	
	fprintf( fp, "End\n\n"						);
	fprintf( fp, "#END\n"						);
    }
    fclose( fp );
    return;
}

void save_senates( SENATE2_DATA *clan )
{
    FILE *fp;
    char filename[256];
    char buf[MAX_STRING_LENGTH];

    if ( !clan )
    {
	bug( "save_senates: null senate pointer!", 0 );
	return;
    }
        
    if ( !clan->filename || clan->filename[0] == '\0' )
    {
	sprintf( buf, "save_senate: %s has no filename", clan->name );
	bug( buf, 0 );
	return;
    }
 
    sprintf( filename, "%s%s", SENATE_DIR, clan->filename );
    
    if ( ( fp = fopen( filename, "w" ) ) == NULL )
    {
    	bug( "save_clan: fopen", 0 );
    	perror( filename );
    }
    else
    {
	fprintf( fp, "#CLAN\n" );
	fprintf( fp, "Name         %s~\n",	clan->name		);
	fprintf( fp, "Filename     %s~\n",	clan->filename		);
	fprintf( fp, "Leader       %s~\n",	clan->leader		);
	fprintf( fp, "NumberOne    %s~\n",	clan->number1		);
	fprintf( fp, "NumberTwo    %s~\n",	clan->number2		);	
	fprintf( fp, "End\n\n"						);
	fprintf( fp, "#END\n"						);
    }
    fclose( fp );
    return;
}

/*
 * Read in actual clan data.
 */

#if defined(KEY)
#undef KEY
#endif

#define KEY( literal, field, value )					\
				if ( !str_cmp( word, literal ) )	\
				{					\
				    field  = value;			\
				    fMatch = TRUE;			\
				    break;				\
				}

void fread_jedi( JEDI_DATA *clan, FILE *fp )
{
    char buf[MAX_STRING_LENGTH];
    char *word;
    bool fMatch;

    for ( ; ; )
    {
	word   = feof( fp ) ? "End" : fread_word( fp );
	fMatch = FALSE;

	switch ( UPPER(word[0]) )
	{
	case '*':
	    fMatch = TRUE;
	    fread_to_eol( fp );
	    break;
        
	case 'E':
	    if ( !str_cmp( word, "End" ) )
	    {
		if (!clan->name)
		  clan->name		= STRALLOC( "" );
		if (!clan->leader)
		  clan->leader		= STRALLOC( "" );
		if (!clan->description)
		  clan->description 	= STRALLOC( "" );
		if (!clan->number1)
		  clan->number1		= STRALLOC( "" );		
		if (!clan->number2)
		  clan->number2		= STRALLOC( "" );
		if (!clan->tmpstr)
		  clan->tmpstr		= STRALLOC( "" );
		if (!clan->atwar)
		  clan->atwar		= STRALLOC( "" );		  
		return;
	    }
	    break;
	    
	case 'F':
 	    KEY( "Filename",	clan->filename,		fread_string_nohash( fp ) );
	    break;

	case 'L':
	    KEY( "Leader",	clan->leader,		fread_string( fp ) );
	    break;
 
	case 'N':
	    KEY( "Name",	clan->name,		fread_string( fp ) );
	    KEY( "NumberOne",	clan->number1,		fread_string( fp ) );
	    KEY( "NumberTwo",	clan->number2,		fread_string( fp ) );
	    break;

	}
	
	if ( !fMatch )
	{
	    sprintf( buf, "Fread_clan: no match: %s", word );
	    bug( buf, 0 );
	}
	
    }
}

void fread_senate( SENATE2_DATA *clan, FILE *fp )
{
    char buf[MAX_STRING_LENGTH];
    char *word;
    bool fMatch;

    for ( ; ; )
    {
	word   = feof( fp ) ? "End" : fread_word( fp );
	fMatch = FALSE;

	switch ( UPPER(word[0]) )
	{
	case '*':
	    fMatch = TRUE;
	    fread_to_eol( fp );
	    break;
        
	case 'E':
	    if ( !str_cmp( word, "End" ) )
	    {
		if (!clan->name)
		  clan->name		= STRALLOC( "" );
		if (!clan->leader)
		  clan->leader		= STRALLOC( "" );
		if (!clan->description)
		  clan->description 	= STRALLOC( "" );
		if (!clan->number1)
		  clan->number1		= STRALLOC( "" );		
		if (!clan->number2)
		  clan->number2		= STRALLOC( "" );
		if (!clan->tmpstr)
		  clan->tmpstr		= STRALLOC( "" );
		if (!clan->atwar)
		  clan->atwar		= STRALLOC( "" );		  
		return;
	    }
	    break;
	    
	case 'F':
	    KEY( "Filename",	clan->filename,		fread_string_nohash( fp ) );
	    break;

	case 'L':
	    KEY( "Leader",	clan->leader,		fread_string( fp ) );
	    break;
 
	case 'N':
	    KEY( "Name",	clan->name,		fread_string( fp ) );
	    KEY( "NumberOne",	clan->number1,		fread_string( fp ) );
	    KEY( "NumberTwo",	clan->number2,		fread_string( fp ) );
	    break;
	}
	
	if ( !fMatch )
	{
	    sprintf( buf, "Fread_clan: no match: %s", word );
	    bug( buf, 0 );
	}
	
    }
}

bool load_jedi_file( char *clanfile )
{
    char filename[256];
    JEDI_DATA *clan;
    FILE *fp;
    bool found;

    CREATE( clan, JEDI_DATA, 1 );
    clan->next_subclan = NULL;
    clan->prev_subclan = NULL;
    clan->last_subclan = NULL;
    clan->first_subclan = NULL;    
    clan->mainclan     = NULL;
    
    found = FALSE;
    sprintf( filename, "%s%s", JEDI_DIR, clanfile );

    if ( ( fp = fopen( filename, "r" ) ) != NULL )
    {

	found = TRUE;
	for ( ; ; )
	{
	    char letter;
	    char *word;

	    letter = fread_letter( fp );
	    if ( letter == '*' )
	    {
		fread_to_eol( fp );
		continue;
	    }

	    if ( letter != '#' )
	    {
		bug( "Load_jedi_file: # not found.", 0 );
		break;
	    }

	    word = fread_word( fp );
	    if ( !str_cmp( word, "CLAN"	) )
	    {
	    	fread_jedi( clan, fp );
	    	break;
	    }
	    else
	    if ( !str_cmp( word, "END"	) )
	        break;
	    else
	    {
		char buf[MAX_STRING_LENGTH];

		sprintf( buf, "Load_jedi_file: bad section: %s.", word );
		bug( buf, 0 );
		break;
	    }
	}
	fclose( fp );
    }

    if ( found )
    {
	ROOM_INDEX_DATA *storeroom;

	LINK( clan, first_jedi, last_jedi, next, prev );

	if ( clan->storeroom == 0
	|| (storeroom = get_room_index( clan->storeroom )) == NULL )
	{
	    log_string( "Storeroom not found" );
	    return found;
	}
	
	sprintf( filename, "%s%s.vault", JEDI_DIR, clan->filename );
	if ( ( fp = fopen( filename, "r" ) ) != NULL )
	{
	    int iNest;
	    bool found;
	    OBJ_DATA *tobj, *tobj_next;

	    log_string( "Loading clan storage room" );
	    rset_supermob(storeroom);
	    for ( iNest = 0; iNest < MAX_NEST; iNest++ )
		rgObjNest[iNest] = NULL;

	    found = TRUE;
	    for ( ; ; )
	    {
		char letter;
		char *word;

		letter = fread_letter( fp );
		if ( letter == '*' )
		{
		    fread_to_eol( fp );
		    continue;
		}

		if ( letter != '#' )
		{
		    bug( "Load_jedi_vault: # not found.", 0 );
		    bug( clan->name, 0 );
		    break;
		}

		word = fread_word( fp );
		if ( !str_cmp( word, "OBJECT" ) )	/* Objects	*/
		  fread_obj  ( supermob, fp, OS_CARRY );
		else
		if ( !str_cmp( word, "END"    ) )	/* Done		*/
		  break;
		else
		{
		    bug( "Load_jedi_vault: bad section.", 0 );
		    bug( clan->name, 0 );
		    break;
		}
	    }
	    fclose( fp );
	    for ( tobj = supermob->first_carrying; tobj; tobj = tobj_next 
)
	    {
		tobj_next = tobj->next_content;
		obj_from_char( tobj );
		obj_to_room( tobj, storeroom );
	    }
	    release_supermob();
	}
	else
	    log_string( "Cannot open clan vault" );
    }
    else
      DISPOSE( clan );

    return found;
}

bool load_senate_file( char *clanfile )
{
    char filename[256];
    SENATE2_DATA *clan;
    FILE *fp;
    bool found;

    CREATE( clan, SENATE2_DATA, 1 );
    clan->next_subclan = NULL;
    clan->prev_subclan = NULL;
    clan->last_subclan = NULL;
    clan->first_subclan = NULL;    
    clan->mainclan     = NULL;
    
    found = FALSE;
    sprintf( filename, "%s%s", SENATE_DIR, clanfile );

    if ( ( fp = fopen( filename, "r" ) ) != NULL )
    {

	found = TRUE;
	for ( ; ; )
	{
	    char letter;
	    char *word;

	    letter = fread_letter( fp );
	    if ( letter == '*' )
	    {
		fread_to_eol( fp );
		continue;
	    }

	    if ( letter != '#' )
	    {
		bug( "Load_senate_file: # not found.", 0 );
		break;
	    }

	    word = fread_word( fp );
	    if ( !str_cmp( word, "CLAN"	) )
	    {
	    	fread_senate( clan, fp );
	    	break;
	    }
	    else
	    if ( !str_cmp( word, "END"	) )
	        break;
	    else
	    {
		char buf[MAX_STRING_LENGTH];

		sprintf( buf, "Load_senate_file: bad section: %s.", word );
		bug( buf, 0 );
		break;
	    }
	}
	fclose( fp );
    }

    if ( found )
    {
	ROOM_INDEX_DATA *storeroom;

	LINK( clan, first_senate, last_senate, next, prev );

	if ( clan->storeroom == 0
	|| (storeroom = get_room_index( clan->storeroom )) == NULL )
	{
	    log_string( "Storeroom not found" );
	    return found;
	}
	
	sprintf( filename, "%s%s.vault", SENATE_DIR, clan->filename );
	if ( ( fp = fopen( filename, "r" ) ) != NULL )
	{
	    int iNest;
	    bool found;
	    OBJ_DATA *tobj, *tobj_next;

	    log_string( "Loading clan storage room" );
	    rset_supermob(storeroom);
	    for ( iNest = 0; iNest < MAX_NEST; iNest++ )
		rgObjNest[iNest] = NULL;

	    found = TRUE;
	    for ( ; ; )
	    {
		char letter;
		char *word;

		letter = fread_letter( fp );
		if ( letter == '*' )
		{
		    fread_to_eol( fp );
		    continue;
		}

		if ( letter != '#' )
		{
		    bug( "Load_senate_vault: # not found.", 0 );
		    bug( clan->name, 0 );
		    break;
		}

		word = fread_word( fp );
		if ( !str_cmp( word, "OBJECT" ) )	/* Objects	*/
		  fread_obj  ( supermob, fp, OS_CARRY );
		else
		if ( !str_cmp( word, "END"    ) )	/* Done		*/
		  break;
		else
		{
		    bug( "Load_senate_vault: bad section.", 0 );
		    bug( clan->name, 0 );
		    break;
		}
	    }
	    fclose( fp );
	    for ( tobj = supermob->first_carrying; tobj; tobj = tobj_next )
	    {
		tobj_next = tobj->next_content;
		obj_from_char( tobj );
		obj_to_room( tobj, storeroom );
	    }
	    release_supermob();
	}
	else
	    log_string( "Cannot open clan vault" );
    }
    else
      DISPOSE( clan );

    return found;
}

void load_senates( )
{
    FILE *fpList;
    char *filename;
    char clanlist[256];
    char buf[MAX_STRING_LENGTH];
    SENATE2_DATA *clan;
    SENATE2_DATA *bosclan;
    
    first_senate	= NULL;
    last_senate	= NULL;

    log_string( "Loading senates..." );

    sprintf( clanlist, "%s%s", SENATE_DIR, SENATE_LIST );
    fclose( fpReserve );
    if ( ( fpList = fopen( clanlist, "r" ) ) == NULL )
    {
	perror( clanlist );
	exit( 1 );
    }

    for ( ; ; )
    {
	filename = feof( fpList ) ? "$" : fread_word( fpList );
	log_string( filename );
	if ( filename[0] == '$' )
	  break;

	if ( !load_senate_file( filename ) )
	{
	  sprintf( buf, "Cannot load senate file: %s", filename );
	  bug( buf, 0 );
	}
    }
    fclose( fpList );
    log_string(" Done clans\n\rSorting clans...." );
    fpReserve = fopen( NULL_FILE, "r" );
    
    for ( clan=first_senate ; clan ; clan = clan->next )
    {
       if ( !clan->tmpstr || clan->tmpstr[0] == '\0' )
         continue;
         
       bosclan = get_senate( clan->tmpstr );
       if ( !bosclan ) 
         continue;
         
       LINK( clan , bosclan->first_subclan , bosclan->last_subclan , next_subclan, prev_subclan );
       clan->mainclan = bosclan;
    }
    
    log_string(" Done sorting" );
    return;
}

void load_jedis( )
{
    FILE *fpList;
    char *filename;
    char clanlist[256];
    char buf[MAX_STRING_LENGTH];
    JEDI_DATA *clan;
    JEDI_DATA *bosclan;
    
    first_jedi	= NULL;
    last_clan	= NULL;

    log_string( "Loading clans..." );

    sprintf( clanlist, "%s%s", JEDI_DIR, JEDI_LIST );
    fclose( fpReserve );
    if ( ( fpList = fopen( clanlist, "r" ) ) == NULL )
    {
	perror( clanlist );
	exit( 1 );
    }

    for ( ; ; )
    {
	filename = feof( fpList ) ? "$" : fread_word( fpList );
	log_string( filename );
	if ( filename[0] == '$' )
	  break;

	if ( !load_jedi_file( filename ) )
	{
	  sprintf( buf, "Cannot load clan file: %s", filename );
	  bug( buf, 0 );
	}
    }
    fclose( fpList );
    log_string(" Done clans\n\rSorting clans...." );
    fpReserve = fopen( NULL_FILE, "r" );
    
    for ( clan=first_jedi ; clan ; clan = clan->next )
    {
       if ( !clan->tmpstr || clan->tmpstr[0] == '\0' )
         continue;
         
       bosclan = get_jedi ( clan->tmpstr );
       if ( !bosclan ) 
         continue;
         
       LINK( clan , bosclan->first_subclan , bosclan->last_subclan , next_subclan, prev_subclan );
       clan->mainclan = bosclan;
    }
    
    log_string(" Done sorting" );
    return;
}

void do_setjedi( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    JEDI_DATA *clan;

    if ( IS_NPC( ch ) )
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Usage: setjedi <position> <field> <leader|investigator> <player>\n\r", ch );
	send_to_char( "\n\rField being one of:\n\r", ch );
	send_to_char( " leader investigator\n\r", ch ); 
	if ( get_trust( ch ) >= LEVEL_SUB_IMPLEM )
	{
	  send_to_char( " name filename\n\r", ch );
	}
	return;
    }

    clan = get_jedi( arg1 );
    if ( !clan )
    {
	send_to_char( "No such clan.\n\r", ch );
	return;
    }

    if ( !strcmp( arg2, "leader" ) )
    {
	STRFREE( clan->leader );
	clan->leader = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_jedi( clan );
	return;
    }
    if ( !strcmp( arg2, "investigator" ) )
    {
	STRFREE( clan->number1 );
	clan->number1 = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_jedi( clan );
	return;
    }
    if ( get_trust( ch ) < LEVEL_SUB_IMPLEM )
    {
	do_setclan( ch, "" );
	return;
    }
    if ( !strcmp( arg2, "name" ) )
    {
	STRFREE( clan->name );
	clan->name = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_jedi( clan );
	return;
    }
    if ( !strcmp( arg2, "filename" ) )
    {
	DISPOSE( clan->filename );
	clan->filename = str_dup( argument );
	send_to_char( "Done.\n\r", ch );
	save_jedi( clan );
	write_jedi_list( );
	return;
    }
    do_setjedi( ch, "" );
    return;
}

void do_setsenate( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    SENATE2_DATA *clan;

    if ( IS_NPC( ch ) )
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Usage: setsenate <senate> <field> <senator|assnt1|assnt2> <player>\n\r", ch );
	send_to_char( "\n\rField being one of:\n\r", ch );
	send_to_char( " senator assnt1 assnt2\n\r", ch ); 
	if ( get_trust( ch ) >= LEVEL_SUB_IMPLEM )
	{
	  send_to_char( " name filename\n\r", ch );
	}
	return;
    }

    clan = get_senate( arg1 );
    if ( !clan )
    {
	send_to_char( "No such clan.\n\r", ch );
	return;
    }
    if ( !strcmp( arg2, "senator" ) )
    {
	STRFREE( clan->leader );
	clan->leader = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_senates( clan );
	return;
    }
    if ( !strcmp( arg2, "assnt1" ) )
    {
	STRFREE( clan->number1 );
	clan->number1 = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_senates( clan );
	return;
    }
    if ( !strcmp( arg2, "assnt2" ) )
    {
	STRFREE( clan->number2 );
	clan->number2 = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_senates( clan );
	return;
    }
    if ( get_trust( ch ) < LEVEL_SUB_IMPLEM )
    {
	do_setclan( ch, "" );
	return;
    }
    if ( !strcmp( arg2, "name" ) )
    {
	STRFREE( clan->name );
	clan->name = STRALLOC( argument );
	send_to_char( "Done.\n\r", ch );
	save_senates( clan );
	return;
    }
    if ( !strcmp( arg2, "filename" ) )
    {
	DISPOSE( clan->filename );
	clan->filename = str_dup( argument );
	send_to_char( "Done.\n\r", ch );
	save_senates( clan );
	write_senate_list( );
	return;
    }
    do_setjedi( ch, "" );
    return;
}

void do_showjedi( CHAR_DATA *ch, char *argument )
{   
    JEDI_DATA *clan;

    if ( IS_NPC( ch ) )
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if ( argument[0] == '\0' )
    {
	send_to_char( "Usage: showjedi <jedi seat>\n\r", ch );
	return;
    }

    clan = get_jedi( argument );
    if ( !clan )
    {
	send_to_char( "No such position.\n\r", ch );
	return;
    }

    ch_printf( ch, "%s\n\rFilename: %s\n\r",
    			clan->name,
    			clan->filename);
    ch_printf( ch, "Leader: %s\n\r", clan->leader );
    ch_printf( ch, "Investigator: %s\n\r", clan->number1 );
    return;
}

void do_showsenate( CHAR_DATA *ch, char *argument )
{   
    SENATE2_DATA *clan;

    if ( IS_NPC( ch ) )
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if ( argument[0] == '\0' )
    {
	send_to_char( "Usage: showsenate <senate>\n\r", ch );
	return;
    }

    clan = get_senate( argument );
    if ( !clan )
    {
	send_to_char( "No such senate.\n\r", ch );
	return;
    }

    ch_printf( ch, "%s\n\rFilename: %s\n\r",
    			clan->name,
    			clan->filename);
    ch_printf( ch, "Leader: %s\n\r",
    			clan->leader );
    ch_printf( ch, "Assistant1: %s\n\rAssistant2: %s\n\r",
    			clan->number1,
    			clan->number2 );
    return;
}

void do_makecouncil( CHAR_DATA *ch, char *argument )
{
    char filename[256];
    JEDI_DATA *clan;
    bool found;

    if ( !argument || argument[0] == '\0' )
    {
	send_to_char( "&gUsage: &wmakecouncil &g<&wcouncil posoition&g>&w\n\r", ch );
	return;
    }

    found = FALSE;
    sprintf( filename, "%s%s", JEDI_DIR, strlower(argument) );

    CREATE( clan, JEDI_DATA, 1 );
    LINK( clan, first_jedi, last_jedi, next, prev );
    clan->next_subclan = NULL;
    clan->prev_subclan = NULL;
    clan->last_subclan = NULL;
    clan->first_subclan = NULL;    
    clan->mainclan     = NULL;
    clan->name		= STRALLOC( argument );
    clan->leader	= STRALLOC( "" );
    clan->number1	= STRALLOC( "" );
    clan->number2	= STRALLOC( "" );
    send_to_char("Done.\n\r", ch);
    return;
}

void do_makesenate( CHAR_DATA *ch, char *argument )
{
    char filename[256];
    SENATE2_DATA *clan;
    bool found;

    if ( !argument || argument[0] == '\0' )
    {
	send_to_char( "&gUsage: &wmakesenate &g<&wsenate position&g>&w\n\r", ch );
	return;
    }

    found = FALSE;
    sprintf( filename, "%s%s", SENATE_DIR, strlower(argument) );

    CREATE( clan, SENATE2_DATA, 1 );
    LINK( clan, first_senate, last_senate, next, prev );
    clan->next_subclan = NULL;
    clan->prev_subclan = NULL;
    clan->last_subclan = NULL;
    clan->first_subclan = NULL;    
    clan->mainclan     = NULL;
    clan->name		= STRALLOC( argument );
    clan->leader	= STRALLOC( "" );
    clan->number1	= STRALLOC( "" );
    clan->number2	= STRALLOC( "" );
    send_to_char("Done.\n\r", ch);
    return;
}

void do_jedicouncil( CHAR_DATA *ch, char *argument )
{
    JEDI_DATA *clan;
    int count = 0;

	ch_printf(ch, "\n\r" );     
	ch_printf(ch, " &pCouncil Seat            Jedi Master &w\n\r" );  
        ch_printf(ch, " &w----------------------------------- &w\n\r" );
    for ( clan = first_jedi; clan; clan = clan->next )
    {    
        ch_printf( ch, " &W&G%-23.25s &c%-10s", 
                   clan->name, clan->leader );
        ch_printf( ch, "\n\r" );
        count++;
    }
 
    if ( !count )
    {
	set_char_color( AT_BLUE, ch);
        send_to_char( "There is currently no Jedi Countil.\n\r", ch );
    }
  return;
}
void do_senate( CHAR_DATA *ch, char *argument )
{
    SENATE2_DATA *clan;
    int count = 0;

    ch_printf(ch, "\n\r" );
    ch_printf(ch, " &pPlanet Representative       Senator        Assistant1     Assistant2 &w\n\r" );  
    ch_printf(ch, " &w--------------------------------------------------------------------&w\n\r" );
 for ( clan = first_senate; clan; clan = clan->next )
  {
    ch_printf( ch, " &W&G%-27.25s &c%-14s &c%-14s &c%-10s", 
                   clan->name, clan->leader, clan->number1, clan->number2 );
	
    ch_printf( ch, "\n\r" );
    count++;
  }

    if ( !count )
    {
	set_char_color( AT_BLOOD, ch);
        send_to_char( "There is currently no Senate.\n\r", ch );
    }
   return;
}

int const senate_array[] = {
VNUM_FALLEEN, VNUM_DRALL, VNUM_CHANCELLOR, VNUM_YABLARI, VNUM_ALDERAAN,
VNUM_CEREA, VNUM_CHAMPALA, VNUM_URKUPP, VNUM_DORIN, VNUM_ALPHERIDIES,
VNUM_RODIA, VNUM_MON_CALAMARI, VNUM_MUUNILINST, VNUM_SKYE, VNUM_SULLUST,
VNUM_UMBARA, VNUM_KASHYYYK, VNUM_WOOSTRI, VNUM_CORELLIA, VNUM_NABOO,
VNUM_UBA_111, VNUM_ROCHE, VNUM_IKTOTCH
};

char * const senate_name[] = {
"Falleen", "Drall", "Supreme Chancellor", "Yablari", "Alderaan", "Cerea",
"Champala", "Urkupp", "Dorin", "Alpheridies", "Rodia", "Mon Calamari",
"Muunilinst", "Skye", "Sullust", "Umbara", "Kashyyyk", "Woostri", "Corellia",
"Naboo", "Uba 111", "Roche Asteroid", "Iktotch"
};

void do_checksenate( CHAR_DATA *ch, char *argument )
{
  ROOM_INDEX_DATA *room;
  CHAR_DATA *gch;
  int vnum, count;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && !IS_SET(ch->in_room->room_flags2, ROOM_SENATE) )
   {
	send_to_char("&wYou must be in the &bSenate Chamber&w to use this command.&w\n\r", ch );
	return;
   }
  send_to_char( "&gSenate Seat &w\n\r", ch );
  for( vnum = 0; vnum < 23; vnum++ )
   {
	room = get_room_index( senate_array[vnum] );
	if( !room )
	  continue;
	count = 0;
	for( gch = room->first_person; gch; gch = gch->next_in_room )
	 count++;
	if( count == 0 )
	 ch_printf( ch, "&w%-25s      &rNot Present&w\n\r", senate_name[vnum] );
	else
	 ch_printf( ch, "&w%-25s      &gIn Attendence&w\n\r", senate_name[vnum] );
   }
  return;
}
	
