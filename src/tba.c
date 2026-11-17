#include <stdio.h>
#include <string.h>
#include <arpa/telnet.h>
#include "mud.h"

#define MAX_PALIAS 8
#define HOUSE_COST 25000
#define TELOPT_MSDP 69
#define MSDP_VAR 1
#define MSDP_VAL 2

extern bool write_to_descriptor( int desc, char *txt, int length );

typedef struct house_data HOUSE_DATA;
struct house_data {
    HOUSE_DATA *next;
    char *owner;
    int vnum;
    int locked;
    char *guests;
};
static HOUSE_DATA *first_house;

typedef struct quest_stage QSTAGE;
struct quest_stage { int kind; int vnum; char *text; };
typedef struct bquest_data BQUEST;
struct bquest_data {
    BQUEST *next;
    int id;
    char *name;
    int giver;
    int prize;
    int nstage;
    QSTAGE stage[6];
};
static BQUEST *first_quest;

static HOUSE_DATA *house_by_room( int vnum )
{
    HOUSE_DATA *h;
    for ( h = first_house; h; h = h->next )
	if ( h->vnum == vnum )
	    return h;
    return NULL;
}

static HOUSE_DATA *house_by_owner( const char *name )
{
    HOUSE_DATA *h;
    for ( h = first_house; h; h = h->next )
	if ( !str_cmp( h->owner, name ) )
	    return h;
    return NULL;
}

static int house_guest( HOUSE_DATA *h, const char *name )
{
    char buf[MAX_STRING_LENGTH];
    char word[MAX_INPUT_LENGTH];
    char *p;
    if ( !h->guests || !h->guests[0] )
	return 0;
    strcpy( buf, h->guests );
    p = buf;
    while ( p && *p )
    {
	p = one_argument( p, word );
	if ( !str_cmp( word, name ) )
	    return 1;
    }
    return 0;
}

static void save_houses( void )
{
    FILE *fp;
    HOUSE_DATA *h;
    if ( ( fp = fopen( "../system/houses.dat", "w" ) ) == NULL )
	return;
    for ( h = first_house; h; h = h->next )
	fprintf( fp, "%s %d %d %s~\n", h->owner, h->vnum, h->locked, h->guests && h->guests[0] ? h->guests : "-" );
    fprintf( fp, "$\n" );
    fclose( fp );
}

void load_houses( void )
{
    FILE *fp;
    char *line;
    if ( ( fp = fopen( "../system/houses.dat", "r" ) ) == NULL )
	return;
    for ( ; ; )
    {
	char owner[MAX_INPUT_LENGTH];
	char guests[MAX_INPUT_LENGTH];
	int vnum, locked;
	HOUSE_DATA *h;
	if ( feof(fp) )
	    break;
	line = fread_line( fp );
	if ( !line || line[0] == '$' || line[0] == '\0' )
	    break;
	guests[0] = '\0';
	if ( sscanf( line, "%s %d %d %s", owner, &vnum, &locked, guests ) < 3 )
	    continue;
	CREATE( h, HOUSE_DATA, 1 );
	h->owner = STRALLOC( owner );
	h->vnum = vnum;
	h->locked = locked;
	h->guests = STRALLOC( guests[0] == '-' ? "" : guests );
	h->next = first_house;
	first_house = h;
    }
    fclose( fp );
}

int house_blocks( CHAR_DATA *ch, ROOM_INDEX_DATA *room )
{
    HOUSE_DATA *h;
    if ( !ch || !room || IS_NPC(ch) || IS_IMMORTAL(ch) )
	return 0;
    h = house_by_room( room->vnum );
    if ( !h || !h->locked )
	return 0;
    if ( !str_cmp( h->owner, ch->name ) || house_guest( h, ch->name ) )
	return 0;
    return 1;
}

void do_buyhouse( CHAR_DATA *ch, char *argument )
{
    HOUSE_DATA *h;
    if ( IS_NPC(ch) || !ch->in_room )
	return;
    if ( house_by_owner( ch->name ) )
    {
	send_to_char( "You already own a house.\n\r", ch );
	return;
    }
    if ( house_by_room( ch->in_room->vnum ) )
    {
	send_to_char( "Someone already owns this room.\n\r", ch );
	return;
    }
    if ( ch->gold < HOUSE_COST )
    {
	ch_printf( ch, "A house costs %d credits.\n\r", HOUSE_COST );
	return;
    }
    ch->gold -= HOUSE_COST;
    CREATE( h, HOUSE_DATA, 1 );
    h->owner = STRALLOC( ch->name );
    h->vnum = ch->in_room->vnum;
    h->locked = 1;
    h->guests = STRALLOC( "" );
    h->next = first_house;
    first_house = h;
    save_houses();
    send_to_char( "You buy this room as your house. It is locked. Use house guest <name> and house unlock.\n\r", ch );
}

void do_house( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    HOUSE_DATA *h;
    if ( IS_NPC(ch) )
	return;
    h = house_by_owner( ch->name );
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	if ( !h )
	    send_to_char( "You own no house. buyhouse purchases the room you are standing in.\n\r", ch );
	else
	    ch_printf( ch, "Your house is room %d. It is %s. Guests: %s\n\r",
		h->vnum, h->locked ? "locked" : "open", h->guests[0] ? h->guests : "none" );
	return;
    }
    if ( !h )
    {
	send_to_char( "You own no house.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg, "lock" ) )
    {
	h->locked = 1;
	save_houses();
	send_to_char( "House locked.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg, "unlock" ) )
    {
	h->locked = 0;
	save_houses();
	send_to_char( "House unlocked.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg, "guest" ) )
    {
	char name[MAX_INPUT_LENGTH];
	char buf[MAX_STRING_LENGTH];
	one_argument( argument, name );
	if ( name[0] == '\0' )
	{
	    send_to_char( "house guest <name>\n\r", ch );
	    return;
	}
	sprintf( buf, "%s %s", h->guests, name );
	STRFREE( h->guests );
	h->guests = STRALLOC( buf );
	save_houses();
	ch_printf( ch, "%s may enter your locked house.\n\r", name );
	return;
    }
    if ( !str_cmp( arg, "unguests" ) || !str_cmp( arg, "unguest" ) )
    {
	STRFREE( h->guests );
	h->guests = STRALLOC( "" );
	save_houses();
	send_to_char( "Guest list cleared.\n\r", ch );
	return;
    }
    send_to_char( "house, house lock, house unlock, house guest <name>, house unguest.\n\r", ch );
}

static BQUEST *quest_by_id( int id )
{
    BQUEST *q;
    for ( q = first_quest; q; q = q->next )
	if ( q->id == id )
	    return q;
    return NULL;
}

void load_quests( void )
{
    FILE *fp;
    char *word;
    BQUEST *q = NULL;
    int n = 0;
    if ( ( fp = fopen( "../system/quests.dat", "r" ) ) == NULL )
	return;
    for ( ; ; )
    {
	if ( feof(fp) )
	    break;
	word = fread_word( fp );
	if ( !str_cmp( word, "End" ) || !str_cmp( word, "$" ) )
	    break;
	if ( !str_cmp( word, "Quest" ) )
	{
	    CREATE( q, BQUEST, 1 );
	    q->next = first_quest;
	    first_quest = q;
	    n = 0;
	    continue;
	}
	if ( !q )
	    continue;
	if ( !str_cmp( word, "Id" ) ) q->id = fread_number( fp );
	else if ( !str_cmp( word, "Name" ) ) q->name = fread_string( fp );
	else if ( !str_cmp( word, "Giver" ) ) q->giver = fread_number( fp );
	else if ( !str_cmp( word, "Prize" ) ) q->prize = fread_number( fp );
	else if ( !str_cmp( word, "Stage" ) && n < 6 )
	{
	    q->stage[n].kind = fread_letter( fp );
	    q->stage[n].vnum = fread_number( fp );
	    q->stage[n].text = fread_string( fp );
	    n++;
	    q->nstage = n;
	}
	else
	    fread_to_eol( fp );
    }
    fclose( fp );
}

static void quest_advance( CHAR_DATA *ch )
{
    BQUEST *q;
    if ( IS_NPC(ch) || !ch->pcdata || ch->pcdata->q_id < 1 )
	return;
    q = quest_by_id( ch->pcdata->q_id );
    if ( !q )
	return;
    ch->pcdata->q_stage++;
    if ( ch->pcdata->q_stage >= q->nstage )
	ch_printf( ch, "&GQuest stage complete. Return to the giver and type qfinish.&w\n\r" );
    else
	ch_printf( ch, "&GQuest: %s&w\n\r", q->stage[ch->pcdata->q_stage].text );
}

void quest_kill( CHAR_DATA *ch, CHAR_DATA *victim )
{
    BQUEST *q;
    QSTAGE *s;
    if ( !ch || !victim || IS_NPC(ch) || !IS_NPC(victim) || !ch->pcdata )
	return;
    q = quest_by_id( ch->pcdata->q_id );
    if ( !q || ch->pcdata->q_stage >= q->nstage )
	return;
    s = &q->stage[ch->pcdata->q_stage];
    if ( s->kind == 'M' && victim->pIndexData && victim->pIndexData->vnum == s->vnum )
	quest_advance( ch );
}

void quest_visit( CHAR_DATA *ch )
{
    BQUEST *q;
    QSTAGE *s;
    if ( !ch || IS_NPC(ch) || !ch->pcdata || !ch->in_room )
	return;
    q = quest_by_id( ch->pcdata->q_id );
    if ( !q || ch->pcdata->q_stage >= q->nstage )
	return;
    s = &q->stage[ch->pcdata->q_stage];
    if ( s->kind == 'R' && ch->in_room->vnum == s->vnum )
	quest_advance( ch );
}

void do_qaccept( CHAR_DATA *ch, char *argument )
{
    BQUEST *q;
    CHAR_DATA *mob;
    int id;
    if ( IS_NPC(ch) )
	return;
    if ( ch->pcdata->q_id )
    {
	send_to_char( "You already have a quest. qstat, or qfinish when it is done.\n\r", ch );
	return;
    }
    id = atoi( argument );
    for ( q = first_quest; q; q = q->next )
	if ( !id || q->id == id )
	    break;
    if ( !q )
    {
	send_to_char( "No such quest.\n\r", ch );
	return;
    }
    for ( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
	if ( IS_NPC(mob) && mob->pIndexData && mob->pIndexData->vnum == q->giver )
	    break;
    if ( !mob )
    {
	send_to_char( "The quest giver is not here.\n\r", ch );
	return;
    }
    ch->pcdata->q_id = q->id;
    ch->pcdata->q_stage = 0;
    ch_printf( ch, "You accept %s.\n\r%s\n\r", q->name, q->stage[0].text );
}

void do_qstat( CHAR_DATA *ch, char *argument )
{
    BQUEST *q;
    if ( IS_NPC(ch) )
	return;
    if ( !ch->pcdata->q_id )
    {
	send_to_char( "You have no quest. Stand by a giver and type qaccept.\n\r", ch );
	return;
    }
    q = quest_by_id( ch->pcdata->q_id );
    if ( !q )
    {
	send_to_char( "That quest no longer exists.\n\r", ch );
	return;
    }
    ch_printf( ch, "%s, stage %d of %d.\n\r", q->name, ch->pcdata->q_stage + 1, q->nstage );
    if ( ch->pcdata->q_stage < q->nstage )
	ch_printf( ch, "%s\n\r", q->stage[ch->pcdata->q_stage].text );
    else
	send_to_char( "Finished. Find the giver and type qfinish.\n\r", ch );
}

void do_qfinish( CHAR_DATA *ch, char *argument )
{
    BQUEST *q;
    CHAR_DATA *mob;
    if ( IS_NPC(ch) || !ch->pcdata->q_id )
    {
	send_to_char( "You have no quest.\n\r", ch );
	return;
    }
    q = quest_by_id( ch->pcdata->q_id );
    if ( !q || ch->pcdata->q_stage < q->nstage )
    {
	send_to_char( "You have not finished the stages.\n\r", ch );
	return;
    }
    for ( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
	if ( IS_NPC(mob) && mob->pIndexData && mob->pIndexData->vnum == q->giver )
	    break;
    if ( !mob )
    {
	send_to_char( "The quest giver is not here.\n\r", ch );
	return;
    }
    ch->gold += q->prize;
    ch_printf( ch, "You are paid %d credits.\n\r", q->prize );
    ch->pcdata->q_id = 0;
    ch->pcdata->q_stage = 0;
}

int alias_expand( CHAR_DATA *ch, char *command, char *rest, char *out, int outlen )
{
    int i;
    if ( IS_NPC(ch) || !ch->pcdata )
	return 0;
    for ( i = 0; i < MAX_PALIAS; i++ )
    {
	if ( ch->pcdata->alias_name[i] && !str_cmp( ch->pcdata->alias_name[i], command ) )
	{
	    snprintf( out, outlen, "%s%s%s", ch->pcdata->alias_text[i], rest[0] ? " " : "", rest );
	    return 1;
	}
    }
    return 0;
}

void do_alias( CHAR_DATA *ch, char *argument )
{
    char name[MAX_INPUT_LENGTH];
    int i, free_slot;
    if ( IS_NPC(ch) )
	return;
    if ( argument[0] == '\0' )
    {
	send_to_char( "Aliases:\n\r", ch );
	for ( i = 0; i < MAX_PALIAS; i++ )
	    if ( ch->pcdata->alias_name[i] )
		ch_printf( ch, "  %s = %s\n\r", ch->pcdata->alias_name[i], ch->pcdata->alias_text[i] );
	return;
    }
    argument = one_argument( argument, name );
    if ( !str_cmp( name, "alias" ) )
    {
	send_to_char( "That name is reserved.\n\r", ch );
	return;
    }
    for ( i = 0; i < MAX_PALIAS; i++ )
	if ( ch->pcdata->alias_name[i] && !str_cmp( ch->pcdata->alias_name[i], name ) )
	    break;
    if ( argument[0] == '\0' )
    {
	if ( i < MAX_PALIAS && ch->pcdata->alias_name[i] )
	{
	    STRFREE( ch->pcdata->alias_name[i] );
	    STRFREE( ch->pcdata->alias_text[i] );
	    ch->pcdata->alias_name[i] = NULL;
	    ch->pcdata->alias_text[i] = NULL;
	    send_to_char( "Alias removed.\n\r", ch );
	}
	else
	    send_to_char( "No alias by that name.\n\r", ch );
	return;
    }
    free_slot = i < MAX_PALIAS ? i : -1;
    if ( free_slot < 0 )
    {
	for ( i = 0; i < MAX_PALIAS; i++ )
	    if ( !ch->pcdata->alias_name[i] )
	    {
		free_slot = i;
		break;
	    }
    }
    if ( free_slot < 0 )
    {
	send_to_char( "Alias list is full.\n\r", ch );
	return;
    }
    if ( ch->pcdata->alias_name[free_slot] )
    {
	STRFREE( ch->pcdata->alias_name[free_slot] );
	STRFREE( ch->pcdata->alias_text[free_slot] );
    }
    ch->pcdata->alias_name[free_slot] = STRALLOC( name );
    ch->pcdata->alias_text[free_slot] = STRALLOC( argument );
    ch_printf( ch, "Alias %s set.\n\r", name );
}

void msdp_update( DESCRIPTOR_DATA *d )
{
    char buf[512];
    char chunk[128];
    int n = 0;
    CHAR_DATA *ch;
    if ( !d || !d->msdp || !d->character )
	return;
    ch = d->original ? d->original : d->character;
    if ( !ch )
	return;
#define ADD(s) do { int L = strlen(s); if ( n + L < (int)sizeof(buf) ) { memcpy(buf+n, s, L); n += L; } } while (0)
    buf[n++] = (char)IAC; buf[n++] = (char)SB; buf[n++] = (char)TELOPT_MSDP;
    buf[n++] = (char)MSDP_VAR; ADD( "HEALTH" );
    buf[n++] = (char)MSDP_VAL; sprintf( chunk, "%d", ch->hit ); ADD( chunk );
    buf[n++] = (char)MSDP_VAR; ADD( "HEALTH_MAX" );
    buf[n++] = (char)MSDP_VAL; sprintf( chunk, "%d", ch->max_hit ); ADD( chunk );
    buf[n++] = (char)MSDP_VAR; ADD( "MOVEMENT" );
    buf[n++] = (char)MSDP_VAL; sprintf( chunk, "%d", ch->move ); ADD( chunk );
    buf[n++] = (char)MSDP_VAR; ADD( "MOVEMENT_MAX" );
    buf[n++] = (char)MSDP_VAL; sprintf( chunk, "%d", ch->max_move ); ADD( chunk );
    if ( ch->in_room )
    {
	buf[n++] = (char)MSDP_VAR; ADD( "ROOM_NAME" );
	buf[n++] = (char)MSDP_VAL; ADD( ch->in_room->name );
	buf[n++] = (char)MSDP_VAR; ADD( "ROOM_VNUM" );
	buf[n++] = (char)MSDP_VAL; sprintf( chunk, "%d", ch->in_room->vnum ); ADD( chunk );
    }
    buf[n++] = (char)IAC; buf[n++] = (char)SE;
    write_to_descriptor( d->descriptor, buf, n );
#undef ADD
}

void msdp_negotiate( DESCRIPTOR_DATA *d, unsigned char cmd, unsigned char opt )
{
    if ( opt != TELOPT_MSDP )
	return;
    if ( cmd == DO )
	d->msdp = 1;
    else if ( cmd == DONT )
	d->msdp = 0;
}
