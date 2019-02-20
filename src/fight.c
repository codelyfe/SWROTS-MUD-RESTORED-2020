#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include "mud.h"

extern char		lastplayercmd[MAX_INPUT_LENGTH];
extern CHAR_DATA *	gch_prev;

/* From Skills.c */
int ris_save( CHAR_DATA *ch, int chance, int ris );

/* From newarena.c */
void lost_arena(CHAR_DATA *ch);

/* From space.c */
void remship(SHIP_DATA *ship);

/* From comm.c */
void    name_log args( ( const char *str, ...) );

/*
 * Local functions.
 */
void	dam_message	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dam,
			    int dt, bool critical ) );
void	death_cry	args( ( CHAR_DATA *ch ) );
void	group_gain	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int	xp_compute	args( ( CHAR_DATA *gch, CHAR_DATA *victim ) );
int	align_compute	args( ( CHAR_DATA *gch, CHAR_DATA *victim ) );
ch_ret	one_hit		args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dt, int mod, bool dual ) );
int	obj_hitroll	args( ( OBJ_DATA *obj ) );
bool    get_cover( CHAR_DATA *ch );
bool	dual_flip = FALSE;


/*
 * Check to see if weapon is poisoned.
 */
bool is_wielding_poisoned( CHAR_DATA *ch )
{
         OBJ_DATA *obj;

         if ( ( obj = get_eq_char( ch, WEAR_WIELD ) 	)
         &&   (IS_SET( obj->extra_flags, ITEM_POISONED) )	)
                  return TRUE;

         return FALSE;

}

/*
 * hunting, hating and fearing code				-Thoric
 */
bool is_hunting( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( !ch->hunting || ch->hunting->who != victim )
      return FALSE;
    
    return TRUE;    
}

bool is_hating( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( !ch->hating || ch->hating->who != victim )
      return FALSE;
    
    return TRUE;    
}

bool is_fearing( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( !ch->fearing || ch->fearing->who != victim )
      return FALSE;
    
    return TRUE;    
}

void stop_hunting( CHAR_DATA *ch )
{
    if ( ch->hunting )
    {
	STRFREE( ch->hunting->name );
	DISPOSE( ch->hunting );
	ch->hunting = NULL;
    }
    return;
}

void stop_hating( CHAR_DATA *ch )
{
    if ( ch->hating )
    {
	STRFREE( ch->hating->name );
	DISPOSE( ch->hating );
	ch->hating = NULL;
    }
    return;
}

void stop_fearing( CHAR_DATA *ch )
{
    if ( ch->fearing )
    {
	STRFREE( ch->fearing->name );
	DISPOSE( ch->fearing );
	ch->fearing = NULL;
    }
    return;
}

void start_hunting( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( ch->hunting )
      stop_hunting( ch );

    CREATE( ch->hunting, HHF_DATA, 1 );
    ch->hunting->name = QUICKLINK( victim->name );
    ch->hunting->who  = victim;
    return;
}

void start_hating( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( ch->hating )
      stop_hating( ch );

    CREATE( ch->hating, HHF_DATA, 1 );
    ch->hating->name = QUICKLINK( victim->name );
    ch->hating->who  = victim;
    return;
}

void start_fearing( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( ch->fearing )
      stop_fearing( ch );

    CREATE( ch->fearing, HHF_DATA, 1 );
    ch->fearing->name = QUICKLINK( victim->name );
    ch->fearing->who  = victim;
    return;
}


int max_fight( CHAR_DATA *ch )
{
    return 8;
}

/*
 * Control the fights going on.
 * Called periodically by update_handler.
 * Many hours spent fixing bugs in here by Thoric, as noted by residual
 * debugging checks.  If you never get any of these error messages again
 * in your logs... then you can comment out some of the checks without
 * worry.
 */
void violence_update( void )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *ch;
    CHAR_DATA *lst_ch;
    CHAR_DATA *victim;
    CHAR_DATA *rch, *rch_next;
    AFFECT_DATA *paf, *paf_next;
    TIMER	*timer, *timer_next;
    ch_ret     retcode;
    SKILLTYPE	*skill;

    lst_ch = NULL;
    for ( ch = last_char; ch; lst_ch = ch, ch = gch_prev )
    {
	set_cur_char( ch );

	if ( ch == first_char && ch->prev )
	{
	   bug( "ERROR: first_char->prev != NULL, fixing...", 0 );
	   ch->prev = NULL;
	}

	gch_prev	= ch->prev;

	if ( gch_prev && gch_prev->next != ch )
	{
	    sprintf( buf, "FATAL: violence_update: %s->prev->next doesn't point to ch.",
		ch->name );
	    bug( buf, 0 );	    
	    bug( "Short-cutting here", 0 );
	    ch->prev = NULL;
	    gch_prev = NULL;
	    do_shout( ch, "Thoric says, 'Prepare for the worst!'" );
	}

	/*
	 * See if we got a pointer to someone who recently died...
	 * if so, either the pointer is bad... or it's a player who
	 * "died", and is back at the healer...
	 * Since he/she's in the char_list, it's likely to be the later...
	 * and should not already be in another fight already
	 */
	if ( char_died(ch) )
	    continue;

	/*
	 * See if we got a pointer to some bad looking data...
	 */
	if ( !ch->in_room || !ch->name )
	{
	    log_string( "violence_update: bad ch record!  (Shortcutting.)" );
	    sprintf( buf, "ch: %d  ch->in_room: %d  ch->prev: %d  ch->next: %d",
	    	(int) ch, (int) ch->in_room, (int) ch->prev, (int) ch->next );
	    log_string( buf );
	    log_string( lastplayercmd );
	    if ( lst_ch )
	      sprintf( buf, "lst_ch: %d  lst_ch->prev: %d  lst_ch->next: %d",
	      		(int) lst_ch, (int) lst_ch->prev, (int) lst_ch->next );
	    else
	      strcpy( buf, "lst_ch: NULL" );
	    log_string( buf );
	    gch_prev = NULL;
	    continue;
	}

        /*
         * Experience gained during battle deceases as battle drags on
         */
	if ( ch->fighting )
	  if ( (++ch->fighting->duration % 24) == 0 )
	    ch->fighting->xp = ((ch->fighting->xp * 9) / 10);


	for ( timer = ch->first_timer; timer; timer = timer_next )
	{
	    timer_next = timer->next;
	    if ( --timer->count <= 0 )
	    {
		if ( timer->type == TIMER_DO_FUN )
		{
		    int tempsub;

		    tempsub = ch->substate;
		    ch->substate = timer->value;
		    (timer->do_fun)( ch, "" );
		    if ( char_died(ch) )
		      break;
		    ch->substate = tempsub;
		}
		extract_timer( ch, timer );
	    }
	}

	if ( char_died(ch) )
	  continue;

	/*
	 * We need spells that have shorter durations than an hour.
	 * So a melee round sounds good to me... -Thoric
	 */
	for ( paf = ch->first_affect; paf; paf = paf_next )
	{
	      paf_next	= paf->next;
	      if ( paf->duration > 0 )
		paf->duration--;
	      else
	      if ( paf->duration < 0 )
		;
	      else
	      {
		  if ( !paf_next
		  ||    paf_next->type != paf->type
		  ||    paf_next->duration > 0 )
		  {
		      skill = get_skilltype(paf->type);
		      if ( paf->type > 0 && skill && skill->msg_off )
		      {
                          set_char_color( AT_WEAROFF, ch );
			  send_to_char( skill->msg_off, ch );
			  send_to_char( "\n\r", ch );
		      }
		  }
		  affect_remove( ch, paf );
	      }
	}
	
	if ( ( victim = who_fighting( ch ) ) == NULL
	||   IS_AFFECTED( ch, AFF_PARALYSIS ) )
	 {
	    stop_fighting( ch, TRUE );
	    continue;
	 }

        retcode = rNONE;

	if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE ) )
	{
	   sprintf( buf, "violence_update: %s fighting %s in a SAFE room.",
	   	ch->name, victim->name );
	   log_string( buf );
	   stop_fighting( ch, TRUE );
	}
	else
	if ( IS_AWAKE(ch) && ch->in_room == victim->in_room )
	{
	   if(!IS_NPC(ch))
	     ch->pcdata->lost_attacks = 0;
           retcode = multi_hit( ch, victim, TYPE_UNDEFINED );
	}
	else
	    stop_fighting( ch, FALSE );

	if ( char_died(ch) )
	    continue;

	if ( retcode == rCHAR_DIED
	|| ( victim = who_fighting( ch ) ) == NULL )
	    continue;

	/*
	 *  Mob triggers
	 */
	rprog_rfight_trigger( ch );
	if ( char_died(ch) )
	    continue;
	mprog_hitprcnt_trigger( ch, victim );
	if ( char_died(ch) )
	    continue;
	mprog_fight_trigger( ch, victim );
	if ( char_died(ch) )
	    continue;

	/*
	 * Fun for the whole family!
	 */
	for ( rch = ch->in_room->first_person; rch; rch = rch_next )
	{
	    rch_next = rch->next_in_room;

	    if ( IS_AWAKE(rch) && !rch->fighting )
	    {
		/*
		 * PC's auto-assist others in their group.
		 */
		if ( !IS_NPC(ch) || IS_AFFECTED(ch, AFF_CHARM) )
		{
		    if ( ( !IS_NPC(rch) || IS_AFFECTED(rch, AFF_CHARM) )
		    &&   is_same_group(ch, rch) )
			multi_hit( rch, victim, TYPE_UNDEFINED );
		    continue;
		}

		/*
		 * NPC's assist NPC's of same type or 12.5% chance regardless.
		 */
		if ( IS_NPC(rch) && !IS_AFFECTED(rch, AFF_CHARM)
		&&  !IS_SET(rch->act, ACT_NOASSIST) )
		{
		    if ( char_died(ch) )
			break;
		    if ( rch->pIndexData == ch->pIndexData
		    ||   number_bits( 3 ) == 0 )
		    {
			CHAR_DATA *vch;
			CHAR_DATA *target;
			int number;

			target = NULL;
			number = 0;			for ( vch = ch->in_room->first_person; vch; vch = vch->next )
			{
			    if ( can_see( rch, vch )
			    &&   is_same_group( vch, victim )
			    &&   number_range( 0, number ) == 0 )
			    {
				target = vch;
				number++;
			    }
			}

			if ( target )
			    multi_hit( rch, target, TYPE_UNDEFINED );
		    }
		}
	    }
	}
    }

    return;
}



/*
 * Do one group of attacks.
 */
ch_ret multi_hit( CHAR_DATA *ch, CHAR_DATA *victim, int dt )
{
    OBJ_DATA *armor;
    OBJ_DATA *wield;
    OBJ_DATA *dual;
    int     chance;
    int	    mod;
    ch_ret  retcode;
    
    if ( !IS_NPC(ch) && !IS_NPC(victim) )
      add_timer( ch, TIMER_RECENTFIGHT, 20, NULL, 0 );

    if ( !IS_NPC(ch) && IS_SET( ch->act, PLR_NICE ) && !IS_NPC( victim ) )
      return rNONE;

    if ( (retcode = one_hit( ch, victim, dt, 0, FALSE)) != rNONE )
      return retcode;

    if ( who_fighting( ch ) != victim )
	return rNONE;

    mod = 0;
	
    if ( !IS_NPC(ch) && get_eq_char( ch, WEAR_DUAL_WIELD ) )
     {
      mod = 8;
      if( HAS_FEAT(ch, AMBIDEXTERITY_FEAT) )
	mod -= 2;
      if( HAS_FEAT2(ch, TWO_WEAP_FIGHTING) )
	mod -= 2;
      one_hit( ch, victim, dt, mod, TRUE );
      if( HAS_FEAT(ch, IMPROVED_TWO_WEAPON) )
       {
	mod += 5;
        one_hit( ch, victim, dt, mod, TRUE );
       }
     }

    if ( ch->hitroll >= 6 )
     {
	mod += 5;
    	one_hit( ch, victim, dt, mod, FALSE );
     }
    if ( ch->hitroll >= 11 )
     {
	mod += 10;
    	one_hit( ch, victim, dt, mod, FALSE );
     }
    if ( ch->hitroll >= 16 )
     {
	mod += 15;
    	one_hit( ch, victim, dt, mod, FALSE );
     }
    if ( ch->hitroll >= 21 )
     {
	mod += 20;
    	one_hit( ch, victim, dt, mod, FALSE );
     }

    if(ch->class_level[NOBLELORD_ABILITY] >= 1)
	one_hit( ch, victim, dt, 0, FALSE);  

    wield = get_eq_char( ch, WEAR_WIELD );
    dual  = get_eq_char( ch, WEAR_DUAL_WIELD );

    if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER) )
     {
      if( HAS_FFEAT(ch, RAPID_SHOT) )
	one_hit(ch, victim, dt, 5, FALSE);
     }

    if( wield && wield->item_type == ITEM_WEAPON && wield->value[3] == WEAPON_LIGHTSABER && !IS_OBJ_STAT(wield, ITEM_IGNITED) )
     {
	SET_BIT(wield->extra_flags, ITEM_IGNITED);
	act( AT_YELLOW, "You ignite your lightsaber.", ch, NULL, victim, TO_CHAR );
	act( AT_YELLOW, "$n ignites a lightsaber.", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "$n ignites a lightsaber.", ch, NULL, victim, TO_NOTVICT );
     }
    if( dual && dual->item_type == ITEM_WEAPON && dual->value[3] == WEAPON_LIGHTSABER && !IS_OBJ_STAT(dual, ITEM_IGNITED) )
     {
	SET_BIT(dual->extra_flags, ITEM_IGNITED);
	act( AT_YELLOW, "You ignite your offhand lightsaber.", ch, NULL, victim, TO_CHAR );
	act( AT_YELLOW, "$n ignites an offhand lightsaber.", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "$n ignites an offhand lightsaber.", ch, NULL, victim, TO_NOTVICT );
     }

    if( (armor = get_eq_char(ch, WEAR_BODY) ) == NULL && !wield && !dual && (ch->stance == KTHRI_STANCE || (ch->class_level[MARTIALARTS_ABILITY] == 10 && !IS_DARK(ch) )) )
     {
      if(HAS_STANCE(ch, KTHRI_BASIC) )
       one_hit(ch, victim, dt, 0, FALSE);
      if(HAS_STANCE(ch, KTHRI_EXPERTISE) )
       one_hit(ch, victim, dt, 0, FALSE);
      if(HAS_STANCE(ch, KTHRI_MASTERY) )
       one_hit(ch, victim, dt, 0, FALSE);
     }

    if ( IS_NPC(ch) && ch->numattacks > 0 )
    {
	for ( chance = 0; chance <= (ch->numattacks); chance++ )
	{
	   retcode = one_hit( ch, victim, dt, ( 5 * (chance+1)), FALSE );
	   if ( retcode != rNONE || who_fighting( ch ) != victim )
	     return retcode;
	}
	return retcode;
    }

    return rNONE;
}


/*
 * Weapon types, haus
 */
int weapon_prof_bonus_check( CHAR_DATA *ch, OBJ_DATA *wield, int *gsn_ptr )
{
    int bonus;
    bonus = 0;	
    return bonus;
}

/*
 * Calculate the tohit bonus on the object and return RIS values.
 * -- Altrag
 */
int obj_hitroll( OBJ_DATA *obj )
{
	int tohit = 0;
	AFFECT_DATA *paf;
	
	for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
		if ( paf->location == APPLY_HITROLL )
			tohit += paf->modifier;
	for ( paf = obj->first_affect; paf; paf = paf->next )
		if ( paf->location == APPLY_HITROLL )
			tohit += paf->modifier;
	return tohit;
}

/*
 * Offensive shield level modifier
 */
sh_int off_shld_lvl( CHAR_DATA *ch, CHAR_DATA *victim )
{
  return 0;
}

/*
 * Hit one guy once.
 */
ch_ret one_hit( CHAR_DATA *ch, CHAR_DATA *victim, int dt, int mod, bool dual )
{
    CLAN_DATA *clan;
    CLAN_DATA *clan2;
    CLAN_DATA *clan3;
    OBJ_DATA *wield;
    OBJ_DATA *vict_wield;
    OBJ_DATA *vict_dual;
    int victim_ac;
    bool is_critical=FALSE;
    bool confirm_critical=FALSE;
    int barenumdie, baresizedie;
    int x, to_hit;
    int dam=0;
    int miss;
    int diceroll, diceroll2, deflect_atk;
    int attacktype, cnt;
    int resist=0;
    ch_ret retcode;
    int chance;
    bool fail;
    AFFECT_DATA af;
                

    /*
     * Can't beat a dead char!
     * Guard against weird room-leavings.
     */
    if(!IS_NPC(ch))
    {
      if(ch->pcdata->lost_attacks < 0)
          ch->pcdata->lost_attacks = 0;
      if(ch->pcdata->lost_attacks != 0)
      {
          ch->pcdata->lost_attacks--;
          tail_chain();
        return rNONE;
      }
    }
    if ( victim->position == POS_DEAD || ch->in_room != victim->in_room )
	return rVICT_DIED;                  

    if ( dual == TRUE )
      wield = get_eq_char( ch, WEAR_DUAL_WIELD );
    else
      wield = get_eq_char( ch, WEAR_WIELD );

    if ( ch->fighting		/* make sure fight is already started */
    &&   dt == TYPE_UNDEFINED
    &&   IS_NPC(ch)
    &&   ch->attacks != 0 )
    {
	cnt = 0;
	for ( ;; )
	{
	   x = number_range( 0, 6 );
	   attacktype = 1 << x;
	   if ( IS_SET( ch->attacks, attacktype ) )
	     break;
	   if ( cnt++ > 16 )
	   {
	     attacktype = 0;
	     break;
	   }
	}
	if ( attacktype == ATCK_BACKSTAB )
	  attacktype = 0;
	if ( wield && number_percent( ) > 25 )
	  attacktype = 0;
	switch ( attacktype )
	{
	  default:
	    break;
	  case ATCK_TRIP:
	    retcode = 0;
	    break;
	}
	if ( attacktype )
	  return retcode;
    }

    if ( dt == TYPE_UNDEFINED )
    {
	dt = TYPE_HIT;
	if ( wield && wield->item_type == ITEM_WEAPON )
	    dt += wield->value[3];
	    
	if (wield && wield->item_type == ITEM_WEAPON && wield->value[3] == WEAPON_DUAL_LIGHTSABER)
	    dt = (TYPE_HIT + WEAPON_LIGHTSABER);
    }

    victim_ac = GET_AC(victim);

    if( victim->pcdata && victim->pcdata->clan )
     {
	clan2 = get_clan( victim->pcdata->clan->name );
	if( clan2 && clan2->clan_bonus == BONUS_ARMOR )
	  victim_ac += clan->bonus;
     }

    if( victim->cover == COVER_DUCK )
	victim_ac += 2;
    else if( victim->cover == COVER_LEFT || victim->cover == COVER_RIGHT )
	victim_ac += 4;
    else if( victim->cover == COVER_FULL )
	victim_ac += 8;

    if( who_fighting(victim) == ch )
       victim_ac += victim->dodge_bonus;
    if( IS_AFFECTED( victim, AFF_FLYING ) )
       victim_ac += victim->aerial_defense;

    vict_wield = get_eq_char( victim, WEAR_WIELD );
    vict_dual = get_eq_char( victim, WEAR_DUAL_WIELD );

    if( !vict_wield && !vict_dual )
     {
      if( who_fighting(victim) == ch )
	victim_ac += 2;
     }

    if( (vict_wield && vict_wield->item_type == ITEM_WEAPON && (vict_wield->value[3] == WEAPON_LIGHTSABER || vict_wield->value[3] == WEAPON_DUAL_LIGHTSABER) )
      || ( vict_dual && vict_dual->item_type == ITEM_WEAPON && (vict_dual->value[3] == WEAPON_LIGHTSABER || vict_dual->value[3] == WEAPON_DUAL_LIGHTSABER) ) )
     {
      if( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER ) )
       {
        if( who_fighting(victim) == ch )
 	 {
         	victim_ac += victim->deflect_defense;
	 	victim_ac += victim->lightsaber_defense;
	  if( victim->stance == FORM3_STANCE )
		victim_ac += 1;
         }
       }
      if( victim->stance == FORM2_STANCE && wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_DUAL_LIGHTSABER ) )
       {
	  if( who_fighting(victim) == ch )
		victim_ac += 3;
       }
     }
    
    to_hit = ch->hitroll - mod;

    if( ch->pcdata && ch->pcdata->clan )
     {
	clan = get_clan( ch->pcdata->clan->name );
	if( clan && clan->clan_bonus == BONUS_HITROLL )
	  to_hit += clan->bonus;
     }

    if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_VIBRO || wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_PRIMITIVE || wield->value[3] == WEAPON_SIMPLE || wield->value[3] == WEAPON_DUAL_LIGHTSABER || wield->value[3] == WEAPON_FORCE_PIKE ) )
     	to_hit += stat_table[get_curr_str(ch)].mod;
    else if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER ) )
	to_hit += stat_table[get_curr_dex(ch)].mod;
    else
	to_hit += stat_table[get_curr_str(ch)].mod;

    if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER) )
     if( HAS_FFEAT(ch, POINT_BLANK) )
      if( ch->in_room->vnum == victim->in_room->vnum )
       to_hit += 1;

    to_hit -= victim->inspire_fear;

    if( ch->cover == COVER_DUCK )
	to_hit -= 3;
    else if( ch->cover == COVER_RIGHT || ch->cover == COVER_LEFT )
	to_hit -= 6;
    else if( ch->cover == COVER_FULL )
	to_hit -= 9;

    if( ch->stance == ECHANI_STANCE )
     {
	if( HAS_STANCE(ch, ECHANI_BASIC ) )
	   to_hit += 2;
	if( HAS_STANCE(ch, ECHANI_EXPERTISE ) )
	   to_hit += 2;
	if( HAS_STANCE(ch, ECHANI_MASTERY ) )
	   to_hit += 2;
     }

    if ( IS_AFFECTED( victim, AFF_PARALYSIS ) ) 
       affect_strip( ch, gsn_stun );

    diceroll = number_range( 1,20 );

    if ( diceroll == 1 && wield )
     {
  	check_fumble( ch, wield );
        tail_chain( );
        return rNONE;
     }

    if ( diceroll == 1 || ( diceroll < 20 && ( ( diceroll + to_hit ) < victim_ac ) ) )
    {
     if( victim->deflect_attack > 0 )
      {
       miss = 5;
       if( victim->stance == FORM5_STANCE )
  	 miss += 5;
       if( vict_wield && vict_wield->item_type == ITEM_WEAPON && (vict_wield->value[3] == WEAPON_LIGHTSABER || vict_wield->value[3] == WEAPON_DUAL_LIGHTSABER ) )
        {
	 if( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE || wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER ) )
	  {
           if( ( (diceroll + to_hit) - victim_ac ) <= miss )
            {
	     deflect_atk = number_range(1, 20);
	     if( (deflect_atk + victim->hitroll - victim->deflect_attack) >= GET_AC(ch) )
	      {
                   act( AT_WHITE, "You swing your lightsaber and reflect the blaster bolt back at $n!", ch, NULL, victim, TO_VICT );
                   act( AT_WHITE, "$N swings $s lightsaber and reflects the blast back at you!", ch, NULL, victim, TO_CHAR );
		   act( AT_WHITE, "$N swings $s lightsaber and reflects the blast back at $N!", ch, NULL, victim, TO_NOTVICT);
		   ch->hit -= vict_wield->value[1];
  	      }
            }
	  }
        }
      }
	damage( ch, victim, 0, dt, FALSE);
	tail_chain( );
	return rNONE;
    }

    if ( !wield )       
     {
      barenumdie = 1;
      baresizedie = 4;
      if( ch->stance == STAVA_STANCE )
       {
	if( HAS_STANCE( ch, STAVA_BASIC ) )
	 {
		barenumdie = 4;
		baresizedie = 15;
	 }
	if( HAS_STANCE( ch, STAVA_EXPERTISE ) )
	 {
		barenumdie = 8;
		baresizedie = 25;
	 }
	if( HAS_STANCE( ch, STAVA_MASTERY ) )
	 {
		barenumdie = 12;
		baresizedie = 32;
	 }
       }
    }
    else
	dam = number_range( wield->value[1], wield->value[2] );

    if( !wield && IS_NPC(ch) )
	dam = number_range( ch->barenumdie, ch->baresizedie );
     
    if( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_DUAL_LIGHTSABER ) )
     	dam += number_range( (wield->value[1] * ch->force_weapon), (wield->value[2] * ch->force_weapon) );

    if( wield )
	is_critical = check_critical( ch, diceroll, TRUE, victim_ac );
    else
      	is_critical = check_critical( ch, diceroll, FALSE, victim_ac );

    if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] ==WEAPON_BLASTER || wield->value[3] == WEAPON_BLASTER_RIFLE ||wield->value[3] == WEAPON_HEAVY || wield->value[3] == WEAPON_BOWCASTER) )
     if( HAS_FFEAT(ch, POINT_BLANK) )
      if( ch->in_room->vnum == victim->in_room->vnum )
       dam += 1;

    if( is_critical )
     {
	diceroll2 = number_range(1, 20);
	if( wield )
	  confirm_critical = check_critical( ch, diceroll2, TRUE, victim_ac );
	else
	  confirm_critical = check_critical( ch, diceroll2, FALSE, victim_ac );
     }
    if( confirm_critical )
     {
	if( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_DUAL_LIGHTSABER ) )
	   if( IS_SET( wield->extra_flags, ITEM_IMP_CRITICAL ) )
		dam += number_range( 2, 12 );
	dam = ( dam * 2 );
     }
   
    if ( !IS_AWAKE(victim) )
	dam *= 2;

    if ( wield && wield->item_type == ITEM_WEAPON && ( wield->value[3] != WEAPON_BLASTER || wield->value[3] != WEAPON_BLASTER_RIFLE || wield->value[3] != WEAPON_BOWCASTER || wield->value[3] != WEAPON_HEAVY ) )
        dam += stat_table[get_curr_str(ch)].mod;
    if ( !wield )
	dam += stat_table[get_curr_str(ch)].mod;

    if( ch->pcdata && ch->pcdata->clan )
     {
 	clan3 = get_clan( ch->pcdata->clan->name );
	if( clan3 && clan3->clan_bonus == BONUS_DAMROLL )
	    dam += clan->bonus;
     }

     if ( ( dt == (TYPE_HIT + WEAPON_BLASTER ) || dt == (TYPE_HIT + WEAPON_BLASTER_RIFLE) || dt == (TYPE_HIT + WEAPON_HEAVY) ) && wield && wield->item_type == ITEM_WEAPON )
     {
     	if ( wield->value[4] < 1  )
     	{ 
            act( AT_YELLOW, "$n points their blaster at you but nothing happens.",  ch, NULL, victim, TO_VICT    );
            act( AT_YELLOW, "*CLICK* ... your blaster needs a new ammunition cell!", ch, NULL, victim, TO_CHAR    );            
            if ( IS_NPC(ch) )
     	    {
     	        do_remove( ch, wield->name );
     	    }
            return rNONE;    	    
     	}
     	else if ( wield->blaster_setting == BLASTER_FULL && wield->value[4] >=5 )
        {
     	    dam *=  1.5;
     	    wield->value[4] -= 5;
     	}
     	else if ( wield->blaster_setting == BLASTER_HIGH && wield->value[4] >=4 )
        {
     	    dam *=  1.25;
     	    wield->value[4] -= 4;
     	}
     	else if ( wield->blaster_setting == BLASTER_NORMAL && wield->value[4] >=3 )
     	{
     	    wield->value[4] -= 3;
     	}
     	else if ( wield->blaster_setting == BLASTER_STUN && wield->value[4] >=5 )    
        {
     	    dam /= 10;
     	    wield->value[4] -= 3;
     	    fail = FALSE;
	    if( IS_NPC(victim) )
	      chance = number_range( 10, 25 ) + stat_table[get_curr_con(victim)].mod;
	    else
              chance = (number_range( 1, 20 ) + GET_FORT(victim));
            if ( chance >= 18 )
               fail = TRUE;
            if ( victim->was_stunned > 0 )
            {
               fail = TRUE;
               victim->was_stunned--;
            }
            if ( !fail )
    	    {
		WAIT_STATE( victim, PULSE_VIOLENCE );
		act( AT_BLUE, "Blue rings of energy from $N's blaster knock you down leaving you stunned!", victim, NULL, ch, TO_CHAR );
		act( AT_BLUE, "Blue rings of energy from your blaster strike $N, leaving $M stunned!", ch, NULL, victim, TO_CHAR );
		act( AT_BLUE, "Blue rings of energy from $n's blaster hit $N, leaving $M stunned!", ch, NULL, victim, TO_NOTVICT );
		stop_fighting( victim, TRUE );
		if ( !IS_AFFECTED( victim, AFF_PARALYSIS ) )
		{
	  	   af.type      = gsn_stun;
	  	   af.location  = APPLY_AC;
	  	   af.modifier  = -10;
	  	   af.duration  = ( number_range(1, 4) * 10);
	  	   af.bitvector = AFF_PARALYSIS;
	  	   affect_to_char( victim, &af );
	  	   update_pos( victim );
	  	   if ( IS_NPC(victim) )
	  	   {
	  	       start_hating( victim, ch );
	  	       start_hunting( victim, ch );
	  	       victim->was_stunned = 10;
	  	   }
		}
    	    }
    	    else
            {
               act( AT_BLUE, "Blue rings of energy from $N's blaster hit you but have little effect", victim, NULL, ch, TO_CHAR );
	       act( AT_BLUE, "Blue rings of energy from your blaster hit $N, but nothing seems to happen!", ch, NULL, victim, TO_CHAR );
	       act( AT_BLUE, "Blue rings of energy from $n's blaster hit $N, but nothing seems to happen!", ch, NULL, victim, TO_NOTVICT );
		
            }
     	}
        else if ( wield->blaster_setting == BLASTER_HALF && wield->value[4] >=2 )    
        {
     	    dam *=  0.75;
     	    wield->value[4] -= 2;
     	}
        else    
        {
     	    dam *= 0.5;
     	    wield->value[4] -= 1;
     	}
     
     }
     else if ( dt == (TYPE_HIT + WEAPON_VIBRO ) && wield && wield->item_type == ITEM_WEAPON )
     {
     	if ( wield->value[4] < 1  )
     	{ 
            act( AT_YELLOW, "Your vibro-blade needs recharging ...", ch, NULL, victim, TO_CHAR    );            
            dam /= 3;    	    
     	}
     }
     else if ( dt == (TYPE_HIT + WEAPON_FORCE_PIKE ) && wield && wield->item_type == ITEM_WEAPON )
     {
     	if ( wield->value[4] < 1  )
     	{ 
            act( AT_YELLOW, "Your force-pike needs recharging ...", ch, NULL, victim, TO_CHAR    );            
            dam /= 2;    	    
     	}
     	else 
     	    wield->value[4]--;
     }
     else if ( dt == (TYPE_HIT + WEAPON_LIGHTSABER ) && wield && wield->item_type == ITEM_WEAPON )
     {
     	if ( wield->value[4] < 1  )
     	{ 
            act( AT_YELLOW, "$n waves a dead hand grip around in the air.",  ch, NULL, victim, TO_VICT    );
            act( AT_YELLOW, "You need to recharge your lightsaber ... it seems to be lacking a blade.", ch, NULL, victim, TO_CHAR    );            
     	    if ( IS_NPC(ch) )
     	    {
     	        do_remove( ch, wield->name );
     	    }  
     	    return rNONE;
     	}
     }
     else if ( dt == (TYPE_HIT + WEAPON_BOWCASTER ) && wield && wield->item_type == ITEM_WEAPON )
     {
     	if ( wield->value[4] < 1  )
     	{ 
            act( AT_YELLOW, "$n points their bowcaster at you but nothing happens.",  ch, NULL, victim, TO_VICT    );
            act( AT_YELLOW, "*CLICK* ... your bowcaster needs a new bolt cartridge!", ch, NULL, victim, TO_CHAR    );            
            if ( IS_NPC(ch) )
     	    {
     	        do_remove( ch, wield->name );
     	    }
            return rNONE;    	    
     	}
     	else
          wield->value[4]--;
     }

   if( wield && wield->item_type == ITEM_WEAPON && (wield->value[3] == WEAPON_LIGHTSABER || wield->value[3] == WEAPON_DUAL_LIGHTSABER) && IS_SET(wield->extra_flags, ITEM_STUN) )
    {
      if( IS_NPC(victim) )
	resist = ( number_range( 1, 20 ) + victim->top_level );
      else
        resist = ( number_range( 1, 20 ) + victim->fortitude );
      if( !IS_AFFECTED( victim, AFF_PARALYSIS ) && resist < 15 )
       {
         af.type      = gsn_stun;
         af.location  = APPLY_AC;
         af.modifier  = -10;
         af.duration  = ( number_range(1, 4) * 10);
         af.bitvector = AFF_PARALYSIS;
         affect_to_char( victim, &af );
         update_pos( victim );
       }
    }

    dam -= victim->damage_reduction;
     
    if ( dam <= 0 )
	dam = 1;
    
    if ( (retcode = damage( ch, victim, dam, dt, confirm_critical )) != rNONE )
      return retcode;
    if ( char_died(ch) )
      return rCHAR_DIED;
    if ( char_died(victim) )
      return rVICT_DIED;

    retcode = rNONE;
    if ( dam == 0 )
      return retcode;

    tail_chain( );
    return retcode;
}

/*
 * Calculate damage based on resistances, immunities and suceptibilities
 *					-Thoric
 */
sh_int ris_damage( CHAR_DATA *ch, sh_int dam, int ris )
{
   sh_int modifier;

   modifier = 10;
   if ( IS_SET(ch->immune, ris ) )
     modifier -= 10;
   if ( IS_SET(ch->resistant, ris ) )
     modifier -= 2;
   if ( IS_SET(ch->susceptible, ris ) )
     modifier += 2;
   if ( modifier <= 0 )
     return -1;
   if ( modifier == 10 )
     return dam;
   return (dam * modifier) / 10;
}


/*
 * Inflict damage from a hit.
 */
ch_ret damage( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt, bool critical )
{
    OBJ_DATA *damobj;
    char buf1[MAX_STRING_LENGTH];
    sh_int dameq;
    int room;
    bool npcvict;
    bool loot;
//    int part, iPart;
    ch_ret retcode;

    int init_gold, new_gold, gold_diff;
    int nocorpse = 0;
    retcode = rNONE;

    if ( !ch )
    {
	bug( "Damage: null ch!", 0 );
	return rERROR;
    }
    if ( !victim )
    {
	bug( "Damage: null victim!", 0 );
	return rVICT_DIED;
    }

    if ( victim->position == POS_DEAD )
	return rVICT_DIED;

    npcvict = IS_NPC(victim);

    if ( dam && npcvict && ch != victim )
    {
	if ( !IS_SET( victim->act, ACT_SENTINEL ) )
 	{
	   if ( victim->hunting )
	   {
	     if ( victim->hunting->who != ch )
	     {
		STRFREE( victim->hunting->name );
		victim->hunting->name = QUICKLINK( ch->name );
		victim->hunting->who  = ch;
	     }
           }
	   else
	     start_hunting( victim, ch );
	}

      if ( victim->hating )
      {
	if ( victim->hating->who != ch )
	{
	   STRFREE( victim->hating->name );
	   victim->hating->name = QUICKLINK( ch->name );
	   victim->hating->who  = ch;
	}
      }
      else
	start_hating( victim, ch );
    }

    if ( who_fighting(victim) != ch )
     {
	  if( IS_AFFECTED( ch, AFF_HIDE) )
	   REMOVE_BIT(ch->affected_by, AFF_HIDE);

	   dam += number_range( ch->sneak_attack, (6 * ch->sneak_attack) );
     }
    if ( IS_AFFECTED(ch, AFF_HIDE) )
     {
	     REMOVE_BIT(ch->affected_by, AFF_HIDE);
	     dam += number_range( ch->sneak_attack, (6 * ch->sneak_attack) );
     }

    if ( victim != ch )
    {
	/*
	 * Certain attacks are forbidden.
	 * Most other attacks are returned.
	 */
	if ( is_safe( ch, victim ) )
	    return rNONE;


	if ( victim->position > POS_STUNNED && dt != TYPE_MISSILE)
	{
	    if ( !victim->fighting )
		set_fighting( victim, ch );
	    if ( victim->fighting )
		victim->position = POS_FIGHTING;
	}

	if ( victim->position > POS_STUNNED && dt != TYPE_MISSILE)
	{
	    if ( !ch->fighting )
		set_fighting( ch, victim );
	    if ( IS_NPC(ch)
	    &&   npcvict
	    &&   IS_AFFECTED(victim, AFF_CHARM)
	    &&   victim->master
	    &&   victim->master->in_room == ch->in_room
	    &&   number_bits( 3 ) == 0 )
	    {
		stop_fighting( ch, FALSE );
		retcode = multi_hit( ch, victim->master, TYPE_UNDEFINED );
		return retcode;
	    }
	}
    }
    dam_message( ch, victim, dam, dt, critical );

    if ( victim->master == ch )
	stop_follower( victim );

    if (dam > 10 && dt != TYPE_UNDEFINED && !IS_SET( ch->in_room->room_flags2, ROOM_ARENA))
    {
	/* get a random body eq part */
	dameq  = number_range(WEAR_LIGHT, WEAR_EYES);
	damobj = get_eq_char(victim, dameq);
	if ( damobj )
	{
	  if ( dam > get_obj_resistance(damobj) )
	  {
	     set_cur_obj(damobj);
	     damage_obj(damobj);
	  }
	}
    }

/*    if ( critical )
    {
     part = -1;
     for( iPart = 0; iPart < MAX_PART; iPart++ )
      {
	if( iPart == HEAD_PART || iPart == FEET_PART || iPart == WING_PART )
	  continue;
	part = get_pflag( part_name[iPart] );
	if( !part )
	  continue;
	if( HAS_BODYPART(victim, part) )
	  break;
      }
     if( part != -1 )
	remove_bodypart(ch, victim, part);
    }
*/     
    /*
     * Hurt the victim.
     * Inform the victim of his new state.
     */

    victim->hit -= dam;

    if ( !IS_NPC(victim)
    &&   victim->top_level >= LEVEL_IMMORTAL
    &&   victim->hit < 1 )
       victim->hit = 1;

    /* Make sure newbies dont die */

    if (!IS_NPC(victim) && NOT_AUTHED(victim) && victim->hit < 1)
	victim->hit = 1;

    if ( IS_NPC(victim) && IS_SET(victim->act, ACT_IMMORTAL) )
	victim->hit = 1;

    if ( victim->hit < 1 && !IS_NPC(victim) && IS_SET(victim->in_room->room_flags2, ROOM_ARENA))
     {
        char_from_room(victim);
        char_to_room(victim,victim->pcdata->roomarena);
        victim->hit = victim->max_hit;
        victim->mana = victim->max_mana;
        if( num_in_arena() == 1)
          find_game_winner();
        do_look(victim, "auto");
        stop_fighting( victim, TRUE );
        lost_arena(victim);
        return rNONE;
     }

    if ( !npcvict
    &&   get_trust(victim) >= LEVEL_IMMORTAL
    &&	 get_trust(ch)	   >= LEVEL_IMMORTAL
    &&   victim->hit < 1 )
	victim->hit = 1;
    update_pos( victim );

    switch( victim->position )
    {
    case POS_MORTAL:
	act( AT_DYING, "$n is mortally wounded, and will die soon, if not aided.",
	    victim, NULL, NULL, TO_ROOM );
	send_to_char( "&RYou are mortally wounded, and will die soon, if not aided.",victim);
	break;

    case POS_INCAP:
	act( AT_DYING, "$n is incapacitated and will slowly die, if not aided.",
	    victim, NULL, NULL, TO_ROOM );
	send_to_char( "&RYou are incapacitated and will slowly die, if not aided.",victim);
	break;

    case POS_STUNNED:
        if ( !IS_AFFECTED( victim, AFF_PARALYSIS ) )
        {
	  act( AT_ACTION, "$n is stunned, but will probably recover.",
	    victim, NULL, NULL, TO_ROOM );
	  send_to_char( "&RYou are stunned, but will probably recover.",victim);
	}
	break;

    case POS_DEAD:
	if ( dt >= 0 && dt < top_sn )
	{
	    SKILLTYPE *skill = skill_table[dt];

	    if ( skill->die_char && skill->die_char[0] != '\0' )
	      act( AT_DEAD, skill->die_char, ch, NULL, victim, TO_CHAR );
	    if ( skill->die_vict && skill->die_vict[0] != '\0' )
	      act( AT_DEAD, skill->die_vict, ch, NULL, victim, TO_VICT );
	    if ( skill->die_room && skill->die_room[0] != '\0' )
	      act( AT_DEAD, skill->die_room, ch, NULL, victim, TO_NOTVICT );
	}
	if ( IS_NPC(victim) && IS_SET( victim->act, ACT_NOKILL )  )
	   act( AT_YELLOW, "$n flees for $s life ... barely escaping certain death!", victim, 0, 0, TO_ROOM );
	else if ( IS_NPC(victim) && IS_SET( victim->act, ACT_DROID )  )
	   act( AT_DEAD, "$n EXPLODES into many small pieces!", victim, 0, 0, TO_ROOM );
	else
	   act( AT_DEAD, "$n is DEAD!", victim, 0, 0, TO_ROOM );
	   send_to_char( "&WYou have been KILLED!\n\r", victim);
	break;

    default:
	if ( dam > victim->max_hit / 4 )
	{
	   act( AT_HURT, "That really did HURT!", victim, 0, 0, TO_CHAR );
	   if ( number_bits(3) == 0 )
		worsen_mental_state( ch, 1 );
	}
	if ( victim->hit < victim->max_hit / 4 )

	{
	   act( AT_DANGER, "You wish that your wounds would stop BLEEDING so much!",
		victim, 0, 0, TO_CHAR );
	   if ( number_bits(2) == 0 )
		worsen_mental_state( ch, 1 );
	}
	break;
    }

    if ( victim->hit <=0 && !IS_NPC(victim))
    {
       OBJ_DATA *obj;
       OBJ_DATA *obj_next;
       int cnt=0;
    
       REMOVE_BIT( victim->act, PLR_ATTACKER );
       
        stop_fighting( victim, TRUE );
       
       if ( ( obj = get_eq_char( victim, WEAR_DUAL_WIELD ) ) != NULL )
          unequip_char( victim, obj );
       if ( ( obj = get_eq_char( victim, WEAR_WIELD ) ) != NULL )
          unequip_char( victim, obj );
       if ( ( obj = get_eq_char( victim, WEAR_HOLD ) ) != NULL )
          unequip_char( victim, obj );
       if ( ( obj = get_eq_char( victim, WEAR_MISSILE_WIELD ) ) != NULL )
          unequip_char( victim, obj );
       if ( ( obj = get_eq_char( victim, WEAR_LIGHT ) ) != NULL )
          unequip_char( victim, obj );
        for ( obj = victim->first_carrying; obj; obj = obj_next )
	{
	    obj_next = obj->next_content;

	    if ( obj->wear_loc == WEAR_NONE )
	    {
		if ( obj->pIndexData->progtypes & DROP_PROG && obj->count > 1 ) 
		{
		   ++cnt;
		   separate_obj( obj );
		   obj_from_char( obj );
		   if ( !obj_next )
		     obj_next = victim->first_carrying;
		}
		else
		{
		   cnt += obj->count;
		   obj_from_char( obj );
		}
		act( AT_ACTION, "$n drops $p.", victim, obj, NULL, TO_ROOM );
		act( AT_ACTION, "You drop $p.", victim, obj, NULL, TO_CHAR );
		obj = obj_to_room( obj, victim->in_room );
	    }
        }        
      add_timer( victim, TIMER_RECENTFIGHT, 100, NULL, 0 );
   } 


    /*
     * Payoff for killing things.
     */
    if ( victim->position == POS_DEAD )
    {
	group_gain( ch, victim );
        
	if ( !npcvict )
	{
	    sprintf( log_buf, "%s killed by %s at %d",
		victim->name,
		(IS_NPC(ch) ? ch->short_descr : ch->name),
		victim->in_room->vnum );
	    log_string( log_buf );
	    to_channel( log_buf, CHANNEL_MONITOR, "Monitor", LEVEL_IMMORTAL );

	}
	else
	if ( !IS_NPC(ch) )		/* keep track of mob vnum killed */
	    add_kill( ch, victim );
     
	check_killer( ch, victim );

	if ( !IS_NPC(victim) || !IS_SET( victim->act, ACT_NOKILL )  )
	   loot = legal_loot( ch, victim );
        else
           loot = FALSE;
	if (IS_SET(victim->act, ACT_NOCORPSE))
	  nocorpse=1;        
	//Make sure snipe doesnt loot.
	room = victim->in_room->vnum;
	set_cur_char(victim);
	raw_kill( ch, victim );
	victim = NULL;

	if ( !IS_NPC(ch) && loot )
	{
	   /* Autogold by Scryn 8/12 */
	    if ( IS_SET(ch->act, PLR_AUTOGOLD) )
	    {
		init_gold = ch->gold;
		do_get( ch, "credits corpse" );
		new_gold = ch->gold;
		gold_diff = (new_gold - init_gold);
		if (gold_diff > 0)
                {
                  sprintf(buf1,"%d",gold_diff);
		  do_split( ch, buf1 );
		} 
	    }
	  if(room && ch && ch->in_room && ch->in_room->vnum == room)
	  {
	    if ( IS_SET(ch->act, PLR_AUTOLOOT) && nocorpse == 0)
		do_get( ch, "all corpse" );
	    else
	      if (nocorpse == 0)
		do_look( ch, "in corpse" );

	    if ( IS_SET(ch->act, PLR_AUTOSAC) )
		do_sacrifice( ch, "corpse" );
	  }
	}

	if ( IS_SET( sysdata.save_flags, SV_KILL ) )
	   save_char_obj( ch );
	return rVICT_DIED;
    }

    if ( victim == ch )
	return rNONE;

    /*
     * Take care of link dead people.
     */
    if ( !npcvict && !victim->desc && !victim->switched )
    {
	if ( number_range( 0, victim->wait ) == 0)
	{
	    do_flee( victim, "" );
	    do_flee( victim, "" );
	    do_flee( victim, "" );
	    do_flee( victim, "" );
	    do_flee( victim, "" );
	    do_hail( victim, "" );
	    do_quit( victim, "" );
	    return rNONE;
	}
    }

    /*
     * Wimp out?
     */
    if ( npcvict && dam > 0 )
    {
	if ( ( IS_SET(victim->act, ACT_WIMPY) && number_bits( 1 ) == 0
	&&   victim->hit < victim->max_hit / 2 )
	||   ( IS_AFFECTED(victim, AFF_CHARM) && victim->master
	&&     victim->master->in_room != victim->in_room ) )
	{
	    start_fearing( victim, ch );
	    stop_hunting( victim );
	    //do_flee( victim, "" );
	}
    }
  
    tail_chain( );
    return rNONE;
}

bool is_safe( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( !victim )
        return FALSE;

    /* Thx Josh! */
    if ( who_fighting( ch ) == ch )
	return FALSE;
                 
    if ( IS_SET( victim->in_room->room_flags, ROOM_SAFE ) )
    {
	set_char_color( AT_MAGIC, ch );
	send_to_char( "You'll have to do that elswhere.\n\r", ch );
	return TRUE;
    }

    if ( get_trust(ch) > LEVEL_HERO )
            return FALSE;
 
    if ( IS_NPC(ch) || IS_NPC(victim) )
	return FALSE;


return FALSE;

}

/* checks is_safe but without the output 
   cuts out imms and safe rooms as well 
   for info only */

bool is_safe_nm( CHAR_DATA *ch, CHAR_DATA *victim )
{
    return FALSE;
}


/*
 * just verify that a corpse looting is legal
 */
bool legal_loot( CHAR_DATA *ch, CHAR_DATA *victim )
{
  /* pc's can now loot .. why not .. death is pretty final */
  if ( !IS_NPC(ch) )
     return TRUE;
  /* non-charmed mobs can loot anything */
  if ( IS_NPC(ch) && !ch->master )
    return TRUE;
 
  return FALSE;
 }

/*
see if an attack justifies a KILLER flag --- edited so that none do but can't 
murder a no pk person. --- edited again for planetary wanted flags -- well will be soon :p
 */
 
void check_killer( CHAR_DATA *ch, CHAR_DATA *victim )
{
    
//    int x;
    
    /*
    * Charm-o-rama.
    */
    if ( IS_SET(ch->affected_by, AFF_CHARM) )
    {
	if ( !ch->master )
	{
	    char buf[MAX_STRING_LENGTH];

	    sprintf( buf, "Check_killer: %s bad AFF_CHARM",
		IS_NPC(ch) ? ch->short_descr : ch->name );
	    bug( buf, 0 );
	    REMOVE_BIT( ch->affected_by, AFF_CHARM );
	    return;
	}

	/* stop_follower( ch ); */
	if ( ch->master )
	  check_killer( ch->master, victim );
    }
    
    if ( IS_NPC(victim) )
    {
	if ( !IS_NPC( ch ) )
	{
	  if ( ch->pcdata->clan )
	    ch->pcdata->clan->mkills++;
	  ch->pcdata->mkills++;
	  if (ch->in_room->area)
	    ch->in_room->area->mkills++;
	}
	return;
    }
   
    if ( !IS_NPC(ch) && !IS_NPC(victim) )
    {
	if ( ch->pcdata->clan ) ch->pcdata->clan->pkills++;
	  ch->pcdata->pkills++;
	update_pos(victim);
	if ( victim->pcdata->clan )
	  victim->pcdata->clan->pdeaths++;	   
    }


    if ( IS_NPC(ch) )
      if ( !IS_NPC(victim) && victim->in_room && victim->in_room->area )
	victim->in_room->area->mdeaths++;

    return;
}



/*
 * Set position of a victim.
 */
void update_pos( CHAR_DATA *victim )
{
    if ( !victim )
    {
      bug( "update_pos: null victim", 0 );
      return;
    }

    if ( victim->hit < 1 && IS_SET( victim->act, ACT_IMMORTAL ) )
	victim->hit = 1;

    if ( victim->hit > 0 )
    {
	if ( victim->position <= POS_STUNNED )
	  victim->position = POS_STANDING;
	if ( IS_AFFECTED( victim, AFF_PARALYSIS ) )
	  victim->position = POS_STUNNED;
	return;
    }

    if ( IS_NPC(victim) || victim->hit <= -500 )
    {
	if ( victim->mount )
	{
	  act( AT_ACTION, "$n falls from $N.",
		victim, NULL, victim->mount, TO_ROOM );
	  REMOVE_BIT( victim->mount->act, ACT_MOUNTED );
	  victim->mount = NULL;
	}
	victim->position = POS_DEAD;
	return;
    }

	 if ( victim->hit <= -400 ) victim->position = POS_MORTAL;
    else if ( victim->hit <= -200 ) victim->position = POS_INCAP;
    else          victim->position = POS_STUNNED;

    if ( victim->position > POS_STUNNED
    &&   IS_AFFECTED( victim, AFF_PARALYSIS ) )
      victim->position = POS_STUNNED;

    if ( victim->mount )
    {
	act( AT_ACTION, "$n falls unconscious from $N.",
		victim, NULL, victim->mount, TO_ROOM );
	REMOVE_BIT( victim->mount->act, ACT_MOUNTED );
	victim->mount = NULL;
    }
    return;
}


/*
 * Start fights.
 */
void set_fighting( CHAR_DATA *ch, CHAR_DATA *victim )
{
    FIGHT_DATA *fight;

    if ( ch->fighting )
    {
	char buf[MAX_STRING_LENGTH];

	sprintf( buf, "Set_fighting: %s -> %s (already fighting %s)",
		ch->name, victim->name, ch->fighting->who->name );
	bug( buf, 0 );
	return;
    }

    if ( IS_AFFECTED(ch, AFF_SLEEP) )
      affect_strip( ch, gsn_sleep );

    /* Limit attackers -Thoric */
    if ( victim->num_fighting > max_fight(victim) )
    {
	send_to_char( "There are too many people fighting for you to join in.\n\r", ch );
	return;
    }

    CREATE( fight, FIGHT_DATA, 1 );
    fight->who	 = victim;
    fight->xp	 = (int) xp_compute( ch, victim );
    fight->align = align_compute( ch, victim );
    if ( !IS_NPC(ch) && IS_NPC(victim) )
      fight->timeskilled = times_killed(ch, victim);
    ch->num_fighting = 1;
    ch->fighting = fight;
    ch->position = POS_FIGHTING;
    victim->num_fighting++;
    if ( victim->switched && IS_AFFECTED(victim->switched, AFF_POSSESS) )
    {
	send_to_char( "You are disturbed!\n\r", victim->switched );
	do_return( victim->switched, "" );
    }
    return;
}


CHAR_DATA *who_fighting( CHAR_DATA *ch )
{
    if ( !ch )
    {
	bug( "who_fighting: null ch", 0 );
	return NULL;
    }
    if ( !ch->fighting )
      return NULL;
    return ch->fighting->who;
}

void free_fight( CHAR_DATA *ch )
{
   if ( !ch )
   {
	bug( "Free_fight: null ch!", 0 );
	return;
   }
   if ( ch->fighting )
   {
     if ( !char_died(ch->fighting->who) )
       --ch->fighting->who->num_fighting;
     DISPOSE( ch->fighting );
   }
   ch->fighting = NULL;
   if ( ch->mount )
     ch->position = POS_MOUNTED;
   else
     ch->position = POS_STANDING;
   /* Berserk wears off after combat. -- Altrag */
   if ( IS_AFFECTED(ch, AFF_RAGE) )
   {
     affect_strip(ch, gsn_rage);
     set_char_color(AT_WEAROFF, ch);
     send_to_char(skill_table[gsn_rage]->msg_off, ch);
     send_to_char("\n\r", ch);
   }
   return;
}


/*
 * Stop fights.
 */
void stop_fighting( CHAR_DATA *ch, bool fBoth )
{
    CHAR_DATA *fch;

    free_fight( ch );
    update_pos( ch );

    if ( !fBoth )   /* major short cut here by Thoric */
      return;

    for ( fch = first_char; fch; fch = fch->next )
    {
	if ( who_fighting( fch ) == ch )
	{
	    free_fight( fch );
	    update_pos( fch );
	}
    }
    return;
}



void death_cry( CHAR_DATA *ch )
{

    return;
}



void raw_kill( CHAR_DATA *ch, CHAR_DATA *victim )
{
    
    CHAR_DATA *victmp;
    
    char buf[MAX_STRING_LENGTH];
    char buf2[MAX_STRING_LENGTH];
    char arg[MAX_STRING_LENGTH];    
    long exp;
    OBJ_DATA *obj, *obj_next;
    
    if ( !victim )
    {
      bug( "raw_kill: null victim!", 0 );
      return;
    }
    
    strcpy( arg , victim->name );
    
    stop_fighting( victim, TRUE );

    if ( ch && !IS_NPC(ch) && !IS_NPC(victim) )
    {
      CONTRACT_DATA *contract;
      CONTRACT_DATA *scontract=NULL;
      claim_disintegration( ch , victim );

      for(contract=ch->first_contract;contract;contract=contract->next_in_contract)
      {
        if(!str_cmp(contract->target, victim->name))
        {
          scontract = contract;
          break;
        }
      }

    if(scontract != NULL)
    {
         ch_printf(ch, "&w&RYou have claimed your contract on %s, and collect your reward of %d credits.\n\r", scontract->target, scontract->amount);
	 ch->gold += scontract->amount;
         exp = 200;
         gain_exp(ch, exp );

 	 STRFREE(scontract->target);
  	 UNLINK(scontract, ch->first_contract, ch->last_contract, next_in_contract,prev_in_contract);
  	 DISPOSE(scontract);
    }
  }
/* Take care of polymorphed chars */
    if(IS_NPC(victim) && IS_SET(victim->act, ACT_POLYMORPHED))
    {
      char_from_room(victim->desc->original);
      char_to_room(victim->desc->original, victim->in_room);
      victmp = victim->desc->original;
      raw_kill(ch, victmp);
      return;
    }

    if ( victim->in_room && IS_NPC(victim) && victim->vip_flags != 0 && victim->in_room->area && victim->in_room->area->planet )
    {
       victim->in_room->area->planet->population--;
       victim->in_room->area->planet->population = UMAX( victim->in_room->area->planet->population , 0 );
       victim->in_room->area->planet->pop_support -= (float) ( 1 + 1 / (victim->in_room->area->planet->population + 1) );
       if ( victim->in_room->area->planet->pop_support < -100 )
          victim->in_room->area->planet->pop_support = -100;
    }
    
if ( !IS_NPC(victim) || !IS_SET( victim->act, ACT_NOKILL  ) )
    mprog_death_trigger( ch, victim );
    if ( char_died(victim) )
      return;

if ( !IS_NPC(victim) || !IS_SET( victim->act, ACT_NOKILL  ) )
    rprog_death_trigger( ch, victim );
    if ( char_died(victim) )
      return;

if ( !IS_NPC(victim) || ( !IS_SET( victim->act, ACT_NOKILL  ) && !IS_SET( victim->act, ACT_NOCORPSE ) ) )
    make_corpse( victim, IS_NPC(ch) ? ch->short_descr : ch->name );
else
{
    for ( obj = victim->last_carrying; obj; obj = obj_next )
    {
	obj_next = obj->prev_content;
	obj_from_char( obj );
	extract_obj( obj );
    }
}
    if( !IS_DROID(victim) )
      make_blood( victim );

    if ( IS_NPC(victim) )
    {
	victim->pIndexData->killed++;
	extract_char( victim, TRUE );
	victim = NULL;
	return;
    }

    set_char_color( AT_DIEMSG, victim );
    do_help(victim, "_DIEMSG_" );


/* swreality chnages begin here */

    if ( victim->plr_home )
    {
      ROOM_INDEX_DATA *room = victim->plr_home;
      
      STRFREE( room->name );
      room->name = STRALLOC( "An Empty Apartment" );

      REMOVE_BIT( room->room_flags , ROOM_PLR_HOME );
      SET_BIT( room->room_flags , ROOM_EMPTY_HOME );
     
      fold_area( room->area, room->area->filename, FALSE );      
    }

    if ( victim->pcdata && victim->pcdata->clan )
    {
       if(victim->pcdata->clan->shortname && victim->pcdata->clan->shortname[0] != '\0')
	  remove_member(victim->name, victim->pcdata->clan->shortname);

       if ( !str_cmp( victim->name, victim->pcdata->clan->leader ) )
       {
          STRFREE( victim->pcdata->clan->leader );
          if ( victim->pcdata->clan->number1 )
          {
             victim->pcdata->clan->leader = STRALLOC( victim->pcdata->clan->number1 );
             STRFREE( victim->pcdata->clan->number1 );
             victim->pcdata->clan->number1 = STRALLOC( "" );
          }
          else if ( victim->pcdata->clan->number2 )
          {
             victim->pcdata->clan->leader = STRALLOC( victim->pcdata->clan->number2 );
             STRFREE( victim->pcdata->clan->number2 );
             victim->pcdata->clan->number2 = STRALLOC( "" );
          }
          else
             victim->pcdata->clan->leader = STRALLOC( "" );
       }
       
       if ( !str_cmp( victim->name, victim->pcdata->clan->number1 ) )
       {
          STRFREE( victim->pcdata->clan->number1 );
          if ( victim->pcdata->clan->number2 )
          {
             victim->pcdata->clan->number1 = STRALLOC( victim->pcdata->clan->number2 );
             STRFREE( victim->pcdata->clan->number2 );
             victim->pcdata->clan->number2 = STRALLOC( "" );
          }
          else
             victim->pcdata->clan->number1 = STRALLOC( "" );
       }
       
       if ( !str_cmp( victim->name, victim->pcdata->clan->number2 ) )
       {
          STRFREE( victim->pcdata->clan->number2 );
          victim->pcdata->clan->number1 = STRALLOC( "" );
       }
       
       victim->pcdata->clan->members--;
    }

  if ( !victim )
  {
    DESCRIPTOR_DATA *d;
    
    /* Make sure they aren't halfway logged in. */
    for ( d = first_descriptor; d; d = d->next )
      if ( (victim = d->character) && !IS_NPC(victim)  )
        break;
    if ( d )
      close_socket( d, TRUE );
  }
  else        
  {
    int x, y;
    
    quitting_char = victim;
    save_char_obj( victim );
    saving_char = NULL;
    extract_char( victim, TRUE );
    for ( x = 0; x < MAX_WEAR; x++ )
	for ( y = 0; y < MAX_LAYERS; y++ )
	    save_equipment[x][y] = NULL;
  }
  
  sprintf( buf, "%s%c/%s", PLAYER_DIR, tolower(arg[0]),
          capitalize( arg ) );
  sprintf( buf2, "%s%c/%s", BACKUP_DIR, tolower(arg[0]),
          capitalize( arg ) );
  
  rename( buf, buf2 );

  sprintf( buf, "%s%c/%s.clone", PLAYER_DIR, tolower(arg[0]),
          capitalize( arg ) );
  sprintf( buf2, "%s%c/%s", PLAYER_DIR, tolower(arg[0]),
          capitalize( arg ) );

  rename( buf, buf2 );
  
  sprintf(buf, "%s%s.htm", PROFILE_DIR, capitalize(arg));
  remove(buf);

  return;

}



void group_gain( CHAR_DATA *ch, CHAR_DATA *victim )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *gch;
    CHAR_DATA *lch;
    int xp;
    int members;

    /*
     * Monsters don't get kill xp's or alignment changes.
     * Dying of mortal wounds or poison doesn't give xp to anyone!
     */
    if ( IS_NPC(ch) || victim == ch )
	return;

    members = 0;
    
    for ( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
    {
	if ( is_same_group( gch, ch ) )
	    members++;
    }

    if ( members == 0 )
    {
	bug( "Group_gain: members.", members );
	members = 1;
    }

    lch = ch->leader ? ch->leader : ch;

    for ( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
    {
	OBJ_DATA *obj;
	OBJ_DATA *obj_next;

	if ( !is_same_group( gch, ch ) )
	    continue;

	xp = (int) (xp_compute( gch, victim ) / members);
	 
	gch->alignment = align_compute( gch, victim );
	
	if ( !IS_NPC(gch) && IS_NPC(victim) && gch->pcdata && gch->pcdata->clan
	&& !str_cmp ( gch->pcdata->clan->name , victim->mob_clan ) )
	{
	     xp = 0;
	     sprintf( buf, "You receive no experience for killing your organizations resources.\n\r");
	     send_to_char( buf, gch );
	}
	else
	{
	   sprintf( buf, "You receive %d experience.\n\r", xp );
	   send_to_char( buf, gch );
	}
        
        gain_exp( gch, xp );
        
	for ( obj = ch->first_carrying; obj; obj = obj_next )
	{
	    obj_next = obj->next_content;
	    if ( obj->wear_loc == WEAR_NONE )
		continue;

	    if ( ( IS_OBJ_STAT(obj, ITEM_ANTI_NEUTRAL) && IS_NEUTRAL(ch) ) )
	    {
		act( AT_MAGIC, "You are zapped by $p.", ch, obj, NULL, TO_CHAR );
		act( AT_MAGIC, "$n is zapped by $p.",   ch, obj, NULL, TO_ROOM );
	        
		obj_from_char( obj );
		obj = obj_to_room( obj, ch->in_room );
//		oprog_zap_trigger(ch, obj);  /* mudprogs */
		if ( char_died(ch) )
		  return;
	    }
	}
    }

    return;
}


int align_compute( CHAR_DATA *gch, CHAR_DATA *victim )
{

    int align, newalign;

    align = gch->alignment - victim->alignment;

    if ( align >  500 )
	newalign  = UMIN( gch->alignment + (align-500)/4,  1000 );
    else
    if ( align < -500 )
	newalign  = UMAX( gch->alignment + (align+500)/4, -1000 );
    else
	newalign  = gch->alignment - (int) (gch->alignment / 4);
    
    return newalign;

      if(IS_SET( gch->in_room->room_flags2, ROOM_ARENA ))
        return 0;
    return URANGE ( -1000, 
                     (int) ( gch->alignment - victim->alignment/5 ),
                     1000 );

}


/*
 * Calculate how much XP gch should gain for killing victim
 * Lots of redesigning for new exp system by Thoric
 */
int xp_compute( CHAR_DATA *gch, CHAR_DATA *victim )
{
    CLAN_DATA *clan;
    int align;
    int xp;

    xp	  = 0;
    align = gch->alignment - victim->alignment;

    /* bonus for attacking opposite alignment */
    if ( align >  990 || align < -990 )
	xp = (xp*5) >> 2;
    else
    /* penalty for good attacking same alignment */
    if ( gch->alignment > 300 && align < 250 )
	xp = (xp*3) >> 2;

    xp = number_range( (xp*3) >> 2, (xp*5) >> 2 );

    /* reduce exp for killing the same mob repeatedly		-Thoric */
    if ( !IS_NPC( gch ) && IS_NPC( victim ) )
    {
	int times = times_killed( gch, victim );

	if ( times >= 5 )
	   xp = 0;
	else
	if ( times )
	   xp = (xp * (5-times)) / 5;
    }

    if( gch->pcdata && gch->pcdata->clan )
     {
	clan = get_clan( gch->pcdata->clan->name );
	if( clan && clan->clan_bonus == BONUS_EXP )
	  xp += ( ( xp * clan->bonus ) / 100 );
     }

    /* new xp cap for swreality */
    
    return URANGE(1, xp, 0 );
}


void dam_message( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt, bool critical )
{
    char buf1[256], buf2[256], buf3[256];
    const char *vs;
    const char *vp;
    const char *attack;
    char punct;
    sh_int dampc;
    struct skill_type *skill = NULL;
    bool gcflag = FALSE;
    bool gvflag = FALSE;

    if ( ! dam )
      dampc = 0;
    else
      dampc = ( (dam * 1000) / victim->max_hit) +
              ( 50 - ((victim->hit * 50) / victim->max_hit) );

   /*		     10 * percent					*/
	 if ( dam ==      0 ) { vs = "miss";	vp = "misses";		}
    else if ( dampc <=    5 ) { vs = "barely scratch";vp = "barely scratches";}
    else if ( dampc <=   10 ) { vs = "scratch";	vp = "scratches";	}
    else if ( dampc <=   20 ) { vs = "graze";	vp = "grazes";		}
    else if ( dampc <=   30 ) { vs = "injure";	vp = "injures";		}
    else if ( dampc <=   40 ) { vs = "wound";	vp = "wounds";		}
    else if ( dampc <=   50 ) { vs = "maul";    vp = "mauls";		}
    else if ( dampc <=   60 ) { vs = "decimate";vp = "decimates";	}
    else if ( dampc <=   70 ) { vs = "DISEMBOWEL";vp = "DISEMBOWELS";	}
    else if ( dampc <=   80 ) { vs = "PULVERIZE"; vp = "PULVERIZES";	}
    else if ( dampc <=   90 ) { vs = "EVISCERATE";vp = "EVISCERATES";	}
    else                      { vs = "*** ANNIHILATE ***";
			        vp = "*** ANNIHILATES ***";		}

    punct   = (dampc <= 30) ? '.' : '!';

    if ( dam == 0 && (!IS_NPC(ch) && 
       (IS_SET(ch->pcdata->flags, PCFLAG_GAG)))) gcflag = TRUE;

    if ( dam == 0 && (!IS_NPC(victim) &&
       (IS_SET(victim->pcdata->flags, PCFLAG_GAG)))) gvflag = TRUE;

    if ( dt >=0 && dt < top_sn )
	skill = skill_table[dt];
	
    if ( dt == (TYPE_HIT + WEAPON_BLASTER ) )	
    {    
         char sound[MAX_STRING_LENGTH];
         int vol = number_range( 20 , 80 );
         
         sprintf( sound , "!!SOUND(blaster V=%d)" , vol );
         sound_to_room(ch->in_room, sound);
    }
    
    if ( dt == TYPE_HIT || dam==0 )
    {
	sprintf( buf1, "$n %s $N%c",  vp, punct );
	sprintf( buf2, "You %s $N%c", vs, punct );
	sprintf( buf3, "$n %s you%c", vp, punct );
    }
    else
    if ( dt > TYPE_HIT && is_wielding_poisoned( ch ) )
    {
	if ( dt < TYPE_HIT + sizeof(attack_table)/sizeof(attack_table[0]) )
	    attack	= attack_table[dt - TYPE_HIT];
	else
	{
	    bug( "Dam_message: bad dt %d.", dt );
	    dt  = TYPE_HIT;
	    attack  = attack_table[0];
        }

	sprintf( buf1, "$n's poisoned %s %s $N%c", attack, vp, punct );
	sprintf( buf2, "Your poisoned %s %s $N%c", attack, vp, punct );
	sprintf( buf3, "$n's poisoned %s %s you%c", attack, vp, punct ); 
    }
    else
    {
	if ( skill )
	{
	    attack	= skill->noun_damage;
	    if ( dam == 0 )
	    {
		bool found = FALSE;

		if ( skill->miss_char && skill->miss_char[0] != '\0' )
		{
		   act( AT_HIT, skill->miss_char, ch, NULL, victim, TO_CHAR );
		   found = TRUE;
		}
		if ( skill->miss_vict && skill->miss_vict[0] != '\0' )
		{
		   act( AT_HITME, skill->miss_vict, ch, NULL, victim, TO_VICT );
		   found = TRUE;
		}
		if ( skill->miss_room && skill->miss_room[0] != '\0' )
		{
		   act( AT_ACTION, skill->miss_room, ch, NULL, victim, TO_NOTVICT );
		   found = TRUE;
		}
		if ( found )	/* miss message already sent */
		  return;
	    }
	    else
	    {
		if ( skill->hit_char && skill->hit_char[0] != '\0' )
		  act( AT_HIT, skill->hit_char, ch, NULL, victim, TO_CHAR );
		if ( skill->hit_vict && skill->hit_vict[0] != '\0' )
		  act( AT_HITME, skill->hit_vict, ch, NULL, victim, TO_VICT );
		if ( skill->hit_room && skill->hit_room[0] != '\0' )
		  act( AT_ACTION, skill->hit_room, ch, NULL, victim, TO_NOTVICT );
	    }
	}
	else if ( dt >= TYPE_HIT
	&& dt < TYPE_HIT + sizeof(attack_table)/sizeof(attack_table[0]) )
	    attack	= attack_table[dt - TYPE_HIT];
	else
	{
	    bug( "Dam_message: bad dt %d.", dt );
	    dt  = TYPE_HIT;
	    attack  = attack_table[0];
	}

	sprintf( buf1, "$n's %s %s $N%c",  attack, vp, punct );
	sprintf( buf2, "Your %s %s $N%c",  attack, vp, punct );
	sprintf( buf3, "$n's %s %s you%c", attack, vp, punct );
    }
   if( !critical )   
       sprintf( buf2, "%s You do %d points of damage.", buf2, dam );
   else
       sprintf( buf2, "%s You do %d points of damage on a ciritical hit!", buf2, dam );
   if(dt != TYPE_MISSILE)
   {
    act( AT_ACTION, buf1, ch, NULL, victim, TO_NOTVICT );
    if (!gcflag)  act( AT_HIT, buf2, ch, NULL, victim, TO_CHAR );
    if (!gvflag) act( AT_HITME, buf3, ch, NULL, victim, TO_VICT );
    }
    return;
}


void do_kill( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Kill whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) )
    {
	    send_to_char( "You must MURDER a player.\n\r", ch );
	    return;
    }

    if ( victim == ch )
    {
	send_to_char( "You hit yourself.  Ouch!\n\r", ch );
	multi_hit( ch, ch, TYPE_UNDEFINED );
	return;
    }

    if ( is_safe( ch, victim ) )
	return;

    if ( IS_AFFECTED(ch, AFF_CHARM) && ch->master == victim )
    {
    act( AT_PLAIN, "$N is your beloved master.", ch, NULL, victim, TO_CHAR );
	return;
    }

    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "You do the best you can!\n\r", ch );
	return;
    }

    if(!IS_NPC(ch))
      ch->pcdata->lost_attacks = 0;
    if ( victim->vip_flags != 0 )
       ch->alignment -= 10;

    WAIT_STATE( ch, 1 * PULSE_VIOLENCE );
    multi_hit( ch, victim, TYPE_UNDEFINED );
    return;
}



void do_murde( CHAR_DATA *ch, char *argument )
{
    send_to_char( "If you want to MURDER, spell it out.\n\r", ch );
    return;
}



void do_murder( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char logbuf[MAX_STRING_LENGTH];
    CHAR_DATA *victim;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Murder whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "Suicide is a mortal sin.\n\r", ch );
	return;
    }

    if ( is_safe( ch, victim ) )
       return;
        
    if ( IS_AFFECTED(ch, AFF_CHARM) ) 
    {
      if ( ch->master == victim )
      {
        act( AT_PLAIN, "$N is your beloved master.", ch, NULL, victim, TO_CHAR );
	return;
      }
    }

    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "You do the best you can!\n\r", ch );
	return;
    }
    if(!IS_NPC(ch))
      ch->pcdata->lost_attacks = 0;
    if ( !IS_NPC( victim ) && IS_SET( ch->act, PLR_NICE ) )
    {
      send_to_char( "You feel too nice to do that!\n\r", ch );
      return;
    }

    if (!IS_NPC(ch) && IS_SET(ch->pcdata->act2, ACT_BOUND))
    {
	send_to_char("Thats a bit hard to do right now...\n\r", ch);
	return;
    }

    ch->alignment -= 10;
    
    if((!ch->in_room->area || !in_arena(ch)) || !IS_NPC(ch) || !IS_NPC(victim))
    {
      sprintf( logbuf, "%s: murder %s", ch->name, argument);
      log_string(logbuf);
    }
    WAIT_STATE( ch, 1 * PULSE_VIOLENCE );
    multi_hit( ch, victim, TYPE_UNDEFINED );
    return;
}

bool in_arena( CHAR_DATA *ch )
{

if ( !str_cmp( ch->in_room->area->filename, "arena.are" ) )
  return TRUE;

if ( ch->in_room->vnum < 29 || ch->in_room->vnum > 43 )
  return FALSE;

return TRUE;
}


void do_flee( CHAR_DATA *ch, char *argument )
{
    ROOM_INDEX_DATA *was_in;
    ROOM_INDEX_DATA *now_in;
    char buf[MAX_STRING_LENGTH];
    int attempt;
    sh_int door;
    EXIT_DATA *pexit;

    if ( !who_fighting( ch ) )
    {
	if ( ch->position == POS_FIGHTING )
	{
	  if ( ch->mount )
	    ch->position = POS_MOUNTED;
	  else
	    ch->position = POS_STANDING;
	}
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }

    if ( ch->move <= 0 )
    {
	send_to_char( "You're too exhausted to flee from combat!\n\r", ch );
	return;
    }

    if ( IS_NPC(ch) && IS_SET(ch->act, ACT_NOFLEE) && !IS_AFFECTED(ch,AFF_CHARM))
    {
	send_to_char( "You're too brave to flee!\n\r", ch);
	return;
    }

    if (!IS_NPC(ch) && IS_SET(ch->pcdata->act2, ACT_BOUND))
    {
        send_to_char("Thats a bit hard to do right now...\n\r", ch);
        return;
    }

    /* No fleeing while stunned. - Narn */
    if ( ch->position < POS_FIGHTING )
	return; 

    was_in = ch->in_room;
    for ( attempt = 0; attempt < 8; attempt++ )
    {

	door = number_door( );
	if ( ( pexit = get_exit(was_in, door) ) == NULL
	||   !pexit->to_room
	|| ( IS_SET(pexit->exit_info, EX_CLOSED) )
	|| ( IS_NPC(ch)
	&&   IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB) ) )
	    continue;
 
        REMOVE_BIT   ( ch->affected_by, AFF_SNEAK );
	if ( ch->mount && ch->mount->fighting )
	    stop_fighting( ch->mount, TRUE );
	move_char( ch, pexit, 0 );
	if ( ( now_in = ch->in_room ) == was_in )
	    continue;

	ch->in_room = was_in;
	act( AT_FLEE, "$n runs for cover!", ch, NULL, NULL, TO_ROOM );
	ch->in_room = now_in;
	act( AT_FLEE, "$n glances around for signs of pursuit.", ch, NULL, NULL, TO_ROOM );
        sprintf(buf, "You run for cover!");
        send_to_char( buf, ch );
    
	stop_fighting( ch, TRUE );
	return;
    }

    sprintf(buf, "You attempt to run for cover!");
    send_to_char( buf, ch );
    return;
}

bool get_cover( CHAR_DATA *ch )
{
    ROOM_INDEX_DATA *was_in;
    ROOM_INDEX_DATA *now_in;
    int attempt;
    sh_int door;
    EXIT_DATA *pexit;

    if ( !who_fighting( ch ) )
	return FALSE;

    if ( ch->position < POS_FIGHTING )
	return FALSE; 

    if ( IS_NPC(ch) && IS_SET(ch->act, ACT_NOFLEE) && !IS_AFFECTED(ch,AFF_CHARM))
	return FALSE;

    was_in = ch->in_room;

    for ( attempt = 0; attempt < 10; attempt++ )
    {

	door = number_door( );
	if ( ( pexit = get_exit(was_in, door) ) == NULL
	||   !pexit->to_room
	|| ( IS_SET(pexit->exit_info, EX_CLOSED))
	|| ( IS_NPC(ch)
	&&   IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB) ) )
	    continue;
 
        REMOVE_BIT   ( ch->affected_by, AFF_SNEAK );
	if ( ch->mount && ch->mount->fighting )
	    stop_fighting( ch->mount, TRUE );
	move_char( ch, pexit, 0 );
	if ( ( now_in = ch->in_room ) == was_in )
	    continue;

	ch->in_room = was_in;
	act( AT_FLEE, "$n sprints for cover!", ch, NULL, NULL, TO_ROOM );
	ch->in_room = now_in;
	act( AT_FLEE, "$n spins around and takes aim.", ch, NULL, NULL, TO_ROOM );

	stop_fighting( ch, TRUE );

	return TRUE;
    }

    return FALSE;
}

void do_sla( CHAR_DATA *ch, char *argument )
{
    send_to_char( "If you want to SLAY, spell it out.\n\r", ch );
    return;
}

void do_slay( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );
    one_argument( argument, arg2 );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Slay whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Suicide is a mortal sin.\n\r", ch );
	return;
    }

    if ( !str_cmp( arg2, "immolate" ) )
    {
      act( AT_FIRE, "Your fireball turns $N into a blazing inferno.",  ch, NULL, victim, TO_CHAR    );
      act( AT_FIRE, "$n releases a searing fireball in your direction.", ch, NULL, victim, TO_VICT    );
      act( AT_FIRE, "$n points at $N, who bursts into a flaming inferno.",  ch, NULL, victim, TO_NOTVICT );
    }

    else if ( !str_cmp( arg2, "shatter" ) )
    {
      act( AT_LBLUE, "You freeze $N with a glance and shatter the frozen corpse into tiny shards.",  ch, NULL, victim, TO_CHAR    );
      act( AT_LBLUE, "$n freezes you with a glance and shatters your frozen body into tiny shards.", ch, NULL, victim, TO_VICT    );
      act( AT_LBLUE, "$n freezes $N with a glance and shatters the frozen body into tiny shards.",  ch, NULL, victim, TO_NOTVICT );
    }

    else if ( !str_cmp( arg2, "demon" ) )
    {
      act( AT_IMMORT, "You gesture, and a slavering demon appears.  With a horrible grin, the",  ch, NULL, victim, TO_CHAR );
      act( AT_IMMORT, "foul creature turns on $N, who screams in panic before being eaten alive.",  ch, NULL, victim, TO_CHAR );
      act( AT_IMMORT, "$n gestures, and a slavering demon appears.  The foul creature turns on",  ch, NULL, victim, TO_VICT );
      act( AT_IMMORT, "you with a horrible grin.   You scream in panic before being eaten alive.",  ch, NULL, victim, TO_VICT );
      act( AT_IMMORT, "$n gestures, and a slavering demon appears.  With a horrible grin, the",  ch, NULL, victim, TO_NOTVICT );
      act( AT_IMMORT, "foul creature turns on $N, who screams in panic before being eaten alive.",  ch, NULL, victim, TO_NOTVICT );
    }

    else if ( !str_cmp( arg2, "pounce" ) && get_trust(ch) >= LEVEL_ASCENDANT )
    {
      act( AT_BLOOD, "Leaping upon $N with bared fangs, you tear open $S throat and toss the corpse to the ground...",  ch, NULL, victim, TO_CHAR );
      act( AT_BLOOD, "In a heartbeat, $n rips $s fangs through your throat!  Your blood sprays and pours to the ground as your life ends...", ch, NULL, victim, TO_VICT );
      act( AT_BLOOD, "Leaping suddenly, $n sinks $s fangs into $N's throat.  As blood sprays and gushes to the ground, $n tosses $N's dying body away.",  ch, NULL, victim, TO_NOTVICT );
    }
 
    else if ( !str_cmp( arg2, "slit" ) && get_trust(ch) >= LEVEL_ASCENDANT )
    {
      act( AT_BLOOD, "You calmly slit $N's throat.", ch, NULL, victim, TO_CHAR );
      act( AT_BLOOD, "$n reaches out with a clawed finger and calmly slits your throat.", ch, NULL, victim, TO_VICT );
      act( AT_BLOOD, "$n calmly slits $N's throat.", ch, NULL, victim, TO_NOTVICT );
    }

    else if ( !str_cmp( arg2, "mukao" ) && get_trust(ch) >= LEVEL_ASCENDANT )
    {
      act( AT_BLOOD, "You put an icy finger to $N's forehead, and watch as they dissipate into a cloud of 1's and 0's.", ch, NULL, victim, TO_CHAR );
      act( AT_BLOOD, "$n puts an icy finger to your forehead... feeling a little strange, you look down at your coldly sweating hands. Suddenly, the hands begin to pulse... and then the tips of your fingers shimmer and fall to the ground, seemingly ones and zeros. This phenomena creeps up your entire body until...", ch, NULL, victim, TO_VICT );
      act( AT_BLOOD, "$n puts an icy finger to $N's forehead and you watch as $E becomes nothing but a pile of 1's and 0's.", ch, NULL, victim, TO_NOTVICT );
    }

    else if ( !str_cmp( arg2, "jungle" ) && get_trust(ch) >= LEVEL_ASCENDANT )
    {
      act( AT_GREEN, "You point your hand at $N and scream 'EWOK CHARGE!'  Hundreds of Ewoks pop out of suddenly appearing trees and eviscerate the target.", ch, NULL, victim, TO_CHAR );
      act( AT_GREEN, "$n points at you and screams 'EWOK CHARGE!'  Hundreds of Ewoks pop out of suddenly appearing trees and rip you to pieces.", ch, NULL, victim, TO_VICT );
      act( AT_GREEN, "$n points at $N and screams 'EWOK CHARGE!'  Hundreds of Ewoks pop out of suddenly appearing trees and eviscerate $N.", ch, NULL, victim, TO_NOTVICT );
    }
    else if ( !str_cmp( arg2, "zot" ) && get_trust(ch) >= LEVEL_ASCENDANT )
    {
      act( AT_BLOOD, "You wave your hand, summoning a fiery meteor and dropping it on $N!", ch, NULL, victim, TO_CHAR );
      act( AT_BLOOD, "$n appears before you, smiling cruely as he scans the skies above you.  Suddenly a massive meteor falls and smashes into you, leaving nothing but a huge crater where you were standing.", ch, NULL, victim, TO_VICT );
      act( AT_BLOOD, "$n appears, smiling cruely as a massive meteor crushes $N, leaving a smoking crater in the ground.", ch, NULL, victim, TO_NOTVICT );
    }

    else
    {
      act( AT_IMMORT, "You slay $N in cold blood!",  ch, NULL, victim, TO_CHAR    );
      act( AT_IMMORT, "$n slays you in cold blood!", ch, NULL, victim, TO_VICT    );
      act( AT_IMMORT, "$n slays $N in cold blood!",  ch, NULL, victim, TO_NOTVICT );
    }

    set_cur_char(victim);
    raw_kill( ch, victim );
    return;
}

bool check_critical( CHAR_DATA *ch, int diceroll, bool wield, int armor )
{
   OBJ_DATA *wield2;
   int min_roll;

   if( IS_NPC(ch) )
    {
	if( ( diceroll + ch->hitroll ) >= armor )
	    return TRUE;
   	else
	    return FALSE;
    }

   if( wield == FALSE )
    {
      if( !HAS_FEAT2( ch, MARTIAL_ARTS ) )
	return FALSE;
      if( HAS_FEAT2( ch, MARTIAL_ARTS ) )
	min_roll = 20;
      if( HAS_FEAT2( ch, IMP_MARTIAL_ARTS ) )
	min_roll -= 1;
      if( HAS_FEAT2( ch, ADV_MARTIAL_ARTS ) )
	min_roll -= 1;
      if( diceroll >= min_roll )
	return TRUE;
    }
   wield2 = get_eq_char(ch, WEAR_WIELD);
   if( wield && wield2 && wield2->item_type == ITEM_WEAPON )
    {
     if( ( wield2->value[3] == WEAPON_BLASTER || wield2->value[3] == WEAPON_BLASTER_RIFLE || wield2->value[3] == WEAPON_HEAVY ) && wield2->blaster_setting == BLASTER_STUN )
        return FALSE;
     if( wield2->value[3] == WEAPON_SIMPLE )
      {
	min_roll = 20;
	if( HAS_FEAT2( ch, IMP_CRITICAL_SIMPLE ) )
	  min_roll -= 1;
      }
     if( wield2->value[3] == WEAPON_VIBRO )
      {
	min_roll = 20;
	if( HAS_FEAT2( ch, IMP_CRITICAL_VIBRO ) )
	  min_roll -= 1;
      }
     if( wield2->value[3] == WEAPON_LIGHTSABER || wield2->value[3] == WEAPON_DUAL_LIGHTSABER )
      {
	min_roll = 19;
	if( HAS_FEAT2( ch, IMP_CRITICAL_LIGHTSABER ) )
	  min_roll -= 2;
      }
     if( wield2->value[3] == WEAPON_FORCE_PIKE )
      {
	min_roll = 20;
	if( HAS_FEAT2( ch, IMP_CRITICAL_FORCEPIKE ) )
	  min_roll -= 1;
      }
     if( wield2->value[3] == WEAPON_BLASTER )
      {
	min_roll = 20;
	if( HAS_FEAT2( ch, IMP_CRITICAL_PISTOLS ) )
	  min_roll -= 1;
      }
     if( wield2->value[3] == WEAPON_BLASTER_RIFLE )
      {
	min_roll = 19;
	if( HAS_FEAT2( ch, IMP_CRITICAL_RIFLES ) )
	  min_roll -= 2;
      }
     if( wield2->value[3] == WEAPON_HEAVY )
      {
	min_roll = 19;
	if( HAS_FEAT2( ch, IMP_CRITICAL_HEAVY ) )
	  min_roll -= 2;
      }
     if( wield2->value[3] == WEAPON_BOWCASTER )
      {
	min_roll = 19;
	if( HAS_FEAT2( ch, IMP_CRITICAL_BOWCASTER ) )
	  min_roll -= 2;
      }
     if( diceroll < min_roll )
	return FALSE;
     if( ( diceroll + ch->hitroll ) >= armor )
	return TRUE;
     /* need to add back in min_roll when we add in bodyparts */
    }
  
  return FALSE;
};

void check_fumble( CHAR_DATA *ch, OBJ_DATA *wield )
{
  CHAR_DATA *victim;
  CHAR_DATA *gch;
  int to_hit, vict_ac;
  int members=0;
  int random_vict;

  if( IS_IMMORTAL(ch) || IS_NPC(ch) )
  	return;
    
  for ( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
   {
	if ( gch == ch )
	    continue;
	if ( is_same_group( gch, ch ) )
	    members++;
   }

  if( members == 0 )
   {
	obj_from_char( wield );
	obj_to_room( wield, ch->in_room );
	act( AT_BLOOD, "A mistake during combat has caused you to drop your weapon!&w\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLOOD, "A mistake during combat has caused $n to drop $s weapon!&w\n\r", ch, NULL, NULL, TO_NOTVICT );
	return;
   }

  random_vict = number_range(1, members);
  members = 0;

  for ( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
   {
	if ( is_same_group( gch, ch ) )
	    members++;
	if ( members == random_vict )
	 {
	    victim = gch;
	    break;
	 }
   }
  if( !victim )
   {
	bug( "&RBug: Check Fumber: No Victim&w\n\r", 0 );
	return;
   }
  to_hit = number_range(1, 20) + ch->hitroll;
  vict_ac = ( GET_AC(victim) - stat_table[get_curr_dex(victim)].mod );
  if( to_hit < vict_ac )
   {
	act( AT_YELLOW, "An error on your part causes you to almost hit $N!&w\n\r", ch, NULL, victim, TO_CHAR );  
	act( AT_YELLOW, "An error on $n's part causes $m to almost hit you!&w\n\r", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "An error on $n's part causes $m to almost hi $N!&w\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
   }
  victim->hit -= wield->value[2];
  act( AT_YELLOW, "An error on your part causes you to hit $N!&w\n\r", ch, NULL, victim, TO_CHAR );
  act( AT_YELLOW, "An error on $n's part causes $m to hit you!&w\n\r", ch, NULL, victim, TO_VICT );
  act( AT_YELLOW, "An error on $n's part causes $m to hit $N!&w\n\r", ch, NULL, victim, TO_NOTVICT );
  return;
}
