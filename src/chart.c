#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include "mud.h"

#define CHART_DIR   "../space/charts/"
#define GUIDE_DIR   "../space/guides/"
#define CHART_BASE  900000
#define CHART_MAX   8000

typedef struct chart_data CHART_DATA;

struct chart_data
{
    int seed;
    char planet[64];
    char system[64];
    int biome;
    int vnum;
    int x, y, z;
    ROOM_INDEX_DATA *landing;
    SPACE_DATA *starsystem;
    CHART_DATA *next;
};

static CHART_DATA *first_chart;
extern void ship_from_starsystem( SHIP_DATA *ship, SPACE_DATA *starsystem );
extern MOB_INDEX_DATA *mob_index_hash[MAX_KEY_HASH];

static const char *syl1[] = { "Kor", "Vel", "Ash", "Tor", "Nim", "Bel", "Sar", "Quin", "Dra", "Lom", "Esh", "Var" };
static const char *syl2[] = { "aan", "oth", "esi", "ara", "un", "ion", "ek", "oris", "ath", "el", "une", "ax" };
static const char *biomes[] = { "salt flats", "fungal forest", "glass desert", "storm coast", "crystal hills", "ash canyons", "moss caverns", "red grassland" };
static int biome_sect[] = { SECT_DESERT, SECT_FOREST, SECT_DESERT, SECT_WATER_SWIM, SECT_HILLS, SECT_MOUNTAIN, SECT_UNDERGROUND, SECT_FIELD };

static int lcg( int *s )
{
    *s = (*s * 1103515245 + 12345) & 0x7fffffff;
    return *s;
}

static void chart_name( int seed, char *planet, char *system )
{
    int s = seed;
    int a = lcg( &s ) % 12;
    int b = lcg( &s ) % 12;

    sprintf( planet, "%s%s", syl1[a], syl2[b] );
    sprintf( system, "%s Reach", syl1[a] );
}

static CHART_DATA *chart_by_seed( int seed )
{
    CHART_DATA *c;
    for ( c = first_chart; c; c = c->next )
	if ( c->seed == seed )
	    return c;
    return NULL;
}

static CHART_DATA *chart_by_planet( const char *name )
{
    CHART_DATA *c;
    for ( c = first_chart; c; c = c->next )
	if ( !str_cmp( c->planet, name ) )
	    return c;
    return NULL;
}

static CHART_DATA *chart_by_system( SPACE_DATA *sys )
{
    CHART_DATA *c;
    for ( c = first_chart; c; c = c->next )
	if ( c->starsystem == sys )
	    return c;
    return NULL;
}

static void chart_save( CHART_DATA *c )
{
    FILE *fp;
    char path[256];

    sprintf( path, "%s%d.chart", CHART_DIR, c->seed );
    if ( ( fp = fopen( path, "w" ) ) == NULL )
	return;
    fprintf( fp, "Seed %d\n", c->seed );
    fprintf( fp, "Planet %s~\n", c->planet );
    fprintf( fp, "System %s~\n", c->system );
    fprintf( fp, "Biome %d\n", c->biome );
    fprintf( fp, "Vnum %d\n", c->vnum );
    fprintf( fp, "X %d\nY %d\nZ %d\n", c->x, c->y, c->z );
    fclose( fp );
}

static void chart_mobs( ROOM_INDEX_DATA *rooms[], int nrooms, int seed )
{
    MOB_INDEX_DATA *picks[40];
    int count = 0, hash, i, n, s;

    for ( hash = 0; hash < MAX_KEY_HASH && count < 40; hash++ )
    {
	MOB_INDEX_DATA *mob;
	for ( mob = mob_index_hash[hash]; mob && count < 40; mob = mob->next )
	    if ( mob->level >= 1 && mob->level <= 12 )
		picks[count++] = mob;
    }
    if ( count < 1 )
	return;
    s = seed;
    n = 2 + ( lcg( &s ) % 3 );
    for ( i = 0; i < n; i++ )
    {
	MOB_INDEX_DATA *idx = picks[lcg( &s ) % count];
	CHAR_DATA *mob = create_mobile( idx );
	char_to_room( mob, rooms[lcg( &s ) % nrooms] );
    }
}

static void chart_build( CHART_DATA *c )
{
    ROOM_INDEX_DATA *rooms[9];
    int row, col, i;
    char buf[MAX_STRING_LENGTH];
    SPACE_DATA *sys;
    PLANET_DATA *planet;

    for ( i = 0; i < 9; i++ )
    {
	rooms[i] = make_room( c->vnum + i );
	rooms[i]->sector_type = biome_sect[c->biome];
	REMOVE_BIT( rooms[i]->room_flags, ROOM_PROTOTYPE );
	sprintf( buf, "%s, %s", c->planet, biomes[c->biome] );
	STRFREE( rooms[i]->name );
	rooms[i]->name = STRALLOC( buf );
	sprintf( buf, "You stand on %s, a world of %s in the %s. The horizon is empty of any charted starport.\n\r",
	    c->planet, biomes[c->biome], c->system );
	STRFREE( rooms[i]->description );
	rooms[i]->description = STRALLOC( buf );
    }
    for ( row = 0; row < 3; row++ )
	for ( col = 0; col < 3; col++ )
	{
	    ROOM_INDEX_DATA *here = rooms[row * 3 + col];
	    if ( row > 0 )
		make_exit( here, rooms[(row - 1) * 3 + col], DIR_NORTH );
	    if ( row < 2 )
		make_exit( here, rooms[(row + 1) * 3 + col], DIR_SOUTH );
	    if ( col > 0 )
		make_exit( here, rooms[row * 3 + col - 1], DIR_WEST );
	    if ( col < 2 )
		make_exit( here, rooms[row * 3 + col + 1], DIR_EAST );
	}
    c->landing = rooms[4];
    chart_mobs( rooms, 9, c->seed );

    CREATE( sys, SPACE_DATA, 1 );
    sys->name = STRALLOC( c->system );
    sys->planet1 = STRALLOC( c->planet );
    sys->star1 = STRALLOC( "a nameless star" );
    sys->p1x = c->x;
    sys->p1y = c->y;
    sys->p1z = c->z;
    LINK( sys, first_starsystem, last_starsystem, next, prev );

    CREATE( planet, PLANET_DATA, 1 );
    planet->name = STRALLOC( c->planet );
    planet->starsystem = sys;
    planet->x = c->x;
    planet->y = c->y;
    planet->z = c->z;
    LINK( planet, sys->first_planet, sys->last_planet, next_in_system, prev_in_system );
    LINK( planet, first_planet, last_planet, next, prev );
    c->starsystem = sys;
}

static CHART_DATA *chart_create( int seed )
{
    CHART_DATA *c;
    int s = seed;

    CREATE( c, CHART_DATA, 1 );
    c->seed = seed;
    chart_name( seed, c->planet, c->system );
    c->biome = lcg( &s ) % 8;
    c->vnum = CHART_BASE + seed * 9;
    c->x = ( lcg( &s ) % 40000 ) - 20000;
    c->y = ( lcg( &s ) % 40000 ) - 20000;
    c->z = ( lcg( &s ) % 40000 ) - 20000;
    chart_build( c );
    c->next = first_chart;
    first_chart = c;
    chart_save( c );
    return c;
}

static void chart_load_file( const char *path )
{
    FILE *fp;
    CHART_DATA *c;
    char *planet, *system;

    if ( ( fp = fopen( path, "r" ) ) == NULL )
	return;
    CREATE( c, CHART_DATA, 1 );
    for ( ;; )
    {
	char *word = feof( fp ) ? "End" : fread_word( fp );
	if ( !str_cmp( word, "End" ) || feof( fp ) )
	    break;
	if ( !str_cmp( word, "Seed" ) ) c->seed = fread_number( fp );
	else if ( !str_cmp( word, "Planet" ) ) { planet = fread_string_nohash( fp ); strcpy( c->planet, planet ); DISPOSE( planet ); }
	else if ( !str_cmp( word, "System" ) ) { system = fread_string_nohash( fp ); strcpy( c->system, system ); DISPOSE( system ); }
	else if ( !str_cmp( word, "Biome" ) ) c->biome = fread_number( fp );
	else if ( !str_cmp( word, "Vnum" ) ) c->vnum = fread_number( fp );
	else if ( !str_cmp( word, "X" ) ) c->x = fread_number( fp );
	else if ( !str_cmp( word, "Y" ) ) c->y = fread_number( fp );
	else if ( !str_cmp( word, "Z" ) ) c->z = fread_number( fp );
	else fread_to_eol( fp );
    }
    fclose( fp );
    if ( c->seed < 1 || c->vnum < CHART_BASE )
    {
	DISPOSE( c );
	return;
    }
    chart_build( c );
    c->next = first_chart;
    first_chart = c;
}

void load_charts( void )
{
    DIR *dp;
    struct dirent *de;

    first_chart = NULL;
    if ( ( dp = opendir( CHART_DIR ) ) == NULL )
	return;
    while ( ( de = readdir( dp ) ) != NULL )
    {
	char path[256];
	if ( de->d_name[0] == '.' )
	    continue;
	sprintf( path, "%s%s", CHART_DIR, de->d_name );
	chart_load_file( path );
    }
    closedir( dp );
}

static void guide_add( CHAR_DATA *ch, CHART_DATA *c )
{
    FILE *fp;
    char path[256], line[128];

    sprintf( path, "%s%s.guide", GUIDE_DIR, ch->name );
    if ( ( fp = fopen( path, "r" ) ) != NULL )
    {
	while ( fgets( line, sizeof( line ), fp ) )
	{
	    line[strcspn( line, "\r\n" )] = '\0';
	    if ( !str_cmp( line, c->planet ) )
	    {
		fclose( fp );
		return;
	    }
	}
	fclose( fp );
    }
    if ( ( fp = fopen( path, "a" ) ) == NULL )
	return;
    fprintf( fp, "%s\n", c->planet );
    fclose( fp );
}

static bool guide_has( CHAR_DATA *ch, const char *planet )
{
    FILE *fp;
    char path[256], line[128];

    sprintf( path, "%s%s.guide", GUIDE_DIR, ch->name );
    if ( ( fp = fopen( path, "r" ) ) == NULL )
	return FALSE;
    while ( fgets( line, sizeof( line ), fp ) )
    {
	line[strcspn( line, "\r\n" )] = '\0';
	if ( !str_cmp( line, planet ) )
	{
	    fclose( fp );
	    return TRUE;
	}
    }
    fclose( fp );
    return FALSE;
}

void do_survey( CHAR_DATA *ch, char *argument )
{
    SHIP_DATA *ship;
    CHART_DATA *c;
    int seed, tries;

    if ( ( ship = ship_from_pilotseat( ch->in_room->vnum ) ) == NULL )
    {
	send_to_char( "You must be in the pilot's seat.\n\r", ch );
	return;
    }
    if ( ship->shipstate == SHIP_DOCKED )
    {
	send_to_char( "Launch first. Survey jumps only work in open space.\n\r", ch );
	return;
    }
    for ( tries = 0; tries < 30; tries++ )
    {
	seed = number_range( 1, CHART_MAX );
	if ( !chart_by_seed( seed ) )
	    break;
    }
    c = chart_by_seed( seed );
    if ( !c )
	c = chart_create( seed );
    if ( ship->starsystem )
	ship_from_starsystem( ship, ship->starsystem );
    ship->vx = c->x;
    ship->vy = c->y;
    ship->vz = c->z;
    ship->shipstate = SHIP_READY;
    ship_to_starsystem( ship, c->starsystem );
    ch_printf( ch, "&CThe stars smear and drop you into the &W%s&C.\n\r", c->system );
    ch_printf( ch, "A world hangs below: &W%s&C, %s. Type &Wexplore&C to go down.\n\r", c->planet, biomes[c->biome] );
}

void do_explore( CHAR_DATA *ch, char *argument )
{
    SHIP_DATA *ship;
    CHART_DATA *c;

    if ( ( ship = ship_from_cockpit( ch->in_room->vnum ) ) == NULL )
    {
	send_to_char( "You need to be aboard a ship in a charted system.\n\r", ch );
	return;
    }
    if ( !ship->starsystem || ( c = chart_by_system( ship->starsystem ) ) == NULL )
    {
	send_to_char( "This system is on the old charts. Survey jumps into uncharted space.\n\r", ch );
	return;
    }
    char_from_room( ch );
    char_to_room( ch, c->landing );
    guide_add( ch, c );
    ch_printf( ch, "&GYou set down on &W%s&G. It is written in your guide.\n\r", c->planet );
    do_look( ch, "auto" );
}

void do_guide( CHAR_DATA *ch, char *argument )
{
    FILE *fp;
    char path[256], line[128];
    int n = 0;

    if ( IS_NPC( ch ) )
	return;
    sprintf( path, "%s%s.guide", GUIDE_DIR, ch->name );
    send_to_char( "&CWorlds you have walked:&w\n\r", ch );
    if ( ( fp = fopen( path, "r" ) ) == NULL )
    {
	send_to_char( "The guide is empty.\n\r", ch );
	return;
    }
    while ( fgets( line, sizeof( line ), fp ) )
    {
	CHART_DATA *c;
	line[strcspn( line, "\r\n" )] = '\0';
	c = chart_by_planet( line );
	if ( c )
	    ch_printf( ch, "  &W%s&w, %s, in the %s.\n\r", c->planet, biomes[c->biome], c->system );
	else
	    ch_printf( ch, "  &W%s&w\n\r", line );
	n++;
    }
    fclose( fp );
    if ( n == 0 )
	send_to_char( "The guide is empty.\n\r", ch );
    else
	send_to_char( "Use &Wwarp <planet>&w to return to one of these.\n\r", ch );
}

void do_warp( CHAR_DATA *ch, char *argument )
{
    CHART_DATA *c;
    char arg[MAX_INPUT_LENGTH];

    if ( IS_NPC( ch ) )
	return;
    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Warp to which charted world? See &Wguide&w.\n\r", ch );
	return;
    }
    c = chart_by_planet( arg );
    if ( !c || !guide_has( ch, c->planet ) )
    {
	send_to_char( "That world is not in your guide. You can only return to places you have explored.\n\r", ch );
	return;
    }
    if ( ch->fighting )
    {
	send_to_char( "Not while you are fighting.\n\r", ch );
	return;
    }
    char_from_room( ch );
    char_to_room( ch, c->landing );
    ch_printf( ch, "&CYou step back onto &W%s&C.\n\r", c->planet );
    do_look( ch, "auto" );
}
