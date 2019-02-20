#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"

#define BFS_MARK         BV01

extern int		top_exit;
extern int		top_ed;
extern int		top_affect;
extern int		cur_qobjs;
extern int		cur_qchars;
extern CHAR_DATA *	gch_prev;
extern OBJ_DATA  *	gobj_prev;
CHAR_DATA	*cur_char;
ROOM_INDEX_DATA	*cur_room;
bool		 cur_char_died;
ch_ret		 global_retcode;

int		 cur_obj;
int		 cur_obj_serial;
bool		 cur_obj_extracted;
obj_ret		 global_objcode;

bool is_wizvis( CHAR_DATA *ch , CHAR_DATA *victim );

OBJ_DATA *group_object( OBJ_DATA *obj1, OBJ_DATA *obj2 );

void room_explode( OBJ_DATA *obj , CHAR_DATA *xch, ROOM_INDEX_DATA *room );
void room_explode_1( OBJ_DATA *obj , CHAR_DATA *xch, ROOM_INDEX_DATA *room , int blast );
void room_explode_2( ROOM_INDEX_DATA *room , int blast );

void  explode( OBJ_DATA *obj )
{
            if ( obj->armed_by )
    	    {
    	        ROOM_INDEX_DATA *room;
    	        CHAR_DATA *xch;
    	        bool held = FALSE;

    	        for ( xch = first_char; xch; xch = xch->next )
    	           if ( !IS_NPC( xch ))
/* && nifty_is_name( obj->armed_by, xch->name ) Temp removed to see what happens*/ 
    	           {
    	               if ( obj->carried_by == xch)
	               {
    	                   act( AT_WHITE, "$p EXPLODES in $n's hands!", obj->carried_by, obj, NULL, TO_ROOM );
	                   act( AT_WHITE, "$p EXPLODES in your hands!", obj->carried_by, obj, NULL, TO_CHAR );
	                   room = xch->in_room;
	                   held = TRUE;
	               }
	               else if ( obj->in_room )
	                   room = obj->in_room;
	               else 
	                   room = NULL;

	               if ( room )
	               {
    	                      if ( !held && room->first_person )
    	                          act( AT_WHITE, "$p EXPLODES!", room->first_person , obj, NULL, TO_ROOM );
	                      room_explode( obj , xch, room );
			      break;
	               }
    	           }           
    	    }
            make_scraps(obj);
}

void room_explode( OBJ_DATA *obj, CHAR_DATA *xch, ROOM_INDEX_DATA *room )
{
            int blast;
            blast = (int) (obj->value[1] / 500) ;
	    room_explode_1( obj , xch, room , blast );
	    room_explode_2( room , blast );
	    
}

void room_explode_1( OBJ_DATA *obj , CHAR_DATA *xch, ROOM_INDEX_DATA *room , int blast )
{
          CHAR_DATA *rch;
	  CHAR_DATA *rnext;
	  OBJ_DATA  *robj;
          OBJ_DATA  *robj_next;
          int dam;
    	  if ( IS_SET( room->room_flags, BFS_MARK ) )
    	     return;
    	  
    	  SET_BIT( room->room_flags , BFS_MARK );
          echo_to_room(AT_WHITE, room, "The shockwave from a massive explosion rips through your body!");    	                        
    	  for ( rch = room->first_person ; rch ;  rch = rnext )
    	  {  
    	                           rnext = rch->next_in_room;
    	                           //'act( AT_WHITE, "The shockwave from a massive explosion rips through your body!", room->first_person , obj, NULL, TO_ROOM );
    	                           
    	                           dam = number_range ( obj->value[0] , obj->value[1] );
    	                           damage( rch, rch , dam, TYPE_UNDEFINED, FALSE );
    	                           if ( !char_died(rch) )
    	                           {
    	                            if ( IS_NPC( rch ) )
                                    {
      				      if ( IS_SET( rch->act , ACT_SENTINEL ) )
      				      {
         				rch->was_sentinel = rch->in_room;
         				REMOVE_BIT( rch->act, ACT_SENTINEL );
      				      }
				      if(obj->item_type != ITEM_SHIPBOMB)
				      {
      			 	      start_hating( rch , xch );
      			 	      start_hunting( rch , xch );
				      }
   			            }
   			           } 
                                }
    	                    
    	  for ( robj = room->first_content; robj; robj = robj_next )        
          {        
                                   robj_next = robj->next_content;        
                                   if ( robj != obj && robj->item_type != ITEM_SPACECRAFT && robj->item_type != ITEM_SCRAPS 
                                   && robj->item_type != ITEM_CORPSE_NPC && robj->item_type != ITEM_CORPSE_PC && robj->item_type != ITEM_DROID_CORPSE)
                                     make_scraps( robj );        
           }        
                            
           /* other rooms */          
           {
                   EXIT_DATA *pexit;
    	                        
    	            for ( pexit = room->first_exit; pexit; pexit = pexit->next )
                    {
		           if ( pexit->to_room
		           &&   pexit->to_room != room )
	    		   {	
	    		        if ( blast > 0 )
	    		        {
	    		            int roomblast;
	    		            roomblast = blast - 1;
	    		            room_explode_1( obj , xch, pexit->to_room , roomblast );
	                        }
	                        else
	    		       	    echo_to_room( AT_WHITE, pexit->to_room , "You hear a loud EXPLOSION not to far from here." );          
    		           }
    		    }
           }
    	                
}

void room_explode_2( ROOM_INDEX_DATA *room , int blast )
{

    	  if ( !IS_SET( room->room_flags, BFS_MARK ) )
    	     return;
    	  
    	  REMOVE_BIT( room->room_flags , BFS_MARK );
    	                        
          if ( blast > 0 ) 
          {
                   int roomblast;
                   EXIT_DATA *pexit;
    	                        
    	            for ( pexit = room->first_exit; pexit; pexit = pexit->next )
                    {
		           if ( pexit->to_room
		           &&   pexit->to_room != room )
	    		   {	
	    		            roomblast = blast - 1;
	    		            room_explode_2( pexit->to_room , roomblast );
    		           }
    		    }
           }
    	                
}

bool is_wizvis( CHAR_DATA *ch , CHAR_DATA *victim )
{
    if ( !IS_NPC(victim)
    &&   IS_SET(victim->act, PLR_WIZINVIS)
    &&   get_trust( ch ) < victim->pcdata->wizinvis )
	return FALSE;
	
    return TRUE;
}

/*
 * Return how much exp a char has
 */
int get_exp( CHAR_DATA *ch , int ability )
{
    if ( ability >= MAX_ABILITY || ability < 0 )
      return 0;
    
    return ch->experience;
}

/*
 * Calculate roughly how much experience a character is worth
 */
int get_exp_worth( CHAR_DATA *ch )
{
    int exp;

    exp = ch->top_level * 50;
    exp += ch->max_hit * 2;
    exp -= (ch->armor-50) * 2;
    exp += ( ch->barenumdie * ch->baresizedie + GET_DAMROLL(ch) ) * 50;
    exp += GET_HITROLL(ch) * ch->top_level * 10;
    if ( IS_AFFECTED(ch, AFF_SANCTUARY) )
      exp += exp * 1.5;
    exp = URANGE( MIN_EXP_WORTH, exp, MAX_EXP_WORTH );

    return exp;
}

/*								-Thoric
 * Return how much experience is required for ch to get to a certain level
 */
int exp_level( sh_int level)
{
   int lvl;

   lvl = UMAX(0, level - 1);
  
   return ( lvl * lvl * 500 );
}

/*
 * Get what level ch is based on exp
 */
sh_int level_exp( CHAR_DATA *ch, int exp )
{
    int x, lastx, y, tmp;

    x = LEVEL_SUPREME;
    lastx = x;
    y = 0;
    while ( !y )
    {
	tmp = exp_level( x);
	lastx = x;
	if ( tmp > exp )
	  x /= 2;
	else
	if (lastx != x )
	  x += ( x / 2 );
	else
	  y = x;
    }
    if ( y < 1 )
      y = 1;
    if ( y > LEVEL_SUPREME )
      y = LEVEL_SUPREME;
    return y;
}

/*
 * Retrieve a character's trusted level for permission checking.
 */
sh_int get_trust( CHAR_DATA *ch )
{
    if ( !ch )
       return 0;

    if ( ch->desc ) 
      if ( ch->desc->original )
	ch = ch->desc->original;

    if ( ch->trust != 0 )
	return ch->trust;

    if ( IS_NPC(ch) && ch->top_level >= LEVEL_AVATAR )
	return LEVEL_AVATAR;

    if ( ch->top_level >= LEVEL_NEOPHYTE && IS_RETIRED( ch ) )
      return LEVEL_NEOPHYTE;

    return ch->top_level;
}


/*
 * Retrieve a character's age.
 */
sh_int get_age( CHAR_DATA *ch )
{
  if( !IS_NPC(ch) && ch->pcdata->age == IS_CHILD )
    return 8 + ( ch->played + (current_time - ch->logon) ) / 14400;
  else
    return 17 + ( ch->played + (current_time - ch->logon) ) / 14400;
}


/*
   get_curr_xxx have been changed to alot for stat bonuses, even
   after trained to max. If you feel this is incorrect, change
   at will.
   Old Format Was:

   sh_int get_curr_str( CHAR_DATA *ch )
   {
       sh_int max;

       max  = 20 + race_table[ch->race].str_plus;
       max = UMIN(max,25);
       return URANGE( 3, ch->perm_str + ch->mod_str, max );
   }
*/

/*
 * Retrieve character's current strength.
 */
sh_int get_curr_str( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_str + ch->mod_str, 25 );
}



/*
 * Retrieve character's current intelligence.
 */
sh_int get_curr_int( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_int + ch->mod_int, 25 );
}

/*
 * Retrieve character's current wisdom.
 */
sh_int get_curr_wis( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_wis + ch->mod_wis, 25 );
}



/*
 * Retrieve character's current dexterity.
 */
sh_int get_curr_dex( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_dex + ch->mod_dex, 25 );
}



/*
 * Retrieve character's current constitution.
 */
sh_int get_curr_con( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_con + ch->mod_con, 25 );
}

/*
 * Retrieve character's current charisma.
 */
sh_int get_curr_cha( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_cha + ch->mod_cha, 25 );
}

/*
 * Retrieve character's current luck.
 */
sh_int get_curr_lck( CHAR_DATA *ch )
{
    return URANGE( 3, ch->perm_lck + ch->mod_lck, 25 );
}

/* Not changed for obvious reasons */
sh_int get_curr_frc( CHAR_DATA *ch )
{
    sh_int max;

    max  = 20;
    max = UMIN(max,25);
            
    return URANGE( 0 , ch->perm_frc + ch->mod_frc, max );
}


/*
 * Retrieve a character's carry capacity.
 * Vastly reduced (finally) due to containers		-Thoric
 */
int can_carry_n( CHAR_DATA *ch )
{
    int penalty = 0;

    if ( !IS_NPC(ch) && get_trust(ch) >= LEVEL_IMMORTAL )
	return get_trust(ch)*200;

    if ( IS_NPC(ch) && IS_SET(ch->act, ACT_PET) )
	return 0;

    if ( get_eq_char(ch, WEAR_WIELD) )
      ++penalty;
    if ( get_eq_char(ch, WEAR_DUAL_WIELD) )
      ++penalty;
    if ( get_eq_char(ch, WEAR_MISSILE_WIELD) )
      ++penalty;
    if ( get_eq_char(ch, WEAR_HOLD) )
      ++penalty;
    if ( get_eq_char(ch, WEAR_SHIELD) )
      ++penalty;
    return URANGE(5, (ch->top_level+15)/5 + get_curr_dex(ch)-13 - penalty, 20);
}



/*
 * Retrieve a character's carry capacity.
 */
int can_carry_w( CHAR_DATA *ch )
{
    if ( !IS_NPC(ch) && get_trust(ch) >= LEVEL_IMMORTAL )
	return 1000000;

    if ( IS_NPC(ch) && IS_SET(ch->act, ACT_PET) )
	return 0;

    return str_app[get_curr_str(ch)].carry;
}


/*
 * See if a player/mob can take a piece of prototype eq		-Thoric
 */
bool can_take_proto( CHAR_DATA *ch )
{
  if ( IS_IMMORTAL(ch) )
    return TRUE;
  else
  if ( IS_NPC(ch) && IS_SET(ch->act, ACT_PROTOTYPE) )
    return TRUE;
  else
    return FALSE;
}


/*
 * See if a string is one of the names of an object.
 */
bool is_name( const char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];

    for ( ; ; )
    {
	namelist = one_argument( namelist, name );
	if ( name[0] == '\0' )
	    return FALSE;
	if ( !str_cmp( str, name ) )
	    return TRUE;
    }
}

bool is_name_prefix( const char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];

    for ( ; ; )
    {
	namelist = one_argument( namelist, name );
	if ( name[0] == '\0' )
	    return FALSE;
	if ( !str_prefix( str, name ) )
	    return TRUE;
    }
}

/*
 * See if a string is one of the names of an object.		-Thoric
 * Treats a dash as a word delimiter as well as a space
 */
bool is_name2( const char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];

    for ( ; ; )
    {
	namelist = one_argument2( namelist, name );
	if ( name[0] == '\0' )
	    return FALSE;
	if ( !str_cmp( str, name ) )
	    return TRUE;
    }
}

bool is_name2_prefix( const char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];

    for ( ; ; )
    {
	namelist = one_argument2( namelist, name );
	if ( name[0] == '\0' )
	    return FALSE;
	if ( !str_prefix( str, name ) )
	    return TRUE;
    }
}

/*								-Thoric
 * Checks if str is a name in namelist supporting multiple keywords
 */
bool nifty_is_name( char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];
    
    if ( !str || str[0] == '\0' )
      return FALSE;
 
    for ( ; ; )
    {
	str = one_argument2( str, name );
	if ( name[0] == '\0' )
	    return TRUE;
	if ( !is_name2( name, namelist ) )
	    return FALSE;
    }
}

bool nifty_is_name_prefix( char *str, char *namelist )
{
    char name[MAX_INPUT_LENGTH];
    
    if ( !str || str[0] == '\0' )
      return FALSE;
 
    for ( ; ; )
    {
	str = one_argument2( str, name );
	if ( name[0] == '\0' )
	    return TRUE;
	if ( !is_name2_prefix( name, namelist ) )
	    return FALSE;
    }
}

/*
 * Apply or remove an affect to a character.
 */
void affect_modify( CHAR_DATA *ch, AFFECT_DATA *paf, bool fAdd )
{
    OBJ_DATA *wield;
    int mod;
    struct skill_type *skill;
    ch_ret retcode;

    mod = paf->modifier;

    if ( fAdd )
    {
	SET_BIT( ch->affected_by, paf->bitvector );
    }
    else
    {
	REMOVE_BIT( ch->affected_by, paf->bitvector );
	/*
	 * might be an idea to have a duration removespell which returns
	 * the spell after the duration... but would have to store
	 * the removed spell's information somewhere...		-Thoric
	 */
	if ( (paf->location % REVERSE_APPLY) == APPLY_REMOVESPELL )
	  return;
	switch( paf->location % REVERSE_APPLY )
	{
	  case APPLY_AFFECT:        REMOVE_BIT( ch->affected_by, mod );	return;
	  case APPLY_RESISTANT:     REMOVE_BIT( ch->resistant, mod );	return;
	  case APPLY_IMMUNE:        REMOVE_BIT( ch->immune, mod );	return;
	  case APPLY_SUSCEPTIBLE:   REMOVE_BIT( ch->susceptible, mod );	return;
	  case APPLY_WEARSPELL:	    /* affect only on wear */		return;
	  case APPLY_REMOVE:	    SET_BIT( ch->affected_by, mod );	return;
	}
	mod = 0 - mod;
    }

    switch ( paf->location % REVERSE_APPLY )
    {
    default:
	bug( "Affect_modify: unknown location %d.", paf->location );
	return;

    case APPLY_NONE:						break;
    case APPLY_STR:           ch->mod_str		+= mod;	break;
    case APPLY_DEX:           ch->mod_dex		+= mod;	break;
    case APPLY_INT:           ch->mod_int		+= mod;	break;
    case APPLY_WIS:           ch->mod_wis		+= mod;	break;
    case APPLY_CON:	      ch->mod_con		+= mod;	break;
    case APPLY_CHA:	      ch->mod_cha		+= mod; break;
    case APPLY_LCK:	      ch->mod_lck		+= mod; break;
    case APPLY_SEX:
	ch->sex = (ch->sex+mod) % 3;
	if ( ch->sex < 0 )
	  ch->sex += 2;
	ch->sex = URANGE( 0, ch->sex, 2 );
	break;
    case APPLY_INJURY:	      ch->skill_level[TREAT_INJURY] +=mod; break;
    case APPLY_AGE:						break;
    case APPLY_HEIGHT:	      ch->height		+= mod;	break;
    case APPLY_WEIGHT:	      ch->weight		+= mod;	break;
    case APPLY_MANA:          ch->max_mana		+= mod;	break;
    case APPLY_HIT:           ch->max_hit		+= mod;	break;
    case APPLY_MOVE:          ch->max_move		+= mod;	break;
    case APPLY_GOLD:						break;
    case APPLY_EXP:						break;
    case APPLY_AC:            ch->armor			+= mod;	break;
    case APPLY_HITROLL:       ch->hitroll		+= mod;	break;
    case APPLY_DAMROLL:       ch->damroll		+= mod;	break;
    case APPLY_FORT: 	      ch->fortitude		+= mod;	break;
    case APPLY_REFL:          ch->reflexes		+= mod;	break;
    case APPLY_WILL:  	      ch->willpower		+= mod;	break;
    case APPLY_SAVING_SPELL:  ch->saving_spell_staff	+= mod;	break;
    case APPLY_AFFECT:        SET_BIT( ch->affected_by, mod );	break;
    case APPLY_RESISTANT:     SET_BIT( ch->resistant, mod );	break;
    case APPLY_IMMUNE:        SET_BIT( ch->immune, mod );	break;
    case APPLY_SUSCEPTIBLE:   SET_BIT( ch->susceptible, mod );	break;
    case APPLY_WEAPONSPELL:	/* see fight.c */		break;
    case APPLY_REMOVE:	      REMOVE_BIT(ch->affected_by, mod);	break;

    case APPLY_FULL:
	if ( !IS_NPC(ch) )
	    ch->pcdata->condition[COND_FULL] =
		URANGE( 0, ch->pcdata->condition[COND_FULL] + mod, 48 );
	break;

    case APPLY_THIRST:
	if ( !IS_NPC(ch) )
	    ch->pcdata->condition[COND_THIRST] =
		URANGE( 0, ch->pcdata->condition[COND_THIRST] + mod, 48 );
	break;

    case APPLY_DRUNK:
	if ( !IS_NPC(ch) )
	    ch->pcdata->condition[COND_DRUNK] =
		URANGE( 0, ch->pcdata->condition[COND_DRUNK] + mod, 48 );
	break;

    case APPLY_MENTALSTATE:
	ch->mental_state	= URANGE(-100, ch->mental_state + mod, 100);
	break;
    case APPLY_EMOTION:
	ch->emotional_state	= URANGE(-100, ch->emotional_state + mod, 100);
	break;

    case APPLY_STRIPSN:
	if ( IS_VALID_SN(mod) )
	  affect_strip( ch, mod );
	else
	  bug( "affect_modify: APPLY_STRIPSN invalid sn %d", mod );
	break;

/* spell cast upon wear/removal of an object	-Thoric */
    case APPLY_WEARSPELL:
    case APPLY_REMOVESPELL:
	if ( IS_SET(ch->in_room->room_flags, ROOM_NO_MAGIC)
	||   IS_SET(ch->immune, RIS_MAGIC)
	||   saving_char == ch		/* so save/quit doesn't trigger */
	||   loading_char == ch )	/* so loading doesn't trigger */
	   return;

	mod = abs(mod);
	if ( IS_VALID_SN(mod)
	&&  (skill=skill_table[mod]) != NULL
	&&   skill->type == SKILL_SPELL )
	   if ( (retcode=(*skill->spell_fun) ( mod, 0, ch, ch )) == rCHAR_DIED
	   ||   char_died(ch) )
	      return;
	break;


/* skill apply types	-Thoric */

    case APPLY_TRACK:   /* needs to be replaced */		break;
    case APPLY_HIDE:
	if ( !IS_NPC(ch) )
	  ch->skill_level[HIDE_SKILL] = UMAX( 0, ch->skill_level[HIDE_SKILL] + mod ); 
	break;
    case APPLY_SLEIGHT:
	if ( !IS_NPC(ch) )
	  ch->skill_level[SLEIGHT_OF_HAND] = UMAX( 0, ch->skill_level[SLEIGHT_OF_HAND] + mod );
	break;
    case APPLY_SNEAK:
	if ( !IS_NPC(ch) )
	  ch->skill_level[MOVE_SILENTLY] = UMAX( 0, ch->skill_level[MOVE_SILENTLY] + mod );
	break;
    case APPLY_DISABLE:
	if ( !IS_NPC(ch) )
	  ch->skill_level[DISABLE_DEVICE] = UMAX( 0, ch->skill_level[DISABLE_DEVICE] + mod );
	break;
    case APPLY_LISTEN:
	if ( !IS_NPC(ch) )
	  ch->skill_level[LISTEN_SKILL] = UMAX( 0, ch->skill_level[LISTEN_SKILL] + mod );
	break;
    case APPLY_WILLPOWER:
	if ( !IS_NPC(ch) )
	  ch->willpower = UMAX( 0, ch->willpower + mod );
	break;
    case APPLY_SPOT:
	if ( !IS_NPC(ch) )
	  ch->skill_level[SPOT_SKILL] = UMAX( 0, ch->skill_level[SPOT_SKILL] + mod );
	break;
    case APPLY_SEARCH:
	if ( !IS_NPC(ch) )
	  ch->skill_level[SEARCH_SKILL] = UMAX( 0, ch->skill_level[SEARCH_SKILL] + mod );
	break;
    case APPLY_CLIMB:
	if ( !IS_NPC(ch) )
	  ch->skill_level[CLIMB_SKILL] = UMAX( 0, ch->skill_level[CLIMB_SKILL] + mod );
	break;
    }

    /*
     * Check for weapon wielding.
     * Guard against recursion (for weapons with affects).
     */
    if ( !IS_NPC( ch )
    &&   saving_char != ch
    && ( wield = get_eq_char( ch, WEAR_WIELD ) ) != NULL
    &&   get_obj_weight(wield) > str_app[get_curr_str(ch)].wield )
    {
	static int depth;

	if ( depth == 0 )
	{
	    depth++;
	    act( AT_ACTION, "You are too weak to wield $p any longer.", 
		ch, wield, NULL, TO_CHAR );
	    act( AT_ACTION, "$n stops wielding $p.", ch, wield, NULL, TO_ROOM );
	    unequip_char( ch, wield );
	    depth--;
	}
    }

    return;
}



/*
 * Give an affect to a char.
 */
void affect_to_char( CHAR_DATA *ch, AFFECT_DATA *paf )
{
    AFFECT_DATA *paf_new;

    if ( !ch )
    {
      bug( "Affect_to_char: NULL ch!", 0 );
      return;
    }

    if ( !paf )
    {
      bug( "Affect_to_char: NULL paf!", 0 );
      return;
    }

    CREATE( paf_new, AFFECT_DATA, 1 );
    LINK( paf_new, ch->first_affect, ch->last_affect, next, prev );
    paf_new->type	= paf->type;
    paf_new->duration	= paf->duration;
    paf_new->location	= paf->location;
    paf_new->modifier	= paf->modifier;
    paf_new->bitvector	= paf->bitvector;

    affect_modify( ch, paf_new, TRUE );
    return;
}


/*
 * Remove an affect from a char.
 */
void affect_remove( CHAR_DATA *ch, AFFECT_DATA *paf )
{
    if ( !ch->first_affect )
    {
	bug( "Affect_remove: no affect.", 0 );
	return;
    }

    affect_modify( ch, paf, FALSE );

    UNLINK( paf, ch->first_affect, ch->last_affect, next, prev );
    DISPOSE( paf );
    return;
}

/*
 * Strip all affects of a given sn.
 */
void affect_strip( CHAR_DATA *ch, int sn )
{
    AFFECT_DATA *paf;
    AFFECT_DATA *paf_next;

    for ( paf = ch->first_affect; paf; paf = paf_next )
    {
	paf_next = paf->next;
	if ( paf->type == sn )
	    affect_remove( ch, paf );
    }

    return;
}



/*
 * Return true if a char is affected by a spell.
 */
bool is_affected( CHAR_DATA *ch, int sn )
{
    AFFECT_DATA *paf;

    for ( paf = ch->first_affect; paf; paf = paf->next )
	if ( paf->type == sn )
	    return TRUE;

    return FALSE;
}


/*
 * Add or enhance an affect.
 * Limitations put in place by Thoric, they may be high... but at least
 * they're there :)
 */
void affect_join( CHAR_DATA *ch, AFFECT_DATA *paf )
{
    AFFECT_DATA *paf_old;

    for ( paf_old = ch->first_affect; paf_old; paf_old = paf_old->next )
	if ( paf_old->type == paf->type )
	{
	    paf->duration = UMIN( 1000000, paf->duration + paf_old->duration );
	    if ( paf->modifier )
		paf->modifier = UMIN( 5000, paf->modifier + paf_old->modifier );
	    else
	        paf->modifier = paf_old->modifier;
	    affect_remove( ch, paf_old );
	    break;
	}

    affect_to_char( ch, paf );
    return;
}


/*
 * Move a char out of a room.
 */
void char_from_room( CHAR_DATA *ch )
{
    OBJ_DATA *obj;

    if ( !ch )
    {
	bug( "Char_from_room: NULL char.", 0 );
	return;
    }

    if ( !ch->in_room )
    {
	bug( "Char_from_room: NULL room: %s", ch->name );
	return;
    }


    if ( ( obj = get_eq_char( ch, WEAR_LIGHT ) ) != NULL
    &&   obj->item_type == ITEM_LIGHT
    &&   obj->value[2] != 0
    &&   ch->in_room->light > 0 )
	--ch->in_room->light;

    UNLINK( ch, ch->in_room->first_person, ch->in_room->last_person,
		next_in_room, prev_in_room );
    ch->in_room      = NULL;
    ch->next_in_room = NULL;
    ch->prev_in_room = NULL;

    if ( !IS_NPC(ch)
    &&   get_timer( ch, TIMER_SHOVEDRAG ) > 0 )
	remove_timer( ch, TIMER_SHOVEDRAG );

    return;
}


/*
 * Move a char into a room.
 */
void char_to_room( CHAR_DATA *ch, ROOM_INDEX_DATA *pRoomIndex )
{
    OBJ_DATA *obj;

    if ( !ch )
    {
	bug( "Char_to_room: NULL ch!", 0 );
	return;
    }
    if ( !pRoomIndex )
    {
	char buf[MAX_STRING_LENGTH];

	sprintf( buf, "Char_to_room: %s -> NULL room!  Putting char in limbo (%d)",
		ch->name, ROOM_VNUM_LIMBO );
	bug( buf, 0 );
        /* This used to just return, but there was a problem with crashing
           and I saw no reason not to just put the char in limbo. -Narn */
        pRoomIndex = get_room_index( ROOM_VNUM_LIMBO );
    }

    ch->in_room		= pRoomIndex;
    LINK( ch, pRoomIndex->first_person, pRoomIndex->last_person,
    	      next_in_room, prev_in_room );


    if ( ( obj = get_eq_char( ch, WEAR_LIGHT ) ) != NULL
    &&   obj->item_type == ITEM_LIGHT
    &&   obj->value[2] != 0 )
	++ch->in_room->light;

    if ( !IS_NPC(ch)
    &&    IS_SET(ch->in_room->room_flags, ROOM_SAFE)
    &&    get_timer(ch, TIMER_SHOVEDRAG) <= 0 )
       add_timer( ch, TIMER_SHOVEDRAG, 10, NULL, 0 );  /*-30 Seconds-*/

    return;
}

/*
 * Give an obj to a char.
 */
OBJ_DATA *obj_to_char( OBJ_DATA *obj, CHAR_DATA *ch )
{
    OBJ_DATA *otmp;
    OBJ_DATA *oret = obj;
    bool skipgroup, grouped;
    int oweight = get_obj_weight( obj );
    int onum = get_obj_number( obj );
    int wear_loc = obj->wear_loc;

    skipgroup = FALSE;
    grouped = FALSE;

    if (IS_OBJ_STAT( obj, ITEM_PROTOTYPE ) )
    {
	if (!IS_IMMORTAL( ch ) 
	&& (IS_NPC(ch) && !IS_SET(ch->act, ACT_PROTOTYPE)) )
	  return obj_to_room( obj, ch->in_room );
    }

    if ( loading_char == ch )
    {
	int x,y;
	for ( x = 0; x < MAX_WEAR; x++ )
	  for ( y = 0; y < MAX_LAYERS; y++ )
	    if ( save_equipment[x][y] == obj )
	    {
		skipgroup = TRUE;
		break;
	    }
    }

    if ( !skipgroup )
      for ( otmp = ch->first_carrying; otmp; otmp = otmp->next_content )
	if ( (oret=group_object( otmp, obj )) == otmp )
	{
	    grouped = TRUE;
	    break;
	}

    if ( !grouped )
    {
	LINK( obj, ch->first_carrying, ch->last_carrying, next_content, prev_content );
	obj->carried_by	 		= ch;
	obj->in_room	 		= NULL;
	obj->in_obj	 		= NULL;
    }
    if (wear_loc == WEAR_NONE)
    {
	ch->carry_number	+= onum;
	ch->carry_weight	+= oweight;
    }
  
    return (oret ? oret : obj);
}



/*
 * Take an obj from its character.
 */
void obj_from_char( OBJ_DATA *obj )
{
    CHAR_DATA *ch;

    if ( ( ch = obj->carried_by ) == NULL )
    {
	bug( "Obj_from_char: null ch.", 0 );
	return;
    }

    if ( obj->wear_loc != WEAR_NONE )
	unequip_char( ch, obj );

    /* obj may drop during unequip... */
    if ( !obj->carried_by )
      return;

    UNLINK( obj, ch->first_carrying, ch->last_carrying, next_content, prev_content );

    if ( IS_OBJ_STAT( obj, ITEM_COVERING ) && obj->first_content )
	empty_obj( obj, NULL, NULL );

    obj->in_room	 = NULL;
    obj->carried_by	 = NULL;
    ch->carry_number	-= get_obj_number( obj );
    ch->carry_weight	-= get_obj_weight( obj );
    return;
}


/*
 * Find the ac value of an obj, including position effect.
 */
int apply_ac( OBJ_DATA *obj, int iWear )
{
    if ( obj->item_type != ITEM_ARMOR )
	return 0;

    switch ( iWear )
    {
    case WEAR_BODY:	return 3 * obj->value[0];
    case WEAR_HEAD:	return 2 * obj->value[0];
    case WEAR_LEGS:	return 2 * obj->value[0];
    case WEAR_FEET:	return     obj->value[0];
    case WEAR_HANDS:	return     obj->value[0];
    case WEAR_ARMS:	return     obj->value[0];
    case WEAR_SHIELD:	return     obj->value[0];
    case WEAR_FINGER_L:	return     obj->value[0];
    case WEAR_FINGER_R: return     obj->value[0];
    case WEAR_NECK_1:	return     obj->value[0];
    case WEAR_NECK_2:	return     obj->value[0];
    case WEAR_ABOUT:	return 2 * obj->value[0];
    case WEAR_WAIST:	return     obj->value[0];
    case WEAR_WRIST_L:	return     obj->value[0];
    case WEAR_WRIST_R:	return     obj->value[0];
    case WEAR_HOLD:	return     obj->value[0];
    case WEAR_EYES:	return	   obj->value[0];
    case WEAR_BACK:	return	   obj->value[0];
    }

    return 0;
}



/*
 * Find a piece of eq on a character.
 * Will pick the top layer if clothing is layered.		-Thoric
 */
OBJ_DATA *get_eq_char( CHAR_DATA *ch, int iWear )
{
    OBJ_DATA *obj, *maxobj = NULL;

    for ( obj = ch->first_carrying; obj; obj = obj->next_content )
	if ( obj->wear_loc == iWear ){
	    if ( !obj->pIndexData->layers )
		return obj;
	    else
	    if ( !maxobj
	    ||    obj->pIndexData->layers > maxobj->pIndexData->layers )
		maxobj = obj;
        }

    return maxobj;
}



/*
 * Equip a char with an obj.
 */
void equip_char( CHAR_DATA *ch, OBJ_DATA *obj, int iWear )
{
    AFFECT_DATA *paf;
    OBJ_DATA	*otmp;

    if ( (otmp=get_eq_char( ch, iWear )) != NULL
    &&   (!otmp->pIndexData->layers || !obj->pIndexData->layers) )
    {
	bug( "Equip_char: already equipped (%s, %d).", ch->name, iWear );
	return;
    }

    separate_obj(obj);	/* just in case */
    if ( ( IS_OBJ_STAT(obj, ITEM_ANTI_NEUTRAL) && IS_NEUTRAL(ch) ) )
    {
	/*
	 * Thanks to Morgenes for the bug fix here!
	 */
	if ( loading_char != ch )
	{
	   act( AT_MAGIC, "You are zapped by $p and drop it.", ch, obj, NULL, TO_CHAR );
	   act( AT_MAGIC, "$n is zapped by $p and drops it.",  ch, obj, NULL, TO_ROOM );
	}
	if ( obj->carried_by )
	   obj_from_char( obj );
	obj_to_room( obj, ch->in_room );
//	oprog_zap_trigger( ch, obj);
	if ( IS_SET(sysdata.save_flags, SV_ZAPDROP) && !char_died(ch) )
	    save_char_obj( ch );
	return;
    }

    ch->armor      	+= apply_ac( obj, iWear );
    obj->wear_loc	 = iWear;

    ch->carry_number	-= get_obj_number( obj );

    for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
	affect_modify( ch, paf, TRUE );
    for ( paf = obj->first_affect; paf; paf = paf->next )
	affect_modify( ch, paf, TRUE );

    if ( obj->item_type == ITEM_LIGHT
    &&   obj->value[2] != 0
    &&   ch->in_room )
	++ch->in_room->light;

    return;
}



/*
 * Unequip a char with an obj.
 */
void unequip_char( CHAR_DATA *ch, OBJ_DATA *obj )
{
    AFFECT_DATA *paf;

    if ( obj->wear_loc == WEAR_NONE )
    {
	bug( "Unequip_char: already unequipped.", 0 );
	return;
    }

    ch->carry_number	+= get_obj_number( obj );

    ch->armor		+= apply_ac( obj, obj->wear_loc );
    obj->wear_loc	 = -1;

    for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
	affect_modify( ch, paf, FALSE );
    if ( obj->carried_by )
      for ( paf = obj->first_affect; paf; paf = paf->next )
	affect_modify( ch, paf, FALSE );

    if ( !obj->carried_by )
      return;

    if ( obj->item_type == ITEM_LIGHT
    &&   obj->value[2] != 0
    &&   ch->in_room
    &&   ch->in_room->light > 0 )
	--ch->in_room->light;

    return;
}



/*
 * Count occurrences of an obj in a list.
 */
int count_obj_list( OBJ_INDEX_DATA *pObjIndex, OBJ_DATA *list )
{
    OBJ_DATA *obj;
    int nMatch;

    nMatch = 0;
    for ( obj = list; obj; obj = obj->next_content )
	if ( obj->pIndexData == pObjIndex )
	    nMatch++;

    return nMatch;
}



/*
 * Move an obj out of a room.
 */
void	write_corpses	args( ( CHAR_DATA *ch, char *name ) );

int falling;

void obj_from_room( OBJ_DATA *obj )
{
    ROOM_INDEX_DATA *in_room;

    if ( ( in_room = obj->in_room ) == NULL )
    {
	bug( "obj_from_room: NULL.", 0 );
	return;
    }

    UNLINK( obj, in_room->first_content, in_room->last_content,
    		 next_content, prev_content );

    if ( IS_OBJ_STAT( obj, ITEM_COVERING ) && obj->first_content )
	empty_obj( obj, NULL, obj->in_room );

    if (obj->item_type == ITEM_FIRE)
	  obj->in_room->light -= obj->count;

    obj->carried_by   = NULL;
    obj->in_obj	      = NULL;
    obj->in_room      = NULL;
    if ( obj->pIndexData->vnum == OBJ_VNUM_CORPSE_PC && falling == 0 )
      write_corpses( NULL, obj->short_descr+14 );
    return;
}


/*
 * Move an obj into a room.
 */
OBJ_DATA *obj_to_room( OBJ_DATA *obj, ROOM_INDEX_DATA *pRoomIndex )
{
    OBJ_DATA *otmp, *oret;
    sh_int count = obj->count;
    sh_int item_type = obj->item_type;

    for ( otmp = pRoomIndex->first_content; otmp; otmp = otmp->next_content )
	if ( (oret=group_object( otmp, obj )) == otmp )
	{
	    if (item_type == ITEM_FIRE)
	      pRoomIndex->light += count;
	    return oret;
	}

    LINK( obj, pRoomIndex->first_content, pRoomIndex->last_content,
    	       next_content, prev_content );
    obj->in_room				= pRoomIndex;
    obj->carried_by				= NULL;
    obj->in_obj					= NULL;
    if (item_type == ITEM_FIRE)
      pRoomIndex->light += count;
    falling++;
    obj_fall( obj, FALSE );
    falling--;
    if ( obj->pIndexData->vnum == OBJ_VNUM_CORPSE_PC && falling == 0 )
      write_corpses( NULL, obj->short_descr+14 );
    return obj;
}



/*
 * Move an object into an object.
 */
OBJ_DATA *obj_to_obj( OBJ_DATA *obj, OBJ_DATA *obj_to )
{
    OBJ_DATA *otmp, *oret;

    if ( obj == obj_to )
    {
	bug( "Obj_to_obj: trying to put object inside itself: vnum %d", obj->pIndexData->vnum );
	return obj;
    }
    /* Big carry_weight bug fix here by Thoric */
    if ( obj->carried_by != obj_to->carried_by )
    {
       if ( obj->carried_by )
	 obj->carried_by->carry_weight -= get_obj_weight( obj );
       if ( obj_to->carried_by )
	 obj_to->carried_by->carry_weight += get_obj_weight( obj );
    }

    for ( otmp = obj_to->first_content; otmp; otmp = otmp->next_content )
	if ( (oret=group_object( otmp, obj )) == otmp )
	    return oret;

    LINK( obj, obj_to->first_content, obj_to->last_content,
    	       next_content, prev_content );
    obj->in_obj				 = obj_to;
    obj->in_room			 = NULL;
    obj->carried_by			 = NULL;

    return obj;
}


/*
 * Move an object out of an object.
 */
void obj_from_obj( OBJ_DATA *obj )
{
    OBJ_DATA *obj_from;

    if ( ( obj_from = obj->in_obj ) == NULL )
    {
	bug( "Obj_from_obj: null obj_from.", 0 );
	return;
    }

    UNLINK( obj, obj_from->first_content, obj_from->last_content,
    		 next_content, prev_content );

    if ( IS_OBJ_STAT( obj, ITEM_COVERING ) && obj->first_content )
	empty_obj( obj, obj->in_obj, NULL );

    obj->in_obj       = NULL;
    obj->in_room      = NULL;
    obj->carried_by   = NULL;

    for ( ; obj_from; obj_from = obj_from->in_obj )
	if ( obj_from->carried_by )
	    obj_from->carried_by->carry_weight -= get_obj_weight( obj );

    return;
}



/*
 * Extract an obj from the world.
 */
void extract_obj( OBJ_DATA *obj )
{
    OBJ_DATA *obj_content;

    if ( !obj )
    {
	bug( "extract_obj: !obj" );
	return;
    }

    if ( obj_extracted(obj) )
    {
	bug( "extract_obj: obj %d already extracted!", obj->pIndexData->vnum );
	return;
    }

    if ( obj->item_type == ITEM_PORTAL )
      remove_portal( obj );

    if ( obj->carried_by )
	obj_from_char( obj );
    else
    if ( obj->in_room )
	obj_from_room( obj );
    else
    if ( obj->in_obj )
	obj_from_obj( obj );

    while ( ( obj_content = obj->last_content ) != NULL )
      extract_obj( obj_content );

    {
	AFFECT_DATA *paf;
	AFFECT_DATA *paf_next;

	for ( paf = obj->first_affect; paf; paf = paf_next )
	{
	    paf_next    = paf->next;
	    DISPOSE( paf );
	}
	obj->first_affect = obj->last_affect = NULL;
    }

    {
	EXTRA_DESCR_DATA *ed;
	EXTRA_DESCR_DATA *ed_next;

	for ( ed = obj->first_extradesc; ed; ed = ed_next )
	{
	    ed_next = ed->next;
	    STRFREE( ed->description );
	    STRFREE( ed->keyword     );
	    DISPOSE( ed );
	}
	obj->first_extradesc = obj->last_extradesc = NULL;
    }

    if ( obj == gobj_prev )
      gobj_prev		= obj->prev;

    UNLINK( obj, first_object, last_object, next, prev );
    /* shove onto extraction queue */
    queue_extracted_obj( obj );

    obj->pIndexData->count -= obj->count;
    numobjsloaded -= obj->count;
    --physicalobjects;
    if ( obj->serial == cur_obj )
    {
	cur_obj_extracted = TRUE;
	if ( global_objcode == rNONE )
	  global_objcode = rOBJ_EXTRACTED;
    }
    return;
}



/*
 * Extract a char from the world.
 */
void extract_char( CHAR_DATA *ch, bool fPull )
{
    CHAR_DATA *wch;
    OBJ_DATA *obj;
    char buf[MAX_STRING_LENGTH];
    ROOM_INDEX_DATA *location;

    if ( !ch )
    {
    	bug( "Extract_char: NULL ch.", 0 );
	return;		/* who removed this line? */
    }

    if ( !ch->in_room )
    {
	bug( "Extract_char: NULL room.", 0 );
	return;
    }

    if ( ch == supermob )
    {
	bug( "Extract_char: ch == supermob!", 0 );
	return;
    }

    if ( char_died(ch) )
    {
	sprintf( buf, "extract_char: %s already died!", ch->name );
	bug( buf, 0 );
	return;
    }

    if ( ch == cur_char )
      cur_char_died = TRUE;
    /* shove onto extraction queue */
    queue_extracted_char( ch, fPull );

    if ( gch_prev == ch )
      gch_prev = ch->prev;

    if ( fPull && !IS_SET(ch->act, ACT_POLYMORPHED))
	die_follower( ch );

    stop_fighting( ch, TRUE );

    if ( ch->mount )
    {
	REMOVE_BIT( ch->mount->act, ACT_MOUNTED );
	ch->mount = NULL;
	ch->position = POS_STANDING;
    }

    if (IS_SET(ch->in_room->room_flags2, ROOM_ARENA))
    {
        ch->hit = ch->max_hit;
        ch->mana = ch->max_mana;
        ch->move = ch->max_move;
    }

    if ( IS_NPC(ch) && IS_SET( ch->act, ACT_MOUNTED ) )
	for ( wch = first_char; wch; wch = wch->next )
	   if ( wch->mount == ch )
	   {
		wch->mount = NULL;
		wch->position = POS_STANDING;
	   }

    REMOVE_BIT( ch->act, ACT_MOUNTED );

    REMOVE_BIT( ch->affected_by, AFF_SANCTUARY);

    while ( (obj = ch->last_carrying) != NULL )
	extract_obj( obj );

    char_from_room( ch );

    if ( !fPull )
    {
	location = NULL;

	if ( !location )
  	  location = get_room_index( wherehome( ch ) );

	if ( !location )
	  location = get_room_index( 1 );

	char_to_room( ch, location );

	act( AT_MAGIC, "$n appears from some strange swirling mists!", ch, NULL, NULL, TO_ROOM );
        ch->position = POS_RESTING;
	return;
    }

    if ( IS_NPC(ch) )
    {
	--ch->pIndexData->count;
	--nummobsloaded;
    }

    if ( ch->desc && ch->desc->original )
	do_return( ch, "" );

    for ( wch = first_char; wch; wch = wch->next )
	if ( wch->reply == ch )
	    wch->reply = NULL;

    UNLINK( ch, first_char, last_char, next, prev );

    if ( ch->desc ){
	if ( ch->desc->character != ch )
	    bug( "Extract_char: char's descriptor points to another char", 0 );
	else
	{
	    ch->desc->character = NULL;
	    close_socket( ch->desc, FALSE );
	    ch->desc = NULL;
	}
    }
    return;
}


/*
 * Find a char in the room.
 */
CHAR_DATA *get_char_room( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char fix[MAX_STRING_LENGTH];
    CHAR_DATA *rch;
    int number, count, vnum;

    number = number_argument( argument, arg );
    if ( !str_cmp( arg, "self" ) )
	return ch;

    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    count  = 0;

    for ( rch = ch->in_room->first_person; rch; rch = rch->next_in_room )
	{
		if(ch == rch)  continue;
		sprintf(fix, "__%s", rch->name);
	 if ( (can_see( ch, rch ) && (nifty_is_name(arg, PERS(rch, ch)) || !str_cmp(arg, fix)))
	    ||  (IS_NPC(rch) && vnum == rch->pIndexData->vnum) || (IS_NPC(ch) && (nifty_is_name(arg, rch->name))) || (IS_NPC(rch) && nifty_is_name(arg, rch->name)))
	 {
	    if ( number == 0 && !IS_NPC(rch) )
		return rch;
	    else
	    if ( ++count == number )
		return rch;
	 }
    }

    if ( vnum != -1 )
	return NULL;

    /* If we didn't find an exact match, run through the list of characters
       again looking for prefix matching, ie gu == guard.
       Added by Narn, Sept/96
    */
    count  = 0;
    for ( rch = ch->in_room->first_person; rch; rch = rch->next_in_room )
    {
	if ( !can_see( ch, rch ) || !nifty_is_name_prefix(arg, PERS(rch, ch)) || ch == rch || (IS_NPC(ch) && (!nifty_is_name_prefix(arg, rch->name))))
	    continue;
	if ( number == 0 && !IS_NPC(rch) )
	    return rch;
	else
	if ( ++count == number )
	    return rch;
    }

    return NULL;
}




/*
 * Find a char in the world.
 */
CHAR_DATA *get_char_world( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *wch;
    int number, count, vnum;

    number = number_argument( argument, arg );
    count  = 0;
    if ( !str_cmp( arg, "self" ) )
	return ch;

    /*
     * Allow reference by vnum for saints+			-Thoric
     */
    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    /* check the room for an exact match */
    for ( wch = ch->in_room->first_person; wch; wch = wch->next_in_room )
	if ( (nifty_is_name( arg, PERS(wch, ch) ) || 
		(IS_NPC(ch) && (nifty_is_name(arg, wch->name)))
		||  (IS_NPC(wch) && vnum == wch->pIndexData->vnum))
		 && is_wizvis(ch,wch))	
	{
	    if ( number == 0 && !IS_NPC(wch) )
		return wch;
	    else
	    if ( ++count == number )
		return wch;
	}

    count = 0;

    /* check the world for an exact match */
    for ( wch = first_char; wch; wch = wch->next )
	if ( (nifty_is_name( arg, PERS(wch, ch) ) || (IS_NPC(ch) && (nifty_is_name(arg, wch->name)))
	||  (IS_NPC(wch) && vnum == wch->pIndexData->vnum)) && is_wizvis(ch,wch) )
	{
	    if ( number == 0 && !IS_NPC(wch) )
		return wch;
	    else
	    if ( ++count == number  )
		return wch;
	}

    /* bail out if looking for a vnum match */
    if ( vnum != -1 )
	return NULL;

    /*
     * If we didn't find an exact match, check the room for
     * for a prefix match, ie gu == guard.
     * Added by Narn, Sept/96
     */
    count  = 0;
    for ( wch = ch->in_room->first_person; wch; wch = wch->next_in_room )
    {
	if ( !nifty_is_name_prefix( arg, PERS(wch, ch) ) || (IS_NPC(ch) && (!nifty_is_name_prefix(arg, wch->name))) )
	    continue;
	if ( number == 0 && !IS_NPC(wch) && is_wizvis(ch,wch))
	    return wch;
	else
	if ( ++count == number  && is_wizvis(ch, wch) )
	    return wch;
    }

    /*
     * If we didn't find a prefix match in the room, run through the full list
     * of characters looking for prefix matching, ie gu == guard.
     * Added by Narn, Sept/96
     */
    count  = 0;
    for ( wch = first_char; wch; wch = wch->next )
    {
	if ( !nifty_is_name_prefix( arg, PERS(wch, ch) ) || (IS_NPC(ch) && (!nifty_is_name(arg, wch->name))))
	    continue;
	if ( number == 0 && !IS_NPC(wch) && is_wizvis(ch, wch) )
	    return wch;
	else
	if ( ++count == number  && is_wizvis(ch, wch) )
	    return wch;
    }

    return NULL;
}

/* Find a character by name, no PERS */
CHAR_DATA *get_char_world_ooc( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *wch;
    int number, count, vnum;

    number = number_argument( argument, arg );
    count  = 0;
    if ( !str_cmp( arg, "self" ) )
	return ch;

    /*
     * Allow reference by vnum for saints+			-Thoric
     */
    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    /* check the room for an exact match */
    for ( wch = ch->in_room->first_person; wch; wch = wch->next_in_room )
	if ( (nifty_is_name( arg, wch->name ) || 
		(IS_NPC(ch) && (nifty_is_name(arg, wch->name)))
		||  (IS_NPC(wch) && vnum == wch->pIndexData->vnum))
		 && is_wizvis(ch,wch))	
	{
	    if ( number == 0 && !IS_NPC(wch) )
		return wch;
	    else
	    if ( ++count == number )
		return wch;
	}

    count = 0;

    /* check the world for an exact match */
    for ( wch = first_char; wch; wch = wch->next )
	if ( (nifty_is_name( arg, wch->name ) || (IS_NPC(ch) && (nifty_is_name(arg, wch->name)))
	||  (IS_NPC(wch) && vnum == wch->pIndexData->vnum)) && is_wizvis(ch,wch) )
	{
	    if ( number == 0 && !IS_NPC(wch) )
		return wch;
	    else
	    if ( ++count == number  )
		return wch;
	}

    /* bail out if looking for a vnum match */
    if ( vnum != -1 )
	return NULL;

    /*
     * If we didn't find an exact match, check the room for
     * for a prefix match, ie gu == guard.
     * Added by Narn, Sept/96
     */
    count  = 0;
    for ( wch = ch->in_room->first_person; wch; wch = wch->next_in_room )
    {
	if ( !nifty_is_name_prefix( arg, wch->name ) || (IS_NPC(ch) && (!nifty_is_name_prefix(arg, wch->name))) )
	    continue;
	if ( number == 0 && !IS_NPC(wch) && is_wizvis(ch,wch))
	    return wch;
	else
	if ( ++count == number  && is_wizvis(ch, wch) )
	    return wch;
    }

    /*
     * If we didn't find a prefix match in the room, run through the full list
     * of characters looking for prefix matching, ie gu == guard.
     * Added by Narn, Sept/96
     */
    count  = 0;
    for ( wch = first_char; wch; wch = wch->next )
    {
	if ( !nifty_is_name_prefix( arg, wch->name ) || (IS_NPC(ch) && (!nifty_is_name(arg, wch->name))))
	    continue;
	if ( number == 0 && !IS_NPC(wch) && is_wizvis(ch, wch) )
	    return wch;
	else
	if ( ++count == number  && is_wizvis(ch, wch) )
	    return wch;
    }

    return NULL;
}

/*
 * Find a char by comfreq
 */

CHAR_DATA *get_char_from_comfreq( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *wch;

    if ( !str_cmp( argument, ch->comfreq ) || !str_cmp(argument, "self"))
	return ch;

    /* check mud for matching comfreq, or immortal name */
    for ( wch = first_char; wch; wch = wch->next )
	{
	 if(IS_IMMORTAL(ch))
     {
	   if(nifty_is_name_prefix(argument, wch->name))
		return wch;
     }
	 else
     {
      if( !str_cmp( argument, wch->comfreq ) || (IS_IMMORTAL(wch) && nifty_is_name_prefix(argument, wch->name)) )
	  {
	    if ( !IS_NPC(wch) || (IS_IMMORTAL(wch) && can_see(ch, wch)) )
		return wch;
	  }
	 }
    }

    return NULL;
}


/*
 * Find some object with a given index data.
 * Used by area-reset 'P', 'T' and 'H' commands.
 */
OBJ_DATA *get_obj_type( OBJ_INDEX_DATA *pObjIndex )
{
    OBJ_DATA *obj;

    for ( obj = last_object; obj; obj = obj->prev )
	if ( obj->pIndexData == pObjIndex )
	    return obj;

    return NULL;
}


/*
 * Find an obj in a list.
 */
OBJ_DATA *get_obj_list( CHAR_DATA *ch, char *argument, OBJ_DATA *list )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    int number;
    int count;

    number = number_argument( argument, arg );
    count  = 0;
    for ( obj = list; obj; obj = obj->next_content )
	if ( can_see_obj( ch, obj ) && nifty_is_name( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    /* If we didn't find an exact match, run through the list of objects
       again looking for prefix matching, ie swo == sword.
       Added by Narn, Sept/96
    */
    count = 0;
    for ( obj = list; obj; obj = obj->next_content )
	if ( can_see_obj( ch, obj ) && nifty_is_name_prefix( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    return NULL;
}

/*
 * Find an obj in a list...going the other way			-Thoric
 */
OBJ_DATA *get_obj_list_rev( CHAR_DATA *ch, char *argument, OBJ_DATA *list )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    int number;
    int count;

    number = number_argument( argument, arg );
    count  = 0;
    for ( obj = list; obj; obj = obj->prev_content )
	if ( can_see_obj( ch, obj ) && nifty_is_name( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    /* If we didn't find an exact match, run through the list of objects
       again looking for prefix matching, ie swo == sword.
       Added by Narn, Sept/96
    */
    count = 0;
    for ( obj = list; obj; obj = obj->prev_content )
	if ( can_see_obj( ch, obj ) && nifty_is_name_prefix( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    return NULL;
}



/*
 * Find an obj in player's inventory.
 */
OBJ_DATA *get_obj_carry( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    int number, count, vnum;

    number = number_argument( argument, arg );
    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    count  = 0;
    for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
	if ( obj->wear_loc == WEAR_NONE
	&&   can_see_obj( ch, obj )
	&&  (nifty_is_name( arg, obj->name ) || obj->pIndexData->vnum == vnum) )
	    if ( (count += obj->count) >= number )
		return obj;

    if ( vnum != -1 )
	return NULL;

    /* If we didn't find an exact match, run through the list of objects
       again looking for prefix matching, ie swo == sword.
       Added by Narn, Sept/96
    */
    count = 0;
    for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
	if ( obj->wear_loc == WEAR_NONE
	&&   can_see_obj( ch, obj )
	&&   nifty_is_name_prefix( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    return NULL;
}



/*
 * Find an obj in player's equipment.
 */
OBJ_DATA *get_obj_wear( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    int number, count, vnum;

    if ( !ch )
    {
       bug( "get_obj_wear: null ch" );
    }

    number = number_argument( argument, arg );

    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    count  = 0;
    for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
	if ( obj->wear_loc != WEAR_NONE
	&&   can_see_obj( ch, obj )
	&&  (nifty_is_name( arg, obj->name ) || obj->pIndexData->vnum == vnum) )
	    if ( ++count == number )
		return obj;

    if ( vnum != -1 )
	return NULL;

    /* If we didn't find an exact match, run through the list of objects
       again looking for prefix matching, ie swo == sword.
       Added by Narn, Sept/96
    */
    count = 0;
    for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
	if ( obj->wear_loc != WEAR_NONE
	&&   can_see_obj( ch, obj )
	&&   nifty_is_name_prefix( arg, obj->name ) )
	    if ( ++count == number )
		return obj;

    return NULL;
}



/*
 * Find an obj in the room or in inventory.
 */
OBJ_DATA *get_obj_here( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;

    if ( !ch || !ch->in_room ) 
       return NULL;

    obj = get_obj_list_rev( ch, argument, ch->in_room->last_content );
    if ( obj )
	return obj;

    if ( ( obj = get_obj_carry( ch, argument ) ) != NULL )
	return obj;

    if ( ( obj = get_obj_wear( ch, argument ) ) != NULL )
	return obj;

    return NULL;
}



/*
 * Find an obj in the world.
 */
OBJ_DATA *get_obj_world( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    int number, count, vnum;

    if (!ch)
       return NULL;

    if ( ( obj = get_obj_here( ch, argument ) ) != NULL )
	return obj;

    number = number_argument( argument, arg );

    /*
     * Allow reference by vnum for saints+			-Thoric
     */
    if ( get_trust(ch) >= LEVEL_SAVIOR && is_number( arg ) )
	vnum = atoi( arg );
    else
	vnum = -1;

    count  = 0;
    for ( obj = first_object; obj; obj = obj->next )
	if ( can_see_obj( ch, obj ) && (nifty_is_name( arg, obj->name )
	||   vnum == obj->pIndexData->vnum) )
	    if ( (count += obj->count) >= number )
		return obj;

    /* bail out if looking for a vnum */
    if ( vnum != -1 )
	return NULL;

    /* If we didn't find an exact match, run through the list of objects
       again looking for prefix matching, ie swo == sword.
       Added by Narn, Sept/96
    */
    count  = 0;
    for ( obj = first_object; obj; obj = obj->next )
	if ( can_see_obj( ch, obj ) && nifty_is_name_prefix( arg, obj->name ) )
	    if ( (count += obj->count) >= number )
		return obj;

    return NULL;
}


/*
 * How mental state could affect finding an object		-Thoric
 * Used by get/drop/put/quaff/recite/etc
 * Increasingly freaky based on mental state and drunkeness
 */
bool ms_find_obj( CHAR_DATA *ch )
{
    int ms = ch->mental_state;
    int drunk = IS_NPC(ch) ? 0 : ch->pcdata->condition[COND_DRUNK];
    char *t;

    /*
     * we're going to be nice and let nothing weird happen unless
     * you're a tad messed up
     */
    drunk = UMAX( 1, drunk );
    if ( abs(ms) + (drunk/3) < 30 )
	return FALSE;
    if ( (number_percent() + (ms < 0 ? 15 : 5))> abs(ms)/2 + drunk/4 )
	return FALSE;
    if ( ms > 15 )	/* range 1 to 20 */
	switch( number_range( UMAX(1, (ms/5-15)), (ms+4) / 5 ) )
	{
	    default:
	    case  1: t="As you reach for it, you forgot what it was...\n\r";					break;
	    case  2: t="As you reach for it, something inside stops you...\n\r";				break;
	    case  3: t="As you reach for it, it seems to move out of the way...\n\r";				break;
	    case  4: t="You grab frantically for it, but can't seem to get a hold of it...\n\r";		break;
	    case  5: t="It disappears as soon as you touch it!\n\r";						break;
	    case  6: t="You would if it would stay still!\n\r";							break;
	    case  7: t="Whoa!  It's covered in blood!  Ack!  Ick!\n\r";						break;
	    case  8: t="Wow... trails!\n\r";									break;
	    case  9: t="You reach for it, then notice the back of your hand is growing something!\n\r";		break;
	    case 10: t="As you grasp it, it shatters into tiny shards which bite into your flesh!\n\r";		break;
	    case 11: t="What about that huge dragon flying over your head?!?!?\n\r";				break;
	    case 12: t="You stratch yourself instead...\n\r";							break;
	    case 13: t="You hold the universe in the palm of your hand!\n\r";					break;
	    case 14: t="You're too scared.\n\r";								break;
	    case 15: t="Your mother smacks your hand... 'NO!'\n\r";						break;
	    case 16: t="Your hand grasps the worse pile of revoltingness than you could ever imagine!\n\r";	break;
	    case 17: t="You stop reaching for it as it screams out at you in pain!\n\r";			break;
	    case 18: t="What about the millions of burrow-maggots feasting on your arm?!?!\n\r";		break;
	    case 19: t="That doesn't matter anymore... you've found the true answer to everything!\n\r";	break;
	    case 20: t="A supreme entity has no need for that.\n\r";						break;
	}
    else
    {
	int sub = URANGE(1, abs(ms)/2 + drunk, 60);
	switch( number_range( 1, sub/10 ) )
	{
	    default:
	    case  1: t="In just a second...\n\r";				break;
	    case  2: t="You can't find that...\n\r";					break;
	    case  3: t="It's just beyond your grasp...\n\r";				break;
	    case  4: t="...but it's under a pile of other stuff...\n\r";		break;
	    case  5: t="You go to reach for it, but pick your nose instead.\n\r";	break;
	    case  6: t="Which one?!?  I see two... no three...\n\r";			break;
	}
    }
    send_to_char( t, ch );
    return TRUE;
}


/*
 * Generic get obj function that supports optional containers.	-Thoric
 * currently only used for "eat" and "quaff".
 */
OBJ_DATA *find_obj( CHAR_DATA *ch, char *argument, bool carryonly )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( !str_cmp( arg2, "from" )
    &&   argument[0] != '\0' )
	argument = one_argument( argument, arg2 );

    if ( arg2[0] == '\0' )
    {
	if ( carryonly && ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
	{
	    send_to_char( "You do not have that item.\n\r", ch );
	    return NULL;
	}
	else
	if ( !carryonly && ( obj = get_obj_here( ch, arg1 ) ) == NULL )
	{
	    act( AT_PLAIN, "I see no $T here.", ch, NULL, arg1, TO_CHAR );
	    return NULL;
	}
	return obj;
    }
    else
    {
	OBJ_DATA *container;
	
	if ( carryonly
	&& ( container = get_obj_carry( ch, arg2 ) ) == NULL
	&& ( container = get_obj_wear( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "You do not have that item.\n\r", ch );
	    return NULL;
	}
	if ( !carryonly && ( container = get_obj_here( ch, arg2 ) ) == NULL )
	{
	    act( AT_PLAIN, "I see no $T here.", ch, NULL, arg2, TO_CHAR );
	    return NULL;
	}
	
	if ( !IS_OBJ_STAT(container, ITEM_COVERING )
	&&    IS_SET(container->value[1], CONT_CLOSED) )
	{
	    act( AT_PLAIN, "The $d is closed.", ch, NULL, container->name, TO_CHAR );
	    return NULL;
	}

	obj = get_obj_list( ch, arg1, container->first_content );
	if ( !obj )
	    act( AT_PLAIN, IS_OBJ_STAT(container, ITEM_COVERING) ?
		"I see nothing like that beneath $p." :
		"I see nothing like that in $p.",
		ch, container, NULL, TO_CHAR );
	return obj;
    }
    return NULL;
}

int get_obj_number( OBJ_DATA *obj )
{
    return obj->count;
}


/*
 * Return weight of an object, including weight of contents.
 */
int get_obj_weight( OBJ_DATA *obj )
{
    int weight;

    weight = obj->count * obj->weight;
    for ( obj = obj->first_content; obj; obj = obj->next_content )
	weight += get_obj_weight( obj );

    return weight;
}



/*
 * True if room is dark.
 */
bool room_is_dark( ROOM_INDEX_DATA *pRoomIndex )
{
    if ( !pRoomIndex )
    {
	bug( "room_is_dark: NULL pRoomIndex", 0 );
	return TRUE;
    }

    if ( pRoomIndex->light > 0 )
	return FALSE;

    if ( IS_SET(pRoomIndex->room_flags, ROOM_DARK) )
	return TRUE;

    if ( pRoomIndex->sector_type == SECT_INSIDE
    ||   pRoomIndex->sector_type == SECT_CITY )
	return FALSE;

    if ( weather_info.sunlight == SUN_SET
    ||   weather_info.sunlight == SUN_DARK )
	return TRUE;

    return FALSE;
}



/*
 * True if room is private.
 */
bool room_is_private( CHAR_DATA *ch , ROOM_INDEX_DATA *pRoomIndex )
{
    CHAR_DATA *rch;
    int count;

    if ( !ch )
    {
	bug( "room_is_private: NULL ch", 0 );
      return FALSE; 
    }
    
    if ( !pRoomIndex )
    {
	bug( "room_is_private: NULL pRoomIndex", 0 );
	return FALSE;
    }
    
    if ( IS_SET(pRoomIndex->room_flags, ROOM_PLR_HOME) && ch->plr_home != pRoomIndex)
        return TRUE; 
    
    count = 0;

    for ( rch = pRoomIndex->first_person; rch; rch = rch->next_in_room )
	count++;

    if ( IS_SET(pRoomIndex->room_flags, ROOM_PRIVATE)  && count >= 2 )
	return TRUE;

    if ( IS_SET(pRoomIndex->room_flags, ROOM_SOLITARY) && count >= 1 )
	return TRUE;

    return FALSE;
}



/*
 * True if char can see victim.
 */
bool can_see( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if (!victim)
       return FALSE;

    if ( victim->position == POS_FIGHTING || victim->position < POS_SLEEPING )
       return TRUE;

    if ( !ch )
    {
      if ( IS_AFFECTED(victim, AFF_INVISIBLE)
      ||   IS_AFFECTED(victim, AFF_HIDE)
      ||   IS_SET(victim->act, PLR_WIZINVIS) ) 
	return FALSE;
      else
	return TRUE;
    }

    if ( ch == victim )
	return TRUE;

    if ( !IS_NPC(victim)
    &&   IS_SET(victim->act, PLR_WIZINVIS)
    &&   get_trust( ch ) < victim->pcdata->wizinvis )
	return FALSE;

    if ( victim->position == POS_FIGHTING || victim->position < POS_SLEEPING )
       return TRUE;

    /* SB */
    if ( IS_NPC(victim)   
    &&   IS_SET(victim->act, ACT_MOBINVIS)
    &&   get_trust( ch ) < victim->mobinvis )
        return FALSE;

    if ( !IS_IMMORTAL(ch) && !IS_NPC(victim) && !victim->desc 
    &&    get_timer(victim, TIMER_RECENTFIGHT) > 0
    &&  (!victim->switched || !IS_AFFECTED(victim->switched, AFF_POSSESS)) )
	return FALSE;

    if ( !IS_NPC(ch) && IS_SET(ch->act, PLR_HOLYLIGHT) )
	return TRUE;
	
    /* The miracle cure for blindness? -- Altrag */
    if ( !IS_AFFECTED(ch, AFF_TRUESIGHT) )
    {
	if ( IS_AFFECTED(ch, AFF_BLIND) && !IS_AFFECTED(ch, AFF_DARKVISION) && ( !IS_NPC(ch) && !IS_SET(ch->pcdata->alchemy, ALCHEMY_DARKVISION) ) )
	  return FALSE;

	if ( room_is_dark( ch->in_room ) && !IS_AFFECTED(ch, AFF_INFRARED) )
	  return FALSE;

	if ( IS_AFFECTED(victim, AFF_HIDE)
	&&   !victim->fighting 
	&&   !IS_AFFECTED(ch, AFF_INFRARED))
	  return FALSE;
        
        if ( ch->race == RACE_DEFEL && victim->race == RACE_DEFEL )
          return TRUE;

    }

    return TRUE;
}



/*
 * True if char can see obj.
 */
bool can_see_obj( CHAR_DATA *ch, OBJ_DATA *obj )
{
    int chance;

    if ( !IS_NPC(ch) && IS_SET(ch->act, PLR_HOLYLIGHT) )
	return TRUE;
	
    if ( IS_OBJ_STAT( obj, ITEM_BURRIED ) )
	return FALSE;

    if ( IS_AFFECTED( ch, AFF_TRUESIGHT ) )
        return TRUE;

    if ( IS_AFFECTED( ch, AFF_BLIND ) )
	return FALSE;

    if ( IS_OBJ_STAT(obj, ITEM_HIDDEN) )
	return FALSE;

    if ( obj->item_type == ITEM_LIGHT && obj->value[2] != 0 )
	return TRUE;

    if ( room_is_dark( ch->in_room ) && !IS_AFFECTED(ch, AFF_INFRARED) )
	return FALSE;
    if ( obj->item_type == ITEM_CAMERA )
     {
      int diff=0;
      if( IS_IMMORTAL(ch) )
	  return TRUE;
      if ( obj->value[1] == 1 )
     	diff = 5;
      else if( obj->value[1] == 2 )
	diff = 15;
      else if( obj->value[1] == 3 )
	diff = 25;
      else if( obj->value[1] == 4 )
	diff = 35;
      else 
	diff = 20;
      chance = ( number_range(1, 20) + ch->skill_level[SPOT_SKILL] + stat_table[get_curr_wis(ch)].mod );
      if( chance < diff )
	  return FALSE;
     }

    return TRUE;
}



/*
 * True if char can drop obj.
 */
bool can_drop_obj( CHAR_DATA *ch, OBJ_DATA *obj )
{
    if ( !IS_OBJ_STAT(obj, ITEM_NODROP) )
	return TRUE;

    if ( !IS_NPC(ch) && get_trust(ch) >= LEVEL_IMMORTAL )
	return TRUE;

    if ( IS_NPC(ch) && ch->pIndexData->vnum == 3 )
	return TRUE;

    return FALSE;
}


/*
 * Return ascii name of an item type.
 */
char *item_type_name( OBJ_DATA *obj )
{
    if ( obj->item_type < 1 || obj->item_type > MAX_ITEM_TYPE )
    {
	bug( "Item_type_name: unknown type %d.", obj->item_type );
	return "(unknown)";
    }

    return o_types[obj->item_type];
}



/*
 * Return ascii name of an affect location.
 */
char *affect_loc_name( int location )
{
    switch ( location )
    {
    case APPLY_NONE:		return "none";
    case APPLY_STR:		return "strength";
    case APPLY_DEX:		return "dexterity";
    case APPLY_INT:		return "intelligence";
    case APPLY_WIS:		return "wisdom";
    case APPLY_CON:		return "constitution";
    case APPLY_CHA:		return "charisma";
    case APPLY_LCK:		return "luck";
    case APPLY_SEX:		return "sex";
    case APPLY_INJURY:		return "treat injury";
    case APPLY_AGE:		return "age";
    case APPLY_MANA:		return "mana";
    case APPLY_HIT:		return "hp";
    case APPLY_MOVE:		return "moves";
    case APPLY_GOLD:		return "gold";
    case APPLY_EXP:		return "experience";
    case APPLY_AC:		return "armor class";
    case APPLY_HITROLL:		return "hit roll";
    case APPLY_DAMROLL:		return "damage roll";
    case APPLY_FORT:		return "fortitude";
    case APPLY_REFL:		return "reflexes";
    case APPLY_WILL:		return "willpower";
    case APPLY_SAVING_SPELL:	return "save vs spell";
    case APPLY_HEIGHT:		return "height";
    case APPLY_WEIGHT:		return "weight";
    case APPLY_AFFECT:		return "affected_by";
    case APPLY_RESISTANT:	return "resistant";
    case APPLY_IMMUNE:		return "immune";
    case APPLY_SUSCEPTIBLE:	return "susceptible";
    case APPLY_DISABLE:		return "disable device";
    case APPLY_TRACK:		return "track";
    case APPLY_SLEIGHT:		return "sleight of hand";
    case APPLY_LISTEN:		return "listen";
    case APPLY_SNEAK:		return "sneak";
    case APPLY_HIDE:		return "hide";
    case APPLY_SPOT:		return "spot";
    case APPLY_WILLPOWER:	return "willpower";
    case APPLY_SEARCH:		return "search";
    case APPLY_CLIMB:		return "climb";
    case APPLY_SCRIBE:		return "scribe";
    case APPLY_COVER_TRAIL:	return "cover trail";
    case APPLY_WEAPONSPELL:	return "weapon spell";
    case APPLY_WEARSPELL:	return "wear spell";
    case APPLY_REMOVESPELL:	return "remove spell";
    case APPLY_MENTALSTATE:	return "mental state";
    case APPLY_EMOTION:		return "emotional state";
    case APPLY_STRIPSN:		return "dispel";
    case APPLY_REMOVE:		return "remove";
    case APPLY_FULL:		return "hunger";
    case APPLY_THIRST:		return "thirst";
    case APPLY_DRUNK:		return "drunk";
    case APPLY_BLOOD:		return "blood";
    }

    bug( "Affect_location_name: unknown location %d.", location );
    return "(unknown)";
}



/*
 * Return ascii name of an affect bit vector.
 */
char *affect_bit_name( int vector )
{
    static char buf[512];

    buf[0] = '\0';
    if ( vector & AFF_BLIND         ) strcat( buf, " blind"         );
    if ( vector & AFF_INVISIBLE     ) strcat( buf, " invisible"     );
    if ( vector & AFF_GAS_BREATH    ) strcat( buf, " gas breath"    );
    if ( vector & AFF_DARKVISION    ) strcat( buf, " dark vision"   );
    if ( vector & AFF_COLD_RESIST   ) strcat( buf, " cold resistant");
    if ( vector & AFF_HEAT_RESIST   ) strcat( buf, " heat resistant");
    if ( vector & AFF_FDEFENSE      ) strcat( buf, " force defense" );
    if ( vector & AFF_SANCTUARY     ) strcat( buf, " sanctuary"     );
    if ( vector & AFF_BATTLEMIND    ) strcat( buf, " battlemind"    );
    if ( vector & AFF_INFRARED      ) strcat( buf, " infrared"      );
    if ( vector & AFF_SORCERY       ) strcat( buf, " sith sorcery"  );
    if ( vector & AFF_COVER_TRAIL   ) strcat( buf, " cover trail"   );
    if ( vector & AFF_POISON        ) strcat( buf, " poison"        );
    if ( vector & AFF_MIND          ) strcat( buf, " force mind"    );
    if ( vector & AFF_PARALYSIS     ) strcat( buf, " paralysis"     );
    if ( vector & AFF_SLEEP         ) strcat( buf, " sleep"         );
    if ( vector & AFF_SNEAK         ) strcat( buf, " sneak"         );
    if ( vector & AFF_HIDE          ) strcat( buf, " hide"          );
    if ( vector & AFF_CHARM         ) strcat( buf, " charm"         );
    if ( vector & AFF_POSSESS       ) strcat( buf, " possess"       );
    if ( vector & AFF_FLYING        ) strcat( buf, " flying"        );
    if ( vector & AFF_ENHANCE       ) strcat( buf, " enhance abil"  );
    if ( vector & AFF_FLOATING      ) strcat( buf, " floating"      );
    if ( vector & AFF_TRUESIGHT     ) strcat( buf, " true_sight"    );
    if ( vector & AFF_ENHANCESENSES ) strcat( buf, " enhance senses");
    if ( vector & AFF_FORCE         ) strcat( buf, " call force"    );
    if ( vector & AFF_FEAR          ) strcat( buf, " fear"          );
    if ( vector & AFF_FORCE_RESIST  ) strcat( buf, " force resist"  );
    if ( vector & AFF_POSSESS       ) strcat( buf, " possess"       );
    if ( vector & AFF_RAGE          ) strcat( buf, " rage"          );
    if ( vector & AFF_AQUA_BREATH   ) strcat( buf, " aqua_breath"   );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}



/*
 * Return ascii name of extra flags vector.
 */
char *extra_bit_name( int extra_flags )
{
    static char buf[512];

    buf[0] = '\0';
    if ( extra_flags & ITEM_GLOW         ) strcat( buf, " glow"         );
    if ( extra_flags & ITEM_HUM          ) strcat( buf, " hum"          );
    if ( extra_flags & ITEM_DARK         ) strcat( buf, " dark"         );
    if ( extra_flags & ITEM_HUTT_SIZE    ) strcat( buf, " hutt_size"    );
    if ( extra_flags & ITEM_CONTRABAND   ) strcat( buf, " contraband"   );
    if ( extra_flags & ITEM_INVIS        ) strcat( buf, " invis"        );
    if ( extra_flags & ITEM_RENTED       ) strcat( buf, " rented"       );
    if ( extra_flags & ITEM_NODROP       ) strcat( buf, " nodrop"       );
    if ( extra_flags & ITEM_BLESS        ) strcat( buf, " bless"        );
    if ( extra_flags & ITEM_IMP_CRITICAL ) strcat( buf, " imp critical" );
    if ( extra_flags & ITEM_STUN         ) strcat( buf, " stun"         );
    if ( extra_flags & ITEM_ANTI_NEUTRAL ) strcat( buf, " anti-neutral" );
    if ( extra_flags & ITEM_NOREMOVE     ) strcat( buf, " noremove"     );
    if ( extra_flags & ITEM_INVENTORY    ) strcat( buf, " inventory"    );
    if ( extra_flags & ITEM_DEATHROT	 ) strcat( buf, " deathrot"	);
    if ( extra_flags & ITEM_ANTI_SOLDIER ) strcat( buf, " anti-soldier" );
    if ( extra_flags & ITEM_ANTI_THIEF   ) strcat( buf, " anti-thief"   );
    if ( extra_flags & ITEM_ANTI_HUNTER  ) strcat( buf, " anti-hunter"  );
    if ( extra_flags & ITEM_INSTALLED    ) strcat( buf, " installed"    );
    if ( extra_flags & ITEM_ANTI_SITH    ) strcat( buf, " anti-sith"    );
    if ( extra_flags & ITEM_IGNITED      ) strcat( buf, " ignited"      );
    if ( extra_flags & ITEM_SMALL_SIZE   ) strcat( buf, " small_size"   );
    if ( extra_flags & ITEM_LARGE_SIZE   ) strcat( buf, " large_size"   );
    if ( extra_flags & ITEM_DONATION     ) strcat( buf, " donation"     );
    if ( extra_flags & ITEM_CLANOBJECT   ) strcat( buf, " clan"         );
    if ( extra_flags & ITEM_IMBUED       ) strcat( buf, " imbued"       );
    if ( extra_flags & ITEM_PROTOTYPE    ) strcat( buf, " prototype"    );
    if ( extra_flags & ITEM_HUMAN_SIZE   ) strcat( buf, " human_size"   );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}

/*
 * Return ascii name of magic flags vector. - Scryn
 */
char *magic_bit_name( int magic_flags )
{
    static char buf[512];

    buf[0] = '\0';
    if ( magic_flags & ITEM_RETURNING     ) strcat( buf, " returning"     );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}

/*
 * Set off a trap (obj) upon character (ch)			-Thoric
 */
ch_ret spring_trap( CHAR_DATA *ch, OBJ_DATA *obj )
{
      int dam;
      int typ;
      int lev;
      char *txt;
      char buf[MAX_STRING_LENGTH];
      ch_ret retcode;

      typ = obj->value[1];
      lev = obj->value[2];

      retcode = rNONE;
 
      switch(typ)
      {
       default:
	 txt = "hit by a trap";					break;
       case TRAP_TYPE_POISON_GAS:
	 txt = "surrounded by a green cloud of gas";		break;
       case TRAP_TYPE_POISON_DART:
	 txt = "hit by a dart";					break;
       case TRAP_TYPE_POISON_NEEDLE:
	 txt = "pricked by a needle";				break;
       case TRAP_TYPE_POISON_DAGGER:
	 txt = "stabbed by a dagger";				break;
       case TRAP_TYPE_POISON_ARROW:
	 txt = "struck with an arrow";				break;
       case TRAP_TYPE_BLINDNESS_GAS:
	 txt = "surrounded by a red cloud of gas";		break;
       case TRAP_TYPE_SLEEPING_GAS:
	 txt = "surrounded by a yellow cloud of gas";		break;
       case TRAP_TYPE_FLAME:
	 txt = "struck by a burst of flame";			break;
       case TRAP_TYPE_EXPLOSION:
	 txt = "hit by an explosion";				break;
       case TRAP_TYPE_ACID_SPRAY:
	 txt = "covered by a spray of acid";			break;
       case TRAP_TYPE_ELECTRIC_SHOCK:
	 txt = "suddenly shocked";				break;
       case TRAP_TYPE_BLADE:
	 txt = "sliced by a razor sharp blade";			break;
       case TRAP_TYPE_SEX_CHANGE:
	 txt = "surrounded by a mysterious aura";		break;
      }

      dam = number_range( obj->value[2], obj->value[2] * 2);
      sprintf( buf, "You are %s!", txt );
      act( AT_HITME, buf, ch, NULL, NULL, TO_CHAR );
      sprintf( buf, "$n is %s.", txt );
      act( AT_ACTION, buf, ch, NULL, NULL, TO_ROOM );
      --obj->value[0];
      if ( obj->value[0] <= 0 )
	extract_obj( obj );
      switch(typ)
      {
       default:
       case TRAP_TYPE_POISON_DART:
       case TRAP_TYPE_POISON_NEEDLE:
       case TRAP_TYPE_POISON_DAGGER:
       case TRAP_TYPE_POISON_ARROW:
       case TRAP_TYPE_POISON_GAS:
       case TRAP_TYPE_BLINDNESS_GAS:
       case TRAP_TYPE_SLEEPING_GAS:
       case TRAP_TYPE_ACID_SPRAY:
       case TRAP_TYPE_SEX_CHANGE:
       case TRAP_TYPE_FLAME:
       case TRAP_TYPE_EXPLOSION:
       case TRAP_TYPE_ELECTRIC_SHOCK:
       case TRAP_TYPE_BLADE:
	 break;
      }
      return retcode;
}

/*
 * Check an object for a trap					-Thoric
 */
ch_ret check_for_trap( CHAR_DATA *ch, OBJ_DATA *obj, int flag )
{
  OBJ_DATA *check;
  ch_ret    retcode;

  if ( !obj->first_content )
    return rNONE;

  retcode = rNONE;

  for ( check = obj->first_content; check; check = check->next_content )
    if ( check->item_type == ITEM_TRAP
    &&   IS_SET(check->value[3], flag) )
    {
      retcode = spring_trap( ch, check );
      if ( retcode != rNONE )
	return retcode;
    }
  return retcode;
}

/*
 * Check the room for a trap					-Thoric
 */
ch_ret check_room_for_traps( CHAR_DATA *ch, int flag )
{
    OBJ_DATA *check;
    ch_ret    retcode;
  
    retcode = rNONE;

    if ( !ch )
      return rERROR;
    if ( !ch->in_room || !ch->in_room->first_content )
      return rNONE;
    
    for ( check = ch->in_room->first_content; check; check = check->next_content )
    {
        if ( check->item_type == ITEM_LANDMINE && flag == TRAP_ENTER_ROOM )
        {
            explode (check);
            return rNONE; 
        }
	else if ( check->item_type == ITEM_TRAP
	&&   IS_SET(check->value[3], flag) )
	{
	   retcode = spring_trap( ch, check );
	   if ( retcode != rNONE )
	     return retcode;
	}
    }
    return retcode;
}

/*
 * return TRUE if an object contains a trap			-Thoric
 */
bool is_trapped( OBJ_DATA *obj )
{
    OBJ_DATA *check;

    if ( !obj->first_content )
      return FALSE;

    for ( check = obj->first_content; check; check = check->next_content )
      if ( check->item_type == ITEM_TRAP )
	return TRUE;

    return FALSE;
}

/*
 * If an object contains a trap, return the pointer to the trap	-Thoric
 */
OBJ_DATA *get_trap( OBJ_DATA *obj )
{
    OBJ_DATA *check;

    if ( !obj->first_content )
      return NULL;

    for ( check = obj->first_content; check; check = check->next_content )
      if ( check->item_type == ITEM_TRAP )
	return check;

    return NULL;
}

/*
 * Remove an exit from a room					-Thoric
 */
void extract_exit( ROOM_INDEX_DATA *room, EXIT_DATA *pexit )
{
    UNLINK( pexit, room->first_exit, room->last_exit, next, prev );
    if ( pexit->rexit )
      pexit->rexit->rexit = NULL;
    STRFREE( pexit->keyword );
    STRFREE( pexit->description );
    DISPOSE( pexit );
}

/*
 * Remove a room
 */
void extract_room( ROOM_INDEX_DATA *room )
{
  bug( "extract_room: not implemented", 0 );
  /*
  (remove room from hash table)
  clean_room( room )
  DISPOSE( room );
   */
  return;
}

/*
 * clean out a room (leave list pointers intact )		-Thoric
 */
void clean_room( ROOM_INDEX_DATA *room )
{
   EXTRA_DESCR_DATA	*ed, *ed_next;
   EXIT_DATA		*pexit, *pexit_next;

   STRFREE( room->description );
   STRFREE( room->name );
   for ( ed = room->first_extradesc; ed; ed = ed_next )
   {
	ed_next = ed->next;
	STRFREE( ed->description );
	STRFREE( ed->keyword );
	DISPOSE( ed );
	top_ed--;
   }
   room->first_extradesc	= NULL;
   room->last_extradesc		= NULL;
   for ( pexit = room->first_exit; pexit; pexit = pexit_next )
   {
	pexit_next = pexit->next;
	STRFREE( pexit->keyword );
	STRFREE( pexit->description );
	DISPOSE( pexit );
	top_exit--;
   }
   room->first_exit = NULL;
   room->last_exit = NULL;
   room->room_flags = 0;
   room->sector_type = 0;
   room->light = 0;
}

/*
 * clean out an object (index) (leave list pointers intact )	-Thoric
 */
void clean_obj( OBJ_INDEX_DATA *obj )
{
	AFFECT_DATA *paf;
	AFFECT_DATA *paf_next;
	EXTRA_DESCR_DATA *ed;
	EXTRA_DESCR_DATA *ed_next;

	STRFREE( obj->name );
	STRFREE( obj->short_descr );
	STRFREE( obj->description );
	STRFREE( obj->action_desc );
	obj->item_type		= 0;
	obj->extra_flags	= 0;
	obj->wear_flags		= 0;
	obj->count		= 0;
	obj->weight		= 0;
	obj->cost		= 0;
	obj->value[0]		= 0;
	obj->value[1]		= 0;
	obj->value[2]		= 0;
	obj->value[3]		= 0;
	for ( paf = obj->first_affect; paf; paf = paf_next )
	{
	    paf_next    = paf->next;
	    DISPOSE( paf );
	    top_affect--;
	}
	obj->first_affect	= NULL;
	obj->last_affect	= NULL;
	for ( ed = obj->first_extradesc; ed; ed = ed_next )
	{
	    ed_next		= ed->next;
	    STRFREE( ed->description );
	    STRFREE( ed->keyword     );
	    DISPOSE( ed );
	    top_ed--;
	}
	obj->first_extradesc	= NULL;
	obj->last_extradesc	= NULL;
}

/*
 * clean out a mobile (index) (leave list pointers intact )	-Thoric
 */
void clean_mob( MOB_INDEX_DATA *mob )
{
	MPROG_DATA *mprog, *mprog_next;

	STRFREE( mob->player_name );
	STRFREE( mob->short_descr );
	STRFREE( mob->long_descr  );
	STRFREE( mob->description );
	mob->spec_fun	= NULL;
	mob->spec_2	= NULL;
	mob->pShop	= NULL;
	mob->rShop	= NULL;
	mob->progtypes	= 0;
	
	for ( mprog = mob->mudprogs; mprog; mprog = mprog_next )
	{
	    mprog_next = mprog->next;
	    STRFREE( mprog->arglist );
	    STRFREE( mprog->comlist );
	    DISPOSE( mprog );
	}
	mob->count	 = 0;	   mob->killed		= 0;
	mob->sex	 = 0;	   mob->level	        = 0;
	mob->act	 = 0;	   mob->affected_by	= 0;
	mob->alignment	 = 0;	   mob->mobthac0	= 0;
	mob->ac		 = 0;	   mob->hitnodice	= 0;
	mob->hitsizedice = 0;	   mob->hitplus		= 0;
	mob->damnodice	 = 0;	   mob->damsizedice	= 0;
	mob->damplus	 = 0;	   mob->gold		= 0;
	mob->position	 = 0; 
	mob->defposition = 0;	   mob->height		= 0;
	mob->weight	 = 0;
}

extern int top_reset;

/*
 * Remove all resets from an area				-Thoric
 */
void clean_resets( AREA_DATA *tarea )
{
    RESET_DATA *pReset, *pReset_next;

    for ( pReset = tarea->first_reset; pReset; pReset = pReset_next )
    {
	pReset_next = pReset->next;
	DISPOSE( pReset );
	--top_reset;
    }
    tarea->first_reset	= NULL;
    tarea->last_reset	= NULL;
}

/* no more silliness */
void name_stamp_stats( CHAR_DATA *ch )
{
}

/*
 * "Fix" a character's stats					-Thoric
 */
void fix_char( CHAR_DATA *ch )
{
    AFFECT_DATA *aff;
    OBJ_DATA *carry[MAX_LEVEL*200];
    OBJ_DATA *obj;
    int x, ncarry;

    de_equip_char( ch );

    ncarry = 0;
    while ( (obj=ch->first_carrying) != NULL )
    {
	carry[ncarry++]  = obj;
	obj_from_char( obj );
    }

    for ( aff = ch->first_affect; aff; aff = aff->next )
	affect_modify( ch, aff, FALSE );

    ch->affected_by	= race_table[ch->race].affected;
    ch->mental_state	= 0;
    ch->hit		= UMAX( 1, ch->hit  );
    ch->mana		= UMAX( 1, ch->mana );
    ch->move		= UMAX( 1, ch->move );
    ch->armor		= 10;
    ch->mod_str		= 0;
    ch->mod_dex		= 0;
    ch->mod_wis		= 0;
    ch->mod_int		= 0;
    ch->mod_con		= 0;
    ch->mod_cha		= 0;
    ch->mod_lck		= 0;
    ch->damroll		= 0;
    ch->hitroll		= 0;
    ch->alignment	= URANGE( -1000, ch->alignment, 1000 );
    ch->saving_breath	= 0;
    ch->saving_wand	= 0;
    ch->saving_para_petri = 0;
    ch->saving_spell_staff = 0;
    ch->saving_poison_death = 0;

    ch->carry_weight	= 0;
    ch->carry_number	= 0;

    for ( aff = ch->first_affect; aff; aff = aff->next )
	affect_modify( ch, aff, TRUE );

    for ( x = 0; x < ncarry; x++ )
	obj_to_char( carry[x], ch );

    re_equip_char( ch );
}


/*
 * Show an affect verbosely to a character			-Thoric
 */
void showaffect( CHAR_DATA *ch, AFFECT_DATA *paf )
{
	char buf[MAX_STRING_LENGTH];
	int x;

	if ( !paf )
	{
	    bug( "showaffect: NULL paf", 0 );
	    return;
	}
	if ( paf->location != APPLY_NONE && paf->modifier != 0 )
	{
	    switch( paf->location )
	    {
	      default:
		sprintf( buf, "Affects %s by %d.\n\r",
		  affect_loc_name( paf->location ), paf->modifier );
		break;
	      case APPLY_AFFECT:
		sprintf( buf, "Affects %s by",
		  affect_loc_name( paf->location ) );
		for ( x = 0; x < 32 ; x++ )
		if ( IS_SET( paf->modifier, 1 << x ) )
		{
		  strcat( buf, " " );
		  strcat( buf, a_flags[x] );
		}
		strcat( buf, "\n\r" );
		break;
	      case APPLY_WEAPONSPELL:
	      case APPLY_WEARSPELL:
	      case APPLY_REMOVESPELL:
		sprintf( buf, "Casts spell '%s'\n\r",
			IS_VALID_SN(paf->modifier) ? skill_table[paf->modifier]->name
						   : "unknown" );
		break;
	      case APPLY_RESISTANT:
	      case APPLY_IMMUNE:
	      case APPLY_SUSCEPTIBLE:
		sprintf( buf, "Affects %s by",
		  affect_loc_name( paf->location ) );
		for ( x = 0; x < 32 ; x++ )
		if ( IS_SET( paf->modifier, 1 << x ) )
		{
		  strcat( buf, " " );
		  strcat( buf, ris_flags[x] );
		}
		strcat( buf, "\n\r" );
		break;
	    }
	    send_to_char( buf, ch );
	}
}

/*
 * Set the current global object to obj				-Thoric
 */
void set_cur_obj( OBJ_DATA *obj )
{
    cur_obj = obj->serial;
    cur_obj_extracted = FALSE;
    global_objcode = rNONE;
}

/*
 * Check the recently extracted object queue for obj		-Thoric
 */
bool obj_extracted( OBJ_DATA *obj )
{
    OBJ_DATA *cod;

    if ( !obj )
        return TRUE;
    
    if ( obj->serial == cur_obj
    &&   cur_obj_extracted )
	return TRUE;

    for (cod = extracted_obj_queue; cod; cod = cod->next )
	if ( obj == cod )
	     return TRUE;
    return FALSE;
}

/*
 * Stick obj onto extraction queue
 */
void queue_extracted_obj( OBJ_DATA *obj )
{
    
    ++cur_qobjs;
    obj->next = extracted_obj_queue;
    extracted_obj_queue = obj;
}

/*
 * Clean out the extracted object queue
 */
void clean_obj_queue()
{
    OBJ_DATA *obj;

    while ( extracted_obj_queue )
    {
	obj = extracted_obj_queue;
	extracted_obj_queue = extracted_obj_queue->next;
	STRFREE( obj->name        );
	STRFREE( obj->description );
	STRFREE( obj->short_descr );
	DISPOSE( obj );
	--cur_qobjs;
    }
}

/*
 * Set the current global character to ch			-Thoric
 */
void set_cur_char( CHAR_DATA *ch )
{
    cur_char	   = ch;
    cur_char_died  = FALSE;
    cur_room	   = ch->in_room;
    global_retcode = rNONE;
}

/*
 * Check to see if ch died recently				-Thoric
 */
bool char_died( CHAR_DATA *ch )
{
    EXTRACT_CHAR_DATA *ccd;

    if ( ch == cur_char && cur_char_died )
	return TRUE;

    for (ccd = extracted_char_queue; ccd; ccd = ccd->next )
	if ( ccd->ch == ch )
	     return TRUE;
    return FALSE;
}

/*
 * Add ch to the queue of recently extracted characters		-Thoric
 */
void queue_extracted_char( CHAR_DATA *ch, bool extract )
{
    EXTRACT_CHAR_DATA *ccd;

    if ( !ch )
    {
	bug( "queue_extracted char: ch = NULL", 0 );
	return;
    }
    CREATE( ccd, EXTRACT_CHAR_DATA, 1 );
    ccd->ch			= ch;
    ccd->room			= ch->in_room;
    ccd->extract		= extract;
    if ( ch == cur_char )
      ccd->retcode		= global_retcode;
    else
      ccd->retcode		= rCHAR_DIED;
    ccd->next			= extracted_char_queue;
    extracted_char_queue	= ccd;
    cur_qchars++;
}

/*
 * clean out the extracted character queue
 */
void clean_char_queue()
{
    EXTRACT_CHAR_DATA *ccd;

    for ( ccd = extracted_char_queue; ccd; ccd = extracted_char_queue )
    {
	extracted_char_queue = ccd->next;
	if ( ccd->extract )
	  free_char( ccd->ch );
	DISPOSE( ccd );
	--cur_qchars;
    }
}

/*
 * Add a timer to ch						-Thoric
 * Support for "call back" time delayed commands
 */
void add_timer( CHAR_DATA *ch, sh_int type, sh_int count, DO_FUN *fun, int value )
{
    TIMER *timer;

    for ( timer = ch->first_timer; timer; timer = timer->next )
	if ( timer->type == type )
	{
	   timer->count  = count;
	   timer->do_fun = fun;
	   timer->value	 = value;
	   break;
	}	
    if ( !timer )
    {
	CREATE( timer, TIMER, 1 );
	timer->count	= count;
	timer->type	= type;
	timer->do_fun	= fun;
	timer->value	= value;
	LINK( timer, ch->first_timer, ch->last_timer, next, prev );
    }
}

TIMER *get_timerptr( CHAR_DATA *ch, sh_int type )
{
    TIMER *timer;

    for ( timer = ch->first_timer; timer; timer = timer->next )
      if ( timer->type == type )
        return timer;
    return NULL;
}

sh_int get_timer( CHAR_DATA *ch, sh_int type )
{
    TIMER *timer;

    if ( (timer = get_timerptr( ch, type )) != NULL )
      return timer->count;
    else
      return 0;
}

void extract_timer( CHAR_DATA *ch, TIMER *timer )
{
    if ( !timer )
    {
	bug( "extract_timer: NULL timer", 0 );
	return;
    }

    UNLINK( timer, ch->first_timer, ch->last_timer, next, prev );
    DISPOSE( timer );
    return;
}

void remove_timer( CHAR_DATA *ch, sh_int type )
{
    TIMER *timer;

    for ( timer = ch->first_timer; timer; timer = timer->next )
       if ( timer->type == type )
         break;

    if ( timer )
      extract_timer( ch, timer );
}

bool in_soft_range( CHAR_DATA *ch, AREA_DATA *tarea )
{
  if ( IS_IMMORTAL(ch) )
    return TRUE;
  else
  if ( IS_NPC(ch) )
    return TRUE;
  else
  if ( (tarea) && (ch->top_level >= tarea->low_soft_range || ch->top_level <= tarea->hi_soft_range ))
    return TRUE;
  else
    return FALSE;
}

bool in_hard_range( CHAR_DATA *ch, AREA_DATA *tarea )
{
  if ( IS_IMMORTAL(ch) )
    return TRUE;
  else
  if ( IS_NPC(ch) )
    return TRUE;
  else
  if ( (tarea) && (ch->top_level >= tarea->low_hard_range && ch->top_level <= tarea->hi_hard_range ))
    return TRUE;
  else
    return FALSE;
}


/*
 * Scryn, standard luck check 2/2/96
 */
bool chance( CHAR_DATA *ch, sh_int percent ) 
{
/*  sh_int clan_factor, ms;*/
    sh_int deity_factor, ms;

    if (!ch)
    {
	bug("Chance: null ch!", 0);
	return FALSE;
    }

/* Code for clan stuff put in by Narn, Feb/96.  The idea is to punish clan
members who don't keep their alignment in tune with that of their clan by
making it harder for them to succeed at pretty much everything.  Clan_factor
will vary from 1 to 3, with 1 meaning there is no effect on the player's
change of success, and with 3 meaning they have half the chance of doing
whatever they're trying to do. 

Note that since the neutral clannies can only be off by 1000 points, their
maximum penalty will only be half that of the other clan types.

  if ( IS_CLANNED( ch ) )
    clan_factor = 1 + abs( ch->alignment - ch->pcdata->clan->alignment ) / 1000; 
  else
    clan_factor = 1;
*/
/* Mental state bonus/penalty:  Your mental state is a ranged value with
 * zero (0) being at a perfect mental state (bonus of 10).
 * negative values would reflect how sedated one is, and
 * positive values would reflect how stimulated one is.
 * In most circumstances you'd do best at a perfectly balanced state.
 */
  
    deity_factor = 0;

  ms = 10 - abs(ch->mental_state);

  if ( (number_percent() - get_curr_lck(ch) + 13 - ms) + deity_factor <= 
percent )
    return TRUE;
  else
    return FALSE;
}

bool chance_attrib( CHAR_DATA *ch, sh_int percent, sh_int attrib )
{
/* Scryn, standard luck check + consideration of 1 attrib 2/2/96*/ 
  sh_int  deity_factor;

  if (!ch)
  {
    bug("Chance: null ch!", 0);
    return FALSE;
  }

    deity_factor = 0;

  if (number_percent() - get_curr_lck(ch) + 13 - attrib + 13 + deity_factor <= percent )
    return TRUE;
  else
    return FALSE;

}


/*
 * Make a simple clone of an object (no extras...yet)		-Thoric
 */
OBJ_DATA *clone_object( OBJ_DATA *obj )
{
    OBJ_DATA *clone;

    CREATE( clone, OBJ_DATA, 1 );
    clone->pIndexData	= obj->pIndexData;
    clone->name		= QUICKLINK( obj->name );
    clone->short_descr	= QUICKLINK( obj->short_descr );
    clone->description	= QUICKLINK( obj->description );
    clone->action_desc	= QUICKLINK( obj->action_desc );
    clone->item_type	= obj->item_type;
    clone->extra_flags	= obj->extra_flags;
    clone->magic_flags	= obj->magic_flags;
    clone->wear_flags	= obj->wear_flags;
    clone->wear_loc	= obj->wear_loc;
    clone->weight	= obj->weight;
    clone->cost		= obj->cost;
    clone->level	= obj->level;
    clone->timer	= obj->timer;
    clone->value[0]	= obj->value[0];
    clone->value[1]	= obj->value[1];
    clone->value[2]	= obj->value[2];
    clone->value[3]	= obj->value[3];
    clone->value[4]	= obj->value[4];
    clone->value[5]	= obj->value[5];
    clone->count	= 1;
    ++obj->pIndexData->count;
    ++numobjsloaded;
    ++physicalobjects;
    cur_obj_serial = UMAX((cur_obj_serial + 1 ) & (BV30-1), 1);
    clone->serial = clone->pIndexData->serial = cur_obj_serial;
    LINK( clone, first_object, last_object, next, prev );
    return clone;
}

/*
 * If possible group obj2 into obj1				-Thoric
 * This code, along with clone_object, obj->count, and special support
 * for it implemented throughout handler.c and save.c should show improved
 * performance on MUDs with players that hoard tons of potions and scrolls
 * as this will allow them to be grouped together both in memory, and in
 * the player files.
 */
OBJ_DATA *group_object( OBJ_DATA *obj1, OBJ_DATA *obj2 )
{
    if ( !obj1 || !obj2 )
	return NULL;
    if ( obj1 == obj2 )
	return obj1;

    if ( obj1->pIndexData == obj2->pIndexData
/*
    &&	!obj1->pIndexData->mudprogs
    &&  !obj2->pIndexData->mudprogs
*/
    &&   QUICKMATCH( obj1->name,	obj2->name )
    &&   QUICKMATCH( obj1->short_descr,	obj2->short_descr )
    &&   QUICKMATCH( obj1->description,	obj2->description )
    &&   QUICKMATCH( obj1->action_desc,	obj2->action_desc )
    &&   obj1->item_type	== obj2->item_type
    &&   obj1->extra_flags	== obj2->extra_flags
    &&   obj1->magic_flags	== obj2->magic_flags
    &&   obj1->wear_flags	== obj2->wear_flags
    &&   obj1->wear_loc		== obj2->wear_loc
    &&	 obj1->weight		== obj2->weight
    &&	 obj1->cost		== obj2->cost
    &&   obj1->level		== obj2->level
    &&   obj1->timer		== obj2->timer
    &&	 obj1->value[0]		== obj2->value[0]
    &&	 obj1->value[1]		== obj2->value[1]
    &&	 obj1->value[2]		== obj2->value[2]
    &&	 obj1->value[3]		== obj2->value[3]
    &&	 obj1->value[4]		== obj2->value[4]
    &&	 obj1->value[5]		== obj2->value[5]
    &&	!obj1->first_extradesc  && !obj2->first_extradesc
    &&  !obj1->first_affect	&& !obj2->first_affect
    &&  !obj1->first_content	&& !obj2->first_content )
    {
	obj1->count += obj2->count;
	obj1->pIndexData->count += obj2->count;	/* to be decremented in */
	numobjsloaded += obj2->count;		/* extract_obj */
	extract_obj( obj2 );
	return obj1;
    }
    return obj2;
}

/*
 * Split off a grouped object					-Thoric
 * decreased obj's count to num, and creates a new object containing the rest
 */
void split_obj( OBJ_DATA *obj, int num )
{
    int count;
    OBJ_DATA *rest;

    if (!obj)
        return;

    count =obj->count;
    
    if ( count <= num || num == 0 )
      return;

    rest = clone_object(obj);
    --obj->pIndexData->count;	/* since clone_object() ups this value */
    --numobjsloaded;
    rest->count = obj->count - num;
    obj->count = num;

    if ( obj->carried_by )
    {
	LINK( rest, obj->carried_by->first_carrying,
		   obj->carried_by->last_carrying,
		   next_content, prev_content );
	rest->carried_by	 	= obj->carried_by;
	rest->in_room	 		= NULL;
	rest->in_obj	 		= NULL;
    }
    else
    if ( obj->in_room )
    {
	LINK( rest, obj->in_room->first_content, obj->in_room->last_content,
		    next_content, prev_content );
	rest->carried_by	 	= NULL;
	rest->in_room	 		= obj->in_room;
	rest->in_obj	 		= NULL;
    }
    else
    if ( obj->in_obj )
    {
	LINK( rest, obj->in_obj->first_content, obj->in_obj->last_content,
		    next_content, prev_content );
	rest->in_obj			 = obj->in_obj;
	rest->in_room			 = NULL;
	rest->carried_by		 = NULL;
    }
}

void separate_obj( OBJ_DATA *obj )
{
    split_obj( obj, 1 );
}

/*
 * Empty an obj's contents... optionally into another obj, or a room
 */
bool empty_obj( OBJ_DATA *obj, OBJ_DATA *destobj, ROOM_INDEX_DATA *destroom )
{
    OBJ_DATA *otmp, *otmp_next;
    CHAR_DATA *ch = obj->carried_by;
    bool movedsome = FALSE;

    if ( !obj )
    {
	bug( "empty_obj: NULL obj", 0 );
	return FALSE;
    }
    if ( destobj || (!destroom && !ch && (destobj = obj->in_obj) != NULL) )
    {
	for ( otmp = obj->first_content; otmp; otmp = otmp_next )
	{
	    otmp_next = otmp->next_content;
	    if ( destobj->item_type == ITEM_CONTAINER
	    &&   get_obj_weight( otmp ) + get_obj_weight( destobj )
		 > destobj->value[0] )
		continue;
	    obj_from_obj( otmp );
	    obj_to_obj( otmp, destobj );
	    movedsome = TRUE;
	}
	return movedsome;
    }
    if ( destroom || (!ch && (destroom = obj->in_room) != NULL) )
    {
	for ( otmp = obj->first_content; otmp; otmp = otmp_next )
	{
	    otmp_next = otmp->next_content;
	    if ( ch && (otmp->pIndexData->progtypes & DROP_PROG) && otmp->count > 1 ) 
	    {
		separate_obj( otmp );
		obj_from_obj( otmp );
		if ( !otmp_next )
		  otmp_next = obj->first_content;
	    }
	    else
		obj_from_obj( otmp );
	    otmp = obj_to_room( otmp, destroom );
	    if ( ch )
	    {
		oprog_drop_trigger( ch, otmp );		/* mudprogs */
		if ( char_died(ch) )
		  ch = NULL;
	    }
	    movedsome = TRUE;
	}
	return movedsome;
    }
    if ( ch )
    {
	for ( otmp = obj->first_content; otmp; otmp = otmp_next )
	{
	    otmp_next = otmp->next_content;
	    obj_from_obj( otmp );
	    obj_to_char( otmp, ch );
	    movedsome = TRUE;
	}
	return movedsome;
    }
    bug( "empty_obj: could not determine a destination for vnum %d",
	obj->pIndexData->vnum );
    return FALSE;
}

/*
 * Improve mental state						-Thoric
 */
void better_mental_state( CHAR_DATA *ch, int mod )
{
    int c = URANGE( 0, abs(mod), 20 );
    int con = get_curr_con(ch);

    if( IS_IMMORTAL(ch) )
	return;

    c += number_percent() < con ? 1 : 0;

    if ( ch->mental_state < 0 )
	ch->mental_state = URANGE( -100, ch->mental_state + c, 0 );
    else
    if ( ch->mental_state > 0 )
	ch->mental_state = URANGE( 0, ch->mental_state - c, 100 );
}

/*
 * Deteriorate mental state					-Thoric
 */
void worsen_mental_state( CHAR_DATA *ch, int mod )
{
    int c   = URANGE( 0, abs(mod), 20 );
    int con = get_curr_con(ch);

    if( IS_IMMORTAL(ch) )
	return;

    c -= number_percent() < con ? 1 : 0;
    if ( c < 1 )
	return;

    if ( ch->mental_state < 0 )
	ch->mental_state = URANGE( -100, ch->mental_state - c, 100 );
    else
    if ( ch->mental_state > 0 )
	ch->mental_state = URANGE( -100, ch->mental_state + c, 100 );
    else
	ch->mental_state -= c;
}


/*
 * Add gold to an area's economy				-Thoric
 */
void boost_economy( AREA_DATA *tarea, int gold )
{
    if (!tarea) return;
    while ( gold >= 1000000000 )
    {
    	
	++tarea->high_economy;
	gold -= 1000000000;
    }
    tarea->low_economy += gold;
    while ( tarea->low_economy >= 1000000000 )
    {
	++tarea->high_economy;
	tarea->low_economy -= 1000000000;
    }
}

/*
 * Take gold from an area's economy				-Thoric
 */
void lower_economy( AREA_DATA *tarea, int gold )
{
    while ( gold >= 1000000000 )
    {
	tarea->high_economy -= 1;
	gold -= 1000000000;
    }
    tarea->low_economy -= gold;
    while ( tarea->low_economy < 0 )
    {
	tarea->high_economy -=1;
	tarea->low_economy += 1000000000;
    }
}

/*
 * Check to see if economy has at least this much gold		   -Thoric
 */
bool economy_has( AREA_DATA *tarea, int gold )
{
    int hasgold = ((tarea->high_economy > 0) ? 1 : 0) * 1000000000
		+ tarea->low_economy;

    if ( hasgold >= gold )
	return TRUE;
    return FALSE;
}

/*
 * Used in db.c when resetting a mob into an area		    -Thoric
 * Makes sure mob doesn't get more than 10% of that area's gold,
 * and reduces area economy by the amount of gold given to the mob
 */
void economize_mobgold( CHAR_DATA *mob )
{
    int gold;
    AREA_DATA *tarea;

    /* make sure it isn't way too much */
    mob->gold = UMIN( mob->gold, mob->top_level * mob->top_level * 400 );
    if ( !mob->in_room )
	return;
    tarea = mob->in_room->area;

    gold = ((tarea->high_economy > 0) ? 1 : 0) * 1000000000 + tarea->low_economy;
    mob->gold = URANGE( 0, mob->gold, gold / 10 );
    if ( mob->gold )
	lower_economy( tarea, mob->gold );
}


/*
 * Add another notch on that there belt... ;)
 * Keep track of the last so many kills by vnum			-Thoric
 */
void add_kill( CHAR_DATA *ch, CHAR_DATA *mob )
{
    int x;
    sh_int vnum, track;

    if ( IS_NPC(ch) )
	return;

    if ( !IS_NPC(mob) )
	return;

    vnum = mob->pIndexData->vnum;
    track = URANGE( 2, MAX_KILLTRACK/LEVEL_AVATAR, MAX_KILLTRACK );
    for ( x = 0; x < track; x++ )
	if ( ch->pcdata->killed[x].vnum == vnum )
	{
	    if ( ch->pcdata->killed[x].count < 50 )
		++ch->pcdata->killed[x].count;
	    return;
	}
	else
	if ( ch->pcdata->killed[x].vnum == 0 )
	    break;
    memmove( (char *) ch->pcdata->killed+sizeof(KILLED_DATA),
		ch->pcdata->killed, (track-1) * sizeof(KILLED_DATA) );
    ch->pcdata->killed[0].vnum  = vnum;
    ch->pcdata->killed[0].count = 1;
    if ( track < MAX_KILLTRACK )
	ch->pcdata->killed[track].vnum = 0;
}

/*
 * Return how many times this player has killed this mob	-Thoric
 * Only keeps track of so many (MAX_KILLTRACK), and keeps track by vnum
 */
int times_killed( CHAR_DATA *ch, CHAR_DATA *mob )
{
    int x;
    sh_int vnum, track;

    if ( IS_NPC(ch) )
	return 0;

    if ( !IS_NPC(mob) )
	return 0;

    vnum = mob->pIndexData->vnum;
    track = URANGE( 2, MAX_KILLTRACK/LEVEL_AVATAR, MAX_KILLTRACK );
    for ( x = 0; x < track; x++ )
	if ( ch->pcdata->killed[x].vnum == vnum )
	    return ch->pcdata->killed[x].count;
	else
	if ( ch->pcdata->killed[x].vnum == 0 )
	    break;
    return 0;
}


/*
 * Remove group affects from a character.
 */
void rem_group_affects( CHAR_DATA *ch )
{
    if ( !ch->first_affect )
	return;

//    affect_strip ( ch, gsn_battle_command );

/*
    for(paf = ch->first_affect; paf; paf = paf->next )
    {
      if(paf == AFF_BATTLE_COMMAND)
      {
       affect_modify( ch, paf, FALSE );
       UNLINK( paf, ch->first_affect, ch->last_affect, next, prev );
       DISPOSE( paf );
      }
    }
*/
    return;
}

int GET_AC ( CHAR_DATA *ch )
{
  int ac=0;

  ac = ch->armor;

  if( IS_AWAKE(ch) )
    ac += stat_table[get_curr_dex(ch)].mod;

  return ac;
}

void remove_bodypart( CHAR_DATA *ch, CHAR_DATA *victim, int part )
{
  OBJ_DATA *wield;
  OBJ_DATA *remove;
  int chance;

  if( IS_NPC(victim) || IS_IMMORTAL(victim) )
	return;

  if( !HAS_BODYPART(victim, part) )
   {
      	bug( "&RBUG: remove_bodypart: victim doesn't have boydpart.&w\n\r", 0 );
	return;
   }
  if( part == PART_ARM_R1 || part == PART_ARM_L1 )
   	remove = get_eq_char( victim, WEAR_ARMS );
  if( part == PART_HAND_R1 )
	remove = get_eq_char( victim, WEAR_WIELD );
  if( part == PART_HAND_L1 )
	remove = get_eq_char( victim, WEAR_DUAL_WIELD );
  if( part == PART_LEG_R || part == PART_LEG_L )
	remove = get_eq_char( victim, WEAR_LEGS );
  if( part == PART_EYE_R || part == PART_EYE_L )
	remove = get_eq_char( victim, WEAR_EYES );

  wield = get_eq_char( ch, WEAR_WIELD );
  if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_DUAL_LIGHTSABER || wield->value[3] == WEAPON_VIBRO ) )
   {
    if( part == PART_ARM_R1 || part == PART_ARM_R2 || part == PART_ARM_L1 || part == PART_ARM_L2
     || part == PART_LEG_R || part == PART_LEG_L )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	if( part == PART_LEG_R || part == PART_LEG_L )
	 {
	  act( AT_BLOOD, "With a swift slash, you dismember $N's leg!&w\n\r", ch, NULL, victim, TO_CHAR );
	  act( AT_BLOOD, "With a swift slash, $n dismembers your leg!&w\n\r", ch, NULL, victim, TO_VICT );
	  act( AT_BLOOD, "With a swift slash, $n dismembers $N's leg!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	  return;
	 }
	else
	 {
	  act( AT_BLOOD, "With a swift slash, you dismember $N's arm!&w\n\r", ch, NULL, victim, TO_CHAR );
	  act( AT_BLOOD, "With a swfit slash, $n dismembers your arm!&w\n\r", ch, NULL, victim, TO_VICT );
	  act( AT_BLOOD, "With a swift slash, $n dismembers $N's arm!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	  return;
	 }
       }
     }
    else if ( part == PART_HAND_R1 || part == PART_HAND_L1 || part == PART_HAND_R2 || part == PART_HAND_L2 )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
        REMOVE_BIT(victim->xflags, part);
        act( AT_BLOOD, "With a swift slash, you dismember $N's hand!&w\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_BLOOD, "With a swift slash, $n dismembers your hand!&w\n\r", ch, NULL, victim, TO_VICT );
        act( AT_BLOOD, "With a swift slash, $n dismembers $N's hand!&w\n\r", ch, NULL, victim, TO_NOTVICT );
        return;
       }
     }
    else if ( part == PART_EYE_L || part == PART_EYE_R )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	act( AT_BLOOD, "A well placed slice dismembers $N's eye!&w\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "A well placed slice dismembers your eye!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "A well placed slice by $n dismembers $N's eye!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
       }
     }
   }
  else if( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_BOWCASTER || wield->value[3] == WEAPON_HEAVY ) )
   {
    if( part == PART_ARM_R1 || part == PART_ARM_R2 || part == PART_ARM_L1 || part == PART_ARM_L2
     || part == PART_LEG_R || part == PART_LEG_L )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	if( part == PART_LEG_R || part == PART_LEG_L )
	 {
	  act( AT_BLOOD, "A well aimed blaster shot severs $N's leg!&w\n\r", ch, NULL, victim, TO_CHAR );
	  act( AT_BLOOD, "A well aimed blaster shot severs your leg!&w\n\r", ch, NULL, victim, TO_VICT );
	  act( AT_BLOOD, "A well aimed blaster shot from $n severs $N's leg!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	  return;
	 }
       }
     else
      {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	act( AT_BLOOD, "A well aimed blaster shot severs $N's arm!&w\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "A well aimed blaster shot severs your arm!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "A well aimed blaster shot from $n severs $N's arm!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
       }
      }
     }
    else if ( part == PART_EYE_L || part == PART_EYE_R )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	act( AT_BLOOD, "A well aimed blaster shot has caused $N to lose an eye!&w\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "A well aimed blaster shot has caused you to lose an eye!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "A well aimed blaster shot from $n causes $N to lose an eye!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
       }
     }
   }
  else
   {
    if( part == PART_ARM_R1 || part == PART_ARM_R2 || part == PART_ARM_L1 || part == PART_ARM_L2
     || part == PART_LEG_R || part == PART_LEG_L )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	if( part == PART_LEG_R || part == PART_LEG_L )
	 {
	  act( AT_BLOOD, "With a well placed crush, you dismember $N's leg!&w\n\r", ch, NULL, victim, TO_CHAR );
	  act( AT_BLOOD, "With a well placed crush, $n dismembers your leg!&w\n\r", ch, NULL, victim, TO_VICT );
	  act( AT_BLOOD, "With a well placed crush, $n dismembers $N's leg!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	  return;
	 }
       }
      else
       {
         chance = ( GET_FORT(victim) + number_range(1,20) );
         if( chance < 15 )
          {
	 	REMOVE_BIT(victim->xflags, part);
		act( AT_BLOOD, "With a well placed crush, you dismember $N's arm!&w\n\r", ch, NULL, victim, TO_CHAR );
		act( AT_BLOOD, "With a well placed crush, $n dismembers your arm!&w\n\r", ch, NULL, victim, TO_VICT );
		act( AT_BLOOD, "With a well placed crush, $n dismembers $N's arm!&w\n\r", ch, NULL, victim, TO_NOTVICT );
		return;
          }
       }
     }
    else if ( part == PART_EYE_L || part == PART_EYE_R )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	act( AT_BLOOD, "A well placed crush destroys $N's eye!&w\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "A well placed crush destroys your eye!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "A well placed crush from $n destroys $N's eye!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
       }
     }
    else if ( part == PART_HAND_R1 || part == PART_HAND_L1 || part == PART_HAND_R2 || part == PART_HAND_L2 )
     {
      chance = ( GET_FORT(victim) + number_range(1,20) );
      if( chance < 15 )
       {
	REMOVE_BIT(victim->xflags, part);
	act( AT_BLOOD, "A well placed crush has dismembered $N's hand!&w\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "A well placed crush from $n has dismembered your hand!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "A well placed crush from $n has dismembered $N's hand!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
       }
     }
   }
}    

QUEST_DATA * quest_from_name( CHAR_DATA *ch, char *argument )
{
  QUEST_DATA *quest;

  if( IS_NPC(ch) )
    return NULL;

  for( quest = ch->first_quest; quest; quest = quest->next )
  	if( !str_cmp( quest->name, argument ) )
	  return quest;
  return NULL;
}

int skill_roll( CHAR_DATA *ch, int iSkill )
{
  int x=0;

  if( IS_NPC(ch) )
	return 10;
  if( iSkill < 0 || iSkill > MAX_NSKILL )
   {
	bug( "iSkill out of range.", 0 );
	return 0;
   }
  x = ch->skill_level[iSkill];

  /* Some skills must be known to be able to use */
  if( x == 0 && ( iSkill == ASTROGATE_SKILL || iSkill == DEMOLITIONS_SKILL 
   || iSkill == DISABLE_DEVICE || iSkill == PILOT_SKILL || iSkill == REPAIR_SKILL
   || iSkill == SLEIGHT_OF_HAND || iSkill == TUMBLE_SKILL ) )
	return 0;
  
  /* The "iSkill >= 5 && iSkill <= 20" takes care of all the craft skills */
  if( iSkill == APPRAISE_SKILL || iSkill == COMPUTER_SKILL || iSkill == DEMOLITIONS_SKILL 
   || iSkill == DISABLE_DEVICE || iSkill == REPAIR_SKILL || iSkill == SEARCH_SKILL 
   || iSkill == ASTROGATE_SKILL || ( iSkill >= 5 && iSkill <= 20 ) )
   	x += stat_table[get_curr_int(ch)].mod;

  if( iSkill == BALANCE_SKILL || iSkill == ESCAPE_ARTIST || iSkill == HIDE_SKILL 
   || iSkill == MOVE_SILENTLY || iSkill == RIDE_SKILL || iSkill == SLEIGHT_OF_HAND 
   || iSkill == TUMBLE_SKILL )
	x += stat_table[get_curr_dex(ch)].mod;

  if( iSkill == CLIMB_SKILL || iSkill == SWIM_SKILL )
	x += stat_table[get_curr_str(ch)].mod;

  if( iSkill == DIPLOMACY_SKILL || iSkill == DISGUISE_SKILL || iSkill == GATHER_INFO
   || iSkill == INTIMIDATE_SKILL )
	x += stat_table[get_curr_cha(ch)].mod;

  if( iSkill == GAMBLE_SKILL || iSkill == LISTEN_SKILL || iSkill == SPOT_SKILL
   || iSkill == SURVIVAL_SKILL || iSkill == TREAT_INJURY )
	x += stat_table[get_curr_wis(ch)].mod;

  x += number_range(1,20);

  return x;
}

int fskill_roll( CHAR_DATA *ch, int iSkill )
{
  int x=0;

  if( IS_NPC(ch) )
	return 10;
  if( iSkill < 0 || iSkill > MAX_FSKILL )
   {
	bug( "iSkill out of range, fskill_roll", 0 );
	return 0;
   }

  x = ch->force_level[iSkill];

  /* Some force skills must be known to use */
  if( x == 0 && ( iSkill == BATTLEMIND_SKILL || iSkill == FARSEEING_SKILL
   || iSkill == ILLUSION_SKILL ) )
	return 0;

  if( iSkill == AFFECT_MIND || iSkill == FORCE_DEFENSE || iSkill == FORCE_STEALTH
   || iSkill == HEAL_SELF || iSkill == ILLUSION_SKILL )
	x += stat_table[get_curr_cha(ch)].mod;

  if( iSkill == BATTLEMIND_SKILL || iSkill == DRAIN_ENERGY || iSkill == ENHANCE_ABILITY )
	x += stat_table[get_curr_con(ch)].mod;

  if( iSkill == ENHANCE_SENSES || iSkill == FARSEEING_SKILL || iSkill == FEAR_SKILL
   || iSkill == HEAL_OTHER || iSkill == SEE_FORCE || iSkill == TELEPATHY_SKILL )
   	x += stat_table[get_curr_wis(ch)].mod;

  if( iSkill == FORCE_GRIP || iSkill == FORCE_LIGHTNING || iSkill == FORCE_STRIKE
   || iSkill == MOVE_OBJECT || iSkill == ALCHEMY_SKILL )
  	x += stat_table[get_curr_int(ch)].mod;

  x += number_range(1,20);

  return x;
}

