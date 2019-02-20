#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"

void do_skills( CHAR_DATA *ch, char *argument )
{
 char arg[MAX_INPUT_LENGTH];
 char arg2[MAX_INPUT_LENGTH];
 int iSkill, skill, gain;
 int maxskill=0;

 argument = one_argument(argument, arg);
 argument = one_argument(argument, arg2);

   if( IS_NPC(ch) )
	return;

  if( arg[0] == '\0' )
   {
   ch_printf( ch, "&wAppraise              &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[APPRAISE_SKILL], ch->skill_percent[APPRAISE_SKILL] );
   ch_printf( ch, "&wAstrogate             &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[ASTROGATE_SKILL], ch->skill_percent[ASTROGATE_SKILL] );
   ch_printf( ch, "&wBalance               &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[BALANCE_SKILL], ch->skill_percent[BALANCE_SKILL] );
   ch_printf( ch, "&wClimb                 &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CLIMB_SKILL], ch->skill_percent[CLIMB_SKILL] );
   ch_printf( ch, "&wCraft &g- &wArmor         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_ARMOR], ch->skill_percent[CRAFT_ARMOR] );
   ch_printf( ch, "&g      -&w Blaster       &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_BLASTERS], ch->skill_percent[CRAFT_BLASTERS] );
   ch_printf( ch, "&g      -&w Computer      &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_COMPUTER], ch->skill_percent[CRAFT_COMPUTER] );
   ch_printf( ch, "&g      -&w Droid         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_DROID], ch->skill_percent[CRAFT_DROID] );
   ch_printf( ch, "&g      -&w Device        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_DEVICE], ch->skill_percent[CRAFT_DEVICE] );
  if( IS_IMMORTAL(ch) || ch->class_level[FORCE_ADEPT_ABILITY] != 0 || ch->class_level[JEDIGUARDIAN_ABILITY] != 0 || ch->class_level[JEDICONSULAR_ABILITY] != 0 )
   ch_printf( ch, "&g      -&w Lightsaber    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_LIGHTSABER], ch->skill_percent[CRAFT_LIGHTSABER] );
   ch_printf( ch, "&g      -&w Bowcaster     &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_BOWCASTER], ch->skill_percent[CRAFT_BOWCASTER] );
   ch_printf( ch, "&g      -&w Heavy Weap    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_HEAVY], ch->skill_percent[CRAFT_HEAVY] );
   ch_printf( ch, "&g      -&w Hyperdrive    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_HYPERDRIVE], ch->skill_percent[CRAFT_HYPERDRIVE] );
   ch_printf( ch, "&g      -&w Medpac        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_MEDPAC], ch->skill_percent[CRAFT_MEDPAC] );
   ch_printf( ch, "&g      -&w Simple        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_SIMPLE], ch->skill_percent[CRAFT_SIMPLE] );
   ch_printf( ch, "&g      -&w Slugthrower   &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_SLUG], ch->skill_percent[CRAFT_SLUG] );
   ch_printf( ch, "&g      -&w Midship       &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_MIDSHIP], ch->skill_percent[CRAFT_MIDSHIP] );
   ch_printf( ch, "&g      -&w Starfighter   &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_FIGHTER], ch->skill_percent[CRAFT_FIGHTER] );
   ch_printf( ch, "&g      -&w Ship Weap     &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_STARWEAP], ch->skill_percent[CRAFT_STARWEAP] );
   ch_printf( ch, "&g      -&w Vibro         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[CRAFT_VIBRO], ch->skill_percent[CRAFT_VIBRO] );   
   ch_printf( ch, "&wDemolitions           &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[DEMOLITIONS_SKILL], ch->skill_percent[DEMOLITIONS_SKILL] );
   ch_printf( ch, "&wDiplomacy             &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[DIPLOMACY_SKILL], ch->skill_percent[DIPLOMACY_SKILL] );
   ch_printf( ch, "&wDisable Device        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[DISABLE_DEVICE], ch->skill_percent[DISABLE_DEVICE] );
   ch_printf( ch, "&wDisguise              &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[DISGUISE_SKILL], ch->skill_percent[DISGUISE_SKILL] );
   ch_printf( ch, "&wEscape Artist         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[ESCAPE_ARTIST], ch->skill_percent[ESCAPE_ARTIST] );
   ch_printf( ch, "&wGamble                &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[GAMBLE_SKILL], ch->skill_percent[GAMBLE_SKILL] );
   ch_printf( ch, "&wGather Information    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[GATHER_INFO], ch->skill_percent[GATHER_INFO] );
   ch_printf( ch, "&wHide                  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[HIDE_SKILL], ch->skill_percent[HIDE_SKILL] );
   ch_printf( ch, "&wIntimidate            &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[INTIMIDATE_SKILL], ch->skill_percent[INTIMIDATE_SKILL] );
   ch_printf( ch, "&wListen                &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[LISTEN_SKILL], ch->skill_percent[LISTEN_SKILL] );
   ch_printf( ch, "&wMove Silently         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[MOVE_SILENTLY], ch->skill_percent[MOVE_SILENTLY] );
   ch_printf( ch, "&wPilot                 &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[PILOT_SKILL], ch->skill_percent[PILOT_SKILL] );
   ch_printf( ch, "&wRepair                &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[REPAIR_SKILL], ch->skill_percent[REPAIR_SKILL] );
   ch_printf( ch, "&wRide                  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[RIDE_SKILL], ch->skill_percent[RIDE_SKILL] );
   ch_printf( ch, "&wSearch                &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[SEARCH_SKILL], ch->skill_percent[SEARCH_SKILL] );
   ch_printf( ch, "&wSleight Of Hand       &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[SLEIGHT_OF_HAND], ch->skill_percent[SLEIGHT_OF_HAND] );
   ch_printf( ch, "&wSpeak Language        &g- &w%3d&w\n\r", ch->skill_level[SPEAK_LANG] );
   ch_printf( ch, "&wSpot                  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[SPOT_SKILL], ch->skill_percent[SPOT_SKILL] );
   ch_printf( ch, "&wSurvival              &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[SURVIVAL_SKILL], ch->skill_percent[SURVIVAL_SKILL] );
   ch_printf( ch, "&wSwim                  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[SWIM_SKILL], ch->skill_percent[SWIM_SKILL] );
   ch_printf( ch, "&wTreat Injury          &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[TREAT_INJURY], ch->skill_percent[TREAT_INJURY] );
   ch_printf( ch, "&wTumble                &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[TUMBLE_SKILL], ch->skill_percent[TUMBLE_SKILL] );
   ch_printf( ch, "&wUse Computer          &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->skill_level[COMPUTER_SKILL], ch->skill_percent[COMPUTER_SKILL] );
   ch_printf( ch, "\n\r" );
   ch_printf( ch, "&wYou have &g%d&w skillpoints left.\n\r", ch->skillpoints );
   return;
   }
  if( !str_cmp(arg, "learn") )
   {
    if( arg[0] == '\0' )
     {
	send_to_char( "&wLearn which skill?\n\r", ch );
	return;
     }
    skill = -1;
    for( iSkill = 0; iSkill < MAX_NSKILL; iSkill++ )
     {
      if( !str_prefix( arg2, nskill_name[iSkill] ) )
       {
	skill = iSkill;
	break;
       }
     }
    if( skill == -1 )
     {
	send_to_char( "&wThat isn't a skill.\n\r", ch );
	return;
     }
    if( !IS_IMMORTAL(ch) && skill == CRAFT_LIGHTSABER && ch->class_level[FORCE_ADEPT_ABILITY] == 0 && ch->class_level[JEDIGUARDIAN_ABILITY] == 0 && ch->class_level[JEDICONSULAR_ABILITY] == 0 )
     {
	send_to_char( "&wThat isn't a skill.\n\r", ch );
	return;
     }
    if( argument[0] == '\0' || !is_number(argument) )
     {
      	ch_printf( ch, "&wPut how many skillpoints into the &g%s&w skill?\n\r", nskill_name[iSkill] );
      	return;
     }
    gain = atoi(argument);
    if( gain < 1 )
     {
	send_to_char( "&wNow you're just being sillie.\n\r", ch );
	return;
     }
    if( gain > ch->skillpoints )
     {
	send_to_char( "&wYou don't have that many skillpoints.\n\r", ch );
	return;
     }
    maxskill = skill_max( ch, skill );
    if( (gain + ch->skill_level[skill] ) > maxskill )
     {
	ch_printf( ch, "&w&WYou can only have &G%d &w&Wskillpoints in &G%s&w&W.\n\r", maxskill, nskill_name[skill] );
	return;
     }
    if( skill == SPEAK_LANG )
     {
      if( ch->skill_level[SPEAK_LANG] >= 29 )
       {
	send_to_char( "&wMax skill for &bSpeak Language&w is &r29&w.\n\r", ch );
	return;
       }
      if( ch->skill_level[SPEAK_LANG] + gain > 29 )
       {
	ch_printf( ch, "&wYou can only put &r%d&w more pointsinto &bSpeak Language&w.\n\r", (29 - ch->skill_level[SPEAK_LANG]) );
	return;
       }
     }
    ch->skill_level[skill] += gain;
    ch->skill_percent[skill] = 0;
    ch->skillpoints -= gain;
    ch_printf( ch, "&wYou put &r%d&w skillpoints into the &b%s&w skill.\n\r", gain, nskill_name[skill] );
    return;
   }
  send_to_char( "Huh?\n\r", ch );
  return;
}

void do_fskills( CHAR_DATA *ch, char *argument )
{
  char arg[MAX_INPUT_LENGTH];
  char arg2[MAX_INPUT_LENGTH];
  int skill, iSkill, gain;
  int bonus=0;
  argument = one_argument( argument, arg );
  argument = one_argument( argument, arg2);

  if( IS_NPC(ch) )
   return;

  if( !HAS_FEAT(ch, FORCE_SENSITIVE) && !IS_IMMORTAL(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }

 if( arg[0] == '\0' )
  {
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, SITH_SORCERY) )
     ch_printf( ch, "&r+&wAlchemy          &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[ALCHEMY_SKILL], ch->force_percent[ALCHEMY_SKILL] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
     ch_printf( ch, "&w Affect Mind      &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[AFFECT_MIND], ch->force_percent[AFFECT_MIND] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, CONTROL_FEAT) )
     ch_printf( ch, "&w Battlemind       &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[BATTLEMIND_SKILL], ch->force_percent[BATTLEMIND_SKILL] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
     ch_printf( ch, "&r+&wDrain Energy     &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[DRAIN_ENERGY], ch->force_percent[DRAIN_ENERGY] );
  if( IS_IMMORTAL(ch) || HAS_FEAT( ch, FORCE_SENSITIVE ) )
     ch_printf( ch, "&w Enhance Ability  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[ENHANCE_ABILITY], ch->force_percent[ENHANCE_ABILITY] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, SENSE_FEAT) )
   {
     ch_printf( ch, "&w Enhance Senses   &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[ENHANCE_SENSES], ch->force_percent[ENHANCE_SENSES] );
     ch_printf( ch, "&w Farseeing        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FARSEEING_SKILL], ch->force_percent[FARSEEING_SKILL] );
     ch_printf( ch, "&r+&wFear             &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FEAR_SKILL], ch->force_percent[FEAR_SKILL] );
   }
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, CONTROL_FEAT) )
     ch_printf( ch, "&w Force Defense    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FORCE_DEFENSE], ch->force_percent[FORCE_DEFENSE] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
   {
     ch_printf( ch, "&r+&wForce Grip       &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FORCE_GRIP], ch->force_percent[FORCE_GRIP] );
     ch_printf( ch, "&r+&wForce Lightning  &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FORCE_LIGHTNING], ch->force_percent[FORCE_LIGHTNING] );
   }
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, CONTROL_FEAT) )
     ch_printf( ch, "&w Force Stealth    &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FORCE_STEALTH], ch->force_percent[FORCE_STEALTH] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
   {
     ch_printf( ch, "&w Force Strike     &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[FORCE_STRIKE], ch->force_percent[FORCE_STRIKE] );
     ch_printf( ch, "&w Heal Another     &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[HEAL_OTHER], ch->force_percent[HEAL_OTHER] );
   }
  if( IS_IMMORTAL(ch) || HAS_FEAT( ch, FORCE_SENSITIVE ) )
     ch_printf( ch, "&w Heal Self        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[HEAL_SELF], ch->force_percent[HEAL_SELF] );
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
   {
     ch_printf( ch, "&w Illusion         &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[ILLUSION_SKILL], ch->force_percent[ILLUSION_SKILL] );
     ch_printf( ch, "&w Move Object      &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[MOVE_OBJECT], ch->force_percent[MOVE_OBJECT] );
   }
  if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, SENSE_FEAT) )
   {
     ch_printf( ch, "&w See Force        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[SEE_FORCE], ch->force_percent[SEE_FORCE] );
     ch_printf( ch, "&w Telepathy        &g- &w%3d  &g(&w%2d&g/&w100&g)&w\n\r", ch->force_level[TELEPATHY_SKILL], ch->force_percent[TELEPATHY_SKILL] );
   } 
  send_to_char( "\n\r", ch );
  send_to_char( "&r+&w denotes a &gDark Side&w skill.\n\r", ch );
  send_to_char( "\n\r", ch );
  ch_printf( ch, "&w You have &g%d&w skillpoints remaining.\n\r", ch->skillpoints );
  return;
  }
  if( !str_cmp(arg, "learn") )
   {
    if( arg[0] == '\0' )
     {
	send_to_char( "&wLearn which skill?\n\r", ch );
	return;
     }
    skill = -1;
    for( iSkill = 0; iSkill < MAX_FSKILL; iSkill++ )
     {
      if( !str_prefix( arg2, fskill_name[iSkill] ) )
       {
	skill = iSkill;
	break;
       }
     }
    if( skill == -1 )
     {
	send_to_char( "&wThat isn't a skill.\n\r", ch );
	return;
     }
    if( argument[0] == '\0' || !is_number(argument) )
     {
      	ch_printf( ch, "&wPut how many skillpoints into the &b%s&w skill?\n\r", fskill_name[iSkill] );
      	return;
     }
    gain = atoi(argument);
    if( gain < 1 )
     {
	send_to_char( "&wNow you're just being sillie.\n\r", ch );
	return;
     }
    if( ch->pcdata->force_bonus >= 700 && ch->pcdata->force_bonus < 850 )
	bonus = 4;
    if( ch->pcdata->force_bonus >= 850 && ch->pcdata->force_bonus < 950 )
	bonus = 8;
    if( ch->pcdata->force_bonus >= 950 )
	bonus = 10;
    if( (gain + ch->force_level[skill] ) > fskill_max( ch, skill ) )
     {
        ch_printf( ch, "&w&WYou can only have &G%d &w&Wskillpoints in &G%s&w&W.\n\r", fskill_max( ch, skill ), fskill_name[skill] );
        return;
     }
    if( gain > ch->skillpoints )
     {
	send_to_char( "&wYou don't have that many skillpoints.\n\r", ch );
	return;
     }
    ch->force_level[skill] += gain;
    ch->force_percent[skill] = 0;
    ch->skillpoints -= gain;
    ch_printf( ch, "&wYou put &r%d&w skillpoints into the &b%s&w skill.\n\r", gain, fskill_name[skill] );
    return;
   }
  send_to_char( "Huh?\n\r", ch );
  return;
}

int get_fflag( char *flag )
{
  int x;
  for ( x = 0; x < 32; x++ )
    if ( !str_cmp( flag, feat_name[x] ) )
        return x;
    return -1;
}

int get_f2flag( char *flag )
{
  int x;
  for ( x = 0; x < 32; x++ )
    if ( !str_cmp( flag, feat2_name[x] ) )
	return x;
    return -1;
}

void do_feats( CHAR_DATA *ch, char *argument )
{

  if( IS_NPC(ch) )
    return;

 if( argument[0] == '\0' )
 {
  send_to_char( "&wAlertness&w ", ch );
   if( HAS_FEAT(ch, ALERTNESS_FEAT) )
	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "\n\r", ch );
  send_to_char( "&wAmbidexterity&w ", ch );
   if( HAS_FEAT(ch, AMBIDEXTERITY_FEAT) )
	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "&w\n\r", ch );
  send_to_char( "&wAthletic&w ", ch );
   if( HAS_FEAT(ch, ATHLETIC_FEAT) )
	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "\n\r", ch );
  send_to_char( "&wBlind-Fighting&w ", ch );
   if( HAS_FEAT(ch, BLIND_FIGHT) )
	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "\n\r", ch );
  send_to_char( "&wCautious&w ", ch );
   if( HAS_FEAT(ch, CAUTIOUS_FEAT ) )
   	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "\n\r", ch );
  send_to_char( "&wDodge&w ", ch );
   if( HAS_FEAT(ch, DODGE_FEAT ) )
	send_to_char( "&r+\n\r", ch );
   else
	send_to_char( "\n\r", ch );
  send_to_char( "&wFame&w ", ch );
   if( HAS_FEAT(ch, FAME_FEAT ) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wForce-Sensitive&w ", ch );
   if( HAS_FEAT(ch, FORCE_SENSITIVE) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wFrightful Presense&w ", ch );
   if( HAS_FEAT(ch, FRIGHTFUL_PRESENSE) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wGearhead&w ", ch );
   if( HAS_FEAT(ch, GEARHEAD_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wGreat Fortitude&w ", ch );
   if( HAS_FEAT(ch, GREAT_FORTITUDE) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wHeadstrong&w ", ch );
   if( HAS_FEAT(ch, HEADSTRONG_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wImproved Disarm&w ", ch );
   if( HAS_FEAT(ch, IMPROVED_DISARM) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch ); 
  send_to_char( "&wImproved Trip&w ", ch );
   if( HAS_FEAT(ch, IMPROVED_TRIP) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wImproved Two Weapon Fighting&w ", ch );
   if( HAS_FEAT(ch, IMPROVED_TWO_WEAPON) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wInfamy&w ", ch );
   if( HAS_FEAT(ch, INFAMY_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wInfluence&w ", ch );
   if( HAS_FEAT(ch, INFLUENCE_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wIron Will&w ", ch );
   if( HAS_FEAT(ch, IRON_WILL) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wLightning Reflexes&w ", ch );
   if( HAS_FEAT(ch, LIGHTNING_REFLEXES) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wLow Profile&w ", ch );
   if( HAS_FEAT(ch, LOW_PROFILE) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wNimble&w ", ch );
   if( HAS_FEAT(ch, NIMBLE_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wQuickness\n\r", ch );
  send_to_char( "&wRugged&w ", ch );
   if( HAS_FEAT(ch, RUGGED_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wSharp-Eyed&w ", ch );
   if( HAS_FEAT(ch, SHARP_EYED) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wSkill Emphasis\n\r", ch );
  send_to_char( "&wSpacer&w ", ch );
   if( HAS_FEAT(ch, SPACER_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wStarship Dodge&w ", ch );
   if( HAS_FEAT(ch, STARSHIP_DODGE) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wStarfighter Operations&w ", ch );
   if( HAS_FEAT(ch, FIGHTER_OPS) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wMidship Operations&w ", ch );
   if( HAS_FEAT(ch, MIDSHIP_OPS) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wCapital Operations&w ", ch );
   if( HAS_FEAT(ch, CAPITAL_OPS) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wSteady&w ", ch );
   if( HAS_FEAT(ch, STEADY_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wStealthy&w ", ch );
   if( HAS_FEAT(ch, STEALTHY_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wTrack&w ", ch );
   if( HAS_FEAT(ch, TRACK_FEAT) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&wTwo Weapon Fighting&w ", ch );
   if( HAS_FEAT(ch, TWO_WEAP_FIGHTING) )
        send_to_char( "&r+\n\r", ch );
   else
        send_to_char( "\n\r", ch );
  send_to_char( "&bBlaster Feats&w\n\r", ch );
  if( HAS_FEAT3(ch, POINT_BLANK ) )
   send_to_char( "&gPoint Blank Shot&w, ", ch );
  else
   send_to_char( "&wPoint Blank Shot, ", ch );
  if( HAS_FEAT3(ch, PRECISE_SHOT ) )
   send_to_char( "&gPrecise Shot&w, ", ch );
  else
   send_to_char( "&wPrecise Shot, ", ch );
  if( HAS_FEAT3(ch, FAR_SHOT ) )
   send_to_char( "&gFar Shot&w, ", ch );
  else
   send_to_char( "&wFar Shot, ", ch );
  if( HAS_FEAT3(ch, RAPID_SHOT ) )
   send_to_char( "&gRapid Shot&w\n\r", ch );
  else
   send_to_char( "&wRapid Shot\n\r", ch );   
  send_to_char( "&bWeapon Proficiencies&w\n\r", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
   send_to_char( "&gBlaster Pistols&w, ", ch );
  else
   send_to_char( "&wBlaster Pistols, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
   send_to_char( "&gBlaster Rifles&w, ", ch );
  else
   send_to_char( "&wBlaster Rifles, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_HEAVY) )
   send_to_char( "&gHeavy Weapons&w, ", ch );
  else
   send_to_char( "&wHeavy Weapons, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_PRIMITIVE) )
   send_to_char( "&gPrimitive&w, ", ch );
  else
   send_to_char( "&wPrimitive, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
   send_to_char( "&gSimple&w, ", ch );
  else
   send_to_char( "&wSimple, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
   send_to_char( "&gVibros&w, ", ch );
  else
   send_to_char( "&wVibros, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) )
   send_to_char( "&gLightsaber&w, ", ch );
  else
   send_to_char( "&wLightsaber, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_FORCEPIKE) )
   send_to_char( "&gForce Pike&w, ", ch );
  else
   send_to_char( "&wForce Pike, ", ch );
  if( HAS_FEAT2(ch, WEAP_PROF_BOWCASTER) )
   send_to_char( "&gBowcasters&w\n\r", ch );
  else
   send_to_char( "&wBowcasters\n\r", ch );
 
  send_to_char( "&bImproved Critical&w\n\r", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_PISTOLS) )
   send_to_char( "&gBlaster Pistols&w, ", ch );
  else
   send_to_char( "&wBlaster Pistols, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_RIFLES) )
   send_to_char( "&gBlaster Rifles&w, ", ch );
  else
   send_to_char( "&wBlaster Rifles, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_HEAVY) )
   send_to_char( "&gHeavy Weapons&w, ", ch );
  else
   send_to_char( "&wHeavy Weapons, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_PRIMITIVE) )
   send_to_char( "&gPrimitive&w, ", ch );
  else
   send_to_char( "&wPrimitive, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_SIMPLE) )
   send_to_char( "&gSimple&w, ", ch );
  else
   send_to_char( "&wSimple, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_VIBRO) )
   send_to_char( "&gVibros&w, ", ch );
  else
   send_to_char( "&wVibros, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_LIGHTSABER) )
   send_to_char( "&gLightsaber&w, ", ch );
  else 
   send_to_char( "&wLightsaber, ", ch );
  if( HAS_FEAT2(ch, IMP_CRITICAL_BOWCASTER) )
   send_to_char( "&gBowcasters&w\n\r", ch );
  else
   send_to_char( "&wBowcasters\n\r", ch );
  
  send_to_char( "&bArmor Proficiencies&w\n\r", ch );
  if( HAS_FEAT2(ch, ARMOR_LIGHT) )
   send_to_char( "&gLight Armor&w, ", ch );
  else
   send_to_char( "&wLight Armor, ", ch );
  if( HAS_FEAT2(ch, ARMOR_MEDIUM) )
   send_to_char( "&gMedium Armor&w, ", ch );
  else
   send_to_char( "&wMedium Armor, ", ch );
  if( HAS_FEAT2(ch, ARMOR_HEAVY) )
   send_to_char( "&gHeavy Armor&w, ", ch );
  else
   send_to_char( "&wHeavy Armor, ", ch );
  if( HAS_FEAT2(ch, ARMOR_POWERED) )
   send_to_char( "&gPowered Armor&w\n\r", ch );
  else
   send_to_char( "&wPowered Armor\n\r", ch );
  
  send_to_char( "&bMartial Proficiencies&w\n\r", ch );
  if( HAS_FEAT2(ch, MARTIAL_ARTS) )
   send_to_char( "&gMartial Arts&w, ", ch );
  else
   send_to_char( "&wMartial Arts, ", ch );
  if( HAS_FEAT2(ch, DEF_MARTIAL_ARTS) ) 
   send_to_char( "&gDefensive Martial Arts&w, ", ch );
  else
   send_to_char( "&wDefensive Martial Arts, ", ch );
  if( HAS_FEAT2(ch, IMP_MARTIAL_ARTS) )
   send_to_char( "&gImproved Martial Arts&w, ", ch );
  else
   send_to_char( "&wImproved Martial Arts, ", ch );
  if( HAS_FEAT(ch, ADV_MARTIAL_ARTS) )
   send_to_char( "&gAdvanced Martial Arts&w\n\r", ch );
  else
   send_to_char( "&wAdvanced Martial Arts\n\r", ch );
  send_to_char( "\n\r", ch );
  ch_printf( ch, "&wYou have &g%d&w free feats.\n\r", ch->unused_feats );
  return;
 }

 if( ch->unused_feats < 1 )
 {
	send_to_char( "&wYou don't have any unused feat points.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "point blank") || !str_cmp(argument, "point blank shot" ) )
 {
	if( HAS_FEAT3(ch, POINT_BLANK) )
	 {
		send_to_char( "&wYou already have this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats3, POINT_BLANK);
	send_to_char( "&wYou now possess the &YPoint Blank Shot&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "precise shot") )
 {
	if( HAS_FEAT3(ch, PRECISE_SHOT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT3(ch, POINT_BLANK) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats3, PRECISE_SHOT);
	send_to_char( "&wYou now possess the &YPrecise Shot&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "far shot" ) )
 {
	if( HAS_FEAT3(ch, FAR_SHOT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT3(ch, POINT_BLANK) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats3, FAR_SHOT);
	send_to_char( "&wYou now possess the &YFar Shot&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "rapid shot" ) )
 {
	if( HAS_FEAT3(ch, RAPID_SHOT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT3(ch, POINT_BLANK) || get_curr_dex(ch) < 13 )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats3, RAPID_SHOT);
	send_to_char( "&wYou now possess the &YRapid Shot&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "martial arts") )
 {
	if( IS_DROID(ch) )
	 {
		send_to_char( "&wDroids must purchase Martial Art programming.\n\r", ch );
		return;
	 }
	if( HAS_FEAT2(ch, MARTIAL_ARTS) )
         {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, MARTIAL_ARTS);
	send_to_char( "&wYou have gained the &YMartial Arts&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "advanced martial arts") )
 {
	if( IS_DROID(ch) )
	 {
		send_to_char( "&wDroids must purchase Martial Art programming.\n\r", ch );
		return;
	 }
	if( HAS_FEAT(ch, ADV_MARTIAL_ARTS) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT2(ch, IMP_MARTIAL_ARTS) || ch->top_level < 8 )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, ADV_MARTIAL_ARTS);
	send_to_char( "&wYou have gained the &YImproved Martial Arts&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "defensive martial arts") )
 {
	if( IS_DROID(ch) )
	 {
		send_to_char( "&wDroids must purchase martial arts programming.\n\r", ch );
		return;
	 }
	if( HAS_FEAT2(ch, DEF_MARTIAL_ARTS) ) 
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT2(ch, MARTIAL_ARTS) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, DEF_MARTIAL_ARTS);
	send_to_char( "&wYou have gained the &YDefensive Martial Arts&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "improved martial arts") )
 {
	if( IS_DROID(ch) )
	 {
		send_to_char( "&wDroids must purchase martial arts programming.\n\r", ch );
		return;
	 }
	if( HAS_FEAT2(ch, IMP_MARTIAL_ARTS) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT2(ch, MARTIAL_ARTS) || ch->top_level < 4 )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, IMP_MARTIAL_ARTS);
	send_to_char( "&wYou have gained the &YImproved Martial Arts&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "alertness") )
 {
	if( HAS_FEAT(ch, ALERTNESS_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[LISTEN_SKILL] += 2;
	ch->skill_level[SPOT_SKILL] += 2;
	SET_BIT(ch->feats, ALERTNESS_FEAT);
	send_to_char( "&wYou have gained the &YAlertness&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "ambidexterity") )
 {
	if( HAS_FEAT(ch, AMBIDEXTERITY_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( get_curr_dex(ch) < 15 )
	 {
		send_to_char( "&wYou lack the required &bDexterity&w to do this.\n\r", ch );
		return;
	 }
	SET_BIT(ch->feats, AMBIDEXTERITY_FEAT);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have gained the &YAmbidexterity&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "athletic") )
 {
	if( HAS_FEAT(ch, ATHLETIC_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[CLIMB_SKILL] += 2;
	ch->skill_level[SWIM_SKILL] += 2;
	SET_BIT(ch->feats, ATHLETIC_FEAT);
	send_to_char( "&wYou have gained the &YAthletic&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "blind-fighting") )
 {
	if( HAS_FEAT(ch, BLIND_FIGHT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, BLIND_FIGHT);
	send_to_char( "&wYou have gained the &YBlind-Fighting&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "cautious" ) )
 {
	if( HAS_FEAT(ch, CAUTIOUS_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
 	 }
	ch->unused_feats -= 1;
	ch->skill_level[DISABLE_DEVICE] += 2;
	ch->skill_level[DEMOLITIONS_SKILL] += 2;
	SET_BIT(ch->feats, CAUTIOUS_FEAT);
	send_to_char( "&wYou have gained the &YCautious&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "dodge" ) )
 {
	if( HAS_FEAT(ch, DODGE_FEAT) ) 
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->dodge_bonus += 1;
	SET_BIT(ch->feats, DODGE_FEAT);
	send_to_char( "&wYou have gained the &YDodge&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "fame" ) )
 {
	if( HAS_FEAT(ch, FAME_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->reputation += 3;
	SET_BIT(ch->feats, FAME_FEAT);
	send_to_char( "&wYou have gained the &YFame&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "force-sensitive") || !str_cmp(argument, "force sensitive") )
 {
        if( IS_DROID(ch) )
         {
                send_to_char( "&wDroids can't be Force-Sensitive.\n\r", ch );
                return;
         }
	if( HAS_FEAT(ch, FORCE_SENSITIVE) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->forcepoints += 1;
	SET_BIT(ch->feats, FORCE_SENSITIVE);
	send_to_char( "&wYou have gained the &YForce-Sensitive&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "frightful presense") )
 {
	if( HAS_FEAT(ch, FRIGHTFUL_PRESENSE) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( get_curr_cha(ch) < 15 || ch->skill_level[INTIMIDATE_SKILL] < 9 )
   	 {
		send_to_char( "&wYou are lacking one of the requirements to gain this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, FRIGHTFUL_PRESENSE);
	send_to_char( "&wYou have gained the &YFrightful Presense&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "gearhead") )
 {
	if( HAS_FEAT(ch, GEARHEAD_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[REPAIR_SKILL] += 2;
	ch->skill_level[COMPUTER_SKILL] += 2;
	SET_BIT(ch->feats, GEARHEAD_FEAT);
	send_to_char( "&wYou have gained the &YGearhead&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "great fortitude") )
 {
	if( HAS_FEAT(ch, GREAT_FORTITUDE) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->fortitude += 2;
	SET_BIT(ch->feats, GREAT_FORTITUDE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have gained the &YGreat Fortitude&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "headstrong" ) )
 {
	if( HAS_FEAT(ch, HEADSTRONG_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->willpower += 1;
	ch->skill_level[INTIMIDATE_SKILL] += 2;
	SET_BIT(ch->feats, HEADSTRONG_FEAT);
	send_to_char( "&wYou have gained the &YHeadstrong&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "improved disarm") )
 {
	if( HAS_FEAT(ch, IMPROVED_DISARM) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( get_curr_dex(ch) < 13 )
	 {
	 	send_to_char( "&wYou lack one of the requirements to gain this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, IMPROVED_DISARM);
	send_to_char( "&wYou have gained the &YImproved Disarm&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "improved trip") )
 {
	if( HAS_FEAT(ch, IMPROVED_TRIP) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( get_curr_dex(ch) < 13 )
	 {
		send_to_char( "&wYou lack one of the requirements to gain this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, IMPROVED_TRIP);
	send_to_char( "&wYou have gained the &YImproved Trip&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "improved two weapon fighting" ) )
 {
	if( HAS_FEAT(ch, IMPROVED_TWO_WEAPON) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }	
	if( !HAS_FEAT(ch, TWO_WEAP_FIGHTING) || !HAS_FEAT(ch, AMBIDEXTERITY_FEAT) || ch->top_level < 9 )
	 {
	 	send_to_char( "&wYou lack one of the requirements for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, IMPROVED_TWO_WEAPON);
	send_to_char( "&wYou have gained the &YImproved Two Weapon Fighting&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "infamy" ) )
 {
	if( HAS_FEAT(ch, INFAMY_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->reputation += 3;
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, INFAMY_FEAT);
	send_to_char( "&wYou have gained the &YInfamy&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "influence" ) )
 {
	if( HAS_FEAT(ch, INFLUENCE_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->reputation += 2;
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, INFLUENCE_FEAT);
	send_to_char( "&wYou have gained the &YInfluence&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "iron will" ) )
 {
	if( HAS_FEAT(ch, IRON_WILL) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->willpower += 2;
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, IRON_WILL );
	send_to_char( "&wYou have gained the &YIron Will&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "lightning reflexes") )
 {
	if( HAS_FEAT(ch, LIGHTNING_REFLEXES) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->reflexes += 2;
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, LIGHTNING_REFLEXES);
	send_to_char( "&wYou have gained the &YLightning Reflexes&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "low profile") )
 {
	if( HAS_FEAT(ch, LOW_PROFILE) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->reputation -= 2;
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, LOW_PROFILE);
	send_to_char( "&wYou have gained the &YLow Profile&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "nimble") )
 {
	if( HAS_FEAT(ch, NIMBLE_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[ESCAPE_ARTIST] += 2;
	ch->skill_level[SLEIGHT_OF_HAND] += 2;
	SET_BIT(ch->feats, NIMBLE_FEAT);
	send_to_char( "&wYou have gained the &YNimble&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "quickness") )
 {
	ch->unused_feats -= 1;
	ch->max_hit += 5;
	ch->hit += 5;
	send_to_char( "&wYou have gained the &YQuickness&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "rugged") )
 {
	if( HAS_FEAT(ch, RUGGED_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->fortitude += 1;
	ch->skill_level[SURVIVAL_SKILL] += 2;
	SET_BIT(ch->feats, RUGGED_FEAT);
	send_to_char( "&wYou have gained the &YRugged&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "sharp-eyed") || !str_cmp(argument, "sharp eyed") )
 {
	if( HAS_FEAT(ch, SHARP_EYED) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[SEARCH_SKILL] += 2;
	ch->skill_level[SPOT_SKILL] += 2;
	SET_BIT(ch->feats, SHARP_EYED);
	send_to_char( "&wYou have gained the &YSharp-Eyed&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "skill emphasis") )
 {
	ch->unused_feats -= 1;
	ch->skillpoints += 5;
	send_to_char( "&wYou have gained the &YSkill Emphasis&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "spacer") )
 {
	if( HAS_FEAT(ch, SPACER_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[ASTROGATE_SKILL] += 2;
	ch->skill_level[PILOT_SKILL] += 2;
	SET_BIT(ch->feats, SPACER_FEAT);
	send_to_char( "&wYou have gained the &YSpacer&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "starship dodge") )
 {
	if( HAS_FEAT(ch, STARSHIP_DODGE) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( get_curr_dex(ch) < 13 || ch->skill_level[PILOT_SKILL] < 6 )
	 {
		send_to_char( "&wYou lack one of the requirements to take this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, STARSHIP_DODGE);
	send_to_char( "&wYou have gained the &YStarship Dodge&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "starfighter operations") )
 {
	if( HAS_FEAT(ch, FIGHTER_OPS) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( ch->skill_level[PILOT_SKILL] < 2 )
	 {
		send_to_char( "&wYou lack the requirement to take this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, FIGHTER_OPS);
	send_to_char( "&wYou have gained the &YStarfighter Operations&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "midship operations") )
 {
	if( HAS_FEAT(ch, MIDSHIP_OPS) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( ch->skill_level[PILOT_SKILL] < 2 )
	 {
		send_to_char( "&wYou lack the requirement to take this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, MIDSHIP_OPS);
	send_to_char( "&wYou have gained the &YMidship Operations&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "capital operations") )
 {
	if( HAS_FEAT(ch, CAPITAL_OPS) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( ch->skill_level[PILOT_SKILL] < 2 )
	 {
		send_to_char( "&wYou lack the requirement to take this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats, CAPITAL_OPS);
	send_to_char( "&wYou have gained the &YCapital Operations&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "steady") )
 {
	if( HAS_FEAT(ch, STEADY_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->reflexes += 1;
	ch->skill_level[BALANCE_SKILL] += 2;
	SET_BIT(ch->feats, STEADY_FEAT);
	send_to_char( "&wYou have gained the &YSteady&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "stealthy") )
 {
	if( HAS_FEAT(ch, STEALTHY_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	ch->skill_level[HIDE_SKILL] += 2;
	ch->skill_level[MOVE_SILENTLY] += 2;
	SET_BIT(ch->feats, STEALTHY_FEAT);
	send_to_char( "&wYou have gained the &YStealthy&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "track") )
 {
	if( HAS_FEAT2(ch, TRACK_FEAT) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, TRACK_FEAT);
	send_to_char( "&wYou have gained the &YTrack&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "two weapon fighting") )
 {
	if( HAS_FEAT2(ch, TWO_WEAP_FIGHTING) )
	 {
		send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, TWO_WEAP_FIGHTING);
	send_to_char( "&wYou have gained the &YTwo Weapon Fighting&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "pistol") || !str_cmp(argument, "pistols") || !str_cmp( argument, "blaster pistols") || !str_cmp(argument, "blaster pistol"))
 {
	if( HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_PISTOLS) )
	   {
		send_to_char( "&wYou already are a master with &bBlaster Pistols&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_PISTOLS);
	  send_to_char( "&wYou have gained the &YImproved Critical Blaster Pistol&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Blaster Pistol&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "force pike") )
 {
	if( HAS_FEAT2(ch, WEAP_PROF_FORCEPIKE) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_FORCEPIKE) )
	   {
		send_to_char( "&wYou already area  master with &bForce Pikes&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_FORCEPIKE);
	  send_to_char( "&wYou have gained the &YImproved Critical Force Pikes&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_FORCEPIKE);
	send_to_char( "&wYou gained the &YWeapon Proficiency Force Pikes&w.\n\r", ch);
	return;
 }
 if( !str_cmp(argument, "rifle") || !str_cmp(argument, "rifles") || !str_cmp(argument, "blaster rifles") || !str_cmp(argument, "blaster rifle"))
 {
	if( HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_RIFLES) )
	   {
		send_to_char( "&wYou already are a master with &bBlaster Rifles&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_RIFLES);
	  send_to_char( "&wYou have gained the &YImproved Critical Blaster Rifle&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Blaster Rifle&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "heavy") || !str_cmp(argument, "heavy weapon") || !str_cmp(argument, "heavy weapons") )
 {
	if( HAS_FEAT2(ch, WEAP_PROF_HEAVY) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_HEAVY) )
	   {
		send_to_char( "&wYou already are a master with &bHeavy Weapons&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_HEAVY);
	  send_to_char( "&wYou have gained the &YImproved Critical Heavy Weapon&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_HEAVY);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Heavy Weapons&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "primitive") )
 {
	if( HAS_FEAT2(ch, WEAP_PROF_PRIMITIVE) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_PRIMITIVE) )
	   {
		send_to_char( "&wYou already are a master with &bPrimitive Weapons&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_PRIMITIVE);
	  send_to_char( "&wYou have gained the &YImproved Critical Primitive Weapon&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Primitive Weapon&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "simple") )
 {
	if( HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_SIMPLE) )
	   {
		send_to_char( "&wYou already are a master with &bSimple Weapons&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_SIMPLE);
	  send_to_char( "&wYou have gained the &YImproved Critical Simple Weapon&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Simple Weapons&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "vibro") || !str_cmp(argument, "vibros"))
 {
	if( HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_VIBRO) )
	   {
		send_to_char( "&wYou already are a master with &bVibro Weapons&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_VIBRO);
	  send_to_char( "&wYou have gained the &YImproved Critical Vibro Weapon&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Vibro Weapons&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "lightsaber") )
 {
	if( HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_LIGHTSABER) )
	   {
		send_to_char( "&wYou already are a master with &bLightsabers&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_LIGHTSABER);
	  send_to_char( "&wYou have gained the &YImproved Critical Lightsabers&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_LIGHTSABER);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Lightsabers&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "bowcaster") || !str_cmp( argument, "bowcasters" ))
 {
	if( HAS_FEAT2(ch, WEAP_PROF_BOWCASTER) )
	 {
	  if( HAS_FEAT2(ch, IMP_CRITICAL_BOWCASTER) )
	   {
		send_to_char( "&wYou already are a master with &bBowcasters&w.\n\r", ch );
		return;
	   }
	  ch->unused_feats -= 1;
	  SET_BIT(ch->feats2, IMP_CRITICAL_BOWCASTER);
	  send_to_char( "&wYou have gained the &YImproved Critical Bowcasters&w feat.\n\r", ch );
	  return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, WEAP_PROF_BOWCASTER);
	send_to_char( "&wYou have gained the &YWeapon Proficiency Bowcaster&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "light armor") )
 {
	if( HAS_FEAT2(ch, ARMOR_LIGHT) )
	 {
		send_to_char( "&wYou already have that fead.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, ARMOR_LIGHT);
	send_to_char( "&wYou have gained the &YLight Armor&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "medium armor") )
 {
	if( HAS_FEAT2(ch, ARMOR_MEDIUM) )
	 {
		send_to_char( "&wYou already have that fead.\n\r", ch );
		return;
	 }
	if( !HAS_FEAT2(ch, ARMOR_LIGHT) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, ARMOR_MEDIUM);
	send_to_char( "&wYou have gained the &YMedium Armor&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "heavy armor") )
 {
	if( HAS_FEAT2(ch, ARMOR_HEAVY) )
	 {
		send_to_char( "&wYou already have that fead.\n\r", ch );
		return;
	 }
	if( HAS_FEAT2(ch, ARMOR_MEDIUM) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, ARMOR_HEAVY);
	send_to_char( "&wYou have gained the &YHeavy Armor&w feat.\n\r", ch );
	return;
 }
 if( !str_cmp(argument, "powered armor") )
 {
	if( HAS_FEAT2(ch, ARMOR_POWERED) )
	 {
		send_to_char( "&wYou already have that fead.\n\r", ch );
		return;
	 }
	if( HAS_FEAT2(ch, ARMOR_MEDIUM) )
	 {
		send_to_char( "&wYou lack a requirement for this feat.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->feats2, ARMOR_POWERED);
	send_to_char( "&wYou have gained the &YPowered Armor&w feat.\n\r", ch );
	return;
 }

 send_to_char( "&wThat isn't a feat.\n\r", ch );
 return;
}

void do_ffeats( CHAR_DATA *ch, char *argument )
{
  if( IS_NPC(ch) )
	return;

  if( !HAS_FEAT(ch, FORCE_SENSITIVE) && !IS_IMMORTAL(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }

  if( argument[0] == '\0' )
   {
     send_to_char( "&wAlter ", ch );
       if( HAS_FFEAT(ch, ALTER_FEAT) )
	send_to_char( "&r+&w\n\r", ch );
       else
	send_to_char( "\n\r", ch );
     if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, ALTER_FEAT) )
      {
       if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, CONTROL_FEAT) )
	{
	send_to_char( " &wFocus ", ch );
	 if( HAS_FFEAT(ch, FOCUS_FEAT) )
	  send_to_char( "&r+&w\n\r", ch );
	 else
	  send_to_char( "\n\r", ch );
	}
	send_to_char( " &wForce Flight ", ch );
	 if( HAS_FFEAT(ch, FORCE_FLIGHT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wForce Whirlwind ", ch );
	 if( HAS_FFEAT(ch, FORCE_WHIRLWIND) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	if( IS_IMMORTAL(ch) || ch->darkpoints >= 2 )
	 {
	  send_to_char( " &wHatred ", ch );
	   if( HAS_FFEAT(ch, HATRED_FEAT) )
	    send_to_char( "&r+&w\n\r", ch );
	   else
	    send_to_char( "\n\r", ch );
         }
	send_to_char( " &wMind Trick ", ch );
	 if( HAS_FFEAT(ch, MIND_TRICK) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( "\n\r", ch );
       }
      send_to_char( "&wControl ", ch );
       if( HAS_FFEAT(ch, CONTROL_FEAT) )
	send_to_char( "&r+&w\n\r", ch );
       else
	send_to_char( "\n\r", ch );
      if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, CONTROL_FEAT) )
       {
	send_to_char( " &wAttuned ", ch );
	 if( HAS_FFEAT(ch, ATTUNED_FEAT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wDissipate Energy ", ch );
	 if( HAS_FFEAT(ch, DISSIPATE_ENERGY) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wLightsaber Defense ", ch );
	 if( HAS_FFEAT(ch, LIGHTSABER_DEFENSE) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wKnight Defense ", ch );
	 if( HAS_FFEAT(ch, KNIGHT_DEFENSE) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wMaster Defense ", ch );
	 if( HAS_FFEAT(ch, MASTER_DEFENSE) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wMettle ", ch );
	 if( HAS_FFEAT(ch, METTLE_FEAT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wRage ", ch );
	 if( HAS_FFEAT(ch, RAGE_FEAT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( "\n\r", ch );
       }
      send_to_char( "&wSense ", ch );
       if( HAS_FFEAT(ch, SENSE_FEAT) )
	send_to_char( "&r+&w\n\r", ch );
       else
	send_to_char( "\n\r", ch );
      if( IS_IMMORTAL(ch) || HAS_FFEAT(ch, SENSE_FEAT) )
       {
	send_to_char( " &wAware ", ch );
	 if( HAS_FFEAT( ch, AWARE_FEAT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wForce Mind ", ch );
	 if( HAS_FFEAT( ch, FORCE_MIND) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wImproved Force Mind ", ch );
	 if( HAS_FFEAT( ch, IMP_FORCE_MIND) )
	  send_to_char( "&r+&w\n\r", ch );
	 else
	  send_to_char( "\n\r", ch );
	send_to_char( " &wKnight Mind ", ch );
	 if( HAS_FFEAT( ch, KNIGHT_MIND) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wMaster Mind ", ch );
	 if( HAS_FFEAT( ch, MASTER_MIND) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	send_to_char( " &wLink ", ch );
	 if( HAS_FFEAT( ch, LINK_FEAT) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
	if( IS_IMMORTAL(ch) || ch->darkpoints >= 6 )
	 {
	  send_to_char( " &wSith Sorcery ", ch );
	   if( HAS_FFEAT(ch, SITH_SORCERY) )
	    send_to_char( "&r+&w\n\r", ch );
	   else
	    send_to_char( "\n\r", ch );
	 }
	send_to_char( "\n\r", ch );
       }
    if( IS_IMMORTAL(ch) || ( HAS_FFEAT(ch, SENSE_FEAT) && HAS_FFEAT(ch, ALTER_FEAT) ) )
     {
	send_to_char( "&wMalevolent ", ch );
	 if( HAS_FFEAT( ch, MALEVOLENT_FEAT ) )
          send_to_char( "&r+&w\n\r", ch );
         else
          send_to_char( "\n\r", ch );
     }
    if( IS_IMMORTAL(ch) || ( HAS_FFEAT(ch, ALTER_FEAT) && HAS_FEAT(ch, CONTROL_FEAT) && HAS_FFEAT(ch, SITH_SORCERY) ) )
     {
	send_to_char( "&wDrain Force ", ch );
	 if( HAS_FFEAT(ch, DRAIN_FORCE ) )
	  send_to_char( "&r+&w\n\r", ch );
	 else
	  send_to_char( "\n\r", ch );
     }
    send_to_char( "\n\r", ch );
    ch_printf( ch, "&wYou have &b%d&w free feats.\n\r", ch->unused_feats );
    return;
   }

  if( ch->unused_feats < 1 )
   {
	send_to_char( "&wYou don't have any free feats.\n\r", ch );
	return;
   }

  if( !str_cmp(argument, "alter") )
   {
	if( HAS_FFEAT(ch, ALTER_FEAT) )
	 {
	  	send_to_char( "&wYou already possess this feat.\n\r", ch );
		return;
	 }
	if( !IS_FORCER(ch) )
	 {
		send_to_char( "&wOnly &YForcers&w can take Force feats.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, ALTER_FEAT);
	send_to_char( "&wYou have gained the Force feat of &bAlter&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "focus") )
  {
	if( HAS_FFEAT(ch, FOCUS_FEAT) )
	 {
		send_to_char( "&wYou already possess that feat.\n\r", ch );
		return;
	 }
	if( !HAS_FFEAT(ch, ALTER_FEAT) || !HAS_FFEAT(ch, CONTROL_FEAT) )
	 {
		send_to_char( "&wYou lack one of the requirements.\n\r", ch );
		return;
	 }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, ALTER_FEAT);
	ch->force_level[FORCE_STRIKE] += 2;
	ch->force_level[FORCE_STEALTH] += 2;
	send_to_char( "&wYou have gained the Force feat &bFocus&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "force flight") )
   {
        if( HAS_FFEAT(ch, FORCE_FLIGHT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, ALTER_FEAT) || ch->force_level[MOVE_OBJECT] < 6 || ch->top_level < 7 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, FORCE_FLIGHT);
	send_to_char( "&wYou have gained the Force feat &bForce Flight&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "force whirlwind" ) )
   {
        if( HAS_FFEAT(ch, FORCE_WHIRLWIND) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, ALTER_FEAT) || get_curr_int(ch) < 13 || ch->force_level[MOVE_OBJECT] < 5 || ch->top_level < 6 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, FORCE_WHIRLWIND);
	send_to_char( "&wYou have gained the Force feat &bForce Whirlwind&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "mind trick" ) )
   {
        if( HAS_FFEAT(ch, MIND_TRICK) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, ALTER_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, MIND_TRICK);
	ch->force_level[AFFECT_MIND] += 2;
	ch->force_level[ILLUSION_SKILL] += 2;
	send_to_char( "&wYou gain the Force feat &bMind Trick&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "control") )
   {
        if( HAS_FFEAT(ch, CONTROL_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FEAT(ch, FORCE_SENSITIVE) || !IS_FORCER(ch) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, CONTROL_FEAT);
	send_to_char( "&wYou gain the Force feat &bControl&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "attunded" ) )
   {
        if( HAS_FFEAT(ch, ATTUNED_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, CONTROL_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, ATTUNED_FEAT);
	ch->force_level[HEAL_SELF] += 2;
	ch->force_level[ENHANCE_ABILITY] += 2;
	send_to_char( "&wYou gain the Force feat &bAttuned&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "dissipate energy") )
   {
        if( HAS_FFEAT(ch, DISSIPATE_ENERGY) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, CONTROL_FEAT) || ch->top_level < 4 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, DISSIPATE_ENERGY);
	send_to_char( "&wYou gain the Force feat &bDissipate Energy&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "lightsaber defense") )
   {
        if( HAS_FFEAT(ch, LIGHTSABER_DEFENSE) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, CONTROL_FEAT) || get_curr_dex(ch) < 13 || ch->top_level < 3
	 || !HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, LIGHTSABER_DEFENSE);
	ch->lightsaber_defense += 2;
	send_to_char( "&wYou gain the Force feat &bLightsaber Defense&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "knight defense" ) )
   {
        if( HAS_FFEAT(ch, KNIGHT_DEFENSE) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, LIGHTSABER_DEFENSE) || ch->top_level < 7)
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, KNIGHT_DEFENSE);
	ch->lightsaber_defense += 2;
	send_to_char( "&wYou gain the Force feat &bKnight Defense&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "master defense") )
   {
        if( HAS_FFEAT(ch, MASTER_DEFENSE) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, LIGHTSABER_DEFENSE) || ch->top_level < 11 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	ch->lightsaber_defense += 2;
	SET_BIT(ch->force_feats, MASTER_DEFENSE);
	send_to_char( "&wYou gain the Force feat &bMaster Defense&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "mettle") )
   {
        if( HAS_FFEAT(ch, METTLE_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, CONTROL_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, METTLE_FEAT);
	ch->force_level[FORCE_DEFENSE] += 2;
	ch->force_level[BATTLEMIND_SKILL] += 2;
	send_to_char( "&wYou gain the Force feat &bMettle&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "rage") )
   {
        if( HAS_FFEAT(ch, RAGE_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, CONTROL_FEAT) || ch->darkpoints < 2 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, RAGE_FEAT);
	send_to_char( "&wYou gain the Force feat &bRage&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "sense") )
   {
        if( HAS_FFEAT(ch, SENSE_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FEAT(ch, FORCE_SENSITIVE) || !IS_FORCER(ch) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;	
	SET_BIT(ch->force_feats, SENSE_FEAT);
	send_to_char( "&wYou gain the Force feat &bSense&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "aware") )
   {
        if( HAS_FFEAT(ch, AWARE_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, SENSE_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	ch->force_level[ENHANCE_SENSES] += 2;
	ch->force_level[SEE_FORCE] += 2;
	SET_BIT(ch->force_feats, AWARE_FEAT);
	send_to_char( "&wYou gain the Force feat &bAware&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "force mind") )
   {
        if( HAS_FFEAT(ch, FORCE_MIND) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, SENSE_FEAT) || get_curr_wis(ch) < 15 || ch->top_level < 3 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, FORCE_MIND);
	send_to_char( "&wYou gain the Force feat &bForce Mind&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "improved force mind" ) )
   {
        if( HAS_FFEAT(ch, IMP_FORCE_MIND) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, SENSE_FEAT) || get_curr_wis(ch) < 15 || ch->top_level < 5 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, IMP_FORCE_MIND);
	send_to_char( "&wYou gained the Force feat &bImproved Force Mind&w.\n\r", ch );
	return;
   }
  if( !str_cmp(argument, "knight mind") )
   {
        if( HAS_FFEAT(ch, KNIGHT_MIND) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, FORCE_MIND) || ch->top_level < 7 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, KNIGHT_MIND );
	send_to_char( "&wYou gained the Force feat &bKnight Mind&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "master mind") )
   {
        if( HAS_FFEAT(ch, MASTER_MIND) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, FORCE_MIND) || ch->top_level < 11 )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, MASTER_MIND);
	send_to_char( "&wYou gained the Force feat &bMaster Mind&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "link" ) )
   {
        if( HAS_FFEAT(ch, LINK_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, SENSE_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, LINK_FEAT);
	ch->force_level[TELEPATHY_SKILL] += 2;
	ch->force_level[FARSEEING_SKILL] += 2;
	send_to_char( "&wYou gained the Force feat &bLink&w.\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "malevolent" ) )
   {
        if( HAS_FFEAT(ch, MALEVOLENT_FEAT) )
         {
                send_to_char( "&wYou already possess that feat.\n\r", ch );
                return;
         }
        if( !HAS_FFEAT(ch, ALTER_FEAT) || !HAS_FFEAT(ch, SENSE_FEAT) )
         {
                send_to_char( "&wYou lack one of the requirements.\n\r", ch );
                return;
         }
	ch->unused_feats -= 1;
	SET_BIT(ch->force_feats, MALEVOLENT_FEAT);
	ch->force_level[FEAR_SKILL] += 2;
	ch->force_level[FORCE_GRIP] += 2;
	send_to_char( "&wYou gained the Force feat &bMalevolent&w.\n\r", ch );
	return;
   }
  send_to_char( "&wThat isn't a feat.\n\r", ch );
  return;
}

void level_class( CHAR_DATA *ch, int ability )
{
  int level, gain, skill;

  if( IS_NPC(ch) )
     return;

  if( ability < 0 || ability >= MAX_ABILITY )
   {
	bug( "&rlevel_class: ability out of range&w\n\r", 0);
	return;
   }
  if( ability == AEROBAT_ABILITY )
   {
     ch->class_level[AEROBAT_ABILITY] += 1;
     level = ch->class_level[AEROBAT_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     skill = 4 + stat_table[get_curr_int(ch)].mod;
     ch->skillpoints += skill;
     if( level != 1 && level != level != 5  && level != 9 )
        ch->hitroll += 1;
     if( level == 1 )
      {
	ch->reflexes += 3;
	ch->aerial_defense += 2;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 3 )
	ch->reputation += 1;
     if( level == 4 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	SET_BIT(ch->feats3, AERIAL_EVASION);
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 6 )
	ch->reflexes += 1;
     if( level == 7 )
      {
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
      }
     if( level == 9 )
      {
	ch->armor += 1;
	ch->aerial_defense += 2;
      }
     if( level == 10 )
      {
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     return;
    }
  if( ability == MYSTICAGENT_ABILITY )
   {
     ch->class_level[MYSTICAGENT_ABILITY] += 1;
     level = ch->class_level[MYSTICAGENT_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     skill = 6 + stat_table[get_curr_int(ch)].mod;
     ch->skillpoints += skill;
     if( level != 1 && level != level != 5 && level != 9 )
        ch->hitroll += 1;
     if( level == 1 )
      {
	ch->willpower += 3;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 3 )
	ch->willpower += 2;
     if( level == 4 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 2;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->armor += 1;
	ch->willpower += 1;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->willpower += 2;
	ch->armor += 1;
      }
     if( level == 9 )
      {
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     return;
    }
  if( ability == ESPIONAGE_ABILITY )
   {
     ch->class_level[ESPIONAGE_ABILITY] += 1;
     level = ch->class_level[ESPIONAGE_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     skill = 6 + stat_table[get_curr_int(ch)].mod;
     ch->skillpoints += skill;
     if( level != 1 && level != level != 5 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	ch->fortitude += 1;
	ch->willpower += 2;
	ch->reflexes += 1;
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
      }
     if( level == 4 )
	ch->reputation += 1;
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     return;
   }
  if( ability == BERSERKER_ABILITY )
   {
     ch->class_level[BERSERKER_ABILITY] += 1;
     level = ch->class_level[BERSERKER_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     skill = 6 + stat_table[get_curr_int(ch)].mod;
     ch->skillpoints += skill;
     if( level != 1 && level != 5 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	ch->fortitude += 1;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->armor += 2;
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
     }
    if( level == 2 )
     {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
     }
    if( level == 3 )
	ch->sneak_attack += 2;
    if( level == 4 )
     {
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
     }
    if( level == 5 )
     {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reputation += 1;
     }
    return;
   }
  if( ability == FRINGER_ABILITY )
   {
     ch->class_level[FRINGER_ABILITY] += 1;
     level = ch->class_level[FRINGER_ABILITY];
     if( level == 1 )
    	gain = 8;
     else
	gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
	gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
	skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->fortitude += 2;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 3;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	SET_BIT(ch->feats2, BARTER_FEAT);
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->jury_rig += 2;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->skill_level[SURVIVAL_SKILL] += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->jury_rig += 2;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
      }
     if( level == 9 )
      {
	ch->willpower += 1;
	ch->jury_rig += 2;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->skill_level[SURVIVAL_SKILL] += 2;
	ch->armor += 1;
      }
     if( level == 11 )
	ch->hitroll += 1;
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 13 )
      {
	ch->reputation += 1;
	ch->jury_rig += 2;
      }
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
      }
     if( level == 17 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->skill_level[SURVIVAL_SKILL] += 2;
      }
     if( level == 19 )
	ch->hitroll += 1;
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == NOBLE_ABILITY )
    {
     ch->class_level[NOBLE_ABILITY] += 1;
     level = ch->class_level[NOBLE_ABILITY];
     if( level == 1 )
        gain = 6;
     else
        gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->armor += 2;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->coordinate += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;	
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->coordinate += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->unused_feats += 1;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 11 )
	ch->hitroll += 1;
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 13 )
	ch->coordinate += 1;
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 17 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->coordinate += 1;
      }
     if( level == 19 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
      }
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->coordinate += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
   }
  if( ability == SCOUNDREL_ABILITY )
   {
     ch->class_level[SCOUNDREL_ABILITY] += 1;
     level = ch->class_level[SCOUNDREL_ABILITY];
     if( level == 1 )
        gain = 6;
     else
        gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (8 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->reflexes += 2;
	SET_BIT(ch->feats2, ILLICIT_BARTER);
	ch->armor += 2;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->precise_attack += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     if( level == 5 )
      {
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     if( level == 9 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->precise_attack += 1;
	ch->armor += 1;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 11 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 13 )
	ch->armor += 1;
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->precise_attack += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     if( level == 17 )
	ch->armor += 1;
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
      }
     if( level == 19 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     return;
    }
   if( ability == SCOUT_ABILITY )
    {
     ch->class_level[SCOUT_ABILITY] += 1;
     level = ch->class_level[SCOUT_ABILITY];
     if( level == 1 )
        gain = 8;
     else
        gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;	
	ch->unused_feats += 1;
	ch->armor += 2;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	SET_BIT(ch->feats2, TRAILBLAZING_FEAT);
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->heart += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->reputation += 1;
	SET_BIT(ch->feats2, UNCANNY_DODGE);
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 6 )
	ch->hitroll += 1;
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;	
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
	ch->armor += 1;
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
      }
     if( level == 11 )
      {
	ch->hitroll += 1;
	ch->heart += 1;
	ch->armor += 1;
      }
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 13 )
	ch->armor += 1;
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->heart += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 17 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->heart += 1;
      }
     if( level == 19 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
      }
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == SOLDIER_ABILITY )
    {
     ch->class_level[SOLDIER_ABILITY] += 1;
     level = ch->class_level[SOLDIER_ABILITY];
     if( level == 1 )
        gain = 10;
     else
        gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     ch->hitroll += 1;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	SET_BIT(ch->feats2, WEAP_PROF_HEAVY);
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 2;
	ch->armor += 3;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     if( level == 5 )
	ch->armor += 1;
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 7 )
	ch->armor += 1;
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     if( level == 9 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 11 )
	ch->armor += 1;
     if( level == 12 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     if( level == 13 )
	ch->armor += 1;
     if( level == 14 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 15 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     if( level == 17 )
	ch->armor += 1;
     if( level == 18 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 19 )
      	ch->armor += 1;
     if( level == 20 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     return;
    }
   if( ability == TECH_SPEC_ABILITY )
    {
     ch->class_level[TECH_SPEC_ABILITY] += 1;
     level = ch->class_level[TECH_SPEC_ABILITY];
     if( level == 1 )
        gain = 6;
     else
        gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
	ch->armor += 2;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
	ch->reputation += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->specialty += 1;
      }
     if( level == 5 )
	ch->armor += 1;
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->specialty += 1;
      }
     if( level == 9 )
       	ch->reflexes += 1;
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->armor += 1;
      }
     if( level == 11 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->specialty += 1;
	ch->reputation += 1;
      }
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->armor += 1;
      }
     if( level == 13 )
	ch->willpower += 1;
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->specialty += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 17 )
      {
	ch->specialty += 1;
	ch->armor += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
      }
     if( level == 19 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->specialty += 1;
	ch->reputation += 1;
      }
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == FORCE_ADEPT_ABILITY )
    {
     ch->class_level[FORCE_ADEPT_ABILITY] += 1;
     level = ch->class_level[FORCE_ADEPT_ABILITY];
     if( level == 1 )
        gain = 8;
     else
        gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->armor += 3;
	ch->unused_feats += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->talisman += 2;
      }
     if( level == 9 )
      {
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 11 )
      {
	ch->hitroll += 1;
	ch->secret += 1;
      }
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->skillpoints += 5;
      }
     if( level == 13 )
      {
	ch->force_weapon += 1;
	ch->reputation += 1;
      }
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->talisman += 2;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->secret += 1;
      }
     if( level == 17 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 19 )
	ch->hitroll += 1;
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == JEDICONSULAR_ABILITY )
    {
     ch->class_level[JEDICONSULAR_ABILITY] += 1;
     level = ch->class_level[JEDICONSULAR_ABILITY];
     if( level == 1 )
        gain = 8;
     else
        gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_LIGHTSABER);
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats, FORCE_SENSITIVE);
	ch->fortitude += 2;
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->unused_feats += 1;
	ch->deflect_defense += 1;
	ch->armor += 3;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
	ch->deflect_attack += 4;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->unused_feats += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
	ch->skillpoints += 5;
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;	
	ch->willpower += 1;
	ch->deflect_defense += 1;
	ch->armor += 1;
      }
     if( level == 11 )
      {
	ch->hitroll += 1;
	ch->unused_feats += 1;
      }
     if( level == 12 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 13 )
     	ch->deflect_attack -= 1;
     if( level == 14 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 15 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->deflect_defense += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 17 )
      {
	ch->reflexes += 1;
	ch->deflect_attack -= 1;
	ch->armor += 1;
      }
     if( level == 18 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
      }
     if( level == 19 )
      {
	ch->hitroll += 1;
	ch->skillpoints += 5;
      }
     if( level == 20 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == JEDIGUARDIAN_ABILITY )
    {
     ch->class_level[JEDIGUARDIAN_ABILITY] += 1;
     level = ch->class_level[JEDIGUARDIAN_ABILITY];
     if( level == 1 )
        gain = 10;
     else
        gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
        skill *= 4;
     ch->skillpoints += skill;
     ch->hitroll += 1;
     if( level == 1 )
      {
	SET_BIT(ch->feats2, WEAP_PROF_LIGHTSABER);
	SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	SET_BIT(ch->feats, FORCE_SENSITIVE);
	ch->fortitude += 2;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->deflect_defense += 1;
	ch->unused_feats += 1;
	ch->armor += 3;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 3 )
      {
	ch->unused_feats += 1;
	ch->deflect_attack += 4;
	ch->armor += 1;
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 5 )
      {
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
      }
     if( level == 7 )
      {
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 9 )
      {
	ch->deflect_defense += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
      }
     if( level == 11 )
      {
	ch->deflect_attack -= 1;
	ch->armor += 1;
      }
     if( level == 12 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 13 )
      {
	ch->deflect_defense += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 14 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
      }
     if( level == 15 )
      {
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
      }
     if( level == 16 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->deflect_attack -= 1;
      }
     if( level == 17 )
      {
	ch->willpower += 1;
	ch->deflect_defense += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 18 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 19 )
      {
	ch->deflect_attack -= 1;
	ch->armor += 1;
      }
     if( level == 20 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
      }
     return;
    }
  if( ability == BOUNTYHUNTER_ABILITY )
   {
     ch->class_level[BOUNTYHUNTER_ABILITY] += 1;
     level = ch->class_level[BOUNTYHUNTER_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->skillpoints += skill;
     ch->hitroll += 1;
     if( level == 1 )
      {
        if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->target += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->sneak_attack += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
	ch->target += 1;
     if( level == 4 )
      {
	ch->sneak_attack += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->target += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
	ch->sneak_attack += 1;
     if( level == 7 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->target += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->sneak_attack += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
     	ch->target += 1;
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->sneak_attack += 1;
	ch->armor += 1;
	ch->willpower += 1;
      }
     return;
    }
   if( ability == CRIMELORD_ABILITY )
    {
     ch->class_level[CRIMELORD_ABILITY] += 1;
     level = ch->class_level[CRIMELORD_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->skillpoints += skill;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->fortitude += 1;
	ch->inspire_fear += 2;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->inspire_fear += 2;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
      {
	ch->fortitude += 1;
	ch->inspire_fear += 2;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( level == DEVOTEE_ABILITY )
    {
     ch->class_level[DEVOTEE_ABILITY] += 1;
     level = ch->class_level[DEVOTEE_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 && level != 9 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->unused_feats += 1;
	ch->skillpoints += 5;
	ch->armor += 2;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->talisman += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
	ch->unused_feats += 1;
     if( level == 4 )
      {
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->willpower += 1;
	ch->force_weapon += 1;
      }
     if( level == 7 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     if( level == 8 )
      {
	ch->willpower += 1;
	ch->talisman += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
      	ch->force_weapon += 1;
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
      }
     return;
    }
   if( ability == MARAUDER_ABILITY )
    {
     ch->class_level[MARAUDER_ABILITY] += 1;
     level = ch->class_level[MARAUDER_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	if( !HAS_FEAT2(ch, WEAP_PROF_PRIMITIVE) )
	 SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	ch->fortitude += 2;
	ch->reflexes += 2;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
        ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 5 )
      {
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 7 )
      {
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 9 )
      {
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == TROOPER_ABILITY )
    {
     ch->class_level[TROOPER_ABILITY] += 1;
     level = ch->class_level[TROOPER_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, ARMOR_LIGHT) )
	 SET_BIT(ch->feats2, ARMOR_LIGHT);
	if( !HAS_FEAT2(ch, ARMOR_MEDIUM) )
	 SET_BIT(ch->feats2, ARMOR_MEDIUM);
	if( !HAS_FEAT2(ch, ARMOR_HEAVY) )
	 SET_BIT(ch->feats2, ARMOR_HEAVY);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	if( !HAS_FEAT2(ch, WEAP_PROF_HEAVY) )
	 SET_BIT(ch->feats2, WEAP_PROF_HEAVY);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 2;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
       }
      if( level == 2 )
       {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
       }
      if( level == 3 )
       if( !HAS_FEAT2(ch, UNCANNY_DODGE) )
	SET_BIT(ch->feats2, UNCANNY_DODGE);
      if( level == 4 )
       {
	ch->fortitude += 1;
	ch->reputation += 1;
       }
      if( level == 5 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
       }
      if( level == 6 )
        ch->fortitude += 1;
      if( level == 7 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
       }
      if( level == 8 )
       {
	ch->fortitude += 1;
	ch->reputation += 1;
       }
      if( level == 10 )
       {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
       }
      return;
     }
    if( ability == JEDIACE_ABILITY )
     {
     ch->class_level[JEDIACE_ABILITY] += 1;
     level = ch->class_level[JEDIACE_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
      {
	if(!HAS_FEAT(ch, FIGHTER_OPS) )
	 SET_BIT(ch->feats, FIGHTER_OPS);
	ch->fortitude += 1;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->familiarity += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->familiarity += 1;
      }
     return;
    }
   if( ability == INVESTIGATOR_ABILITY )
    {
     ch->class_level[INVESTIGATOR_ABILITY] += 1;
     level = ch->class_level[INVESTIGATOR_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->target += 1;
	ch->deflect_defense += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->hitroll += 1;
	ch->target += 1;
      }
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->deflect_attack -= 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->target += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == JEDIMASTER_ABILITY )
    {
     ch->class_level[JEDIMASTER_ABILITY] += 1;
     level = ch->class_level[JEDIMASTER_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
	ch->secret += 1;
       }
      if( level == 2 )
       {
	ch->fortitude += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
       }
      if( level == 3 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->secret += 1;
	ch->reputation += 1;
       }
      if( level == 4 )
       {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
       }
      if( level == 5 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->deflect_defense += 1;
	ch->reputation += 1;
       }
      if( level == 6 )
       {
	ch->fortitude += 1;
	ch->secret += 1;
	ch->armor += 1;
       }
      if( level == 7 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->reputation += 1;
       }
      if( level == 8 )
       {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
       }
      if( level == 9 )
       {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->force_weapon += 1;
	ch->reputation += 1;
       }
      if( level == 10 )
       {
	ch->fortitude += 1;
	ch->deflect_attack -= 1;
	ch->armor += 1;
       }
      return;
     }
    if( ability == STARSHIPACE_ABILITY )
     {
     ch->class_level[STARSHIPACE_ABILITY] += 1;
     level = ch->class_level[STARSHIPACE_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     if( level == 1 )
      {
 	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->familiarity += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
	ch->hitroll += 1;
     if( level == 4 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->familiarity += 1;
	ch->armor += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->familiarity += 1;
	ch->armor += 1;
      }
     if( level == 7 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
      }
     if( level == 8 )
      {
	ch->hitroll += 1;
	ch->reflexes += 1;
	ch->familiarity += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->hitroll += 1;
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->familiarity += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == ENGINEER_ABILITY )
    {
     ch->class_level[ENGINEER_ABILITY] += 1;
     level = ch->class_level[ENGINEER_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 && level != 9 )
 	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->efficiency += 1;
      }
     if( level == 3 )
      {
	ch->fortitude += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->efficiency += 2;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->reputation += 1;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 9 )
      {
	ch->fortitude += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->reflexes += 1;	
	ch->willpower += 1;
	ch->efficiency += 2;
      }
     return;
    }
   if( ability == INFILTRATOR_ABILITY )
    {
     ch->class_level[INFILTRATOR_ABILITY] += 1;
     level = ch->class_level[INFILTRATOR_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 && level != 9 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 1;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->armor += 1;
	SET_BIT(ch->feats3, COVERT_MOVEMENT);
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
	ch->armor += 1;
      }
     if( level == 3 )
      {
	ch->sneak_attack += 1;
	ch->reputation += 1;
      }
     if( level == 4 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	SET_BIT(ch->feats3, AMBUSH_FEAT);
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->reflexes += 1;
	ch->sneak_attack += 1;
	ch->reputation += 1;
      }
     if( level == 7 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->skillpoints += 5;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 9 )
      {
	ch->sneak_attack += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	SET_BIT(ch->feats3, UNCANNY_HIDE);
	ch->armor += 1;
      }
     return;
    }
   if( ability == PROTECTOR_ABILITY )
    {
     ch->class_level[PROTECTOR_ABILITY] += 1;
     level = ch->class_level[PROTECTOR_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 && level != 9 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->skill_level[DISGUISE_SKILL] += 5;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	SET_BIT(ch->feats3, HARMS_WAY);
      }
     if( level == 3 )
	ch->reputation += 1;
     if( level == 4 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->reflexes += 1;
	ch->reputation += 1;
      }
     if( level == 7 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 8 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
      }
     if( level == 9 )
	ch->reputation += 1;
     if( level == 10 )
      {
	ch->fortitude += 1;	
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     return;
    }
   if( ability == MARTIALARTS_ABILITY )
    {
     ch->class_level[MARTIALARTS_ABILITY] += 1;
     level = ch->class_level[MARTIALARTS_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PRIMITIVE) )
	 SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	if( !HAS_FEAT2(ch, UNCANNY_DODGE) )
	 SET_BIT(ch->feats2, UNCANNY_DODGE);
	ch->fortitude += 1;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 3 )
	ch->unused_feats += 1;
     if( level == 4 )
      {
	ch->reflexes += 1;
        SET_BIT(ch->feats3, HALF_BLASTER);
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->reflexes += 1;
	ch->unused_feats += 1;
      }
     if( level == 7 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	SET_BIT(ch->feats3, FULL_BLASTER);
      }
     if( level == 9 )
	ch->unused_feats += 1;
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
        SET_BIT(ch->feats3, GRAND_MASTER);
      }
     return;
    }
   if( ability == SLICER_ABILITY )
    {
     ch->class_level[SLICER_ABILITY] += 1;
     level = ch->class_level[SLICER_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 3 && level != 5 && level != 7 && level != 9 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 2 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
      }
     if( level == 3 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->skillpoints += 5;
	ch->reputation += 1;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
      }
     if( level == 9 )
      {
	ch->fortitude += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->reflexes += 1;
	ch->skillpoints += 5;
      }
     return;
    }
   if( ability == WITCH_ABILITY )
    {
     ch->class_level[WITCH_ABILITY] += 1;
     level = ch->class_level[WITCH_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 && level != 9 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_PRIMITIVE) )
	 SET_BIT(ch->feats2, WEAP_PROF_PRIMITIVE);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->inspire_fear += 1;
	ch->armor += 2;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
	SET_BIT(ch->force_feats, SPIDER_WALK);
      }
     if( level == 3 )
      if( !HAS_FFEAT(ch, CONTROL_FEAT) )
	SET_BIT(ch->force_feats, CONTROL_FEAT);
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reputation += 1;
	if( !HAS_FFEAT(ch, SUMMON_STORM) )
	 SET_BIT(ch->force_feats, SUMMON_STORM);
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->inspire_fear += 1;
	ch->armor += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;	
	ch->reputation += 1;
	if( !HAS_FFEAT(ch, ENSHROUD_FEAT) )
	 SET_BIT(ch->force_feats, ENSHROUD_FEAT);
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
        if( !HAS_FFEAT(ch, FORCE_FLIGHT) )
	 SET_BIT(ch->force_feats, FORCE_FLIGHT);
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
	ch->inspire_fear += 1;
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;	
	ch->reputation += 1;
      }
     return;
    }
   if( ability == ACOLYTE_ABILITY )
    {
     ch->class_level[ACOLYTE_ABILITY] += 1;
     level = ch->class_level[ACOLYTE_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 4 && level != 7 && level != 10 )
     	ch->hitroll += 1;
     if( level == 1 )
      {
	ch->fortitude += 2;
	ch->reflexes += 1;
	ch->willpower += 2;
	if( !HAS_FFEAT(ch, SITH_SORCERY) )
	 SET_BIT(ch->force_feats, SITH_SORCERY);
	if( !HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) )
	 SET_BIT(ch->feats2, WEAP_PROF_LIGHTSABER);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	ch->armor += 2;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->willpower += 1;
	if( !HAS_FFEAT(ch, CONTROL_FEAT) )
	 SET_BIT(ch->force_feats, CONTROL_FEAT);
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->force_weapon += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 7 )
	ch->reflexes += 1;
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
      }
     if( level == 9 )
      {
	ch->willpower += 1;
	ch->reputation += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == SITHLORD_ABILITY )
    {
     ch->class_level[SITHLORD_ABILITY] += 1;
     level = ch->class_level[SITHLORD_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 2;
	ch->reflexes += 2;
	ch->willpower += 2;
	ch->armor += 2;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->force_weapon += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->unused_feats += 1;
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->secret += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
  	ch->force_weapon += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->secret += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == SITHWARRIOR_ABILITY )
    {
     ch->class_level[SITHWARRIOR_ABILITY] += 1;
     level = ch->class_level[SITHWARRIOR_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 2;
	ch->reflexes += 2;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->reflexes += 1;
	ch->enemy_bonus += 1;
	ch->force_weapon += 1;
	ch->armor += 1;
	if( !HAS_FFEAT(ch, SENSE_FEAT) )
	 SET_BIT(ch->force_feats, SENSE_FEAT);
      }
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
	if( !HAS_FEAT2(ch, UNCANNY_DODGE) )
	 SET_BIT(ch->feats2, UNCANNY_DODGE);
      }
     if( level == 6 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->enemy_bonus += 1;
	ch->force_weapon += 1;
      }
     if( level == 7 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 8 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 9 )
      {
	ch->reflexes += 1;
	ch->enemy_bonus += 1;
	ch->armor += 1;
      }
     if( level == 10 )
      {
	ch->fortitude += 1;
	ch->unused_feats += 1;
	ch->force_weapon += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == ANTARIAN_ABILITY )
    {
     ch->class_level[ANTARIAN_ABILITY] += 1;
     level = ch->class_level[ANTARIAN_ABILITY];
     gain = number_range(1, 8);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, ARMOR_LIGHT) )
	 SET_BIT(ch->feats2, ARMOR_LIGHT);
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_RIFLES) )
	 SET_BIT(ch->feats2, WEAP_PROF_RIFLES);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 2;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	if( !HAS_FEAT3(ch, TEAMWORK_FEAT) )
	 SET_BIT(ch->feats3, TEAMWORK_FEAT);
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
      }
     if( level == 3 )
	ch->reputation += 1;
     if( level == 4 )
      {
	ch->fortitude += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == ENFORCER_ABILITY )
    {
     ch->class_level[ENFORCER_ABILITY] += 1;
     level = ch->class_level[ENFORCER_ABILITY];
     gain = number_range(1, 10);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (4 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 )
  	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->inspire_fear += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->willpower += 1;
	ch->unused_feats += 1;
      }
     if( level == 4 )
      {
	ch->inspire_fear += 2;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->unused_feats += 1;
	ch->armor += 1;	
	ch->reputation += 1;
      }
     return;
    }
   if( ability == VIGO_ABILITY )
    {
     ch->class_level[VIGO_ABILITY] += 1;
     level = ch->class_level[VIGO_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 )
    	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->inspire_fear += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 4 )
      {
	ch->inspire_fear += 2;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->fortitude += 1;
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == BROKER_ABILITY )
    {
     ch->class_level[BROKER_ABILITY] += 1;
     level = ch->class_level[BROKER_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 3 && level != 5 )
 	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	if( !HAS_FEAT2(ch, WEAP_PROF_VIBRO) )
	 SET_BIT(ch->feats2, WEAP_PROF_VIBRO);
	ch->reflexes += 1;
	ch->willpower += 2;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->reflexes += 1;
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
      {
	ch->fortitude += 1;
	if( !HAS_FEAT3(ch, PATRON_FEAT) )
	 SET_BIT(ch->feats3, PATRON_FEAT);
      }
     if( level == 4 )
      {
	ch->willpower += 1;
	ch->unused_feats += 1;
	ch->reputation += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
   if( ability == NOBLELORD_ABILITY )
    {
     ch->class_level[NOBLELORD_ABILITY] += 1;
     level = ch->class_level[NOBLELORD_ABILITY];
     gain = number_range(1, 6);
     gain += stat_table[get_curr_con(ch)].mod;
     if( gain < 1 )
        gain = 1;
     ch->hit += gain;
     ch->max_hit += gain;
     skill = (6 + stat_table[get_curr_int(ch)].mod);
     if( level != 1 && level != 5 )
	ch->hitroll += 1;
     if( level == 1 )
      {
	if( !HAS_FEAT2(ch, WEAP_PROF_PISTOLS) )
	 SET_BIT(ch->feats2, WEAP_PROF_PISTOLS);
	if( !HAS_FEAT2(ch, WEAP_PROF_SIMPLE) )
	 SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
	ch->reflexes += 1;
	ch->willpower += 2;	
	ch->armor += 1;	
	ch->reputation += 1;
      }
     if( level == 2 )
      {
	ch->fortitude += 1;
	ch->willpower += 1;
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     if( level == 3 )
	ch->reputation += 1;
     if( level == 4 )
      {
	ch->fortitude += 1;   
	ch->willpower += 1;
      }
     if( level == 5 )
      {
	ch->reflexes += 1;
	ch->armor += 1;
	ch->reputation += 1;
      }
     return;
    }
  return;
}

void do_stance( CHAR_DATA *ch, char *argument )
{
 char arg[MAX_INPUT_LENGTH];
 int iStance, stance;
 
 argument = one_argument(argument, arg);

 if( arg[0] == '\0' )
  {
   send_to_char( "\n\r", ch );
   send_to_char( "&bStances:&w\n\r", ch );
   if( !HAS_STANCE(ch, ECHANI_BASIC) )
	send_to_char( "&wEchani, ", ch );
   else if( HAS_STANCE(ch, ECHANI_MASTERY) )
	send_to_char( "&rEchani&w, ", ch );
   else if( HAS_STANCE(ch, ECHANI_EXPERTISE) )
	send_to_char( "&YEchani&w, ", ch );
   else if( HAS_STANCE(ch, ECHANI_BASIC) )
	send_to_char( "&gEchani&w, ", ch );
   if( !HAS_STANCE(ch, KTARA_BASIC) )
	send_to_char( "&wK'tara, ", ch );
   else if( HAS_STANCE(ch, KTARA_MASTERY) )
	send_to_char( "&rK'tara&w, ", ch );
   else if( HAS_STANCE(ch, KTARA_EXPERTISE) )
	send_to_char( "&YK'tara&w, ", ch );
   else if( HAS_STANCE(ch, KTARA_BASIC) )
	send_to_char( "&gK'tara&w, ", ch );
   if( !HAS_STANCE(ch, KTHRI_BASIC) )
	send_to_char( "&wK'thri, ", ch );
   else if( HAS_STANCE(ch, KTHRI_MASTERY) )
	send_to_char( "&rK'thri&w, ", ch );
   else if( HAS_STANCE(ch, KTHRI_EXPERTISE) )
	send_to_char( "&YK'thri&w, ", ch );
   else if( HAS_STANCE(ch, KTHRI_BASIC) )
	send_to_char( "&gK'thri&w, ", ch );
   if( !HAS_STANCE(ch, STAVA_BASIC) )
	send_to_char( "&wStava, ", ch );
   else if( HAS_STANCE(ch, STAVA_MASTERY) )
	send_to_char( "&rStava&w, ", ch );
   else if( HAS_STANCE(ch, STAVA_EXPERTISE) )
	send_to_char( "&YStava&w, ", ch );
   else if( HAS_STANCE(ch, STAVA_BASIC) )
	send_to_char( "&wStava&w, ", ch );
   if( !HAS_STANCE(ch, WRRUUSHI_BASIC) )
	send_to_char( "&wWrruushi\n\r", ch );
   else if( HAS_STANCE(ch, WRRUUSHI_MASTERY) )
	send_to_char( "&rWrruushi&w\n\r", ch );
   else if( HAS_STANCE(ch, WRRUUSHI_EXPERTISE) )
	send_to_char( "&YWrruushi&w\n\r", ch );
   else if( HAS_STANCE(ch, WRRUUSHI_BASIC) )
	send_to_char( "&gWrruushi&w\n\r", ch );
   if( IS_IMMORTAL(ch) || HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) )
    {
     send_to_char( "\n\r", ch );
     send_to_char( "&bLightsaber Stances:&w\n\r", ch );
     if( !HAS_STANCE( ch, FORM1_MASTERY ) )
	send_to_char( "&wForm One, ", ch );
     else
	send_to_char( "&gForm One&w, ", ch );
     if( !HAS_STANCE( ch, FORM2_MASTERY ) )
	send_to_char( "&wForm Two, ", ch );
     else
	send_to_char( "&gForm Two&w, ", ch );
     if( !HAS_STANCE( ch, FORM3_MASTERY ) )
	send_to_char( "&wForm Three, ", ch );
     else
	send_to_char( "&gForm Three&w, ", ch );
     if( !HAS_STANCE( ch, FORM4_MASTERY ) )
  	send_to_char( "&wForm Four, ", ch );
     else
	send_to_char( "&gForm Four&w, ", ch );
     if( !HAS_STANCE( ch, FORM5_MASTERY ) )
	send_to_char( "&wForm Five, ", ch );
     else
	send_to_char( "&gForm Five&w, ", ch );
     if( !HAS_STANCE( ch, FORM6_MASTERY ) )
   	send_to_char( "&wForm Six, ", ch );
     else
	send_to_char( "&gForm Six&w, ", ch );
     if( !HAS_STANCE( ch, FORM7_MASTERY ) )
	send_to_char( "&wForm Seven\n\r", ch );
     else
	send_to_char( "&gForm Seven&w\n\r", ch );
    }
    send_to_char( "\n\r", ch );
    if( ch->stance == STANCE_NONE )
     {
	send_to_char( "&wYou are currently not in a stance.\n\r", ch );
	return;
     }
    ch_printf( ch, "&wYou are currently utilizing the &g%s&w stance.\n\r", stance_name[ch->stance] );   
    return;
  }
 if( !str_cmp( arg, "learn" ) )
  {
   if( argument[0] == '\0' )
    {
	send_to_char( "&wLearn which stance?\n\r", ch );
	return;
    }
   if( ch->unused_feats < 1 )
    {
	send_to_char( "&wLearning stances requires free feat points, which you do not have.\n\r", ch );
	return;
    }
   stance = -1;
   for( iStance = 0; iStance < MAX_STANCE; iStance++ )
    {
     if ( !str_prefix( argument , stance_name[iStance] ) )
     {
       stance = iStance;
       break;
     }
    }
   if( stance == -1 || stance == STANCE_NONE )
    {
	send_to_char( "&wThat is not a stance, which do you want to learn?\n\r", ch );
	return;
    }
   if( stance == ECHANI_STANCE )
    {
     if( HAS_STANCE( ch, ECHANI_MASTERY ) )
      {
	send_to_char( "&wYou are already a &rMaster&w of the &bEchani&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE( ch, ECHANI_MASTERY ) && HAS_STANCE( ch, ECHANI_EXPERTISE ) )
      {
	SET_BIT(ch->has_stance, ECHANI_MASTERY);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become a &rMaster&w of the &bEchani&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE( ch, ECHANI_EXPERTISE ) && HAS_STANCE( ch, ECHANI_BASIC ) )
      {
	SET_BIT(ch->has_stance, ECHANI_EXPERTISE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rExpert&w of the &bEchani&w stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, ECHANI_BASIC);
     ch->unused_feats -= 1;
     send_to_char( "&wYou have now become an &rApprentice&w of the &bEchani&w stance.\n\r", ch );
     return;
    }
   if( stance == KTARA_STANCE )
    {
     if( HAS_STANCE(ch, KTARA_MASTERY) )
      {
	send_to_char( "&wYou are already a &rMaster&w of the &bK'tara&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTARA_BASIC) )
      {
	ch->unused_feats -= 1;
	SET_BIT(ch->has_stance, KTARA_BASIC);
	send_to_char( "&wYou have now become an &rApprentice&w in the &bK'tara&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTARA_EXPERTISE) )
      {
	SET_BIT(ch->has_stance, KTARA_EXPERTISE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rExpert&w in the &bK'tara&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTARA_MASTERY) )
      {
	SET_BIT(ch->has_stance, KTARA_MASTERY);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rMaster&w in the &bK'tara&w stance.\n\r", ch );
	return;
      }
    }
   if( stance == KTHRI_STANCE )
    {
     if( HAS_STANCE(ch, KTHRI_MASTERY) )
      {
	send_to_char( "&wYou are already a &rMaster&w in the &bK'thri&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTHRI_BASIC) )
      {
	ch->unused_feats -= 1;
	SET_BIT(ch->has_stance, KTHRI_BASIC);
	send_to_char( "&wYou have now become an &rApprentice&w in the &bK'thri&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTHRI_EXPERTISE) )
      {
	SET_BIT(ch->has_stance, KTHRI_EXPERTISE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rExpert&w in the &bK'thri&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, KTHRI_MASTERY) )
      {
	SET_BIT(ch->has_stance, KTHRI_MASTERY);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become a &rMaster&w in the &bK'thri&w stance.\n\r", ch );
	return;
      }
    }
   if( stance == STAVA_STANCE )
    {
     if( HAS_STANCE(ch, STAVA_MASTERY) )
      {
	send_to_char( "&wYou are already a &rMaster&w in the &bStava&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, STAVA_BASIC) )
      {
	ch->unused_feats -= 1;
	SET_BIT(ch->has_stance, STAVA_BASIC);
	send_to_char( "&wYou have now become an &rApprentice&w in the &bStava&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, STAVA_EXPERTISE) )
      {
	SET_BIT(ch->has_stance, STAVA_EXPERTISE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rExpert&w in the &bStavaw stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, STAVA_MASTERY) )
      {
	SET_BIT(ch->has_stance, STAVA_MASTERY);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become a &rMaster&w in the &bStava&w stance.\n\r", ch );
	return;
      }
    }
   if( stance == WRRUUSHI_STANCE )
    {
     if( ch->race != RACE_WOOKIEE )
      {
	send_to_char( "&wOnly &YWookiees&w can learn the &bWrruushi&w fighting stance.\n\r", ch );
	return;
      }
     if( HAS_STANCE(ch, WRRUUSHI_MASTERY) )
      {
	send_to_char( "&wYou are already a &rMaster&w in the &bWrruushi&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, WRRUUSHI_BASIC) )
      {
	ch->unused_feats -= 1;
	SET_BIT(ch->has_stance, WRRUUSHI_BASIC);
	send_to_char( "&wYou have now become an &rApprentice&w in the &bWrruushi&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, WRRUUSHI_EXPERTISE) )
      {
	SET_BIT(ch->has_stance, WRRUUSHI_EXPERTISE);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become an &rExpert&w in the &bWrruushi&w stance.\n\r", ch );
	return;
      }
     if( !HAS_STANCE(ch, WRRUUSHI_MASTERY) )
      {
	SET_BIT(ch->has_stance, WRRUUSHI_MASTERY);
	ch->unused_feats -= 1;
	send_to_char( "&wYou have now become a &rMaster&w in the &bWrruushi&w stance.\n\r", ch );
	return;
      }
    }
   if( !HAS_FEAT2(ch, WEAP_PROF_LIGHTSABER) && ( stance == FORM1_STANCE || stance == FORM2_STANCE || stance == FORM3_STANCE
 	|| stance == FORM4_STANCE || stance == FORM5_STANCE || stance == FORM6_STANCE || stance == FORM7_STANCE ) )
    {
	send_to_char( "&wOnly those proficient with Lightsabers may take Form stances.\n\r", ch );
	return;
    }
   if( stance == FORM1_STANCE )
    {
     if( HAS_STANCE(ch, FORM1_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, CONTROL_FEAT) || !HAS_FFEAT(ch, ATTUNED_FEAT) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM1_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form One&w.\n\r", ch );
     return;
    }
   if( stance == FORM2_STANCE )
    {
     if( HAS_STANCE(ch, FORM2_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, CONTROL_FEAT) || get_curr_dex(ch) < 15 || ch->top_level < 11 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM2_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Two&w.\n\r", ch );
     return;
    }
   if( stance == FORM3_STANCE )
    {
     if( HAS_STANCE(ch, FORM3_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, CONTROL_FEAT) || !HAS_FFEAT(ch, LIGHTSABER_DEFENSE) || !HAS_FEAT(ch, DODGE_FEAT) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM3_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Three&w.\n\r", ch );
     return;
    }
   if( stance == FORM4_STANCE )
    {
     if( HAS_STANCE(ch, FORM4_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, CONTROL_FEAT) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM4_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Four&w.\n\r", ch );
     return;
    }
   if( stance == FORM5_STANCE )
    {
     if( HAS_STANCE(ch, FORM5_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, CONTROL_FEAT) || !HAS_FFEAT(ch, LIGHTSABER_DEFENSE) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM5_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Five&w.\n\r", ch );
     return;
    }
   if( stance == FORM6_STANCE )
    {
     if( HAS_STANCE(ch, FORM6_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( !HAS_FFEAT(ch, SENSE_FEAT) || !HAS_FFEAT(ch, LINK_FEAT) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM6_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Six&w.\n\r", ch );
     return;
    }
   if( stance == FORM7_STANCE )
    {
     if( HAS_STANCE(ch, FORM7_STANCE) )
      {
	send_to_char( "&wYou already possess this stance.\n\r", ch );
	return;
      }
     if( get_curr_dex(ch) < 13 || !HAS_FEAT(ch, DODGE_FEAT) || !HAS_FEAT2(ch, IMP_CRITICAL_LIGHTSABER) || ch->top_level < 7 )
      {
	send_to_char( "&wYou lack one of the requirements for this stance.\n\r", ch );
	return;
      }
     SET_BIT(ch->has_stance, FORM7_STANCE);
     ch->unused_feats -= 1;
     send_to_char( "&wYou are now a &rMaster&w with &bLightsaber Form Seven&w.\n\r", ch );
     return;
    }
  }
 stance = -1;
 for( iStance = 0; iStance < MAX_STANCE; iStance++ )
  {
   if ( !str_prefix( arg , stance_name[iStance] ) )
    {
       stance = iStance;
       break;
    }
  }
 if( stance == -1 )
  {
	send_to_char( "&wThat is not a stance, which do you want to utilize?\n\r", ch );
	return;
  }
 if( stance == ECHANI_STANCE )
  if( !HAS_STANCE(ch, ECHANI_BASIC) )
   {
	send_to_char( "&wYou don't know that stance.\n\r", ch );
	return;
   }
 if( stance == KTARA_STANCE )
  if( !HAS_STANCE(ch, KTARA_STANCE) )
   {
	send_to_char( "&wYou don't know that stance.\n\r", ch );
	return;
   }
 if( stance == STAVA_STANCE )
  if( !HAS_STANCE(ch, STAVA_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == WRRUUSHI_STANCE )
  if( !HAS_STANCE(ch, WRRUUSHI_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM1_STANCE )
  if( !HAS_STANCE(ch, FORM1_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM2_STANCE )
  if( !HAS_STANCE(ch, FORM2_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM3_STANCE )
  if( !HAS_STANCE(ch, FORM3_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM4_STANCE )
  if( !HAS_STANCE(ch, FORM4_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM5_STANCE )
  if( !HAS_STANCE(ch, FORM5_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM6_STANCE )
  if( !HAS_STANCE(ch, FORM6_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 if( stance == FORM7_STANCE )
  if( !HAS_STANCE(ch, FORM7_STANCE) )
   {
        send_to_char( "&wYou don't know that stance.\n\r", ch );
        return;
   }
 ch->stance = stance;
 ch_printf( ch, "&wYou adjust your body into the &b%s&w stance.\n\r", stance_name[ch->stance] );
 return;
}

void gain_darklevel( CHAR_DATA *ch )
{
  int diff, number, stat;

  if( IS_NPC(ch) )
	return;

  if( ch->darkpoints >= get_curr_wis(ch) )
   	diff = 10 + ch->darkpoints;
  else
	diff = 5 + ch->darkpoints;

  number = number_range(1, 20) + ch->fortitude + stat_table[get_curr_con(ch)].mod;

  if( number >= diff )
   {
	send_to_char( "&bYou manage to stave off the debilitating effects of the &rDark Side&b.&w\n\r", ch );
	return;
   }
  stat = number_range(1, 2);
  if( stat == 1 )
   {
	ch->perm_str -= 1;
	send_to_char( "&bThe &rDark Side&b of the Force takes its toll on you by draining your &rStrength&b.&w\n\r", ch );
	return;
   }
  else if( stat == 2 )
   {
	ch->perm_dex -= 1;
	send_to_char( "&bThe &rDark Side&b of the Force takes its toll on you by draining your &rDexterity&b.&w\n\r", ch );
	return;
   }
  else
   {
	ch->perm_con -= 1;
	send_to_char( "&bThe &rDark Side&b of the Force takes its toll on you by draining your &rConstitution&b.&w\n\r", ch );
	return;
   }
}

void gain_darkpoint( CHAR_DATA *ch )
{
  int diff, number;

  if( IS_NPC(ch) )
	return;

  ch->darkpoints += 1;
 
  if( IS_DARK(ch) )
   return;

  diff = 10 + ch->darkpoints;
  number = number_range(1, 20) + stat_table[get_curr_wis(ch)].mod;

  if( number >= diff )
   {
	send_to_char( "&bYou feel the &rDark Side&b of the Force begin to lure you.&w\n\r", ch );
	return;
   }

  ch->darkpoints = get_curr_wis(ch);
  send_to_char( "&bYou feel the &rDark Side&b of the Force take over within you.&w\n\r", ch );
  return;
}

void racial_bonus( CHAR_DATA *ch, int iRace )
{
  if( IS_NPC(ch) )
	return;

  if( iRace == RACE_ANOMID )
   {
	ch->skill_level[REPAIR_SKILL] += 2;
	ch->skill_level[CRAFT_DROID] += 2;
	ch->gold += 10000;
	ch->skill_level[DIPLOMACY_SKILL] += 4;
   }
  if( iRace == RACE_DROID )
   	SET_BIT(ch->feats, AMBIDEXTERITY_FEAT);
  if( iRace == RACE_ARKANIAN || iRace == RACE_RYN )
   {
	ch->reputation += 3;
   	SET_BIT(ch->feats, INFAMY_FEAT);
   }
  if( iRace == RACE_BARTOKK )
	ch->armor += 1;
  if( iRace == RACE_CHAGRIAN )
 	ch->skill_level[SWIM_SKILL] += 4;
  if( iRace == RACE_DEFEL )
   {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->skill_level[HIDE_SKILL] += 4;
   }
  if( iRace == RACE_HUMAN )
   {
	ch->unused_feats += 1;
	ch->skillpoints += 10;
   }
  if( iRace == RACE_HODIN )
   {
	ch->hitroll -= 1;
	ch->armor -= 1;
	ch->skill_level[HIDE_SKILL] -= 4;
	ch->skill_level[CLIMB_SKILL] += 2;
	ch->skill_level[SURVIVAL_SKILL] += 4;
   }
  if( iRace == RACE_HUTT )
   {
	ch->hitroll -= 1;
	ch->armor -= 1;
	ch->skill_level[HIDE_SKILL] -= 4;
	SET_BIT(ch->feats, INFAMY_FEAT);
	ch->reputation += 3;
   }
  if( iRace == RACE_IKTOTCHI )
   {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->skill_level[PILOT_SKILL] += 2;
	SET_BIT(ch->feats, FIGHTER_OPS);
   }
  if( iRace == RACE_JAWA )
   {
	ch->armor += 1;
	ch->hitroll += 1;
	ch->skill_level[HIDE_SKILL] += 4;
	ch->skill_level[SURVIVAL_SKILL] += 2;
   }
  if( iRace == RACE_KLATOOINIAN )
   	ch->willpower += 2;
  if( iRace == RACE_MIRALUKA )
   	SET_BIT(ch->feats, FORCE_SENSITIVE);
  if( iRace == RACE_MON_CALAMARI )
   {
	ch->skill_level[SWIM_SKILL] += 4;
	ch->skill_level[CRAFT_MEDPAC] += 4;
   }
  if( iRace == RACE_MUUN )
   {
	ch->skill_level[APPRAISE_SKILL] += 2;
	ch->skill_level[DIPLOMACY_SKILL] += 4;
   }
  if( iRace == RACE_NOGHRI )
   {
	ch->hitroll += 1;
	ch->armor += 1;
	ch->skill_level[HIDE_SKILL] += 4;
   }
  if( iRace == RACE_QUARREN )
	ch->skill_level[SWIM_SKILL] += 4;
  if( iRace == RACE_RODIAN )
   {
	ch->skill_level[LISTEN_SKILL] += 2;
	ch->skill_level[SPOT_SKILL] += 2;
	ch->skill_level[SEARCH_SKILL] += 2;
	SET_BIT(ch->feats2, TRACK_FEAT);
   }
  if( iRace == RACE_SKYTRI )
   	ch->willpower += 1;
  if( iRace == RACE_SULLUSTAN )
   {
	ch->skill_level[CLIMB_SKILL] += 2;
	ch->skill_level[LISTEN_SKILL] += 2;
   }
  if( iRace == RACE_TOGORIAN )
   {
	ch->hitroll -= 1;
	ch->armor -= 1;
	ch->skill_level[HIDE_SKILL] -= 4;
	SET_BIT(ch->feats2, WEAP_PROF_SIMPLE);
   }
  if( iRace == RACE_TOGRUTA )
 	ch->skill_level[HIDE_SKILL] += 2;
  if( iRace == RACE_TRANDOSHAN )
	ch->armor += 1;
  if( iRace == RACE_TWILEK )
	ch->fortitude += 1;
  if( iRace == RACE_UBESE )
   {
	ch->skill_level[SURVIVAL_SKILL] += 2;
	SET_BIT(ch->feats, GEARHEAD_FEAT);
	ch->skill_level[COMPUTER_SKILL] += 2;
	ch->skill_level[REPAIR_SKILL] += 2;
	SET_BIT(ch->feats2, ARMOR_LIGHT);
   }
  if( iRace == RACE_UMBARAN )
   {
	ch->reputation += 2;
	SET_BIT(ch->feats, INFLUENCE_FEAT);
   }
  if( iRace == RACE_VERPINE )
   {
	ch->armor += 2;
	ch->skill_level[SPOT_SKILL] += 2;
	ch->skill_level[SEARCH_SKILL] += 2;
	ch->skill_level[REPAIR_SKILL] += 2;
	ch->skill_level[COMPUTER_SKILL] += 2;
	SET_BIT(ch->feats, GEARHEAD_FEAT);
   }
  if( iRace == RACE_WOOKIEE )
   {
	ch->skill_level[CLIMB_SKILL] += 2;
	ch->skill_level[INTIMIDATE_SKILL] += 4;
   }
  if( iRace == RACE_WOOSTOID )
	ch->skill_level[COMPUTER_SKILL] += 2;
  return;
}

void do_dfeats( CHAR_DATA *ch, char *argument )
{
  if( IS_NPC(ch) )
 	return;
  if( !IS_IMMORTAL(ch) && !IS_DROID(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
    send_to_char("\n\r", ch );
    send_to_char( "&bAccessories:&w\n\r", ch );
    if( !HAS_DROID(ch, COMLINK_FEAT ) )
    	send_to_char( "&wComlink\n\r", ch );
    else
    	send_to_char( "&gComlink&w\n\r", ch );
    if( !HAS_DROID(ch, DIAGNOSTICS_PACKAGE) )
	send_to_char( "&wDiagnostics Package\n\r", ch );
    else
	send_to_char( "&gDiagnostics Package&w\n\r", ch );
    if( !HAS_DROID(ch, ELECTROSHOCK_PROBE) )
	send_to_char( "&wElectroshock Probe&w\n\r", ch );
    else
	send_to_char( "&gElectroshock Probe\n\r", ch );
    if( !HAS_DROID(ch, FLAMETHROWER_FEAT) )
	send_to_char( "&wFlamethrower&w\n\r", ch );
    else
	send_to_char( "&gFlamethrower\n\r", ch );
    if( !HAS_DROID(ch, INTERNAL_STORAGE) )
	send_to_char( "&wInternal Storage&w\n\r", ch );
    else
	send_to_char( "&gInternal Storage\n\r", ch );
    if( !HAS_DROID(ch, LOCKED_ACCESS) )
	send_to_char( "&wLocked Access&w\n\r", ch );
    else
	send_to_char( "&gLocked Access\n\r", ch );
    if( !HAS_DROID(ch, MAGNETIC_FEET ) )
  	send_to_char( "&wMagnetic Feet&w\n\r", ch );
    else
	send_to_char( "&gMagnetic Feet\n\r", ch );
    if( !HAS_DROID(ch, RUST_INHIBITOR) )
	send_to_char( "&wRust Inhibitor&w\n\r", ch );
    else
	send_to_char( "&gRust Inhibitor\n\r", ch );
    if( !HAS_DROID(ch, SELFDESTRUCT_SYSTEM) )
	send_to_char( "&wSelf-Destruct System&w\n\r", ch );
    else
	send_to_char( "&gSelf-Destruct System\n\r", ch );
    if( !HAS_DROID(ch, IMPROVED_SENSOR) )
	send_to_char( "&wImproved Sensor Package&w\n\r", ch );
    else
	send_to_char( "&gImproved Sensor Package\n\r", ch );
    if( !HAS_DROID(ch, INFRARED_VISION) )
	send_to_char( "&wInfrared Vision&w\n\r", ch );
    else
	send_to_char( "&gInfrared Vision\n\r", ch );
    if( !HAS_DROID(ch, MOTION_SENSORS) )
	send_to_char( "&wMotion Sensors&w\n\r", ch );
    else
	send_to_char( "&gMotion Sensors&w\n\r", ch );
    if( !HAS_DROID(ch, SONIC_SENSORS) )
	send_to_char( "&wSonic Sensors&w\n\r", ch );
    else
	send_to_char( "&gSonic Sensors\n\r", ch );
    if( !HAS_DROID(ch, DEGREE_VISION) )
	send_to_char( "&w360-Degree Vision&w\n\r", ch );
    else
	send_to_char( "&g360-Degree Vision\n\r", ch );
    if( !HAS_DROID(ch, SHIELD_GENERATOR) )
 	send_to_char( "&wShield Generator&w\n\r", ch );
    else
	send_to_char( "&gShield Generator\n\r", ch );
    if( !HAS_DROID(ch, VOCABULATOR_FEAT) )
	send_to_char( "&wVocabulator&w\n\r", ch );
    else
	send_to_char( "&gVocabulator\n\r", ch );
    send_to_char( "\n\r", ch );
    send_to_char( "&bMartial Arts Programming:&w\n\r", ch );
    if( !HAS_DROID(ch, MARTIAL_PROGRAMMING) )
	send_to_char( "&wMartial Programming&w, ", ch );
    else
	send_to_char( "&gMartial Programing, ", ch );
    if( !HAS_DROID(ch, IMP_MARTIAL_PROGRAMMING) )
	send_to_char( "&wImproved Martial&w, ", ch );
    else
	send_to_char( "&gImproved Martial, ", ch );
    if( !HAS_DROID(ch, ADV_MARTIAL_PROGRAMMING) )
	send_to_char( "&wAdvanced Martial&w\n\r", ch );
    else
	send_to_char( "&gAdvanced Martial\n\r", ch );
    send_to_char( "&bArmor Enhancements:&w\n\r", ch );
    if( !HAS_DROID(ch, ARMOR_LIGHT_DROID) )
	send_to_char( "&wLight Armor&w, ", ch );
    else
	send_to_char( "&gLight Armor, ", ch );
    if( !HAS_DROID(ch, ARMOR_MEDIUM_DROID) )
	send_to_char( "&wMedium Armor&w, ", ch );
    else
	send_to_char( "&gMedium Armor, ", ch );
    if( !HAS_DROID(ch, ARMOR_HEAVY_DROID) )
	send_to_char( "&wHeavy Armor&w\n\r", ch );
    else
	send_to_char( "&gHeavy Armor\n\r", ch );
    return;
  }

 if( !IS_SET(ch->in_room->room_flags2, ROOM_DROIDSHOP) )
  {
	send_to_char( "&wYou must be in a &bDroid Maitenance Facility&w inorder to do this.\n\r", ch );
	return;
  }

 if( !str_cmp(argument, "light armor") )
  {
	if( HAS_DROID(ch, ARMOR_LIGHT_DROID) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 5000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 5000;
	ch->damage_reduction += 3;
	SET_BIT(ch->droid_feat, ARMOR_LIGHT_DROID);
	send_to_char( "&wYou now possess a &gLight Armor&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "medium armor") )
  {
	if( HAS_DROID(ch, ARMOR_MEDIUM_DROID) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 15000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 15000;
	ch->damage_reduction += 2;
	SET_BIT(ch->droid_feat, ARMOR_MEDIUM_DROID);
	send_to_char( "&wYou now possess a &gMedium Armor&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "heavy armor") )
  {
	if( HAS_DROID(ch, ARMOR_HEAVY_DROID) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 50000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 50000;
	ch->damage_reduction += 2;
	SET_BIT(ch->droid_feat, ARMOR_HEAVY_DROID);
	send_to_char( "&wYou now possess a &gHeavy Armor&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "comlink") )
  {
	if( HAS_DROID(ch, COMLINK_FEAT) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 250 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 250;
	SET_BIT(ch->droid_feat, COMLINK_FEAT);
	send_to_char( "&wYou now possess a &gComlink&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "diagnostics") || !str_cmp(argument, "diagnostics package") )
  {
	if( HAS_DROID(ch, DIAGNOSTICS_PACKAGE) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 250 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 250;
	ch->skill_level[REPAIR_SKILL] += 4;
	SET_BIT(ch->droid_feat, DIAGNOSTICS_PACKAGE);
	send_to_char( "&wYou now possess a &gDiagnostics&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "electroshock") || !str_cmp(argument, "electroshock probe") )
  {
	if( HAS_DROID(ch, ELECTROSHOCK_PROBE) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 400 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 400;
	SET_BIT(ch->droid_feat, ELECTROSHOCK_PROBE);
	send_to_char( "&wYou now possess an &gElectroshock Probe&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "flamethrower") )
  {
	if( HAS_DROID(ch, FLAMETHROWER_FEAT) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 400 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 400;
	SET_BIT(ch->droid_feat, FLAMETHROWER_FEAT);
	send_to_char( "&wYou now possess a &gFlamethrower&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "internal storage") )
  {
	if( HAS_DROID(ch, INTERNAL_STORAGE) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 150000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 150000;
	SET_BIT(ch->droid_feat, INTERNAL_STORAGE);
	send_to_char( "&wYou now possess an &gInternal Storage&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "locked access") )
  {
	if( HAS_DROID(ch, LOCKED_ACCESS) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 50 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 50;
	SET_BIT(ch->droid_feat, LOCKED_ACCESS);
	send_to_char( "&wYou now possess a &gLocked Access&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "magnetic feet") )
  {
	if( HAS_DROID(ch, MAGNETIC_FEET) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 100 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 100;
	SET_BIT(ch->droid_feat, MAGNETIC_FEET);
	send_to_char( "&wYou now possess a &gMagnetic Feet&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "rust inhibitor") )
  {
	if( HAS_DROID(ch, RUST_INHIBITOR) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 250 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 250;
	SET_BIT(ch->droid_feat, RUST_INHIBITOR);
	send_to_char( "&wYou now possess prevention against &grust&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "improved sensor") || !str_cmp(argument, "improved sensor package") )
  {
	if( HAS_DROID(ch, IMPROVED_SENSOR) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 1000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 1000;
	SET_BIT(ch->droid_feat, IMPROVED_SENSOR);
	ch->skill_level[LISTEN_SKILL] += 2;
	ch->skill_level[SEARCH_SKILL] += 2;
	ch->skill_level[SPOT_SKILL] += 2;
	send_to_char( "&wYou now possess a &gSensor Improvement&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "infrared vision") )
  {
	if( HAS_DROID(ch, INFRARED_VISION) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 1000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 1000;
	SET_BIT(ch->droid_feat, INFRARED_VISION);
	send_to_char( "&wYou now possess an &gInfrared Vision&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "motion sensors") )
  {
	if( HAS_DROID(ch, MOTION_SENSORS) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 1000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 1000;
	ch->skill_level[SPOT_SKILL] += 2;
	SET_BIT(ch->droid_feat, MOTION_SENSORS);
	send_to_char( "&wYou now possess a &gMotion Sensors&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "sonic sensors") )
  {
	if( HAS_DROID(ch, SONIC_SENSORS) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 1000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 1000;
	ch->skill_level[LISTEN_SKILL] += 2;
	SET_BIT(ch->droid_feat, SONIC_SENSORS);
	send_to_char( "&wYou now possess a &gSonic Sensor&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "360-degree vision") || !str_cmp(argument, "360 degree vision") )
  {
	if( HAS_DROID(ch, DEGREE_VISION) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 1000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 1000;
	ch->skill_level[SPOT_SKILL] += 2;
	SET_BIT(ch->droid_feat, DEGREE_VISION);
	send_to_char( "&wYou now possess a &g360 Degree Vision&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "shield generator") )
  {
	if( HAS_DROID(ch, SHIELD_GENERATOR) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 250000 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 250000;
	ch->damage_reduction += 6;
	SET_BIT(ch->droid_feat, SHIELD_GENERATOR);
	send_to_char( "&wYou now possess a &gShield Generator&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "vocabulator") )
  {
	if( HAS_DROID(ch, VOCABULATOR_FEAT) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 250 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 250;
	SET_BIT(ch->droid_feat, VOCABULATOR_FEAT);
	send_to_char( "&wYou now possess a &gVocabulator&w upgrade.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "martial arts") || !str_cmp(argument, "martial arts programming") )
  {
	if( HAS_DROID(ch, MARTIAL_PROGRAMMING) )
	 {
		send_to_char( "&wYou already possess this programming.\n\r", ch );
		return;
	 }
	if( ch->gold < 2500 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 2500;
	SET_BIT(ch->droid_feat, MARTIAL_PROGRAMMING);
	send_to_char( "&wYou have now been programed for &gMartial Arts&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "defensive martial arts") || !str_cmp(argument, "defensive martial arts programming" ) )
  {
	if( HAS_DROID(ch, DEF_MARTIAL_PROGRAMMING) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 2500 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 2500;
	SET_BIT(ch->droid_feat, DEF_MARTIAL_PROGRAMMING);
	send_to_char( "&wYou have now been programed for &gDefensive Martial Arts&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "improved martial arts") || !str_cmp(argument, "improved martial arts programming" ) )
  {
	if( HAS_DROID(ch, IMP_MARTIAL_PROGRAMMING) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 2500 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 2500;
	SET_BIT(ch->droid_feat, IMP_MARTIAL_PROGRAMMING);
	send_to_char( "&wYou have now been programed for &gImproved Martial Arts&w.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "advanced martial arts") || !str_cmp(argument, "advanced martial arts programming" ) )
  {
	if( HAS_DROID(ch, ADV_MARTIAL_PROGRAMMING) )
	 {
		send_to_char( "&wYou already possess this enhancement.\n\r", ch );
		return;
	 }
	if( ch->gold < 2500 )
	 {
		send_to_char( "&wYou don't have enough credits.\n\r", ch );
		return;
	 }
	ch->gold -= 2500;
	SET_BIT(ch->droid_feat, ADV_MARTIAL_PROGRAMMING);
	send_to_char( "&wYou have now been programed for &gAdvanced Martial Arts&w.\n\r", ch );
	return;
  }
send_to_char( "&wPurchase which upgrade or programming?\n\r", ch );
return;
}

void do_specialty( CHAR_DATA *ch, char *argument )
{

 if( IS_NPC(ch) )
 	return;
 if( !IS_IMMORTAL(ch) && ch->class_level[TECH_SPEC_ABILITY] == 0 )
  {
	send_to_char( "&wHuh?\n\r", ch );
	return;
  }
 if( argument[0] == '\0' )
  {
	send_to_char( "\n\r", ch );
	send_to_char( "&gSpecialties:&w\n\r", ch );
	send_to_char( "&wComputer Specialist, Mastercraft, Mechanic, Medical Specialist", ch );
        if( !HAS_FEAT3(ch, TRANSPLANT_FEAT) )
	 send_to_char( ", Surgical Specialist\n\r", ch );
	else
	 send_to_char( "\n\r", ch );
	send_to_char( "\n\r", ch );
	ch_printf( ch, "&gCurrent Mastercraft Level: &w%d\n\r", ch->mastercraft );
	ch_printf( ch, "&gSpecialties Remaining:     &w%d\n\r", ch->specialty );
	return;
  }
 if( !str_cmp(argument, "computer specialist") )
  {
	ch->specialty -= 1;
	ch->skill_level[COMPUTER_SKILL] += 1;
	send_to_char( "&wYour knowledge of &gComputers&w increases.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "mastercraft" ) )
  {
	ch->specialty -= 1;
	ch->mastercraft += 1;
	send_to_char( "&wYour ability to &gCraft Items&w increases.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "mechanic" ) )
  {
	ch->specialty -= 1;
	ch->skill_level[REPAIR_SKILL] += 1;
	send_to_char( "&wYour ability to &gRepair&w objects increases.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "medical specialist") )
  {
	ch->specialty -= 1;
	ch->skill_level[TREAT_INJURY] += 1;
	send_to_char( "&wYour knowledge of &gmedicine&w increases.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "surgical specialist") && HAS_FEAT3(ch, TRANSPLANT_FEAT) )
  {
	send_to_char( "&wYou can only take this specialty once.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "surgical specialist") && !HAS_FEAT3(ch, TRANSPLANT_FEAT) )
  {
	ch->specialty -= 1;
	SET_BIT(ch->feats3, TRANSPLANT_FEAT);
	send_to_char( "&wAfter much studying, you feel confident in your &gSurgical&w abilities.\n\r", ch );
	return;
  }
 send_to_char( "&wWhich specialty were you interested in obtaining?\n\r", ch );
 return;
}

void do_secret( CHAR_DATA *ch, char *argument )
{

  if( IS_NPC(ch) )
 	return;
  if( !IS_IMMORTAL(ch) && ch->class_level[FORCE_ADEPT_ABILITY] == 0 && ch->class_level[JEDICONSULAR_ABILITY] == 0 && ch->class_level[JEDIGUARDIAN_ABILITY] == 0 )
   {
	send_to_char( "&wHuh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&gPlease choose from the following:&w\n\r", ch );
	send_to_char( "&wBattlemind       &g- &w+1 to Battlemind skill\n\r", ch );
	send_to_char( "&wForce Defense    &g- &w+1 to Force Defense skill\n\r", ch );
	send_to_char( "&wForce Strike     &g- &w+1 to Force Strike skill\n\r", ch );
	send_to_char( "&wHeal Other       &g- &w+1 to Heal Other skill\n\r", ch );
	send_to_char( "&wHeal Self        &g- &w+1 to Heal Self skill\n\r", ch );
      if( IS_IMMORTAL(ch) || ch->class_level[SITHLORD_ABILITY] >= 1 )
       {
	send_to_char( "&wAlchemy          &g- &w+1 to Alchemy skill\n\r", ch );
	send_to_char( "&wForce Lightning  &g- &w+1 to Force Lightning skill\n\r", ch );
	send_to_char( "&wForce Grip       &g- &w+1 to Force Grip skill\n\r", ch );
       if( IS_IMMORTAL(ch) || !HAS_FFEAT(ch, DRAIN_FORCE) )
	send_to_char( "&wDrain Force      &g- &wGain Drain Force feat\n\r", ch );
       if( IS_IMMORTAL(ch) || !HAS_FFEAT(ch, HATRED_FEAT) )
	send_to_char( "&wHatred           &g- &wGain Hatred feat\n\r", ch );
       }
        send_to_char( "\n\r", ch );
	ch_printf( ch, "&wYou have &g%d&w force secrets remaining.\n\r", ch->secret );
	return;
  }
 if( ch->secret < 1 )
  {
	send_to_char( "&wYou have no free force secrets remaining.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "hatred" ) )
  {
	if( HAS_FFEAT(ch, HATRED_FEAT) )
	 {
		send_to_char( "&wYou already possess the &rHatred&w feat.\n\r", ch );
		return;
	 }
	if( !HAS_FFEAT(ch, ALTER_FEAT) || ch->darkpoints < 2 )
	 {
		send_to_char( "&wYou must meet the requirements for the &rHatred&w feat first.\n\r", ch );
		return;
	 }
	SET_BIT(ch->force_feats, HATRED_FEAT);
	ch->secret -= 1;
	send_to_char( "&wYou have now obtained the &rHatred&w feat.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "drain force" ) )
  {
	if( HAS_FFEAT(ch, DRAIN_FORCE) )
	 {
		send_to_char( "&wYou already possess the &rDrain Force&w feat.\n\r", ch );
		return;
	 }
	if( !HAS_FFEAT(ch, ALTER_FEAT) || !HAS_FFEAT(ch, CONTROL_FEAT) || ch->top_level < 6 || ch->darkpoints < 6 || !HAS_FFEAT(ch, SITH_SORCERY) )
	 {
		send_to_char( "&wYou must meet the requirements for &rDrain Force&w before you can take it.\n\r", ch );
		return;
	 }
	SET_BIT(ch->force_feats, DRAIN_FORCE);
	ch->secret -= 1;
	send_to_char( "&wYou now possess the &rDrain Force&w feat.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "alchemy" ) || !str_cmp(argument, "force lightning") || !str_cmp(argument, "force grip" ) )
  {
	if( ch->class_level[SITHLORD_ABILITY] == 0 )
	 {
		send_to_char( "&wWhich secret would you like to posses?\n\r", ch );
		return;
	 }
  }
 if( !str_cmp( argument, "alchemy" ) )
  {
	ch->secret -= 1;
	ch->force_level[ALCHEMY_SKILL] += 1;
	ch->force_percent[ALCHEMY_SKILL] = 0;
	send_to_char( "&wYour &rAlchemy&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "force lightning" ) )
  {
	ch->force_level[FORCE_LIGHTNING] += 1;
	ch->force_percent[FORCE_LIGHTNING] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &rForce Lightning&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "force grip" ) )
  {
	ch->force_level[FORCE_GRIP] += 1;
	ch->force_percent[FORCE_GRIP] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &rForce Grip&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp( argument, "battlemind" ) )
  {
	ch->force_level[BATTLEMIND_SKILL] += 1;
	ch->force_percent[BATTLEMIND_SKILL] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &bBattlemind&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "force defense" ) )
  {
	ch->force_level[FORCE_DEFENSE] += 1;
	ch->force_percent[FORCE_DEFENSE] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &bForce Defense&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "force strike") )
  {
	ch->force_level[FORCE_STRIKE] += 1;
	ch->force_percent[FORCE_STRIKE] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &bForce Strike&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "heal other" ) )
  {
	ch->force_level[HEAL_OTHER] += 1;
	ch->force_percent[HEAL_OTHER] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &bHeal Other&w skill raises slightly.\n\r", ch );
	return;
  }
 if( !str_cmp(argument, "heal self" ) )
  {
	ch->force_level[HEAL_SELF] += 1;
	ch->force_percent[HEAL_SELF] = 0;
	ch->secret -= 1;
	send_to_char( "&wYour &bHeal Self&w skill raises slightly.\n\r", ch );
	return;
  }
 send_to_char( "&wUncover which &bForce Secret&w?\n\r", ch );
 return;
}

void do_makecybernetic(CHAR_DATA *ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    int affecttype, affectammount;
    char name[MAX_STRING_LENGTH];
    int level, chance;
    bool checkdura, checkbat, checksuper, checkcircuit, checktool; 
    OBJ_DATA *obj;
    OBJ_INDEX_DATA *pObjIndex;
            
    argument = one_argument( argument, arg );

    if(ch->skill_level[CRAFT_DEVICE] == 0 )
     {
	send_to_char("Huh?\n\r", ch);
	return;
     }

    switch( ch->substate )
    { 
    	default:
    	        
     		if(str_cmp(arg, "imp hand") && str_cmp(arg, "imp arm") && str_cmp(arg, "adv hand") && str_cmp(arg, "adv arm") && str_cmp(arg, "ir eye") && str_cmp(arg, "optic eye") && str_cmp(arg, "target eye") && str_cmp(arg, "aj") && str_cmp(arg, "skeletal") && str_cmp(arg, "sensor") && str_cmp(arg, "comlink") && str_cmp(arg, "tremor"))
		{
    		  send_to_char("Syntax: makecyber <part> \n\r", ch);
	 	  send_to_char("Parts: imp hand, adv hand, imp arm, adv arm, ir eye, optic eye,\n\r", ch);
		  send_to_char("       aj, skeletal, sensor, comlink, tremor \n\r", ch);
    		  return;
    		}
                checkdura = FALSE;
                checkbat = FALSE;
                checksuper = FALSE;
                checkcircuit = FALSE;
                checktool = FALSE;
                if ( !IS_SET( ch->in_room->room_flags, ROOM_FACTORY ) )
                {
                   send_to_char( "&RYou need to be in a factory or workshop to do that.\n\r", ch);
                   return;
                }
                
                for ( obj = ch->last_carrying; obj; obj = obj->prev_content )     
                {
                  if (obj->item_type == ITEM_DURAPLAST)
                    checkdura = TRUE;
                  if (obj->item_type == ITEM_BATTERY)
          	    checkbat = TRUE;
                  if (obj->item_type == ITEM_SUPERCONDUCTOR)
                    checksuper = TRUE;
                  if (obj->item_type == ITEM_CIRCUIT)
                    checkcircuit = TRUE;
                  if (obj->item_type == ITEM_TOOLKIT)
                    checktool = TRUE;
          	    
                }
                
                if ( !checkdura )
                {
                   send_to_char( "&RYou need some duraplast to create the housing.\n\r", ch);
                   return;
                }
 
                if ( !checkbat )
                {
                   send_to_char( "&RYou need a battery to power the implant.\n\r", ch);
                   return;
                }

                if ( !checksuper )
                {
                   send_to_char( "&RYou need a superconductor to focus the energy.\n\r", ch);
                   return;
                }

                if ( !checkcircuit )
                {
                   send_to_char( "&RYou need a circuit board to control the implant.\n\r", ch);
                   return;
                }

                if ( !checktool )
                {
                   send_to_char( "&RYou need a toolkit to build the implant.\n\r", ch);
                   return;
                }
                
	        if ( ch->gold < 100000 )
		{
		   send_to_char( "&RThis process will cost you an additional 55k, which you don't have.\n\r", ch);                
		   return;
 		}
		ch->gold -= 100000;
                

    	        chance = IS_NPC(ch) ? ch->top_level
	                 : number_range(1,20) + ch->skill_level[CRAFT_DEVICE] + stat_table[get_curr_int(ch)].mod;
                if ( chance >= 25 )
    		{
    		   send_to_char( "&GYou begin the long process of creating an implant.\n\r", ch);
    		   act( AT_PLAIN, "$n takes $s tools and begins to work.", ch,
		        NULL, argument , TO_ROOM );
		   add_timer ( ch , TIMER_DO_FUN , 10 , do_makecybernetic , 1 );
    		   ch->dest_buf = str_dup(arg);
    		   return;
	        }
	        send_to_char("&RYou can't figure out what to do.\n\r",ch);	        
    	   	return;	
    	
    	case 1: 
    		if ( !ch->dest_buf )
    		     return;
    		strcpy(arg, ch->dest_buf);
    		DISPOSE( ch->dest_buf);
    		break;
    		
    	case SUB_TIMER_DO_ABORT:
    		DISPOSE( ch->dest_buf );
    		ch->substate = SUB_NONE;    		                                   
    	        send_to_char("&RYou are interupted and fail to finish your work.\n\r", ch);
    	        return;
    }
    
    ch->substate = SUB_NONE;
    
    level = IS_NPC(ch) ? ch->top_level : ch->top_level;



    if ( ( pObjIndex = get_obj_index( IMPLANT_VNUM ) ) == NULL )
    {
         send_to_char( "&RThe item you are trying to create is missing from the database.\n\rPlease inform the administration of this error.\n\r", ch );
         return;
    }    
    
    checkdura = FALSE;
    checkbat = FALSE;
    checksuper = FALSE;
    checkcircuit = FALSE;
    checktool = FALSE;
    
    for ( obj = ch->last_carrying; obj; obj = obj->prev_content )     
    {
       if (obj->item_type == ITEM_TOOLKIT)
          checktool = TRUE;
       if (obj->item_type == ITEM_DURAPLAST && checkdura == FALSE)
       {
          checkdura = TRUE;
          separate_obj( obj );
          obj_from_char( obj );
       }
       if (obj->item_type == ITEM_BATTERY && checkbat == FALSE)
       {
          checkbat = TRUE;
          separate_obj( obj );
          obj_from_char( obj );
       }
       if (obj->item_type == ITEM_SUPERCONDUCTOR && checksuper == FALSE)
       {
          checksuper = TRUE;
          separate_obj( obj );
          obj_from_char( obj );
       }
       if (obj->item_type == ITEM_CIRCUIT && checkcircuit == FALSE)
       {
          checkcircuit = TRUE;
          separate_obj( obj );
          obj_from_char( obj );
       }
       
    }                            
    
    chance = IS_NPC(ch) ? ch->top_level
                : number_range(1,20) + ch->skill_level[CRAFT_DEVICE] + stat_table[get_curr_int(ch)].mod;
                
    if ( chance < 20  || ( !checkdura ) || ( !checktool ) || ( !checkbat ) || ( !checksuper ) || ( !checkcircuit ) )
    {
       send_to_char( "&RYou hold up your newly created implant.\n\r", ch);
       send_to_char( "&RThe implant begins to shake violently turning red hot!\n\r", ch);
       send_to_char( "&RYou drop it as it begins to burn your hand and then.. It disintigrates!\n\r", ch);       
       return;
    }

    if(!str_cmp(arg, "imp arm"))
    {
	affecttype = CAF_IMP_ARM;
	affectammount = 1;
  	strcpy(name, "An Improved Arm implant");
    }
    if(!str_cmp(arg, "adv arm"))
    {
	affecttype = CAF_ADV_ARM;
	affectammount = 2;
	strcpy(name, "An Advanced Arm Modle");
    }
    if(!str_cmp(arg, "imp hand"))
    {
	affecttype = CAF_IMP_HAND;
	affectammount = 1;
	strcpy(name, "An Improved hand implant");
    }
    if(!str_cmp(arg, "adv hand"))
    {
	affecttype = CAF_ADV_HAND;
	affectammount = 2;
	strcpy(name, "An Advanced hand implant");
    }
    if(!str_cmp(arg, "ir eye"))
    {
	affecttype = CAF_IR_EYE;
	affectammount = 0;
	strcpy(name, "A set of IR enhanced eyes");
    }
    if(!str_cmp( arg, "optic eye"))
    {
	affecttype = CAF_OPTIC_EYE;
	affectammount = 0;
	strcpy(name, "A set of Optic Eyes");
    }
    if(!str_cmp( arg, "target eye"))
    {
	affecttype = CAF_TARGET_EYE;
	affectammount = 1;
	strcpy(name, "A pair of eyes with cross hairs");
    }
    if(!str_cmp(arg, "skeletal"))
    {
	affecttype = CAF_SKELETAL;
	affectammount = 4;
	strcpy(name, "A new set of skin.");
    }
    if(!str_cmp(arg, "aj6"))
    {
	affecttype = CAF_AJ6;
	affectammount = 0;
	strcpy(name, "An internal datapad.");
    }
    if(!str_cmp(arg, "comlink"))
    {
	affecttype = CAF_COMLINK;
	affectammount = 0;
	strcpy(name, "An internal comlink.");
    }
    if(!str_cmp(arg, "sensor"))
    {
	affecttype = CAF_SENSOR;
	affectammount = 2;
	strcpy(name, "A Sensor Implant.");
    }
    if(!str_cmp(arg, "tremor"))
    {
	affecttype = CAF_TREMOR;
	affectammount = 3;
	strcpy(name, "Feet Implants.");
    }
    
    obj = create_object( pObjIndex, level );
    obj->item_type = ITEM_IMPLANT;
    SET_BIT( obj->wear_flags, ITEM_TAKE );
    obj->level = level;
    STRFREE( obj->name );
    obj->name = STRALLOC( name );
    STRFREE( obj->short_descr );
    obj->short_descr = STRALLOC( name );        
    STRFREE( obj->description );
    strcat( name, " was dropped here." );
    obj->description = STRALLOC( name );
    
    obj->value[0] = affecttype;
    obj->value[1] = affectammount;
    obj->value[2] = 0;      
    obj->cost = 75000;
                                                                    
    obj = obj_to_char( obj, ch );
                                                            
    send_to_char( "&GYou finish your work and hold up your newly created implant.&w\n\r", ch);
    act( AT_PLAIN, "$n finishes creating a new implant.", ch,
         NULL, argument , TO_ROOM );
    return;
};

void do_patron( CHAR_DATA *ch, char *argument )
{
  CLAN_DATA *clan;
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];
  long value=0;

  argument = one_argument( argument, arg1 );

  if( IS_NPC(ch) )
	return;

  if( !IS_IMMORTAL(ch) && ch->class_level[BROKER_ABILITY] < 5 )
   {
	send_to_char("Huh?\n\r", ch);
	return;
   }

  if( !ch->pcdata->clan || ch->pcdata->clan->name != "Hutt Crime Syndicate" )
   {
	send_to_char("You cannot use this ability outside of the HCS.\n\r", ch);
	return;
   }
	
  if( arg1[0] == '\0' )
   {
	send_to_char("&rUsage: patron loan&w\n\r", ch);
	send_to_char("&r       patron repay <value>&w\n\r", ch);
	return;
   }

  if( !str_cmp(arg1, "loan") )
   {
    if( ch->pcdata->loan > 0 )
     {
	send_to_char("You already have an outstanding loan.\n\r", ch);
	return;
     }
    clan = get_clan( "Hutt Crime Syndicate" );
    if( !clan )
     {
	send_to_char("Something went wrong, inform an IMM.\n\r", ch);
	return;
     }
    if( clan->funds <= 0 )
     {
	send_to_char("You can't borrow money, the HCS is broke!\n\r", ch);
	return;
     }
    value = ((number_range(1,20) + ch->top_level + ch->skill_level[DIPLOMACY_SKILL]) * 1000 );
    if( value > clan->funds )
        value = clan->funds;
    sprintf( buf, "%s has borrowed %ld credits from the HCS!\n\r", ch->name, value );
    talk_channel( ch, buf, CHANNEL_CLAN, "clantalk" );
    clan->funds -= value;
    ch->pcdata->loan += ( value + (value * (10/100)));
    ch->gold += value;
    return;
   }
  
 if( !str_cmp( arg1, "repay" ) )
  {
   if( ch->pcdata->loan == 0 )
    {
	send_to_char("You have no loan to pay back!\n\r", ch);
	return;
    }
   if( argument[0] == '\0' )
    {
	send_to_char("Repay how much?\n\r", ch);
	return;
    }
   value = atoi(argument);
   if( value < 1 )
    {
	send_to_char("Come on, repay something!\n\r", ch);
	return;
    }
   if( value > ch->pcdata->loan )
     	value = ch->pcdata->loan;
   if( value > ch->gold )
    {
	send_to_char("You don't have that many credits on hand.\n\r", ch);
	return;
    }
   if( value == ch->pcdata->loan )
    {
	ch->gold -= value;
	ch->pcdata->loan = 0;
	clan->funds += value;
	sprintf( buf, "%s has repaid their loan in full!\n\r", ch->name );
        talk_channel( ch, buf, CHANNEL_CLAN, "clantalk" );
	return;
    }
   sprintf( buf, "%s has repaid %ld credits of their loan!\n\r", ch->name, value );
   talk_channel( ch, buf, CHANNEL_CLAN, "clantalk" );
   ch->gold -= value;
   ch->pcdata->loan -= value;
   clan->funds += value;
   return;
  }

 do_patron( ch, "" );
 return;
}

void do_installimplant(CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *victim;
  bool checktool,checkimp;
  OBJ_DATA *obj;
  OBJ_DATA *modobj;
  char arg[MAX_INPUT_LENGTH];
  char buf[MAX_INPUT_LENGTH];
  int  chance;

  if(IS_NPC(ch))
    return;

  if(!HAS_FEAT3(ch, TRANSPLANT_FEAT))
   {
	send_to_char("Only a Master Tech Specialist can install modules.\n\r", ch);
	return;
   }

  if(argument[0] == '\0' )
   {
	send_to_char("Syntax: Installimplant <victim>\n\r", ch);
	return;
   }

  strcpy( arg , argument );
  checktool = FALSE;
  checkimp = FALSE;

     if ( (victim = get_char_room(ch, argument) ) == NULL )
	{
	 send_to_char("That person isn't here.\n\r", ch);
	 return;
	}

     if ( IS_NPC(victim))
      {
	 send_to_char("Leave my mobs alone.\n\r", ch);
	 return;
	}

     if ( victim != ch && victim->position != POS_SLEEPING)
	{
	send_to_char("You have to put your patient to sleep for this.\n\r", ch);
	return;
	}

     for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
      {
      	if (obj->item_type == ITEM_TOOLKIT)
      	  checktool = TRUE;
      	if (obj->item_type == ITEM_IMPLANT)
	{
      	  checkimp = TRUE;
	  modobj = obj;
	}
      }

     if ( checktool == FALSE )
      {
      	send_to_char("You need a toolkit to install an implant.\n\r", ch);
      	return;
      }
     if ( checkimp == FALSE )
      {
      	send_to_char("You need an implant to install!\n\r", ch);
      	return;
      }
	if (modobj->value[0] == CAF_IMP_ARM && HAS_CYBER(victim, CYBER_IMP_ARM))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_ADV_ARM && HAS_CYBER(victim, CYBER_ADV_ARM))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_IMP_HAND && HAS_CYBER(victim, CYBER_IMP_HAND))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_ADV_HAND && HAS_CYBER(victim, CYBER_ADV_HAND))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_IR_EYE && HAS_CYBER(victim, CYBER_IR_EYE))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_OPTIC_EYE && HAS_CYBER(victim, CYBER_OPTIC_EYE))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_TARGET_EYE && HAS_CYBER(victim, CYBER_OPTIC_EYE))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_SKELETAL && HAS_CYBER(victim, CYBER_SKELETAL))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_COMLINK && HAS_CYBER(victim, CYBER_COMLINK))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_SENSOR && HAS_CYBER(victim, CYBER_SENSORY))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_AJ6 && HAS_CYBER(victim, CYBER_AJ6))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}
	if (modobj->value[0] == CAF_TREMOR && HAS_CYBER(victim, CYBER_TREMOR))
	{
	send_to_char("You already possess this implant.\n\r", ch);
	return;
	}

     chance = IS_NPC(ch) ? ch->top_level        : number_range(1,20) + ch->skill_level[CRAFT_DEVICE] + stat_table[get_curr_int(ch)].mod;
     if ( chance >= 25 )
      {
  	ch->dest_buf   = str_dup(arg);
       	send_to_char( "&GYou begin the long process of installing a new implant.\n\r", ch);
    	sprintf(buf, "$n takes out $s toolkit and an implant and begins to work.\n\r");
     	act( AT_PLAIN, buf, ch, NULL, argument , TO_ROOM );  	
      }
     else
      {
      send_to_char("&RYou are unable to figure out what to do.\n\r",ch);
      return;
      }
     
     for ( obj = ch->last_carrying; obj; obj = obj->prev_content )
      {
         if (obj->item_type == ITEM_TOOLKIT)
           checktool = TRUE;
         if (obj->item_type == ITEM_IMPLANT)
	   {
           checkimp = TRUE;
           modobj = obj;
         }
           
      }

    chance = IS_NPC(ch) ? ch->top_level
               : ch->skill_level[CRAFT_DEVICE] + number_range(1,20) + stat_table[get_curr_int(ch)].mod;

    if ( chance < 20 )
     {
       send_to_char("&RYou finish installing the new cybernetic and everything's looking good...\n\r", ch);
       send_to_char("&RThen it turns bright red and melts!\n\r", ch);
       return;
     }

	if(modobj->value[0] == CAF_IMP_ARM || modobj->value[0] == CAF_ADV_ARM)
	 {
	  if(HAS_CYBER(victim, CYBER_IMP_ARM) || HAS_CYBER(victim, CYBER_ADV_ARM) )
	   {
	     if(HAS_CYBER(victim, CYBER_IMP_ARM) )
		{
		REMOVE_BIT(victim->implant, CYBER_IMP_ARM);
		victim->perm_dex -= 1;
	 	}
	     if(HAS_CYBER(victim, CYBER_ADV_ARM) )
		{
		REMOVE_BIT(victim->implant, CYBER_ADV_ARM);
		victim->perm_dex -= 2;
		}
	   }
	 }
	if( modobj->value[0] == CAF_IMP_HAND || modobj->value[0] == CAF_ADV_HAND)
	 {
	  if(HAS_CYBER(victim, CYBER_IMP_HAND) || HAS_CYBER(victim, CYBER_ADV_HAND) )
	   {
	     if(HAS_CYBER(victim, CYBER_IMP_HAND) )
		{
		REMOVE_BIT(victim->implant, CYBER_IMP_HAND);
		victim->perm_str -= 1;
		}
	     if(HAS_CYBER(victim, CYBER_ADV_HAND) )
		{
		REMOVE_BIT(victim->implant, CYBER_ADV_HAND);
		victim->perm_str -= 2;
		}
	   }
	 }
	if(modobj->value[0] == CAF_IR_EYE || modobj->value[0] == CAF_OPTIC_EYE || modobj->value[0] == CAF_TARGET_EYE )
	 {
	  if(HAS_CYBER(victim, CYBER_IR_EYE) || HAS_CYBER(victim, CYBER_OPTIC_EYE) || HAS_CYBER(victim, CYBER_TARGET_EYE) )
	   {
	     if(HAS_CYBER(victim, CYBER_IR_EYE) )
	      {
		REMOVE_BIT(victim->implant, CYBER_IR_EYE);
		REMOVE_BIT(victim->affected_by, AFF_TRUESIGHT);
		}
	     if(HAS_CYBER(victim, CYBER_OPTIC_EYE) )
		{
		REMOVE_BIT(victim->implant, CYBER_OPTIC_EYE);
		victim->skill_level[SPOT_SKILL] -= 3;
		}
	     if(HAS_CYBER(victim, CYBER_TARGET_EYE) )		
		REMOVE_BIT(victim->implant, CYBER_TARGET_EYE);	
	   }
	 }

	if(modobj->value[0] == CAF_IMP_ARM)
	 {
	 victim->perm_dex += 1;
	 SET_BIT(victim->implant, CYBER_IMP_ARM);
	 }
	if(modobj->value[0] == CAF_ADV_ARM)
	 {
	 SET_BIT(victim->implant, CYBER_ADV_ARM);
	 victim->perm_dex += 2;
	 }
	if(modobj->value[0] == CAF_IMP_HAND)
	 {
	 SET_BIT(victim->implant, CYBER_IMP_HAND);
	 victim->perm_str += 1;
	 }
	if(modobj->value[0] == CAF_ADV_HAND)
	 {
	 SET_BIT(victim->implant, CYBER_ADV_HAND);
	 victim->perm_str += 2;
	 }
	if(modobj->value[0] == CAF_IR_EYE)
	 {
	 SET_BIT(victim->implant, CYBER_IR_EYE);
	 SET_BIT(victim->affected_by, AFF_TRUESIGHT);
	 }
	if(modobj->value[0] == CAF_OPTIC_EYE)
	 {
	 SET_BIT(victim->implant, CYBER_OPTIC_EYE);
	 victim->skill_level[SPOT_SKILL] += 3;
	 }
	if(modobj->value[0] == CAF_TARGET_EYE )
	 SET_BIT(victim->implant, CYBER_TARGET_EYE);
	if(modobj->value[0] == CAF_SKELETAL)
	 {
	 SET_BIT(victim->implant, CYBER_SKELETAL);
	 victim->armor += 4;
	 }
	if(modobj->value[0] == CAF_SENSOR)
	 {
	 victim->skill_level[SPOT_SKILL] += 2;
	 victim->skill_level[LISTEN_SKILL] += 2;
	 SET_BIT(victim->implant, CYBER_SENSORY);
	 }
	if(modobj->value[0] == CAF_TREMOR)
	 {
	 SET_BIT(victim->implant, CYBER_TREMOR);
	 victim->skill_level[LISTEN_SKILL] += 3;
	 }
	if(modobj->value[0] == CAF_COMLINK)
	 SET_BIT(victim->implant, CYBER_COMLINK);
	if(modobj->value[0] == CAF_AJ6 )
	 SET_BIT(victim->implant, CYBER_AJ6);

      separate_obj( modobj );
      obj_from_char( modobj );
      extract_obj(modobj);
      send_to_char("You finish installing the new implant.\n\r", ch);
      return;
};

void body_parts( CHAR_DATA *ch, int iRace )
{
  if( IS_NPC(ch) )
	return;

  SET_BIT(ch->xflags,  PART_HEAD);
  SET_BIT(ch->xflags, PART_ARM_R1);
  SET_BIT(ch->xflags, PART_ARM_L1);
  SET_BIT(ch->xflags, PART_LEG_R);
  SET_BIT(ch->xflags, PART_LEG_L);
 if( iRace != RACE_HUTT )
  SET_BIT(ch->xflags, PART_FEET); 
  SET_BIT(ch->xflags, PART_HAND_R1);
  SET_BIT(ch->xflags, PART_HAND_L1);
 if( iRace == RACE_BARTOKK )
 {
  SET_BIT(ch->xflags, PART_ARM_R2);
  SET_BIT(ch->xflags, PART_ARM_L2);
  SET_BIT(ch->xflags, PART_HAND_R2);
  SET_BIT(ch->xflags, PART_HAND_L2);
 }
 if( iRace == RACE_SKYTRI )
  SET_BIT(ch->xflags, PART_WINGS);
 if( iRace != RACE_MIRALUKA )
 {
  SET_BIT(ch->xflags, PART_EYE_L);
  SET_BIT(ch->xflags, PART_EYE_R);
 }
  return;
}

void do_cybernetics(CHAR_DATA *ch, char *argument)
{
  if(IS_NPC(ch))
    return;

  if(!IS_IMMORTAL(ch) && IS_DROID(ch))
   {
	send_to_char("Droids already possess enough cybernetics.\n\r", ch);
	return;
   }

  if(HAS_CYBER(ch, CYBER_IMP_ARM) )
   ch_printf(ch, "&bArm:       &pImproved Model&x\n\r", ch);
  else if(HAS_CYBER(ch, CYBER_ADV_ARM) )
   ch_printf(ch, "&bArm:       &pTop Of The Line&x\n\r", ch);
  else
   ch_printf(ch, "&bArm:       &rNo Cybernetic Modification&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_IMP_HAND) )
   ch_printf(ch, "&bHand:      &pImproved Model&x\n\r", ch);
  else if(HAS_CYBER(ch, CYBER_ADV_HAND) )
   ch_printf(ch, "&bHand:      &pTop Of The Line&x\n\r", ch);
  else
   ch_printf(ch, "&bHand:      &rNo Cybernetic Modification&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_IR_EYE) )
   ch_printf(ch, "&bEyes:      &pIR Enhanced Eyes&x\n\r", ch);
  else if(HAS_CYBER(ch, CYBER_OPTIC_EYE) )
   ch_printf(ch, "&bEyes:      &pOptic Eyes&x\n\r", ch);
  else if(HAS_CYBER(ch, CYBER_TARGET_EYE) )
   ch_printf(ch, "&bEyes:      &pTargeting Eyes&x\n\r", ch);
  else
   ch_printf(ch, "&bEyes:      &rNo Cybernetic Modifications&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_COMLINK) )
   ch_printf(ch, "&bComlink:   &pEquipped&x\n\r", ch);
  else
   ch_printf(ch, "&bComlink:   &rNot Equipped&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_SKELETAL) )
   ch_printf(ch, "&bSkeletal:  &pSkeletal Enhancement&x\n\r", ch);
  else 
   ch_printf(ch, "&bSkeletal:  &rNo Modification To Structure&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_TREMOR) )
   ch_printf(ch, "&bFeet:      &pTremor Sensor Supported&x\n\r", ch);
  else
   ch_printf(ch, "&bFeet:      &rNone Equipped&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_AJ6 ) )
   ch_printf(ch, "&bComputer:  &pOnline&x\n\r", ch);
  else
   ch_printf(ch, "&bComputer:  &rOffline&x\n\r", ch);

  if(HAS_CYBER(ch, CYBER_SENSORY ) )
   ch_printf(ch, "&bSensors:   &pImproved&x\n\r", ch);
  else
   ch_printf(ch, "&bSensors:   &rNormal&x\n\r", ch);
 
  return;
};

void do_imbue( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *obj;
  int wis_check;
  int int_check;
  int con_check;

  if( IS_NPC(ch) )
	return;

  if( !IS_IMMORTAL(ch) && ch->class_level[FORCE_ADEPT_ABILITY] == 0 && ch->class_level[JEDIGUARDIAN_ABILITY] == 0 && ch->class_level[JEDICONSULAR_ABILITY] == 0 )
   {
	send_to_char( "&wHuh?\n\r", ch );
	return;
   }
  if( !HAS_FFEAT(ch, CONTROL_FEAT ) )
   {
	send_to_char( "&RYou lack the Control Feat.&w\n\r", ch );
	return;
   }
  if( !HAS_FFEAT(ch, SENSE_FEAT ) )
   {
	send_to_char( "&RYou lack the Sense Feat.&w\n\r", ch );
	return;
   }
  if( !HAS_FFEAT(ch, ALTER_FEAT ) )
   {
	send_to_char( "&RYou lack the Alter Feat.&w\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&bImbue which crystal with the Force?&w\n\r", ch );
	return;
   }
  if( ( obj = get_obj_carry( ch, argument ) ) == NULL )
   {
        send_to_char( "&RYou don't have that item.&w\n\r", ch );
        return;
   }  
  if( obj->item_type != ITEM_CRYSTAL )
   {
	send_to_char( "&RThat item isn't a crystal.&w\n\r", ch );
	return;
   }
  if( IS_SET(obj->extra_flags, ITEM_IMBUED) )
   {
	send_to_char( "&bThat crystal is already imbued.&w\n\r", ch );
	return;
   }
  if( ch->forcepoints < 1 )
   {
	send_to_char( "&RYou lack the required forcepoints to do this.&w\n\r", ch );
	return;
   }
  ch->forcepoints -= 1;
  con_check = ( number_range(1, 20) + stat_table[get_curr_con(ch)].mod );
  wis_check = ( number_range(1, 20) + stat_table[get_curr_wis(ch)].mod );
  int_check = ( number_range(1, 20) + stat_table[get_curr_int(ch)].mod );
  if( con_check < 15 )
   {
	send_to_char( "&RYou fail to reach harmony with your inner self.&w\n\r", ch );
	return;
   }
  if( wis_check < 15 )
   {
	send_to_char( "&RYou fail to reach harmony with the Force.&w\n\r", ch );
	return;
   }
  if( int_check < 15 )
   {
	send_to_char( "&RYou fail to harmonize and imbue the crystal.&w\n\r", ch );
	return;
   }
  ch->forcepoints += 2;
  SET_BIT(obj->extra_flags, ITEM_IMBUED);
  separate_obj( obj );
  send_to_char( "&bYou succeed in imbuing the crystal with the power of the Force.&w\n\r", ch );
  WAIT_STATE(ch, PULSE_VIOLENCE);
  return;
}

void do_ignite( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *wield;
  OBJ_DATA *dual;
  CHAR_DATA *gch;
  char buf[MAX_STRING_LENGTH];

  if( IS_NPC(ch) )
	return;

  if( ( wield = get_eq_char( ch, WEAR_WIELD ) ) == NULL )
   {
	send_to_char( "&RYou aren't wielding any weapon.&w\n\r", ch );
	return;
   }
  if( wield->item_type == ITEM_WEAPON && wield->value[3] == WEAPON_LIGHTSABER )
   {
    if( IS_OBJ_STAT(wield, ITEM_IGNITED) )
     {
	REMOVE_BIT(wield->extra_flags, ITEM_IGNITED);
	send_to_char( "&YYou extinguish a lightsaber.&w\n\r", ch );
	for( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
	 {
	  sprintf( buf, "&Y%s extinguishes a lightsaber.&w", ch->name );
	  if( gch == ch )
	    continue;
          send_to_char( buf, ch );
	 }
     }
    else
     {
	SET_BIT(wield->extra_flags, ITEM_IGNITED);
	send_to_char( "&YYou ignite a lightsaber.&w\n\r", ch );
        for( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
         {
          sprintf( buf, "&Y%s ignites a lightsaber.&w", ch->name );
          if( gch == ch )
		continue;
          send_to_char( buf, ch );
         }
     }
   }
  dual = get_eq_char( ch, WEAR_DUAL_WIELD );
  if( !dual )
	return;
  if( dual->item_type == ITEM_WEAPON && dual->value[3] == WEAPON_LIGHTSABER )
   {
    if( !IS_OBJ_STAT(dual, ITEM_IGNITED) )
     {
	SET_BIT(dual->extra_flags, ITEM_IGNITED);
	send_to_char( "&YYou ignite an offhand lightsaber.&w\n\r", ch );
        for( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
         {
          sprintf( buf, "&Y%s ignites an offhand lightsaber.&w", ch->name );
          if( gch == ch )
		continue;
          send_to_char( buf, ch );
         }
     }
    else
     {
	REMOVE_BIT(dual->extra_flags, ITEM_IGNITED);
	send_to_char( "&YYou extinguish an offhand lightsaber.&w\n\r", ch );
        for( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
         {
          sprintf( buf, "&Y%s extinguishes an offhand lightsaber.&w", ch->name );
          if( gch == ch )
		continue;
          send_to_char( buf, ch );
         }
     }
   }
 return;
}

void do_setsith( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];
  int status;

  argument = one_argument( argument, arg1 );

  if( IS_NPC(ch) || !IS_IMMORTAL(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' || arg1[0] == '\0' )
   {
	send_to_char( "Syntax: Setsith <victim> <status>\n\r", ch );
	send_to_char( "Status: acolyte, lord, master\n\r", ch );
	return;
   }
  victim = get_char_world_ooc( ch, arg1 );
  if( !victim )
   {
	send_to_char( "I do not see that person online.&w\n\r", ch );
	return;
   }
  if( str_cmp( argument, "acolyte" ) && str_cmp( argument, "lord" ) && str_cmp( argument, "master" ) )
   {
	do_setsith( ch, "" );
	return;
   }
  if( !str_cmp( argument, "acolyte" ) )
   {
	sprintf( buf, "Sith Apprentice" );
   	status = STATUS_SITH_APPRENTICE;
   }
  else if( !str_cmp( argument, "lord" ) )
   {
	sprintf( buf, "Sith Lord" );
	status = STATUS_SITH_LORD;
   }
  else if( !str_cmp( argument, "master" ) )
   {
	sprintf( buf, "Dark Lord Of The Sith" );
	status = STATUS_SITH_MASTER;
   }

  if( IS_NPC(victim) )
   {
	send_to_char( "Not on NPCs.\n\r", ch );
	return;
   }
  
  victim->pcdata->force_status = status;
  send_to_char( "Done.\n\r", ch );
  ch_printf( victim, "&WYou have been chosen to be a &R%s&W.\n\r", buf );
  return;
}

void do_resources( CHAR_DATA *ch, char *argument )
{
  int ability;
  long gain;

  if( IS_NPC(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if(!IS_IMMORTAL(ch) && ch->class_level[NOBLE_ABILITY] < 3 && ch->class_level[CRIMELORD_ABILITY] < 2 && ch->class_level[SITHLORD_ABILITY] < 2 && ch->class_level[ENGINEER_ABILITY] < 7 && ch->class_level[NOBLELORD_ABILITY] < 3 && ch->class_level[BROKER_ABILITY] == 0)
   {
	send_to_char("Huh?\n\r", ch);
	return;
   }
  if(ch->resources_temp == 0 )
   {
	send_to_char( "You may not call upon your resources again today.&w\n\r", ch );
	return;
   }
  gain = 0;
  for( ability=0; ability < MAX_ABILITY; ability++ )
   {
     if( ability != NOBLE_ABILITY && ability != CRIMELORD_ABILITY && ability != SITHLORD_ABILITY 
      && ability != ENGINEER_ABILITY && ability != NOBLELORD_ABILITY && ability != BROKER_ABILITY )
	continue;
     gain += ( ( number_range(1, 20) + ch->class_level[ability] + stat_table[get_curr_cha(ch)].mod ) * 100 );
   }
  if( gain < 0 )
   	gain = 1;
  ch->pcdata->bank += gain;
  ch_printf( ch, "&w&WYou call upon your &Rresources&w&W and your bank account is credited &G%ld&w&W credits.&w\n\r", gain );
  ch->resources_temp = 0;
  return;
}

void do_rentlocker( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *obj;
  int x1,x2,x3;

  if( IS_NPC(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&w&WRent which locker?&w\n\r", ch );
	return;
   }
  if( ( obj = get_obj_list( ch, argument, ch->in_room->first_content ) ) == NULL )
   {
	send_to_char( "&rI don't see that locker here.&w\n\r", ch );
	return;
   }
  if( obj->item_type != ITEM_LOCKER )
   {
	send_to_char( "&rThat is not a locker.&w\n\r", ch );
	return;
   }
  if( IS_SET(obj->extra_flags, ITEM_RENTED) )
   {
	send_to_char( "&rThis locker is already being rented.&w\n\r", ch );
	return;
   }
  if( ch->gold < 50 )
   {
	send_to_char( "&rYou lack the 50 credits required to rent a locker.&w\n\r", ch );
	return;
   }
  x1 = number_range(1,99);
  x2 = number_range(1,99);
  x3 = number_range(1,99);
  obj->value[1] = x1;
  obj->value[2] = x2;
  obj->value[3] = x3;
  SET_BIT(obj->extra_flags, ITEM_RENTED);
  if( IS_SET(obj->value[0], CONT_LOCKED) )
   REMOVE_BIT(obj->value[0], CONT_LOCKED);
  if( IS_SET(obj->value[0], CONT_CLOSED) )
   REMOVE_BIT(obj->value[0], CONT_CLOSED);
  ch->gold -= 50;
  ch_printf( ch, "&w&WYour new locker combination is &G%d %d %d&w&W.\n\r", x1, x2, x3 );
  act( AT_PLAIN, "$n slides a credit chip into a locker, renting it for a bit.", ch, NULL, NULL, TO_ROOM );
  return;
}

void do_lockercode( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *obj;
  char locker[MAX_INPUT_LENGTH];
  char code1[MAX_INPUT_LENGTH];
  char code2[MAX_INPUT_LENGTH];
  bool correct_code=TRUE;
  int x1, x2, x3;

  argument = one_argument( argument, locker );
  argument = one_argument( argument, code1 );
  argument = one_argument( argument, code2 );

  if( IS_NPC(ch) || argument[0] == '\0' || code1[0] == '\0' || code2[0] == '\0' || locker[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&Wlockercode <locker> <first number> <second number> <third number>\n\r", ch );
	return;
   }
  if( ( obj = get_obj_list( ch, locker, ch->in_room->first_content ) ) == NULL )
   {
	send_to_char( "&rI don't see that locker here.&w\n\r", ch );
	return;
   }
  if( obj->item_type != ITEM_LOCKER )
   {
	send_to_char( "&rThat is not a locker.&w\n\r", ch );
	return;
   }
  if( !IS_SET(obj->extra_flags, ITEM_RENTED) )
   {
	send_to_char( "&rThat locker is not rented.&w\n\r", ch );
	return;
   }
  if( !IS_SET(obj->value[0], CONT_LOCKED) )
   {
	send_to_char( "&rThat locker isn't locked.&w\n\r", ch );
	return;
   }
  if( !IS_SET(obj->value[0], CONT_CLOSED) )
   {
	send_to_char( "&rThat locker isn't closed.&w\n\r", ch );
	return;
   }
  x1 = atoi(code1);
  x2 = atoi(code2);
  x3 = atoi(argument);
  if( x1 != obj->value[1] )
  	correct_code = FALSE;
  if( x2 != obj->value[2] )
 	correct_code = FALSE;
  if( x3 != obj->value[3] )
	correct_code = FALSE;
  if( !correct_code )
   {
	ch->hit -= number_range(1, 3);
	update_pos(ch);
	act( AT_BLOOD, "You receive a small shock from the locker after incorrectly inputting the combination.\n\r", ch, NULL, NULL, TO_CHAR );
	act( AT_BLOOD, "$n receives a small shock after $e inputs the incorrect combination.\n\r", ch, NULL, NULL, TO_ROOM );
	WAIT_STATE( ch, PULSE_PER_SECOND * 3 );
	return;
   }
  REMOVE_BIT(obj->extra_flags, ITEM_RENTED);
  REMOVE_BIT(obj->value[0], CONT_LOCKED);
  REMOVE_BIT(obj->value[0], CONT_CLOSED);
  act( AT_BLUE, "You input the correct combination and the locker swings open.\n\r", ch, NULL, NULL, TO_CHAR );
  act( AT_BLUE, "$n inputs the correct combination and a locker swings open.\n\r", ch, NULL, NULL, TO_ROOM );
  WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
  return;
}

void do_padawan( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *master;
  CHAR_DATA *padawan;
  char arg1[MAX_INPUT_LENGTH];

  argument = one_argument( argument, arg1 );

  if( IS_NPC(ch) || ( !IS_IMMORTAL(ch) && ch->class_level[JEDIMASTER_ABILITY] == 0 ) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( arg1[0] == '\0' || argument[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&WPadawan <master> <student>&w\n\r", ch );
	return;
   }
  if( ( master = get_char_room( ch, arg1 ) ) == NULL )
   {
	send_to_char( "&RThat master isn't here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(master) )
   {
	send_to_char( "&RNPCs can't be Masters.&w\n\r", ch );
	return;
   }
  if( ( padawan = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&RThat student isn't here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(padawan) )
   {
	send_to_char( "&RNPCs can't be padawans.&w\n\r", ch );
	return;
   }
  if( !IS_IMMORTAL(master) && master->class_level[JEDICONSULAR_ABILITY] < 7 && master->class_level[JEDIGUARDIAN_ABILITY] < 7 )
   {
	send_to_char( "&RThe master is not a Jedi Knight.&w\n\r", ch );
	return;
   }
  if( padawan->pcdata->age != IS_CHILD )
   {
	ch_printf( ch, "&r%s &w&Wis too old to be trained.&w&W\n\r", padawan->name );
	return;
   }
  if( padawan->pcdata->trials == HAS_PASSED )
   {
	send_to_char( "&RThe padawan has already been trained.&w\n\r", ch );
	return;
   }
  if( master->pcdata->student && master->pcdata->student[0] != '\0' )
   {
	send_to_char( "&RThat master already has a student.&w\n\r", ch );
	return;
   }
  if( padawan->pcdata->master && padawan->pcdata->master[0] != '\0' )
   {
	send_to_char( "&RThat student already has a master.&w\n\r", ch );
	return;
   }
  if( master == padawan )
   {
	send_to_char( "You cannot assign a Padawan as their own Master.\n\r", ch );
	return;
   }
  master->pcdata->student = STRALLOC( padawan->name );
  padawan->pcdata->master = STRALLOC( master->name );
  ch_printf( ch, "&G%s &w&Wis now a padawan of &G%s&w\n\r", padawan->name, master->name );
  ch_printf( padawan, "&w&WYou are now a padawn of &G%s&w\n\r", master->name );
  ch_printf( master, "&G%s &w&Wis now your padawan.&w\n\r", padawan->name );
  return;
}

void do_promote( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *padawan;
  CHAR_DATA *master;

  if( IS_NPC(ch) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( !IS_IMMORTAL(ch) && ch->class_level[JEDIMASTER_ABILITY] == 0 )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
  if( argument[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&WJpromote <padawan>\n\r", ch );
	return;
   }
  if( ( padawan = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "I do not see that Padawan here.\n\r", ch );
	return;
   }
  if( IS_NPC(padawan) )
   {
	send_to_char( "NPCs can't be Padawans.\n\r", ch );
	return;
   }
  if( padawan->pcdata->master == NULL )
   {
	send_to_char( "That Padawan does not have a master.\n\r", ch );
	return;
   }
  if( !str_cmp( ch->name, padawan->pcdata->master ) )
   {
	send_to_char( "You cannot promote your own Padawan.\n\r", ch );
	return;
   }
  if( ( master = get_char_room( ch, padawan->pcdata->master ) ) == NULL )
   {
	send_to_char( "Their Master is not yet present.\n\r", ch );
	return;
   }
  if( padawan->pcdata->trials == NOT_PASSED )
   {
	send_to_char( "This Padawan has yet to complete the Trials.\n\r", ch );
	return;
   }
  STRFREE( padawan->pcdata->master );
  STRFREE( master->pcdata->student );
  send_to_char( "You have been promoted to the rank of Jedi Knight.\n\r", padawan );  
  ch_printf( ch, "%s has been promoted to the rank of Jedi Knight.\n\r", padawan->name );
  ch_printf( master, "%s has been promoted to the rank of Jedi Knight.\n\r", padawan->name );
  if( !IS_NPC(master) && master->pcdata->has_trained == NOT_TRAINED )
 	master->pcdata->has_trained = HAS_TRAINED;
  return;
};

void do_test( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *obj;
  CHAR_DATA *victim;
  char buf[MAX_STRING_LENGTH];
  bool has_data=FALSE;
  int chance;
  int value;

  if( IS_NPC(ch) || ( !IS_IMMORTAL(ch) && ch->class_level[JEDIMASTER_ABILITY] == 0 ) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&w&WTest which applicant?&w\n\r", ch );
	return;
   }
  if( ( obj = get_eq_char( ch, WEAR_HOLD ) ) != NULL )
   {
	if( obj->item_type == ITEM_DATAPAD )
		has_data = TRUE;
   }
  if( IS_IMMORTAL(ch) )
	has_data = TRUE;
  if( has_data )
   {
	send_to_char( "&rYou must be holding a DataPad to do this.&w\n\r",ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&rI don't see that person here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
   {
	send_to_char( "&rNot on NPCs&w\n\r", ch );
	return;
   }
  if( victim->pcdata->force_bonus < 1 )
   	victim->pcdata->force_bonus = number_range( 1, 1000 );
  value = victim->pcdata->force_bonus;
  if( value < 700 )
   	sprintf( buf, "%s is weak in the Force", victim->name );
  else if( value >= 700 && value < 850 )
	sprintf( buf, "%s is moderately strong in the Force", victim->name );
  else if( value >= 850 && value < 950 )
   	sprintf( buf, "%s is strong in the Force", victim->name );
  else if( value >= 950 )
	sprintf( buf, "Sample is off the charts" );
  else
	sprintf( buf, "Error Error Error Error" );
  chance = ( number_range(1,20) + ch->skill_level[COMPUTER_SKILL] + stat_table[get_curr_int(ch)].mod );
  victim->hit -= 1;
  update_pos( victim );
  act( AT_BLOOD, "$n takes a small blood sample from you.&w\n\r", ch, NULL, victim, TO_VICT );
  act( AT_PLAIN, "$n takes a small blood sample from $N.\n\r", ch, NULL, victim, TO_NOTVICT );
  act( AT_PLAIN, "You take a small blood sample from $N for analysis.\n\r", ch, NULL, victim, TO_CHAR );
  if( chance < 18 )
   {
	act( AT_BLOOD, "You fail to analyze $N's blood sample.", ch, NULL, victim, TO_CHAR );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	return;
   }
  ch_printf( ch, "&GDonor Name: &w&W%s\n\r", victim->name );
  ch_printf( ch, "&GResults: &w&W%s\n\r", buf );
  return;
}

void do_makesith( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg1[MAX_INPUT_LENGTH];
  bool is_sith=FALSE;

  argument = one_argument( argument, arg1 );

  if( IS_NPC(ch) )
	return;
  if( ch->class_level[SITHLORD_ABILITY] > 0 || ch->class_level[SITHWARRIOR_ABILITY] > 0 || ch->class_level[ACOLYTE_ABILITY] > 0 )
 	is_sith = TRUE;
  if( IS_IMMORTAL(ch) )
 	is_sith = TRUE;
  if( !is_sith )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( !IS_IMMORTAL(ch) && ch->pcdata->force_status != STATUS_SITH_LORD && ch->pcdata->force_status != STATUS_SITH_MASTER )
   {
	send_to_char( "Only Sith Lords and Sith Masters can induct new Sith.\n\r", ch );
	return;
   }
  if( argument[0] == '\0' || arg1[0] == '\0' )
   {
	send_to_char( "&GSyntax: &w&WMakesith <victim> <sith status>&w\n\r", ch );
 	send_to_char( "&GStatus: &w&Wacolyte, lord&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, arg1 ) ) == NULL )
   {
	send_to_char( "&rThat player isn't here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
   {
	send_to_char( "&rNot on NPCs&w\n\r", ch );
	return;
   }
  if( victim == ch )
   {
	send_to_char( "&rYou can't do this to yourself.&w\n\r", ch );
	return;
   }
  if( !str_cmp( argument, "acolyte" ) )
   {
	victim->pcdata->force_status = STATUS_SITH_APPRENTICE;
	ch_printf( ch, "&w&WYou induct &r%s&w&W as a Sith Acolyte.&w\n\r", victim->name );
	ch_printf( ch, "&G%s&w&W inducts you as a Sith Acolyte.&w\n\r", ch->name );
	return;
   }
  else if( !str_cmp( argument, "lord" ) )
   {
	victim->pcdata->force_status = STATUS_SITH_LORD;
	ch_printf( ch, "&w&WYou induct &G%s&w&W as a Sith Lord.&w\n\r", victim->name );
	ch_printf( ch, "&G%s&w&W inducts you as a Sith Lord.&w\n\r", ch->name );
	return;
   }
  else
	do_makesith( ch, "" );
  return;
}

int skill_max( CHAR_DATA *ch, int skill )
{
  int max=0;
  
  max += ( 3 + ch->top_level );

  if( ( skill == LISTEN_SKILL || skill == SPOT_SKILL ) && HAS_FEAT( ch, ALERTNESS_FEAT ) )
 	max += 2;
  if( ( skill == CLIMB_SKILL || skill == SWIM_SKILL ) && HAS_FEAT( ch, ATHLETIC_FEAT ) )
	max += 2;
  if( ( skill == DEMOLITIONS_SKILL || skill == DISABLE_DEVICE ) && HAS_FEAT( ch, CAUTIOUS_FEAT ) )
	max += 2;
  if( ( skill == REPAIR_SKILL || skill == COMPUTER_SKILL ) && HAS_FEAT( ch, GEARHEAD_FEAT ) )
	max += 2;
  if( skill == INTIMIDATE_SKILL && HAS_FEAT( ch, HEADSTRONG_FEAT ) )
	max += 2;
  if( ( skill == ESCAPE_ARTIST || skill == SLEIGHT_OF_HAND ) && HAS_FEAT( ch, NIMBLE_FEAT ) )
	max += 2;
  if( skill == SURVIVAL_SKILL && HAS_FEAT( ch, RUGGED_FEAT ) )
	max += 2;
  if( skill == SEARCH_SKILL && HAS_FEAT( ch, SHARP_EYED ) )
	max += 2;
  if( ( skill == ASTROGATE_SKILL || skill == PILOT_SKILL ) && HAS_FEAT( ch, SPACER_FEAT ) )
	max += 2;
  if( skill == BALANCE_SKILL && HAS_FEAT( ch, STEADY_FEAT ) )
 	max += 2;
  if( ( skill == HIDE_SKILL || skill == MOVE_SILENTLY ) && HAS_FEAT( ch, STEALTHY_FEAT ) )
	max += 2;
 
  return max;
}

int fskill_max( CHAR_DATA *ch, int skill )
{
  int maxskill=0;

  maxskill += ( 3 + ch->top_level );

  if( ( skill == FORCE_STRIKE || skill == FORCE_STEALTH ) && HAS_FFEAT( ch, FOCUS_FEAT ) )
	maxskill += 2;
  if( ( skill == AFFECT_MIND || skill == ILLUSION_SKILL ) && HAS_FFEAT( ch, MIND_TRICK ) )
	maxskill += 2;
  if( ( skill == ENHANCE_ABILITY || skill == HEAL_SELF ) && HAS_FFEAT( ch, ATTUNED_FEAT ) )
	maxskill += 2;
  if( ( skill == BATTLEMIND_SKILL || skill == FORCE_DEFENSE ) && HAS_FFEAT( ch, METTLE_FEAT ) )
	maxskill += 2;
  if( ( skill == ENHANCE_SENSES || skill == SEE_FORCE ) && HAS_FFEAT( ch, AWARE_FEAT ) )
	maxskill += 2;
  if( ( skill == FARSEEING_SKILL || skill == TELEPATHY_SKILL ) && HAS_FFEAT( ch, LINK_FEAT ) )
	maxskill += 2;
  
  return maxskill;
}

void do_drainforce( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *vict;
  int save=0;

  if( IS_NPC(ch) )
  	return;
  if( !IS_IMMORTAL(ch) && !HAS_FEAT3( ch, DRAIN_FORCE ) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( ch->position < POS_FIGHTING )
   {
        send_to_char( "&RYou can't do this in your current state.&w&W\n\r", ch );
        return;
   }
  if( argument[0] == '\0' )
   {
	send_to_char( "&RDrain who's Force?&w\n\r", ch );
	return;
   }
  if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
	send_to_char( "&RI don't seem them here.&w\n\r", ch );
	return;
   }
  if( IS_NPC(victim) )
   {
	send_to_char( "&RNot on NPCs&w&W\n\r", ch );
	return;
   }
  if( IS_DROID(victim) )
   {
	send_to_char( "&RDroids don't have the Force.&w&W\n\r", ch );
	return;
   }
  gain_darkpoint( ch );
  save = ( number_range( 1, 20 ) + GET_FORT(victim) );
  if( save >= 20 )
   {
	act( AT_BLOOD, "$n attempts to drain you of Force, but fails.", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "You attempt to drain $N of Force, but fail.", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "$n attempts to drain $N of Force, but fails.", ch, NULL, victim, TO_NOTVICT );
	if( ( vict = who_fighting( ch ) ) == NULL )
        	set_fighting( ch, victim );
	WAIT_STATE( ch, PULSE_PER_SECOND*3 );
	return;
   }
  if( victim->forcepoints > 0 )
   {
  	ch->forcepoints += 1;
	victim->forcepoints -= 1;
	act( AT_BLOOD, "$n drains you of some Force.", ch, NULL, victim, TO_VICT );
	act( AT_BLOOD, "You drain $N of some Force.", ch, NULL, victim, TO_CHAR );
	act( AT_BLOOD, "$n drains $N of some Force.", ch, NULL, victim, TO_NOTVICT );
	if( ( vict = who_fighting( ch ) ) == NULL )
        	set_fighting( ch, victim );
	WAIT_STATE( ch, PULSE_PER_SECOND*3 );
	return;
   }
  act( AT_BLOOD, "You attempt to drain $N of some Force, but find $E has none.", ch, NULL, victim, TO_CHAR );
  act( AT_BLOOD, "$n attemps to drain you of some Force, but finds you have none.", ch, NULL, victim, TO_VICT );
  act( AT_BLOOD, "$n fails to drain $N of some Force.", ch, NULL, victim, TO_NOTVICT );
  if( ( vict = who_fighting( ch ) ) == NULL )
        set_fighting( ch, victim );
  WAIT_STATE(ch, PULSE_PER_SECOND*3 );
  return;
}

void do_sithsorcery( CHAR_DATA *ch, char *argument )
{
  AFFECT_DATA af;
  int bonus=0;
  int save=0;
  int cost=0;

  if( IS_NPC(ch) )
   	return;
  if( ch->position < POS_FIGHTING )
   {
	send_to_char( "&w&WYou can't do this in your current position.\n\r", ch );
	return;
   }
  if( !IS_IMMORTAL(ch) && !HAS_FEAT3( ch, SITH_SORCERY ) )
   {
	send_to_char( "Huh?\n\r", ch );
	return;
   }
  if( IS_AFFECTED( ch, AFF_SORCERY ) )
   {
	send_to_char( "&w&WYou are already affected by Sith Sorcery.\n\r", ch );
	return;
   }
  gain_darkpoint( ch );
  bonus = ( ch->top_level / 3 );
  if( bonus < 1 )
	bonus = 1;
  af.type = gsn_sithsorcery;
  af.duration = ( 5 * ch->top_level );
  af.location = APPLY_HITROLL;
  af.modifier = bonus;
  af.bitvector = AFF_SORCERY;
  affect_to_char(ch, &af);
  af.location = APPLY_FORT;
  affect_to_char( ch, &af );
  af.location = APPLY_REFL;
  affect_to_char( ch, &af );
  af.location = APPLY_WILL;
  affect_to_char( ch, &af );

  save = ( number_range(1,20) + GET_WILL(ch) );
  if( save < ( 10 + bonus ) )
   {
	cost = number_range( 1, 10 );
	ch->max_hit -= cost;
	ch->hit -= cost;
	update_pos( ch );
	act( AT_BLOOD, "You are filled with the power of the Dark Side, but at such a cost.", ch, NULL, NULL, TO_CHAR );
	act( AT_BLOOD, "$n is filled with the power of the Dark Side.", ch, NULL, NULL, TO_NOTVICT );
	WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
	return;
   }
  act( AT_BLOOD, "You are filled with the power of the Dark Side.", ch, NULL, NULL, TO_CHAR );
  act( AT_BLOOD, "$n is filled with the power of the Dark Side.", ch, NULL, NULL, TO_NOTVICT );
  WAIT_STATE( ch, PULSE_PER_SECOND * 2 );
  return;
}
