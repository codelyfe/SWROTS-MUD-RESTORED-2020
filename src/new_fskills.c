#include <math.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"

void do_alchemy( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg1[MAX_INPUT_LENGTH];
  int chance, diff, cost, dam;

  argument = one_argument( argument, arg1 );

  if( IS_NPC(ch) )
   	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[ALCHEMY_SKILL] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( arg1[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&WAlchemy <Modification> <Victim>\n\r", ch );
	send_to_char( "  &GMods: &w&Wclaws, horns, darkvision, defense,\n\r", ch );
	send_to_char( "          &w&Wstrength, dexterity, constitution,\n\r", ch );
        send_to_char( "          &w&Wintelligence, wisdom, charisma\n\r", ch );
	return;
   }
  if( str_cmp(arg1, "claw") && str_cmp(arg1, "claws") && str_cmp(arg1, "horn")
   && str_cmp(arg1, "horns") && str_cmp(arg1, "dark") && str_cmp(arg1, "darkvision")
   && str_cmp(arg1, "defense") && str_cmp(arg1, "str") && str_cmp(arg1, "strength")
   && str_cmp(arg1, "dex") && str_cmp(arg1, "dexterity") && str_cmp(arg1, "con")
   && str_cmp(arg1, "constitution") && str_cmp(arg1, "int") && str_cmp(arg1, "intelligence")
   && str_cmp(arg1, "wis") && str_cmp(arg1, "wisdom") && str_cmp(arg1, "cha")
   && str_cmp(arg1, "charisma") )
   {
	do_alchemy( ch, "" );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat person isn't here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
   {
	send_to_char( "&rNot on my NPCs!&w\n\r", ch );
	return;
   }
  if( victim->position > POS_SITTING )
   {
	send_to_char( "&rYou can't do that while they are in that position.&w\n\r", ch );
	return;
   }
  if( !str_cmp(arg1, "claw") || !str_cmp(arg1, "claws") )
   {
	if( HAS_BODYPART(ch, PART_CLAWS) || IS_SET(ch->pcdata->alchemy, ALCHEMY_CLAWS) )
	 {
     	  if( victim == ch )
	   send_to_char( "&rYou already possess claws.&w\n\r", ch );
	  else
	   ch_printf( ch, "&G%s&w&W already possesses claws.\n\r", victim->name );
  	  return;
	 }
   }
  if( ( !str_cmp(arg1, "horn") || !str_cmp(arg1, "horns") ) && HAS_BODYPART(victim, PART_HORNS) )
   {
	if( victim == ch )
	 send_to_char( "&rYou already possess horns.&w\n\r", ch );
	else
	 ch_printf( ch, "&G%s&w&W already possesses horns.&w\n\r", victim->name );
	return;
   }
  if( ( !str_cmp(arg1, "dark") || !str_cmp(arg1, "darkvision") ) && ( IS_AFFECTED(victim, AFF_DARKVISION) || IS_SET(victim->pcdata->alchemy, ALCHEMY_DARKVISION) ) )
   {
	if( victim == ch )
	 send_to_char( "&rYou already possess darkvision.&w\n\r", ch );
	else
	 ch_printf( ch, "&G%s&w&W already possesses darkvision.&w\n\r", victim->name );
	return;
   }
  chance = ( number_range(1, 20) + ch->force_level[ALCHEMY_SKILL] + stat_table[get_curr_int(ch)].mod );
  if( IS_TAINTED(ch) )
   chance += 2;
  if( IS_DARK(ch) )
   chance += 4;
  if( !str_cmp( arg1, "horn" ) || !str_cmp( arg1, "horns" ) )
	diff = 15;
  else if( !str_cmp( arg1, "claw" ) || !str_cmp( arg1, "claws" ) )
	diff = 15;
  else if( !str_cmp( arg1, "darkvision" ) )
	diff = 20;
  else if( !str_cmp( arg1, "defense" ) )
	diff = ( 20 + ( victim->pcdata->alchemy_mod * 5 ) );
  else
	diff = ( 25 + ( victim->pcdata->alchemy_mod * 5 ) );
  cost = ( 10000 + (victim->pcdata->alchemy_mod * 500) );
  if( ch->gold < cost )
   {
	ch_printf( ch, "&w&WIt will cost you &G%d&w&W credits, which you do not have.\n\r", cost );
	return;
   }
  gain_darkpoint( ch );
  ch->gold -= cost;
  if( chance < diff )
   {
	act( AT_BLOOD, "There is a slight error during the process, causing $N great harm.\n\r", ch, NULL, victim, TO_CHAR );
 	act( AT_BLOOD, "There is a slight error during the process, causing you great harm.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "There is a slight error during the process, causing $N great harm.\n\r", ch, NULL, victim, TO_NOTVICT );
	dam = number_range( 3, 12 );
	victim->max_hit -= dam;
	victim->hit -= dam;
	update_pos( victim );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
	return;
   }
  if( !str_cmp( arg1, "claw" ) || !str_cmp( arg1, "claws" ) )
   {
	SET_BIT(victim->xflags, PART_CLAWS);
	SET_BIT(victim->pcdata->alchemy, ALCHEMY_CLAWS);
	act( AT_YELLOW, "Through the dark side's alchemical arts, $N's hands grow into fierce claws.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_YELLOW, "Through the dark side's alchemical arts, your hands grow into fierce claws.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "Through the dark side's alchemical arts, $N's hands grow into fierce claws.\n\r", ch, NULL, victim, TO_NOTVICT );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
	victim->pcdata->alchemy_mod += 1;
	return;
   }
  else if( !str_cmp( arg1, "horn" ) || !str_cmp( arg1, "horns" ) )
   {
	SET_BIT(victim->xflags, PART_HORNS);
	SET_BIT(victim->pcdata->alchemy, ALCHEMY_HORNS);
	act( AT_YELLOW, "Through the dark side's alchemical arts, $N sprouts two horns.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_YELLOW, "Through the dark side's alchemical arts, your head sprouts two horns.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "Through the dark side's alchemical arts, $N sprouts two horns.\n\r", ch, NULL, victim, TO_NOTVICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "dark" ) || !str_cmp( arg1, "darkvision" ) )
   {
	SET_BIT(victim->pcdata->alchemy, ALCHEMY_DARKVISION);
	act( AT_BLUE, "$N's eyes glaze over as the Dark Side takes its effect.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLUE, "You feels your eyes glaze over ad the Dark Side takes its effect.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_BLUE, "$N's eyes glaze over as the Dark Side takes its effect.\n\r", ch, NULL, victim, TO_NOTVICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "defense" ) )
   {
	if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_DEFENSE) )
	  SET_BIT(victim->pcdata->alchemy, ALCHEMY_DEFENSE);
	victim->armor += 3;
	act( AT_WHITE, "$N's skin hardens as the alchemy takes hold.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_WHITE, "Your skin hardens as the alchemy takes hold.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_WHITE, "$N's skin hardens as the alchemy takes hold.\n\r", ch, NULL, victim, TO_NOTVICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "str" ) || !str_cmp( arg1, "strength" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_STRENGTH) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_STRENGTH);
        victim->perm_str += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "You feel your body grow stronger as the alchemy changes your body.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "dex" ) || !str_cmp( arg1, "dexterity" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_DEXTERITY) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_DEXTERITY);
        victim->perm_dex += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "You feel your body grow more dexterous as the alchemy effects you.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "con" ) || !str_cmp( arg1, "constitution" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_CONSTITUTION) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_CONSTITUTION);
        victim->perm_con += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "You feel your body grow more resilant as the alchemy takes effect.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "int" ) || !str_cmp( arg1, "intelligence" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_INTELLIGENCE) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_INTELLIGENCE);
        victim->perm_int += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "You feel your mind open to the mysteries of the Force.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "wis" ) || !str_cmp( arg1, "wisdom" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_WISDOM) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_WISDOM);
        victim->perm_wis += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "The Dark Force Spirits bestow upon you great wisdom.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }
  else if( !str_cmp( arg1, "cha" ) || !str_cmp( arg1, "charisma" ) )
   {
        if( !IS_SET(victim->pcdata->alchemy, ALCHEMY_CHARISMA) )
          SET_BIT(victim->pcdata->alchemy, ALCHEMY_CHARISMA);
        victim->perm_cha += 1;
        act( AT_WHITE, "You watch as the alchemy takes effect.\n\r", ch, NULL, victim, TO_CHAR );
        act( AT_WHITE, "Your charisma grows as your body adjusts to the presense of the alchemy.\n\r", ch, NULL, victim, TO_VICT );
        WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
        WAIT_STATE( victim, PULSE_PER_SECOND * 2 );
        victim->pcdata->alchemy_mod += 1;
        return;
   }

 do_alchemy( ch, "" );
 return;
}

void do_battlemind( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  int chance;
  int bonus=0;
  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[BATTLEMIND_SKILL] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( IS_AFFECTED( ch, AFF_BATTLEMIND ) )
   {
	send_to_char( "&w&WYou are already affected by Battlemind.\n\r", ch );
	return;
   }
  chance = ( number_range( 1, 20 ) + ch->force_level[BATTLEMIND_SKILL] + stat_table[get_curr_con(ch)].mod );
  if( ch->hit < 9 )
   {
	send_to_char( "&rYou lack the hitpoints required to do this.&w\n\r", ch );
	return;
   }
  if( chance < 1 )
   {
	ch->hit -= 2;
	update_pos( ch );
	send_to_char( "&rYou could not harness the power of the force.&w\n\r", ch );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	return;
   }
  if( chance >= 1 && chance < 5 )
   	bonus = 1;
  else if( chance >= 5 && chance < 15 )
	bonus = 2;
  else if( chance >= 15 && chance < 25 )
	bonus = 3;
  else if( chance >= 25 && chance < 35 )
	bonus = 4;
  else if( chance >= 35 )
	bonus = 5;
  ch->hit -= ( bonus + 2 );
  update_pos( ch );
  af.type = gsn_battlemind;
  af.duration = ( 10 * ch->force_level[BATTLEMIND_SKILL]);
  af.location = APPLY_HITROLL;
  af.modifier = bonus;
  af.bitvector = AFF_BATTLEMIND;
  affect_to_char(ch, &af);
  send_to_char( "Your combat prowess increases.\n\r", ch );
  return;
}

void do_enhance( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  int chance, bonus;

  if( IS_NPC( ch ) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[ENHANCE_ABILITY] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&GEnhance strength or dexterity?&w\n\r", ch );
	return;
   }
  if( str_cmp( argument, "str" ) && str_cmp( argument, "strength" ) 
   && str_cmp( argument, "dex" ) && str_cmp( argument, "dexterity" ) )
   {
	do_enhance( ch, "" );
	return;
   }
  if( IS_AFFECTED( ch, AFF_ENHANCE ) )
   {
	send_to_char( "&rThe Force is already affecting one of your abilities.&w\n\r", ch );
	return;
   }
  chance = ( number_range( 1, 20 ) + ch->force_level[ENHANCE_ABILITY] + stat_table[get_curr_con(ch)].mod );
  ch->hit -= 3;
  if( chance < 15 )
   {
	act( AT_BLUE, "You fail to harness the power of the Force.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLUE, "$n fails to harness the power of the Force.\n\r", ch, NULL, NULL, TO_NOTVICT );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	return;
   }
  if( chance >= 15 && chance < 20 )
	bonus = 2;
  else if( chance >= 20 && chance < 25 )
	bonus = 4;
  else if( chance >= 25 && chance < 30 )
	bonus = 6;
  else if( chance >= 30 )
	bonus = 8;
  if( !str_cmp( argument, "str" ) || !str_cmp( argument, "strength" ) )
   {
     	act( AT_BLUE, "Your strength is enhanced through the power of the Force.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLUE, "$n appears stronger.\n\r", ch, NULL, NULL, TO_NOTVICT );
	af.location = APPLY_STR;
   }
  else if( !str_cmp( argument, "dex" ) || !str_cmp( argument, "dexterity" ) )
   {
	act( AT_BLUE, "Your dexterity is enhanced through the power of the Force.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLUE, "$n appears more dexterous.\n\r", ch, NULL, NULL, TO_NOTVICT );
	af.location = APPLY_DEX;
   }
  af.type = gsn_enhance_ability;
  af.duration = ( 5 * ch->force_level[ENHANCE_ABILITY] );
  af.modifier = bonus;
  af.bitvector = AFF_ENHANCE;

  affect_to_char( ch, &af );

  WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
  return;
 
}

void do_enhancesenses( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af1;
  AFFECT_DATA af2;
  AFFECT_DATA af3;
  int chance;
  int bonus=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[ENHANCE_SENSES] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( IS_AFFECTED( ch, AFF_ENHANCESENSES ) )
   {
	send_to_char( "&rYou are already affected by this Force Skill.&w\n\r", ch );
	return;
   }
  chance = ( number_range(1, 20) + ch->force_level[ENHANCE_SENSES] + stat_table[get_curr_wis(ch)].mod );
  ch->hit -= 3;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_PER_SECOND*3 );
  if( chance < 10 )
   {
	act( AT_BLUE, "You meditate for a moment and fail to harness the power of the Force.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLUE, "$n meditates for a moment.\n\r", ch, NULL, NULL, TO_NOTVICT );
	return;
   }
  if( chance >= 10 && chance <= 14 )
	bonus = 2;
  else if( chance >= 15 && chance <= 19 )
	bonus = 4;
  else if( chance >= 20 && chance <= 24 )
	bonus = 6;
  else if( chance >= 25 )
	bonus = 8;
  af1.type = gsn_enhance_senses;
  af1.duration = ( 5 * ch->force_level[ENHANCE_SENSES] );
  af1.modifier = bonus;
  af1.location = APPLY_LISTEN;
  af1.bitvector = AFF_ENHANCESENSES; 
  affect_to_char( ch, &af1 );
  af2.type = gsn_enhance_senses;
  af2.duration = ( 5 * ch->force_level[ENHANCE_SENSES] );
  af2.modifier = bonus;
  af2.location = APPLY_SEARCH;
  af2.bitvector = AFF_ENHANCESENSES;
  affect_to_char( ch, &af2 );
  af3.type = gsn_enhance_senses;
  af3.duration = ( 5 * ch->force_level[ENHANCE_SENSES] );
  af3.modifier = bonus;
  af3.location = APPLY_SPOT;
  af3.bitvector = AFF_ENHANCESENSES;
  affect_to_char( ch, &af3 );
  act( AT_BLUE, "You harness the power of the Force to increase your senses.\n\r", ch, NULL, NULL, TO_CHAR );
  act( AT_BLUE, "$n opens $s eyes after meditating, appearing more aware.\n\r", ch, NULL, NULL, TO_NOTVICT );
  return;
}

void do_farseeing( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  ROOM_INDEX_DATA *iRoom;
  int chance, resist;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FARSEEING_SKILL] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&rWhom do you wish to attempt to find?&w\n\r", ch );
	return;
   }
  if( ch->hit < 5 )
   {
	send_to_char( "&rYou lack the energy required to do this.&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_world( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character isn't online.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rThats just foolish.&w\n\r", ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "&rYou should know Droids aren't linked to the Force.&w\n\r", ch );
	return;
   }
  iRoom = get_room_index( victim->in_room->vnum );
  if( !iRoom )
   {
	send_to_char( "&rBad victim room, inform an Immortal.&w\n\r", ch );
	return;
   }
  ch->hit -= 3;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_PER_SECOND*3 );
  chance = ( number_range( 1, 20 ) + ch->force_level[FARSEEING_SKILL] + stat_table[get_curr_wis(ch)].mod );
  if( !IS_NPC(victim) )
    resist = ( number_range( 1, 20 ) + ch->willpower );
  else
    resist = ( number_range( 10, 30 ) );
  if( IS_AFFECTED( victim, AFF_FORCE_RESIST ) )
   	resist += 6;
  if( resist > chance )
   {
	act( AT_BLOOD, "You scan the galaxy for your target, but fail to locate $M.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "$n closes $s eyes for a moment.\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
   }
  send_to_char( "\n\r", ch );
  ch_printf(ch, "&R-=&r( &G&W%s &G&r)&R=-&C&w\n\r", iRoom->name);
  set_char_color( AT_RMDESC, ch ); 	
	
  if ( !IS_NPC(ch) && !IS_SET(ch->act, PLR_BRIEF) )
    send_to_char( iRoom->description, ch );
  show_ships_to_char( iRoom->first_ship, ch );
  show_list_to_char( iRoom->first_content, ch, FALSE, FALSE );
  show_char_to_char( iRoom->first_person,  ch );
  return;
}

void do_fear( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  CHAR_DATA *victim;
  int chance;
  int penalty=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FEAR_SKILL] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&rWho's deepest fears do you wish to uncover?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character isn't in this room.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rYou already frighten even yourself.&w\n\r", ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "&rNot on Droids.&w\n\r", ch );
	return;
   }
  if( IS_AFFECTED( victim, AFF_FEAR ) )
   {
	send_to_char( "&rThey are already scared.&w\n\r", ch );
	return;
   }
  if( ch->hit < 3 )
   {
	send_to_char( "&rYou lack the vitality to do this.&w\n\r", ch );
	return;
   }
  ch->hit -= 2;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_VIOLENCE );
  gain_darkpoint( ch );
  chance = ( number_range( 1, 20 ) + ch->force_level[FEAR_SKILL] + stat_table[get_curr_wis(ch)].mod );
  if( IS_TAINTED(ch) )
	chance += 2;
  if( IS_DARK(ch) )
	chance += 4;
  if( chance < 10 )
   {
	act( AT_YELLOW, "$N laughs at your attempts to be frightening.\n\r", ch, NULL, victim, TO_CHAR );
 	act( AT_YELLOW, "You laugh at $n's attempts to be frightening.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "$N laughs at $n's attempts to be frightening.\n\r", ch, NULL, victim, TO_NOTVICT );
	return;
   }
  if( chance >= 10 && chance <= 14 )
   	penalty = 2;
  else if( chance >= 15 && chance <= 19 )
	penalty = 4;
  else if( chance >= 20 && chance <= 24 )
	penalty = 6;
  else if( chance >= 25 && chance <= 29 )
	penalty = 8;
  else if( chance >= 30 )
	penalty = 10;
  af.type = gsn_fear;
  af.duration = ( 4 * ch->force_level[FEAR_SKILL] );
  af.modifier = -penalty;
  af.location = APPLY_HITROLL;
  af.bitvector = AFF_FEAR;
  affect_to_char( victim, &af );
  act( AT_RED, "$n stares at you menacingly and a strong wave of fear washes over you.\n\r", ch, NULL, victim, TO_VICT );
  act( AT_RED, "You stare menacingly at $N.\n\r", ch, NULL, victim, TO_CHAR );
  act( AT_RED, "$n stares at $N menacingly and $N shudders in fear.\n\r", ch, NULL, victim, TO_NOTVICT );
  return;
}

void do_forcedefense( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  int chance;
  int bonus=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FORCE_DEFENSE] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( IS_AFFECTED( ch, AFF_FDEFENSE ) )
   {
	send_to_char( "&rYou are already protected by the power of the Force.&w\n\r", ch );
	return;
   }
  if( ch->hit < 4 )
   {
	send_to_char( "&rYou lack the strength to do this.&w\n\r", ch );
	return;
   }
  ch->hit -= 3;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_PER_SECOND*2 );
  chance = ( number_range( 1, 20 ) + ch->force_level[FORCE_DEFENSE] + stat_table[get_curr_cha(ch)].mod );
  if( chance < 10 )
   {
	act( AT_RED, "You fail to harness the power of the Force.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_RED, "$n closes $s eyes, looking slightly unsettled.\n\r", ch, NULL, NULL, TO_NOTVICT );
	return;
   }
  if( chance >= 10 && chance <= 14 )
  	bonus = 2;
  else if( chance >= 15 && chance <= 19 )
	bonus = 4;
  else if( chance >= 20 && chance <= 24 )
	bonus = 6;
  else if( chance >= 25 && chance <= 29 )
	bonus = 8;
  else if( chance >= 30 )
	bonus = 10;
  act( AT_BLUE, "You harness the power of the Force and you feel more protected.\n\r", ch, NULL, NULL, TO_CHAR );
  act( AT_BLUE, "$n emits an aura of protection.\n\r", ch, NULL, NULL, TO_NOTVICT );
  af.type = gsn_force_defense;
  af.duration = ( 3 * ch->force_level[FORCE_DEFENSE] );
  af.location = APPLY_WILLPOWER;
  af.modifier = bonus;
  af.bitvector = AFF_FDEFENSE;
  affect_to_char( ch, &af );
  return;
}

void do_forcegrip( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *vict;
  int chance, resist, diff;
  int dam=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FORCE_GRIP] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&rChoke who?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character isn't here.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rWhat good would that do?&w\n\r", ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "&rNot on Droids.&w\n\r", ch );
	return;
   }
  if( IS_SET(ch->in_room->room_flags, ROOM_SAFE ) )
   {
	send_to_char( "&rYou will have to do that someplace else.&w\n\r", ch );
	return;
   }
  if( ch->hit < 5 )
   {
	send_to_char( "&rYou lack the strength to do this.&w\n\r", ch );
	return;
   }
  gain_darkpoint( ch );
  ch->hit -= 4;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_PER_SECOND*2 );
  chance = ( number_range( 1, 20 ) + ch->force_level[FORCE_GRIP] + stat_table[get_curr_int(ch)].mod );
  if( IS_DARK(ch) )
	chance += 4;
  if( IS_TAINTED(ch) )
	chance += 2;
  if( !IS_NPC(victim) )
    resist = ( number_range( 1, 20 ) + ch->willpower );
  else
    resist = 18;
  if( chance < 10 )
	diff = 10;
  else if( chance >= 10 && chance <= 19 )
	diff = 15;
  else if( chance >= 20 )
	diff = 20;
  dam = number_range( 3, 18 );
  if( resist >= diff )
	dam = dam/2;
  act( AT_BLOOD, "You harness the deadly power of the Force to choke $N.\n\r", ch, NULL, victim, TO_CHAR );
  act( AT_BLOOD, "$n harnesses the deadly power of the Force to choke you.\n\r", ch, NULL, victim, TO_VICT );
  act( AT_BLOOD, "$n harnesses the deadly power of the Force to choke $N.\n\r", ch, NULL, victim, TO_NOTVICT );
  WAIT_STATE( victim, PULSE_PER_SECOND*2);
  victim->hit -= dam;
  update_pos( victim );
  if( ( vict = who_fighting( ch ) ) == NULL )
	set_fighting( ch, victim );
  return;
}

void do_forcelightning( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *vict;
  int chance, resist, diff;
  int dam=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FORCE_LIGHTNING] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
   	send_to_char( "&rShock who with a jolt of lightning?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character isn't in this room.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rThere's no point in that.&w\n\r", ch );
	return;
   }
  if( IS_SET(ch->in_room->room_flags, ROOM_SAFE ) )
   {
        send_to_char( "&rYou will have to do that someplace else.&w\n\r", ch );
        return;
   }
  if( ch->hit < 7 )
   {
	send_to_char( "&rYou lack the strength to do this.&w\n\r", ch );
	return;
   }
  ch->hit -= 6;
  update_pos( ch );
  gain_darkpoint( ch );
  WAIT_STATE( ch, PULSE_VIOLENCE );
  chance = ( number_range( 1, 20 ) + ch->force_level[FORCE_LIGHTNING] + stat_table[get_curr_int(ch)].mod );
  if( IS_TAINTED(ch) )
	chance += 2;
  if( IS_DARK(ch) )
	chance += 2;
  if( !IS_NPC(victim) )
    resist = ( number_range( 1, 20 ) + ch->reflexes );
  else
    resist = 18;
  if( chance < 10 )
	diff = 10;
  else if( chance >= 10 && chance <= 14 )
	diff = 15;
  else if( chance >= 15 && chance <= 19 )
	diff = 20;
  else if( chance >= 20 )
	diff = 25;
  dam = number_range(3, 24);
  if( resist >= diff && ch->class_level[SCOUT_ABILITY] >= 6 )
   {
	act( AT_YELLOW, "$N rolls out of the way of your lightning bolts.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_YELLOW, "You narrowly avoid $n's lightning bolts by rolling out of the way.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_YELLOW, "$N narrowly rolls out of the way of $n's lightning bolts.\n\r", ch, NULL, victim, TO_NOTVICT );
	if( ( vict = who_fighting( ch ) ) == NULL )
	  set_fighting( ch, victim );
	return;
   }
  if( resist >= diff )
	dam = dam/2;
  victim->hit -= dam;
  update_pos( victim );
  act( AT_RED, "You draw upon the darkside of the Force and jolt $N with a lightning blast.\n\r", ch, NULL, victim, TO_CHAR );
  act( AT_RED, "$n draws upon the darkside of the Force and jolts you with a lightning blast.\n\r", ch, NULL, victim, TO_VICT );
  act( AT_RED, "$n draws upon the darkside of the Force and jolts $N with a lightning blast.\n\r", ch, NULL, victim, TO_NOTVICT );
  if( ( vict = who_fighting( ch ) ) == NULL )
	set_fighting( ch, victim );
  return;
}

void do_forcestrike( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *vict;
  int chance, resist, diff;
  int dam=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[FORCE_STRIKE] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&bStrike who with the Force?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character is not here.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rNow why would you do that?&w\n\r", ch );
	return;
   }
  if( ch->hit < 3 )
   {
	send_to_char( "&rYou lack the strength to do that.&w\n\r", ch );
	return;
   }
  if( IS_SET(ch->in_room->room_flags, ROOM_SAFE ) )
   {
        send_to_char( "&rYou will have to do that someplace else.&w\n\r", ch );
        return;
   }
  ch->hit -= 2;
  update_pos( ch );
  WAIT_STATE( ch, PULSE_PER_SECOND*3 );
  chance = ( number_range( 1, 20 ) + ch->force_level[FORCE_STRIKE] + stat_table[get_curr_int(ch)].mod );
  resist = ( number_range( 1, 20 ) + ch->reflexes );
  if( chance < 10 )
  	diff = 10;
  else if( chance >= 10 && chance <= 19 )
	diff = 15;
  else if( chance >= 20 )
	diff = 20;
  dam = number_range( 3, 12 );
  if( resist >= diff && ch->class_level[SCOUT_ABILITY] >= 6 )
   {
	act( AT_YELLOW, "$N rolls out of the way of your Force strike.\n\r", ch, NULL, victim, TO_CHAR );
 	act( AT_YELLOW, "You narrowly roll out of the way of $n's Force strike.\n\r", ch, NULL, NULL, TO_VICT );
	act( AT_YELLOW, "$N narrowly rolls out of the way of $n's Force strike.\n\r", ch, NULL, victim, TO_NOTVICT );
	if( ( vict = who_fighting( ch ) ) == NULL )
	  	set_fighting( ch, victim );
	return;
   }
  if( resist >= diff )
	dam = dam/2;
  victim->hit -= dam;
  update_pos( victim );
  act( AT_BLUE, "You strike $N with a blast of the Force.\n\r", ch, NULL, NULL, TO_CHAR ); 
  act( AT_BLUE, "$n strikes you with a blast of the Force.\n\r", ch, NULL, NULL, TO_VICT );
  act( AT_BLUE, "$n strikes $N with a blast of the Force.\n\r", ch, NULL, NULL, TO_NOTVICT );
  if( ( vict = who_fighting( ch ) ) == NULL )
	set_fighting( ch, victim );
  return;
}

void do_heal( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  int chance;
  int gain=0;
  int loss=0;

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[HEAL_SELF] == 0 && ch->force_level[HEAL_OTHER] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&GHeal whom?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rThat character is not here.&w\n\r", ch );
	return;
   }
  if( victim == ch && ch->force_level[HEAL_SELF] == 0 )
   {
	send_to_char( "&rYou lack the skill required for this.&w\n\r", ch );
	return;
   }
  if( victim != ch && ch->force_level[HEAL_OTHER] == 0 )
   {
	send_to_char( "&rYou lack the skill required for this.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	if( ch->position < POS_RESTING )
	 {
		send_to_char( "&rNot in this position.&w\n\r", ch );
		return;
	 }
	if( ch->hit >= ch->max_hit )
	 {
		send_to_char( "&bYou don't require any healing.&w\n\r", ch );
		return;
	 }
	WAIT_STATE( ch, PULSE_PER_SECOND*2 );
	chance = ( number_range( 1, 20 ) + ch->force_level[HEAL_SELF] + stat_table[get_curr_cha(ch)].mod );
	if( chance < 10 )
	 {
	  	ch->hit -= 1;
		act( AT_RED, "You fail to harness the healing power of the Force and cause slight damage to yourself.\n\r", ch, NULL, victim, TO_CHAR );
		act( AT_RED, "$n fails to harness the healing power of the Force and injures $mself.\n\r", ch, NULL, victim, TO_NOTVICT );
		update_pos( ch );
		return;
	 }
	else if( chance >= 10 && chance <= 14 )
		gain = ( number_range( 1, 4 ) + 1 );
	else if( chance >= 15 && chance <= 19 )
		gain = ( number_range( 1, 6 ) + 2 );
	else if( chance >= 20 && chance <= 24 )
		gain = ( number_range( 1, 8 ) + 4 );
	else if( chance >= 25 )
		gain = ( number_range( 2, 12 ) + 6 );
	ch->hit = URANGE( ch->hit, ( ch->hit + gain ), ch->max_hit );
	act( AT_BLUE, "You harness the healing powers of the Force and ease your wounds.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_BLUE, "$n harnesses the healing powers of the Force and eases $s wounds.\n\r", ch, NULL, victim, TO_NOTVICT );
	update_pos( ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "&rThat wont help a Droid much.&w\n\r", ch );
	return;
   }
  if( ch->position < POS_RESTING )
   {
	send_to_char( "&rNot in this position.&w\n\r", ch );
	return;
   }
  if( victim->hit >= victim->max_hit )
   {
	send_to_char( "&rThey don't need any healing.&w\n\r", ch );
	return;
   }
  if( ch->hit < 7 )
   {
	send_to_char( "&rYou lack the required strength for this.&w\n\r", ch );
	return;
   }
  WAIT_STATE( ch, PULSE_PER_SECOND*2 );
  chance = ( number_range( 1, 20 ) + ch->force_level[HEAL_OTHER] + stat_table[get_curr_wis(ch)].mod );
  if( chance < 10 )
   {
	ch->hit -= 1;
	act( AT_RED, "You fail to harness the healing powers of the Force and cause yourself minor damage.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_RED, "$n fails to harness the healing powers of the Force and causes $sself minor damage.\n\r", ch, NULL, victim, TO_VICT );
	act( AT_RED, "$n fails to harness the healing powers of the Force and causes $sself minor damage.\n\r", ch, NULL, victim, TO_NOTVICT );
	update_pos( ch );
	return;
   }
  else if( chance >= 10 && chance <= 14 )
   {
	if( victim->hit < 0 )
	 {
	  	victim->hit = 0;
		ch->hit -= 1;
		act( AT_BLUE, "$n harnesses the healing powers of the Force enough to stabilize $N.\n\r", ch, NULL, victim, TO_NOTVICT );
		act( AT_BLUE, "You harness the healing powers of the Force enough to stabilize $N.\n\r", ch, NULL, victim, TO_CHAR );
		act( AT_BLUE, "$n harnesses the healing powers of the Force enough to stabilize you.\n\r", ch, NULL, victim, TO_VICT );
		update_pos( ch );
		update_pos( victim );
		return;
	 }
	act( AT_RED, "You fail to harness the healing powers of the Force and cause minor damage to yourself.\n\r", ch, NULL, victim, TO_CHAR );
	act( AT_RED, "$n fails to harness the healing powers of the Force and causes minor damage to $sself.\n\r", ch, NULL, victim, TO_VICT );
        act( AT_RED, "$n fails to harness the healing powers of the Forceand causes minor damage to $sself.\n\r", ch, NULL, victim, TO_NOTVICT );
	ch->hit -= 1;
	update_pos( ch );
	return;
   }
  else if( chance >= 15 && chance <= 19 )
   {
	gain = ( number_range( 1, 4 ) + 1 );
	loss = 1;
   }
  else if( chance >= 20 && chance <= 24 )
   {
	gain = ( number_range( 1, 6 ) + 2 );
	loss = 2;
   }
  else if( chance >= 25 && chance <= 29 )
   {
	gain = ( number_range( 1, 8 ) + 4 );
	loss = 4;
   }
  else if( chance >= 30 )
   {
	gain = ( number_range( 2, 12 ) + 6 );
	loss = 6;
   }
  victim->hit = URANGE( victim->hit, victim->hit + gain, victim->max_hit );
  ch->hit -= loss;
  act( AT_BLUE, "You harness the healing powers of the Force and heal $N.\n\r", ch, NULL, victim, TO_CHAR );
  act( AT_BLUE, "$n harnesses the healing powers of the Force and heals you.\n\r", ch, NULL, victim, TO_VICT );
  act( AT_BLUE, "$n harnesses the healing powers of the Force and heals $N.\n\r", ch, NULL, victim, TO_NOTVICT );
  update_pos( ch );
  update_pos( victim );
  return;
}

void do_meditate( CHAR_DATA *ch, char *argument )
{
    switch ( ch->position )
    {
    case POS_SLEEPING:
	if ( IS_AFFECTED(ch, AFF_SLEEP) )
         { 
	   send_to_char( "You can't seem to wake up!\n\r", ch ); 
	   return;
	 }
	send_to_char( "You stir from your slumber and begin to meditate.\n\r", ch );
	act( AT_ACTION, "$n stirs from $s slumber and begins to meditate.", ch, NULL, NULL, TO_ROOM );
        ch->position = POS_MEDITATING;
	break;

    case POS_MEDITATING:
	send_to_char( "You are already meditating.\n\r", ch );
	return;

    case POS_RESTING:
	send_to_char( "You adjust your position slightly and begin to meditate.\n\r", ch );
	act( AT_ACTION, "$n adjusts $s position slightly and begins to meditate.", ch, NULL, NULL, TO_ROOM );
        ch->position = POS_MEDITATING;
	return;

    case POS_STANDING:
        send_to_char( "You sit down and begin to meditate.\n\r", ch );
	act( AT_ACTION, "$n sits down and begins to meditate.", ch, NULL, NULL, TO_ROOM );
        ch->position = POS_MEDITATING;
        break;

    case POS_SITTING:
        send_to_char( "You leans back slightly and begins to meditate.\n\r", ch );
	act( AT_ACTION, "$n leans back slightly and begins to meditate.", ch, NULL, NULL, TO_ROOM );
	ch->position = POS_MEDITATING;
	break;

    case POS_FIGHTING:
	send_to_char( "You are busy fighting!\n\r", ch );
	return;
    case POS_MOUNTED:
        send_to_char( "You'd better dismount first.\n\r", ch );
        return;
    }

    rprog_rest_trigger( ch );
    return;
}

void do_callforce( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  int bonus, duration;
  bool call_light=FALSE;
  bool call_neutral=FALSE;
  bool call_dark=FALSE;  

  if( IS_NPC(ch) )
  	return;
  if( IS_DROID(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( ch->forcepoints < 1 )
   {
	send_to_char( "You lack the Force Points to do this.\n\r", ch );
	return;
   }
  if( HAS_FEAT( ch, FORCE_SENSITIVE ) && !IS_DARK(ch) && argument[0] == '\0' )
   {
	send_to_char( "&rCall upon the Light or the Dark side of the Force?&w&W\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "light" ) )
	call_light = TRUE;
  if( !str_cmp( argument, "dark" ) )
	call_dark = TRUE;
  if( !HAS_FEAT( ch, FORCE_SENSITIVE ) )
   {
	call_light = FALSE;
	call_dark = FALSE;
	call_neutral = TRUE;
   }
  if( IS_DARK(ch) )
   {
	call_light = FALSE;
	call_neutral = FALSE;
	call_dark = TRUE;
   }
  duration = ( ch->top_level * 2 );
  if( call_neutral )
   {
	if( ch->top_level < 11 )
		bonus = number_range(1, 6);
	else if( ch->top_level >= 11 && ch->top_level < 21 )
		bonus = number_range(2, 12);
	else if( ch->top_level >= 21 && ch->top_level < 26 )
		bonus = number_range(3, 18);
	else if( ch->top_level >= 26 )
		bonus = number_range(4, 24);
   }
  else if( call_light )
   {
	if( ch->top_level < 6 )
		bonus = number_range(1, 6);
	else if( ch->top_level >= 6 && ch->top_level < 11 )
		bonus = number_range(2, 12);
	else if( ch->top_level >= 11 && ch->top_level < 16 )
		bonus = number_range(3, 18);
	else if( ch->top_level >= 16 && ch->top_level < 21 )
		bonus = number_range(4, 24);
	else if( ch->top_level >= 21 && ch->top_level < 26 )
		bonus = number_range(5, 30);
	else if( ch->top_level >= 26 )
		bonus = number_range(7, 42);
   }
  else if( call_dark )
   {
	if( ch->top_level < 6 )
		bonus = number_range(2, 12);
	else if( ch->top_level >= 6 && ch->top_level < 11 )
		bonus = number_range(3, 18);
	else if( ch->top_level >= 11 && ch->top_level < 21 )
		bonus = number_range(4, 18);
	else if( ch->top_level >= 21 && ch->top_level < 26 )
		bonus = number_range(5, 30);
	else if( ch->top_level >= 26 )
		bonus = number_range(6, 36);
	gain_darkpoint(ch);
   }
  ch->forcepoints -= 1;
  af.type = gsn_callforce;
  af.duration = duration;
  af.location = APPLY_HITROLL;
  af.modifier = bonus;
  af.bitvector = AFF_FORCE;
  affect_to_char(ch, &af);
  if( call_dark )
   {
    send_to_char( "&rYou call upon the dark side of the Force to aid you!&w&W\n\r", ch );
    act( AT_BLOOD, "$n calls upon the dark side of the Force to aid $s.", ch, NULL, NULL, TO_ROOM );
   }
  else if( call_light )
   {
    send_to_char( "&CYou call upon the light side of the Force to aid you!&w&W\n\r", ch );
    act( AT_MAGIC, "$n calls upon the light side of the Force to aid $s.", ch, NULL, NULL, TO_ROOM );
   }
  else
   {
    send_to_char( "&w&WThe luck of the universe is aiding you!\n\r", ch );
    act( AT_PLAIN, "$n is surrounded by the luck of the Universe.", ch, NULL, NULL, TO_ROOM );
   }
  WAIT_STATE( ch, PULSE_VIOLENCE );
  return;
}
  
void do_forcemind( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  CHAR_DATA *victim;
  char arg[MAX_INPUT_LENGTH];
  int bonus=0;
  int cost=0;

  argument = one_argument( argument, arg );

  if( IS_NPC(ch) )
  	return;
  if( !IS_IMMORTAL(ch) && !HAS_FFEAT( ch, FORCE_MIND ) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( ch->position < POS_FIGHTING )
   {
	send_to_char( "You can't do that in this position.\n\r", ch );
	return;
   }
  if( HAS_FFEAT( ch, FORCE_MIND ) )
   	cost += 5;
  if( HAS_FFEAT( ch, IMP_FORCE_MIND ) )
	cost += 3;
  if( HAS_FFEAT( ch, KNIGHT_MIND ) )
	cost += 4;
  if( HAS_FFEAT( ch, MASTER_MIND ) )
	cost += 4;
  if( ch->hit <= cost )
   {
	send_to_char( "&RYou lack the vitality to do this.&w&W\n\r", ch );
	return;
   }
  if( arg[0] == '\0' || argument[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&WForcemind <victim> <attribute>\n\r", ch );
	send_to_char( "&GValid Attributes: &w&Wstr dex con int wis cha\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
	send_to_char( "I don't see them here.\n\r", ch );
	return;
   }
  if( IS_AFFECTED( victim, AFF_MIND ) )
   {
	send_to_char( "They are already affected by Force Mind.\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
   {
	send_to_char( "Leave my NPCs alone.\n\r", ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "Not on Droids.\n\r", ch );
	return;
   }
  if( HAS_FFEAT( ch, FORCE_MIND ) )
	bonus += 2;
  if( HAS_FFEAT( ch, IMP_FORCE_MIND ) )
	bonus += 2;
  if( HAS_FFEAT( ch, KNIGHT_MIND ) )
 	bonus += 2;
  if( HAS_FFEAT( ch, MASTER_MIND ) )
	bonus += 2;
  if( str_cmp( argument, "str" ) && str_cmp( argument, "dex" ) && str_cmp( argument, "con" ) && str_cmp( argument, "int" ) && str_cmp( argument, "wis" ) && str_cmp( argument, "cha" ) )
   {
	do_forcemind( ch, "" );
	return;
   }
  ch->hit -= cost;
  update_pos( ch );
  af.type = gsn_forcemind;
  af.duration = ( 3 * ch->top_level );
  af.modifier = bonus;
  if( !str_cmp( argument, "str" ) )
    	af.location = APPLY_STR;
  else if( !str_cmp( argument, "dex" ) )
   	af.location = APPLY_DEX;
  else if( !str_cmp( argument, "con" ) )
	af.location = APPLY_CON;
  else if( !str_cmp( argument, "int" ) )
	af.location = APPLY_INT;
  else if( !str_cmp( argument, "wis" ) )
	af.location = APPLY_WIS;
  else if( !str_cmp( argument, "cha" ) )
	af.location = APPLY_CHA;
  af.bitvector = AFF_MIND;
  affect_to_char( victim, &af );
  if( victim == ch )
   {
	act( AT_BLUE, "You become empowered by the Force.", ch, NULL, victim, TO_CHAR );
	act( AT_BLUE, "$n glowes with the power of the Force.", ch, NULL, victim, TO_NOTVICT );
   }
  else
   {
	act( AT_BLUE, "$n empowers $N through the Force.", ch, NULL, victim, TO_NOTVICT );
	act( AT_BLUE, "$n empowers you through the Force.", ch, NULL, victim, TO_VICT );
	act( AT_BLUE, "You emplower $N through the Force.", ch, NULL, victim, TO_CHAR );
   }
  WAIT_STATE( ch, PULSE_PER_SECOND*2 );
  return;
}

void do_drainenergy( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *vict;
  AFFECT_DATA af;
  OBJ_DATA *obj;
  char arg[MAX_INPUT_LENGTH];
  int cost=0;
  int save=0;
  int diff=0;
  int roll=0;

  argument = one_argument( argument, arg );

  if( IS_NPC(ch) )
	return;
  if( !IS_IMMORTAL(ch) && ch->force_level[DRAIN_ENERGY] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( ch->position < POS_FIGHTING )
   {
        send_to_char( "Not in your current position.\n\r", ch );
        return;
   }
  if( arg[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&Wdrainenergy <victim> <object>\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
	send_to_char( "&RI don't see them here.&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "That would be rather pointless.\n\r", ch );
	return;
   }
  roll = ( number_range(1,20) + ch->force_level[DRAIN_ENERGY] + stat_table[get_curr_con(ch)].mod );
  if( roll < 15 )
	diff = 10;
  else if( roll > 15 && roll < 26 )
	diff = 15;
  else
	diff = 20;
  if( argument[0] == '\0' )
   {
	if( !IS_DROID(victim) )
	 {
	   send_to_char( "You can't drain energy out of living creatures.\n\r", ch );
  	   return;
	 }
	if( ch->hit < 12 )
	 {
	   send_to_char( "You lack the vitality to do this.\n\r", ch );
	   return;
	 }
	if( IS_NPC(victim) )
	   save = ( number_range(1,20) + victim->top_level/2 );
	else
	   save = ( number_range(1,20) + GET_WILL(victim) );
	ch->hit -= 12;
	update_pos( ch );
	gain_darkpoint( ch );
	if( ( vict = who_fighting( ch ) ) == NULL )
           set_fighting( ch, victim );
	if( save >= diff )
	 {
	   act( AT_BLOOD, "You fail to drain $N of energy.", ch, NULL, victim, TO_CHAR );
	   act( AT_BLOOD, "$n fails to drain you of energy.", ch, NULL, victim, TO_VICT );
	   act( AT_BLOOD, "$n fails to drain $N of energy.", ch, NULL, victim, TO_NOTVICT );
	   WAIT_STATE( ch, PULSE_PER_SECOND*2 );
	   return;
	 }
	victim->hit -= (number_range(1, 8) + stat_table[get_curr_con(ch)].mod);
	if( !IS_AFFECTED( victim, AFF_PARALYSIS ) )
	 {
	   int fort=0;
	   if( IS_NPC(victim) )
	     fort = ( number_range(1,20) + victim->top_level/2 );
	   else
	     fort = ( number_range(1,20) + GET_FORT(victim) );
	   if( 16 > fort )
	    {
	      af.type      = gsn_stun;
	      af.location  = APPLY_AC;
	      af.modifier  = (stat_table[get_curr_dex(victim)].mod);
	      af.duration  = number_range(15,40);
	      af.bitvector = AFF_PARALYSIS;
	      affect_to_char( victim, &af );
	      update_pos( victim );
	      act( AT_BLOOD, "You drain $N of energy, stunning it momentarily.", ch, NULL, victim, TO_CHAR );
	      act( AT_BLOOD, "$n drains you of energy, stunning you momentarily.", ch, NULL, victim, TO_VICT );
	      act( AT_BLOOD, "$n drains $N of energy, stunning $E momentarily.", ch, NULL, victim, TO_NOTVICT );
	      WAIT_STATE( ch, PULSE_PER_SECOND*2 );
	      return;
	    }
	 }
	update_pos( victim );
	act( AT_BLOOD, "You drain $N of some energy.", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "$n drains you of some energy.", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "$n drains $N of some energy.", ch, NULL, victim, TO_NOTVICT );
	WAIT_STATE( ch, PULSE_PER_SECOND*2 );
	return;
   }
  if ( ( obj = get_obj_wear( victim, argument ) ) == NULL )
   {
        send_to_char( "They are not using that item.\n\r", ch );
        return;
   }
  if( !can_see_obj( ch, obj ) )
   {
	send_to_char( "They are not suing that item.\n\r", ch );
	return;
   }
  if( obj->item_type != ITEM_WEAPON )
   {
	send_to_char( "This is only used on weapons.\n\r", ch );
	return;
   }
  if( obj->value[3] != WEAPON_BLASTER && obj->value[3] != WEAPON_BLASTER_RIFLE && obj->value[3] != WEAPON_HEAVY 
   && obj->value[3] != WEAPON_BOWCASTER && obj->value[3] != WEAPON_FORCE_PIKE && obj->value[3] != WEAPON_LIGHTSABER 
   && obj->value[3] != WEAPON_DUAL_LIGHTSABER )
   {
	send_to_char( "That weapon doesn't have an energy source.\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
	save = ( number_range(1,20) + victim->top_level/2 );
  else
	save = ( number_range(1,20) + GET_WILL(victim) );
  if( obj->value[3] == WEAPON_LIGHTSABER || obj->value[3] == WEAPON_DUAL_LIGHTSABER )
	cost = 8;
  else
	cost = 4;
  if( ch->hit <= cost )
   {
	send_to_char( "You lack the vitality for this.\n\r", ch );
	return;
   }
  if( ( vict = who_fighting( ch ) ) == NULL )
        set_fighting( ch, victim );
  ch->hit -= cost;
  gain_darkpoint( ch );
  update_pos( ch );
  if( save >= diff )
   {
	act( AT_BLOOD, "$n fails in $e attempt to drain your $o of energy.", ch, obj, victim, TO_VICT );
	act( AT_BLOOD, "You fail in your attempt to drain $N's $o of energy.", ch, obj, victim, TO_CHAR );
	act( AT_BLOOD, "$n fails in $e attempt to drain $N's $o of energy.", ch, obj, victim, TO_NOTVICT );
	WAIT_STATE( ch, PULSE_PER_SECOND*2 );
	return;
   }
  obj->value[4] = 0;
  act( AT_BLOOD, "Your $o sputters as $n drains it of energy.", ch, obj, victim, TO_VICT );
  act( AT_BLOOD, "$N's $o sputters as you drain it of energy.", ch, obj, victim, TO_CHAR );
  act( AT_BLOOD, "$n's $o sputters as $n drains it of energy.", ch, obj, victim, TO_NOTVICT );
  WAIT_STATE( ch, PULSE_PER_SECOND*2 );
  return;
}
