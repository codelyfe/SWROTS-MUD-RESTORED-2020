#include <stdio.h>
#include <string.h>
#include "mud.h"

#define MAP_RAD  3
#define MAP_SPAN (MAP_RAD * 2 + 1)

static ROOM_INDEX_DATA *map_grid[MAP_SPAN][MAP_SPAN];
static int map_seen[64];
static int map_seen_count;

static const int map_dirs[8] = { 0, 1, 2, 3, 6, 7, 8, 9 };
static const int map_dx[10] = { 0, 1, 0, -1, 0, 0, 1, -1, 1, -1 };
static const int map_dy[10] = { -1, 0, 1, 0, 0, 0, -1, -1, 1, 1 };

static bool map_already( int vnum )
{
    int i;

    for ( i = 0; i < map_seen_count; i++ )
	if ( map_seen[i] == vnum )
	    return TRUE;
    if ( map_seen_count < 64 )
	map_seen[map_seen_count++] = vnum;
    return FALSE;
}

static const char *map_symbol( ROOM_INDEX_DATA *room, ROOM_INDEX_DATA *here )
{
    if ( room == here )
	return "&W[&R!&W]";
    switch ( room->sector_type )
    {
	case SECT_CITY:		return "&W[&CC&W]";
	case SECT_FIELD:
	case SECT_FARMLAND:
	case SECT_SAVANNA:
	case SECT_STEPPE:	return "&W[&G,&W]";
	case SECT_FOREST:
	case SECT_JUNGLE:
	case SECT_RAINFOREST:
	case SECT_BRUSH:
	case SECT_SCRUB:	return "&W[&GY&W]";
	case SECT_HILLS:	return "&W[&Ym&W]";
	case SECT_MOUNTAIN:
	case SECT_ROCKY:
	case SECT_VOLCANIC:	return "&W[&RM&W]";
	case SECT_WATER_SWIM:
	case SECT_WATER_NOSWIM:
	case SECT_OCEANFLOOR:
	case SECT_UNDERWATER:	return "&W[&B~&W]";
	case SECT_AIR:		return "&W[&C^&W]";
	case SECT_DESERT:	return "&W[&Y.&W]";
	case SECT_SWAMP:
	case SECT_WETLANDS:	return "&W[&G%&W]";
	default:		return "&W[&w.&W]";
    }
}

static void map_walk( ROOM_INDEX_DATA *room, int x, int y, int depth )
{
    int i;

    if ( !room || x < 0 || y < 0 || x >= MAP_SPAN || y >= MAP_SPAN || depth > MAP_RAD )
	return;
    if ( map_grid[y][x] )
	return;
    if ( map_already( room->vnum ) && depth > 0 )
	return;
    map_grid[y][x] = room;

    for ( i = 0; i < 8; i++ )
    {
	int dir = map_dirs[i];
	EXIT_DATA *pexit = get_exit( room, dir );

	if ( !pexit || !pexit->to_room )
	    continue;
	if ( IS_SET( pexit->exit_info, EX_HIDDEN ) )
	    continue;
	map_walk( pexit->to_room, x + map_dx[dir], y + map_dy[dir], depth + 1 );
    }
}

static bool map_linked( ROOM_INDEX_DATA *from, ROOM_INDEX_DATA *to, int dir )
{
    EXIT_DATA *pexit;

    if ( !from || !to )
	return FALSE;
    pexit = get_exit( from, dir );
    return ( pexit && pexit->to_room == to );
}

void show_map( CHAR_DATA *ch )
{
    int x, y;
    bool up, down;
    EXIT_DATA *pexit;

    if ( !ch || !ch->in_room )
	return;

    for ( y = 0; y < MAP_SPAN; y++ )
	for ( x = 0; x < MAP_SPAN; x++ )
	    map_grid[y][x] = NULL;
    map_seen_count = 0;
    map_walk( ch->in_room, MAP_RAD, MAP_RAD, 0 );

    send_to_char( "\n\r", ch );
    for ( y = 0; y < MAP_SPAN; y++ )
    {
	if ( y > 0 )
	{
	    send_to_char( " ", ch );
	    for ( x = 0; x < MAP_SPAN; x++ )
	    {
		if ( map_linked( map_grid[y - 1][x], map_grid[y][x], DIR_SOUTH )
		||   map_linked( map_grid[y][x], map_grid[y - 1][x], DIR_NORTH ) )
		    send_to_char( " |  ", ch );
		else
		    send_to_char( "    ", ch );
	    }
	    send_to_char( "\n\r", ch );
	}

	send_to_char( " ", ch );
	for ( x = 0; x < MAP_SPAN; x++ )
	{
	    if ( map_grid[y][x] )
		send_to_char( map_symbol( map_grid[y][x], ch->in_room ), ch );
	    else
		send_to_char( "   ", ch );
	    if ( x + 1 < MAP_SPAN
	    && ( map_linked( map_grid[y][x], map_grid[y][x + 1], DIR_EAST )
	      || map_linked( map_grid[y][x + 1], map_grid[y][x], DIR_WEST ) ) )
		send_to_char( "-", ch );
	    else
		send_to_char( " ", ch );
	}
	send_to_char( "\n\r", ch );
    }

    up = down = FALSE;
    if ( ( pexit = get_exit( ch->in_room, DIR_UP ) ) && pexit->to_room )
	up = TRUE;
    if ( ( pexit = get_exit( ch->in_room, DIR_DOWN ) ) && pexit->to_room )
	down = TRUE;
    if ( up || down )
	ch_printf( ch, " &W[&R!&W] is you.%s%s\n\r",
	    up ? "  Stairs up." : "",
	    down ? "  Stairs down." : "" );
    else
	send_to_char( " &W[&R!&W] is you.\n\r", ch );
}

void do_map( CHAR_DATA *ch, char *argument )
{
    if ( !ch->in_room )
	return;
    show_map( ch );
}

void do_automap( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC( ch ) )
	return;
    if ( IS_SET( ch->act, PLR_AUTOMAP ) )
    {
	REMOVE_BIT( ch->act, PLR_AUTOMAP );
	send_to_char( "Automap off.\n\r", ch );
    }
    else
    {
	SET_BIT( ch->act, PLR_AUTOMAP );
	send_to_char( "Automap on. A map will be shown each time you look.\n\r", ch );
	show_map( ch );
    }
}
