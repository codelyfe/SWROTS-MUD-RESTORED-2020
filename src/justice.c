#include <stdio.h>
#include <string.h>
#include "mud.h"

#define JAIL_ROOM 2002
#define INFAMY_HUNT 15
#define INFAMY_TRIAL 35

static int is_hunter( CHAR_DATA *mob )
{
    return mob && IS_NPC(mob) && mob->name && !str_prefix( "hunter ", mob->name );
}

static CHAR_DATA *hunter_for( CHAR_DATA *ch )
{
    CHAR_DATA *mob;

    for ( mob = first_char; mob; mob = mob->next )
	if ( is_hunter( mob ) && !str_cmp( mob->name + 7, ch->name ) )
	    return mob;
    return NULL;
}

static CHAR_DATA *hunt_target( CHAR_DATA *mob )
{
    if ( !is_hunter( mob ) )
	return NULL;
    return get_char_world( mob, mob->name + 7 );
}

static ROOM_INDEX_DATA *step_toward( ROOM_INDEX_DATA *from, ROOM_INDEX_DATA *to, int *depth_out )
{
    ROOM_INDEX_DATA *queue[256];
    ROOM_INDEX_DATA *via[256];
    int seen, head, tail, i, dir;
    EXIT_DATA *ex;

    if ( !from || !to || from == to )
	return NULL;
    queue[0] = to;
    via[0] = NULL;
    head = 0;
    tail = 1;
    seen = 1;
    while ( head < tail && tail < 256 )
    {
	ROOM_INDEX_DATA *here = queue[head];
	ROOM_INDEX_DATA *came = via[head];
	head++;
	for ( dir = 0; dir <= 9; dir++ )
	{
	    ROOM_INDEX_DATA *next;
	    int already = 0;
	    ex = get_exit( here, dir );
	    if ( !ex || !ex->to_room || ex->to_room->area != to->area )
		continue;
	    next = ex->to_room;
	    for ( i = 0; i < tail; i++ )
		if ( queue[i] == next )
		    already = 1;
	    if ( already )
		continue;
	    if ( next == from )
	    {
		int depth = 1;
		ROOM_INDEX_DATA *step = here;
		ROOM_INDEX_DATA *prev = came;
		while ( prev && prev != to )
		{
		    for ( i = 0; i < head; i++ )
			if ( queue[i] == prev )
			{
			    step = prev;
			    prev = via[i];
			    depth++;
			    break;
			}
		}
		if ( depth_out )
		    *depth_out = depth;
		return step;
	    }
	    queue[tail] = next;
	    via[tail] = here;
	    tail++;
	    seen++;
	    if ( tail >= 256 )
		break;
	}
    }
    return NULL;
}

static void spawn_hunter( CHAR_DATA *ch )
{
    MOB_INDEX_DATA *index;
    CHAR_DATA *mob;
    char name[MAX_INPUT_LENGTH];
    ROOM_INDEX_DATA *start;

    if ( !ch || IS_NPC(ch) || !ch->in_room || hunter_for( ch ) )
	return;
    index = get_mob_index( 8000 );
    if ( !index )
	index = get_mob_index( 29000 );
    if ( !index )
	return;
    mob = create_mobile( index );
    sprintf( name, "hunter %s", ch->name );
    STRFREE( mob->name );
    STRFREE( mob->short_descr );
    STRFREE( mob->long_descr );
    mob->name = STRALLOC( name );
    mob->short_descr = STRALLOC( "a bounty hunter" );
    mob->long_descr = STRALLOC( "A bounty hunter is here, checking a warrant.\n\r" );
    mob->top_level = UMAX( 1, ch->top_level );
    mob->hitroll = ch->hitroll;
    mob->damroll = ch->damroll;
    mob->armor = ch->armor;
    mob->max_hit = UMAX( 20, ch->max_hit );
    mob->hit = mob->max_hit;
    mob->timer = 0;
    start = get_room_index( 8000 );
    if ( !start )
	start = ch->in_room;
    char_to_room( mob, start );
    if ( start->area == ch->in_room->area )
	ch_printf( ch, "&RAn equal bounty hunter has your warrant and is already on this world.&w\n\r" );
    else
	ch_printf( ch, "&RAn equal bounty hunter has your warrant and is booking passage.&w\n\r" );
}

void gain_infamy( CHAR_DATA *ch, int amt )
{
    if ( !ch || IS_NPC(ch) || !ch->pcdata || amt < 1 || IS_IMMORTAL(ch) )
	return;
    ch->pcdata->infamy += amt;
    ch_printf( ch, "&RYour infamy rises to %d.&w\n\r", ch->pcdata->infamy );
}

static void begin_trial( CHAR_DATA *ch )
{
    ROOM_INDEX_DATA *cell;
    char buf[MAX_STRING_LENGTH];
    int sentence;

    if ( !ch->in_room || ch->pcdata->jail_time > 0 )
	return;
    cell = get_room_index( JAIL_ROOM );
    if ( !cell )
	return;
    sentence = 4 + ( ch->pcdata->infamy / 8 );
    ch->pcdata->jail_from = ch->in_room->vnum;
    ch->pcdata->jail_time = sentence;
    ch->pcdata->infamy = ch->pcdata->infamy / 3;
    sprintf( buf, "&YThe court is in session for all to see. %s is sentenced to %d ticks in a cell, served only while online.&w",
	ch->name, sentence );
    echo_to_all( AT_YELLOW, buf, ECHOTAR_ALL );
    char_from_room( ch );
    char_to_room( ch, cell );
    do_look( ch, "auto" );
}

static void release_prisoner( CHAR_DATA *ch )
{
    ROOM_INDEX_DATA *back;

    back = get_room_index( ch->pcdata->jail_from );
    ch->pcdata->jail_time = 0;
    ch->pcdata->jail_from = 0;
    if ( !back )
	back = get_room_index( ROOM_VNUM_TEMPLE );
    if ( !back )
	return;
    char_from_room( ch );
    char_to_room( ch, back );
    send_to_char( "&GYour sentence is served. You are returned to where you were taken.&w\n\r", ch );
    do_look( ch, "auto" );
}

void justice_tick( void )
{
    CHAR_DATA *ch, *ch_next, *hunter, *target;
    int depth;

    for ( ch = first_char; ch; ch = ch_next )
    {
	ch_next = ch->next;
	if ( IS_NPC(ch) || !ch->pcdata || !ch->desc )
	    continue;
	if ( ch->pcdata->hunt_grace > 0 )
	    ch->pcdata->hunt_grace--;
	if ( ch->pcdata->jail_time > 0 )
	{
	    ch->pcdata->jail_time--;
	    if ( ch->pcdata->jail_time <= 0 )
		release_prisoner( ch );
	    continue;
	}
	if ( ch->pcdata->hunt_grace > 0 )
	    continue;
	if ( ch->pcdata->infamy >= INFAMY_TRIAL )
	    begin_trial( ch );
	else if ( ch->pcdata->infamy >= INFAMY_HUNT )
	    spawn_hunter( ch );
    }

    for ( hunter = first_char; hunter; hunter = ch_next )
    {
	ch_next = hunter->next;
	if ( !is_hunter( hunter ) || !hunter->in_room )
	    continue;
	target = hunt_target( hunter );
	if ( !target || !target->in_room || ( target->pcdata && target->pcdata->jail_time > 0 ) )
	{
	    extract_char( hunter, TRUE );
	    continue;
	}
	if ( hunter->in_room == target->in_room )
	{
	    if ( !hunter->fighting )
	    {
		act( AT_RED, "$n checks a warrant and comes for you.", hunter, NULL, target, TO_VICT );
		multi_hit( hunter, target, TYPE_UNDEFINED );
	    }
	    continue;
	}
	if ( hunter->in_room->area != target->in_room->area )
	{
	    hunter->timer++;
	    if ( hunter->timer == 1 )
		ch_printf( target, "&RThe bounty hunter has left dock after you.&w\n\r" );
	    else if ( hunter->timer == 4 )
		ch_printf( target, "&RThe bounty hunter's ship is in the lanes, closing.&w\n\r" );
	    else if ( hunter->timer == 8 )
		ch_printf( target, "&RThe bounty hunter has entered your system.&w\n\r" );
	    else if ( hunter->timer >= 12 )
	    {
		ROOM_INDEX_DATA *gate = NULL;
		if ( target->in_room->area )
		    gate = get_room_index( target->in_room->area->low_r_vnum );
		if ( !gate )
		    gate = target->in_room;
		char_from_room( hunter );
		char_to_room( hunter, gate );
		hunter->timer = 0;
		ch_printf( target, "&RThe bounty hunter has set down on your world and is on foot.&w\n\r" );
	    }
	    continue;
	}
	{
	    ROOM_INDEX_DATA *step = step_toward( hunter->in_room, target->in_room, &depth );
	    if ( !step )
		continue;
	    if ( depth <= 6 && hunter->timer != depth )
	    {
		hunter->timer = depth;
		ch_printf( target, "&RThe bounty hunter is %d rooms from you.&w\n\r", depth );
	    }
	    char_from_room( hunter );
	    char_to_room( hunter, step );
	    act( AT_PLAIN, "A bounty hunter moves through, following a warrant.", hunter, NULL, NULL, TO_ROOM );
	}
    }
}

void hunter_killed( CHAR_DATA *killer )
{
    if ( !killer || IS_NPC(killer) || !killer->pcdata )
	return;
    killer->pcdata->infamy = UMAX( 0, killer->pcdata->infamy - 20 );
    killer->pcdata->hunt_grace = 12;
    send_to_char( "&GThe contract goes cold. You will not be tracked for a while.&w\n\r", killer );
}

void do_infamy( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) || !ch->pcdata )
	return;
    ch_printf( ch, "Infamy: %d. Jail ticks left: %d. Hunt grace: %d.\n\r",
	ch->pcdata->infamy, ch->pcdata->jail_time, ch->pcdata->hunt_grace );
    ch_printf( ch, "A hunter is dispatched at %d. A public trial starts at %d.\n\r",
	INFAMY_HUNT, INFAMY_TRIAL );
}

void do_sendhunter( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];

    if ( IS_NPC(ch) || !IS_IMMORTAL(ch) )
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Send a bounty hunter after whom?\n\r", ch );
	return;
    }
    if ( ( victim = get_char_world( ch, arg ) ) == NULL || IS_NPC(victim) )
    {
	send_to_char( "That player is not online.\n\r", ch );
	return;
    }
    victim->pcdata->hunt_grace = 0;
    if ( victim->pcdata->infamy < INFAMY_HUNT )
	victim->pcdata->infamy = INFAMY_HUNT;
    spawn_hunter( victim );
    ch_printf( ch, "A hunter has been sent after %s.\n\r", victim->name );
}
