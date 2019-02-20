#include <stdlib.h>
#include <limits.h>
#include <sys/cdefs.h>
#include <sys/time.h>
#include <math.h>

typedef	int				ch_ret;
typedef	int				obj_ret;

/*
 * Accommodate old non-Ansi compilers.
 */
#if defined(TRADITIONAL)
#define const
#define args( list )			( )
#define DECLARE_DO_FUN( fun )		void fun( )
#define DECLARE_SPEC_FUN( fun )		bool fun( )
#define DECLARE_SPELL_FUN( fun )	ch_ret fun( )
#else
#define args( list )			list
#define DECLARE_DO_FUN( fun )		DO_FUN    fun
#define DECLARE_SPEC_FUN( fun )		SPEC_FUN  fun
#define DECLARE_SPELL_FUN( fun )	SPELL_FUN fun
#endif

/* Stuff from newarena.c */
void show_jack_pot();
void do_game();
int num_in_arena();
void find_game_winner();
void do_end_game();
void start_game();
void silent_end();
void write_fame_list(void);
void load_hall_of_fame(void);

/*
 * Short scalar types.
 * Diavolo reports AIX compiler has bugs with short types.
 */
#if	!defined(FALSE)
#define FALSE	 0
#endif

#if	!defined(TRUE)
#define TRUE	 1
#endif

#if	!defined(BERR)
#define BERR	 255
#endif

#if	defined(_AIX)
#if	!defined(const)
#define const
#endif
typedef int				sh_int;
typedef int				bool;
#define unix
#else
typedef short    int			sh_int;
typedef unsigned char			bool;
#endif

/*
 * Structure types.
 */
typedef struct	affect_data		AFFECT_DATA;
typedef struct  quest_data		QUEST_DATA;
typedef struct	area_data		AREA_DATA;
typedef struct  auction_data            AUCTION_DATA; /* auction data */
typedef struct	ban_data		BAN_DATA;
typedef struct	extracted_char_data	EXTRACT_CHAR_DATA;
typedef struct	bug_data		BUG_DATA;
typedef struct	contract_data		CONTRACT_DATA;
typedef struct	fellow_data		FELLOW_DATA;
typedef struct	char_data		CHAR_DATA;
typedef struct	hunt_hate_fear		HHF_DATA;
typedef struct	fighting_data		FIGHT_DATA;
typedef struct	descriptor_data		DESCRIPTOR_DATA;
typedef struct	exit_data		EXIT_DATA;
typedef struct	extra_descr_data	EXTRA_DESCR_DATA;
typedef struct	help_data		HELP_DATA;
typedef struct	menu_data		MENU_DATA;
typedef struct	mob_index_data		MOB_INDEX_DATA;
typedef struct	note_data		NOTE_DATA;
typedef struct	comment_data		COMMENT_DATA;
typedef struct	board_data		BOARD_DATA;
typedef struct	obj_data		OBJ_DATA;
typedef struct	obj_index_data		OBJ_INDEX_DATA;
typedef struct	pc_data			PC_DATA;
typedef struct	reset_data		RESET_DATA;
typedef struct	map_index_data		MAP_INDEX_DATA;   /* maps */
typedef struct	map_data		MAP_DATA;   /* maps */
typedef struct	room_index_data		ROOM_INDEX_DATA;
typedef struct	shop_data		SHOP_DATA;
typedef struct	repairshop_data		REPAIR_DATA;
typedef struct	time_info_data		TIME_INFO_DATA;
typedef struct	hour_min_sec		HOUR_MIN_SEC;
typedef struct	weather_data		WEATHER_DATA;
typedef struct  bounty_data             BOUNTY_DATA;
typedef struct  blackmarket_data	BMARKET_DATA;
typedef struct  cargo_data		CARGO_DATA;
typedef struct  planet_data		PLANET_DATA;
typedef struct  storeroom		STOREROOM;
typedef struct  guard_data		GUARD_DATA;
typedef struct  space_data              SPACE_DATA;
typedef	struct	clan_data		CLAN_DATA;
typedef struct  jedi_data		JEDI_DATA;
typedef	struct	senate_data		SENATE_DATA;
typedef struct  senate2_data		SENATE2_DATA;
typedef struct  ship_data               SHIP_DATA;
typedef struct  module_data             MODULE_DATA;
typedef struct  hanger_data             HANGER_DATA;
typedef struct  turret_data             TURRET_DATA;
typedef struct  ship_prototype_data     SHIP_PROTOTYPE;
typedef struct  missile_data            MISSILE_DATA;
typedef struct  tourney_data            TOURNEY_DATA;
typedef struct	mob_prog_data		MPROG_DATA;
typedef struct	mob_prog_act_list	MPROG_ACT_LIST;
typedef struct 	mpsleep_data		MPSLEEP_DATA;
typedef	struct	editor_data		EDITOR_DATA;
typedef struct	teleport_data		TELEPORT_DATA;
typedef struct	timer_data		TIMER;
typedef struct  godlist_data		GOD_DATA;
typedef struct	system_data		SYSTEM_DATA;
typedef	struct	smaug_affect		SMAUG_AFF;
typedef struct  who_data                WHO_DATA;
typedef	struct	skill_type		SKILLTYPE;
typedef	struct	social_type		SOCIALTYPE;
typedef	struct	cmd_type		CMDTYPE;
typedef	struct	killed_data		KILLED_DATA;
typedef struct	wizent			WIZENT;
typedef struct	member_data		MEMBER_DATA; /* Individual member data */
typedef struct	member_list		MEMBER_LIST; /* List of members in clan */
typedef struct  membersort_data         MS_DATA;     /* List for sorted roster list */

/*
 * Function types.
 */
typedef	void	DO_FUN		args( ( CHAR_DATA *ch, char *argument ) );
typedef bool	SPEC_FUN	args( ( CHAR_DATA *ch ) );
typedef ch_ret	SPELL_FUN	args( ( int sn, int level, CHAR_DATA *ch, void *vo ) );

#define DUR_CONV	23.333333333333333333333333
#define HIDDEN_TILDE	'*'

#define BV00		(1 <<  0)
#define BV01		(1 <<  1)
#define BV02		(1 <<  2)
#define BV03		(1 <<  3)
#define BV04		(1 <<  4)
#define BV05		(1 <<  5)
#define BV06		(1 <<  6)
#define BV07		(1 <<  7)
#define BV08		(1 <<  8)
#define BV09		(1 <<  9)
#define BV10		(1 << 10)
#define BV11		(1 << 11)
#define BV12		(1 << 12)
#define BV13		(1 << 13)
#define BV14		(1 << 14)
#define BV15		(1 << 15)
#define BV16		(1 << 16)
#define BV17		(1 << 17)
#define BV18		(1 << 18)
#define BV19		(1 << 19)
#define BV20		(1 << 20)
#define BV21		(1 << 21)
#define BV22		(1 << 22)
#define BV23		(1 << 23)
#define BV24		(1 << 24)
#define BV25		(1 << 25)
#define BV26		(1 << 26)
#define BV27		(1 << 27)
#define BV28		(1 << 28)
#define BV29		(1 << 29)
#define BV30		(1 << 30)
#define BV31		(1 << 31)
/* 32 USED! DO NOT ADD MORE! SB */

/*
 * String and memory management parameters.
 */
#define MAX_KEY_HASH		 2048
#define MAX_STRING_LENGTH	 4096  /* buf */
#define MAX_INPUT_LENGTH	 1024  /* arg */
#define MAX_INBUF_SIZE		 1024

#define MAX_MOB_COUNT		10


#define HASHSTR			 /* use string hashing */

#define	MAX_LAYERS		 8	/* maximum clothing layers */
#define MAX_NEST	       100	/* maximum container nesting */

#define MAX_KILLTRACK		20	/* track mob vnums killed */

/*
 * Game parameters.
 * Increase the max'es if you add more of something.
 * Adjust the pulse numbers to suit yourself.
 */
#define MAX_EXP_WORTH	       500000
#define MIN_EXP_WORTH		   25

#define MAX_REXITS		   20	/* Maximum exits allowed in 1 room */
#define MAX_SKILL		  282
#define MAX_NSKILL		   43
#define MAX_FSKILL		   19
#define MAX_STAT		   41
#define MAX_ABILITY		   36
#define BASE_CLASS		    7
#define MAX_RL_ABILITY		    8
#define MAX_RACE		   40
#define MAX_DROID		    6
#define MAX_NPC_RACE		   91
#define MAX_ATMO		    8
#define MAX_STANCE		   13
#define MAX_BLASTERS		    5
#define MAX_LASERS		   10
#define MAX_TURBO		    9
#define MAX_MISSILES		    6
#define MAX_IONS		    3
#define MAX_STAT		   41
#define MAX_LEVEL		   36
#define MAX_PART		   15
#define MAX_SIZE		    9
#define MAX_CLAN		   50
#define MAX_PLANET		   30
#define MAX_SHIP                 1000
#define MAX_SHIP_ROOMS             25
#define MAX_BOUNTY                255
#define MAX_GOV                   255

#define	MAX_HERB		   20

#define LEVEL_HERO		   (MAX_LEVEL - 4)
#define LEVEL_IMMORTAL		   (MAX_LEVEL - 4)
#define LEVEL_SUPREME		   MAX_LEVEL
#define LEVEL_INFINITE		   (MAX_LEVEL - 4)
#define LEVEL_ETERNAL		   (MAX_LEVEL - 4)
#define LEVEL_IMPLEMENTOR	   (MAX_LEVEL)
#define LEVEL_SUB_IMPLEM	   (MAX_LEVEL - 1)
#define LEVEL_ASCENDANT		   (MAX_LEVEL - 2)
#define LEVEL_GREATER		   (MAX_LEVEL - 3)
#define LEVEL_LESSER		   (MAX_LEVEL - 4)
#define LEVEL_RETIRED		   (MAX_LEVEL - 5)
#define LEVEL_GOD		   (MAX_LEVEL - 4)
#define LEVEL_TRUEIMM		   (MAX_LEVEL - 4)
#define LEVEL_DEMI		   (MAX_LEVEL - 4)
#define LEVEL_SAVIOR		   (MAX_LEVEL - 4)
#define LEVEL_CREATOR		   (MAX_LEVEL - 4)
#define LEVEL_ACOLYTE		   (MAX_LEVEL - 4)
#define LEVEL_NEOPHYTE		   (MAX_LEVEL - 4)
#define LEVEL_AVATAR		   (MAX_LEVEL - 5)
#include "pfiles.h"



#define LEVEL_LOG		    LEVEL_LESSER
#define LEVEL_HIGOD		    LEVEL_GOD

#define OBJ_VNUM_DEED		67   /* vnum of deed */

#define PULSE_PER_SECOND	    4
#define PULSE_MINUTE              ( 60 * PULSE_PER_SECOND)
#define PULSE_VIOLENCE		  (  3 * PULSE_PER_SECOND)
#define PULSE_MOBILE		  (  4 * PULSE_PER_SECOND)
#define PULSE_TICK		  ( 70 * PULSE_PER_SECOND)
#define PULSE_AREA		  ( 60 * PULSE_PER_SECOND)
#define PULSE_AUCTION             ( 10 * PULSE_PER_SECOND)
#define PULSE_SPACE               ( 10 * PULSE_PER_SECOND)
#define PULSE_TAXES               ( 60 * PULSE_MINUTE)
#define PULSE_ARENA               (30 * PULSE_PER_SECOND)
#define PULSE_FORCE               PULSE_MINUTE

/*
 * Command logging types.
 */
typedef enum
{
  LOG_NORMAL, LOG_ALWAYS, LOG_NEVER, LOG_BUILD, LOG_HIGH, LOG_COMM, LOG_ALL
} log_types;

/*
 * Return types for move_char, damage, greet_trigger, etc, etc
 * Added by Thoric to get rid of bugs
 */
typedef enum
{
  rNONE, rCHAR_DIED, rVICT_DIED, rBOTH_DIED, rCHAR_QUIT, rVICT_QUIT,
  rBOTH_QUIT, rSPELL_FAILED, rOBJ_SCRAPPED, rOBJ_EATEN, rOBJ_EXPIRED,
  rOBJ_TIMER, rOBJ_SACCED, rOBJ_QUAFFED, rOBJ_USED, rOBJ_EXTRACTED,
  rOBJ_DRUNK, rCHAR_IMMUNE, rVICT_IMMUNE, rCHAR_AND_OBJ_EXTRACTED = 128,
  rERROR = 255
} ret_types;

/* Begin new force defines */
typedef enum
{
  FORCE_INROOM,FORCE_ANYWHERE
} force_locations;

typedef enum
{
  FORCE_SKILL_REFRESH,FORCE_SKILL_FINFO,FORCE_SKILL_STUDENT,FORCE_SKILL_MASTER,FORCE_SKILL_IDENTIFY,
  FORCE_SKILL_PROMOTE,FORCE_SKILL_INSTRUCT,FORCE_SKILL_HEAL,FORCE_SKILL_PROTECT,FORCE_SKILL_SHIELD,
  FORCE_SKILL_WHIRLWIND,FORCE_SKILL_STRIKE,FORCE_SKILL_SQUEEZE,FORCE_SKILL_FORCE_LIGHTNING,
  FORCE_SKILL_DISGUISE,FORCE_SKILL_MAKELIGHTSABER,FORCE_SKILL_PARRY,FORCE_SKILL_FINISH,
  FORCE_SKILL_FHELP,FORCE_SKILL_DUALLIGHTSABER,FORCE_SKILL_REFLECT,FORCE_SKILL_CONVERT,
  FORCE_SKILL_MAKEDUALSABER, FORCE_SKILL_AWARENESS
} force_skills_type;

typedef enum
{
  FORCE_NONCOMBAT,FORCE_COMBAT,FORCE_NORESTRICT
} force_skill_types;

typedef enum
{
  FORCE_NONE,FORCE_APPRENTICE,FORCE_KNIGHT,FORCE_MASTER
} force_level_type;

typedef enum
{
  FORCE_GENERAL,FORCE_JEDI,FORCE_SITH
} force_skills_class;

#define MAX_FORCE_SKILL 24

typedef struct force_skills_struct FORCE_SKILL;

struct force_skills_struct
{
    int type;
    int index;
    char *name;
    char *room_effect[5];
    char *victim_effect[5];
    char *ch_effect[5];
    int cost;
    int control;
    int alter;
    int sense;
    char *code;
    int status;
    int wait_state;
    int disabled;
    int notskill;
    int mastertrain;
    DO_FUN *do_fun;
    FORCE_SKILL *next;
    FORCE_SKILL *prev;
};

FORCE_SKILL *first_force_skill;
FORCE_SKILL *last_force_skill;

#define MAX_FORCE_ALIGN 100
#define MIN_FORCE_ALIGN -100

typedef struct force_help_struct FORCE_HELP;

struct force_help_struct
{
    char *name;
    int status;
    int type;
    char *desc;
    int skill;
    FORCE_HELP *next;
    FORCE_HELP *prev;
};

FORCE_HELP *first_force_help;
FORCE_HELP *last_force_help;

/* End force defines */

/* Echo types for echo_to_all */
#define ECHOTAR_ALL	0
#define ECHOTAR_PC	1
#define ECHOTAR_IMM	2

/* defines for new do_who */
#define WT_MORTAL 0
#define WT_IMM    2
#define WT_AVATAR 1
#define WT_NEWBIE 3

/*
 * do_who output structure -- Narn
 */ 
struct who_data
{
  WHO_DATA *prev;
  WHO_DATA *next;
  char *text;
  int  type;
};

/*
 * Site ban structure.
 */
struct	ban_data
{
    BAN_DATA *	next;
    BAN_DATA *	prev;
    char *	name;
    int		level;
    char *	ban_time;
};


/*
 * Time and weather stuff.
 */
typedef enum
{
  SUN_DARK, SUN_RISE, SUN_LIGHT, SUN_SET
} sun_positions;

typedef enum
{
  SKY_CLOUDLESS, SKY_CLOUDY, SKY_RAINING, SKY_LIGHTNING
} sky_conditions;

struct	time_info_data
{
    int		hour;
    int		day;
    int		month;
    int		year;
};

struct hour_min_sec
{
  int hour;
  int min;
  int sec;
  int manual;
};

struct	weather_data
{
    int		mmhg;
    int		change;
    int		sky;
    int		sunlight;
};


/*
 * Structure used to build wizlist
 */
struct	wizent
{
    WIZENT *		next;
    WIZENT *		last;
    char *		name;
    sh_int		level;
};


/*
 * Connected state for a channel.
 */
typedef enum
{
  CON_PLAYING,		CON_GET_NAME,		CON_GET_OLD_PASSWORD,
  CON_CONFIRM_NEW_NAME,	CON_GET_NEW_PASSWORD,	CON_CONFIRM_NEW_PASSWORD,
  CON_GET_NEW_SEX,	CON_READ_MOTD,
  CON_GET_NEW_RACE,	CON_GET_EMULATION,	CON_EDITING,
  CON_GET_WANT_RIPANSI,	CON_TITLE,		CON_PRESS_ENTER,
  CON_WAIT_1,		CON_WAIT_2,		CON_WAIT_3,
  CON_ACCEPTED,         CON_GET_PKILL,		CON_READ_IMOTD,
  CON_GET_AGE,    	CON_GET_MSP,            CON_GET_NEW_CLASS,
  CON_GET_NEW_SECOND,	CON_ROLL_STATS,		CON_STATS_OK,	
  CON_COPYOVER_RECOVER, CON_GET_PUEBLO, 	CON_GET_HEIGHT, 
  CON_GET_BUILD,	CON_GET_DROID
} connection_types;

/*
 * Character substates
 */
typedef enum
{
  SUB_NONE, SUB_PAUSE, SUB_PERSONAL_DESC, SUB_OBJ_SHORT, SUB_OBJ_LONG,
  SUB_OBJ_EXTRA, SUB_MOB_LONG, SUB_MOB_DESC, SUB_ROOM_DESC, SUB_ROOM_EXTRA,
  SUB_ROOM_EXIT_DESC, SUB_WRITING_NOTE, SUB_MPROG_EDIT, SUB_HELP_EDIT,
  SUB_WRITING_MAP, SUB_PERSONAL_BIO, SUB_REPEATCMD, SUB_RESTRICTED,
  SUB_DEITYDESC,SUB_SHIPDESC,SUB_FORCE_CH0,SUB_FORCE_CH1,SUB_FORCE_CH2,
  SUB_FORCE_CH3,SUB_FORCE_CH4,SUB_FORCE_ROOM0,SUB_FORCE_ROOM1,SUB_FORCE_ROOM2,
  SUB_FORCE_ROOM3,SUB_FORCE_ROOM4,SUB_FORCE_VICTIM0,SUB_FORCE_VICTIM1,SUB_FORCE_VICTIM2,
  SUB_FORCE_VICTIM3,SUB_FORCE_VICTIM4,SUB_FORCE_HELP,
  
  /* timer types ONLY below this point */
  SUB_TIMER_DO_ABORT = 128, SUB_TIMER_CANT_ABORT
} char_substates;

/*
 * Descriptor (channel) structure.
 */
struct	descriptor_data
{
    DESCRIPTOR_DATA *	next;
    DESCRIPTOR_DATA *	prev;
    DESCRIPTOR_DATA *	snoop_by;
    CHAR_DATA *		character;
    CHAR_DATA *		original;
    char *		host;
    char *              hostip;
    int			port;
    int			descriptor;
    sh_int		connected;
    sh_int		idle;
    sh_int		lines;
    sh_int		scrlen;
    bool		fcommand;
    char		inbuf		[MAX_INBUF_SIZE];
    char		incomm		[MAX_INPUT_LENGTH];
    char		inlast		[MAX_INPUT_LENGTH];
    int			repeat;
    char *		outbuf;
    unsigned long	outsize;
    int			outtop;
    char *		pagebuf;
    unsigned long	pagesize;
    int			pagetop;
    char *		pagepoint;
    char		pagecmd;
    char		pagecolor;
    int			auth_inc;
    int			auth_state;
    char		abuf[ 256 ];
    int			auth_fd;
    char *		user;
    int 		atimes;
    int			newstate;
    unsigned char	prevcolor;
};



/*
 * Attribute bonus structures.
 */
struct	str_app_type
{
    sh_int	tohit;
    sh_int	todam;
    sh_int	carry;
    sh_int	wield;
};

struct	int_app_type
{
    sh_int	learn;
};

struct	wis_app_type
{
    sh_int	practice;
};

struct	dex_app_type
{
    sh_int	defensive;
};

struct	con_app_type
{
    sh_int	hitp;
    sh_int	shock;
};

struct	cha_app_type
{
    sh_int	charm;
};

struct  lck_app_type
{
    sh_int	luck;
};

struct  frc_app_type
{
    sh_int	force;
};

/* ability classes */

#define ABILITY_NONE		-1
#define FRINGER_ABILITY		0
#define NOBLE_ABILITY		1
#define SCOUNDREL_ABILITY	2
#define SCOUT_ABILITY		3
#define SOLDIER_ABILITY		4
#define TECH_SPEC_ABILITY	5
#define FORCE_ADEPT_ABILITY	6
#define JEDICONSULAR_ABILITY	7
#define JEDIGUARDIAN_ABILITY	8

#define BOUNTYHUNTER_ABILITY	9
#define CRIMELORD_ABILITY	10
#define DEVOTEE_ABILITY		11
#define MARAUDER_ABILITY	12
#define TROOPER_ABILITY		13
#define JEDIACE_ABILITY		14
#define INVESTIGATOR_ABILITY	15
#define JEDIMASTER_ABILITY	16
#define STARSHIPACE_ABILITY	17
#define ENGINEER_ABILITY	18
#define INFILTRATOR_ABILITY	19
#define PROTECTOR_ABILITY	20
#define MARTIALARTS_ABILITY	21
#define SLICER_ABILITY		22
#define WITCH_ABILITY		23
#define ACOLYTE_ABILITY		24
#define SITHLORD_ABILITY	25
#define SITHWARRIOR_ABILITY	26

#define ANTARIAN_ABILITY	27
#define ENFORCER_ABILITY	28
#define VIGO_ABILITY		29
#define BROKER_ABILITY		30
#define NOBLELORD_ABILITY	31
#define ESPIONAGE_ABILITY	32
#define BERSERKER_ABILITY	33
#define AEROBAT_ABILITY		34
#define MYSTICAGENT_ABILITY	35

/* the races */
#define RACE_ANOMID	        0
#define RACE_ARKANIAN		1
#define RACE_BARTOKK		2
#define RACE_CEREAN		3
#define RACE_CHAGRIAN		4
#define RACE_DASHADE		5
#define RACE_DEFEL		6
#define RACE_DRALL		7
#define RACE_DROID		8
#define RACE_FALLEEN            9
#define RACE_HODIN              10
#define RACE_HUMAN		11
#define RACE_HUTT               12
#define RACE_IKTOTCHI           13
#define RACE_JAWA               14
#define RACE_KELDOR 		15
#define RACE_KLATOOINIAN        16
#define RACE_MIRALUKA           17
#define RACE_MON_CALAMARI       18
#define RACE_MUUN               19
#define RACE_NOGHRI             20
#define RACE_QUARREN            21
#define RACE_RODIAN             22
#define RACE_RYN                23
#define RACE_SKYTRI             24
#define RACE_SULLUSTAN          25
#define RACE_TOGORIAN           26
#define RACE_TOGRUTA            27
#define RACE_TRANDOSHAN         28
#define RACE_TWILEK             29
#define RACE_UBESE              30
#define RACE_UMBARAN            31
#define RACE_VERPINE            32
#define RACE_WEEQUAY            33
#define RACE_WOOKIEE            34
#define RACE_WOOSTOID           35
#define RACE_ZELTRON		36

#define DROID_NONE		0
#define DROID_FIRST		1
#define DROID_SECOND		2
#define DROID_THRID		3
#define DROID_FOURTH		4
#define DROID_FIFTH		5

/* Non-Force Skills */
#define APPRAISE_SKILL		0
#define ASTROGATE_SKILL		1
#define BALANCE_SKILL		2
#define CLIMB_SKILL		3
#define COMPUTER_SKILL		4
#define CRAFT_ARMOR		5
#define CRAFT_BLASTERS		6
#define CRAFT_COMPUTER		7
#define CRAFT_DROID		8
#define CRAFT_DEVICE		9
#define CRAFT_LIGHTSABER	10
#define CRAFT_BOWCASTER		11
#define CRAFT_HEAVY		12
#define CRAFT_HYPERDRIVE	13
#define CRAFT_MEDPAC		14
#define CRAFT_SIMPLE		15
#define CRAFT_SLUG		16
#define CRAFT_MIDSHIP		17
#define CRAFT_FIGHTER		18
#define CRAFT_STARWEAP		19
#define CRAFT_VIBRO		20
#define DEMOLITIONS_SKILL	21
#define DIPLOMACY_SKILL		22
#define DISABLE_DEVICE		23
#define DISGUISE_SKILL		24
#define ESCAPE_ARTIST		25
#define GAMBLE_SKILL		26
#define GATHER_INFO		27
#define HIDE_SKILL		28
#define INTIMIDATE_SKILL	29
#define LISTEN_SKILL		30
#define MOVE_SILENTLY		31
#define PILOT_SKILL		32
#define REPAIR_SKILL		33
#define RIDE_SKILL		34
#define SEARCH_SKILL		35
#define SLEIGHT_OF_HAND		36
#define SPEAK_LANG		37
#define SPOT_SKILL		38
#define SURVIVAL_SKILL		39
#define SWIM_SKILL		40
#define TREAT_INJURY		41
#define TUMBLE_SKILL		42

/* Force Skills */
#define ALCHEMY_SKILL		0
#define AFFECT_MIND		1
#define BATTLEMIND_SKILL	2
#define DRAIN_ENERGY		3
#define ENHANCE_ABILITY		4
#define ENHANCE_SENSES		5
#define FARSEEING_SKILL		6
#define FEAR_SKILL		7
#define FORCE_DEFENSE		8
#define FORCE_GRIP		9
#define FORCE_LIGHTNING	        10
#define FORCE_STEALTH		11
#define FORCE_STRIKE		12
#define HEAL_OTHER		13
#define HEAL_SELF		14
#define ILLUSION_SKILL		15
#define MOVE_OBJECT		16
#define SEE_FORCE		17
#define TELEPATHY_SKILL		18

/* Feats */
#define ALERTNESS_FEAT		BV00
#define AMBIDEXTERITY_FEAT	BV01
#define ATHLETIC_FEAT		BV02
#define BLIND_FIGHT		BV03
#define CAUTIOUS_FEAT		BV04
#define DODGE_FEAT		BV05
#define FAME_FEAT		BV06
#define FORCE_SENSITIVE		BV07
#define FRIGHTFUL_PRESENSE	BV08
#define GEARHEAD_FEAT		BV09
#define GREAT_FORTITUDE		BV10
#define HEADSTRONG_FEAT		BV11
#define IMPROVED_DISARM		BV12
#define IMPROVED_TRIP		BV13
#define IMPROVED_TWO_WEAPON	BV14
#define INFAMY_FEAT		BV15
#define INFLUENCE_FEAT		BV16
#define IRON_WILL		BV17
#define LIGHTNING_REFLEXES	BV18
#define LOW_PROFILE		BV19
#define NIMBLE_FEAT		BV20
#define QUICKNESS_FEAT		BV21
#define RUGGED_FEAT		BV22
#define SHARP_EYED		BV23
#define SKILL_EMPHASIS		BV24
#define SPACER_FEAT		BV25
#define STARSHIP_DODGE		BV26
#define FIGHTER_OPS		BV27
#define MIDSHIP_OPS		BV28
#define CAPITAL_OPS		BV29
#define STEADY_FEAT		BV30
#define STEALTHY_FEAT		BV31

/* More Feats */
#define TRACK_FEAT		BV00
#define TWO_WEAP_FIGHTING	BV01
#define WEAP_PROF_PISTOLS	BV02
#define WEAP_PROF_RIFLES	BV03
#define WEAP_PROF_HEAVY		BV04
#define WEAP_PROF_PRIMITIVE	BV05
#define WEAP_PROF_SIMPLE	BV06
#define WEAP_PROF_VIBRO		BV07
#define WEAP_PROF_LIGHTSABER	BV08
#define WEAP_PROF_BOWCASTER	BV09
#define IMP_CRITICAL_PISTOLS	BV10
#define IMP_CRITICAL_RIFLES	BV11
#define IMP_CRITICAL_HEAVY	BV12
#define IMP_CRITICAL_PRIMITIVE	BV13
#define IMP_CRITICAL_SIMPLE	BV14
#define IMP_CRITICAL_VIBRO	BV15
#define IMP_CRITICAL_LIGHTSABER BV16
#define IMP_CRITICAL_BOWCASTER	BV17
#define ARMOR_LIGHT		BV18
#define ARMOR_MEDIUM		BV19
#define ARMOR_HEAVY		BV20
#define ARMOR_POWERED		BV21
#define MARTIAL_ARTS		BV22
#define DEF_MARTIAL_ARTS	BV23
#define IMP_MARTIAL_ARTS	BV24
#define ADV_MARTIAL_ARTS	BV25
#define WEAP_PROF_FORCEPIKE	BV26
#define IMP_CRITICAL_FORCEPIKE	BV27
#define BARTER_FEAT		BV28
#define ILLICIT_BARTER		BV29
#define TRAILBLAZING_FEAT	BV30
#define UNCANNY_DODGE		BV31

/* More Feats */
#define COVERT_MOVEMENT		BV00
#define UNCANNY_HIDE		BV01
#define HARMS_WAY		BV02
#define HALF_BLASTER		BV03
#define FULL_BLASTER		BV04
#define GRAND_MASTER		BV05
#define AMBUSH_FEAT		BV06
#define TEAMWORK_FEAT		BV07
#define PATRON_FEAT		BV08
#define TRANSPLANT_FEAT		BV09
#define AERIAL_EVASION		BV10

/* Force Feats */
#define ALTER_FEAT		BV00
#define ATTUNED_FEAT		BV01
#define AWARE_FEAT		BV02
#define CONTROL_FEAT		BV03
#define DISSIPATE_ENERGY	BV04
#define FOCUS_FEAT		BV05
#define FORCE_FLIGHT		BV06
#define FORCE_MIND		BV07
#define FORCE_WHIRLWIND		BV08
#define IMP_FORCE_MIND		BV09
#define KNIGHT_DEFENSE		BV10
#define KNIGHT_MIND		BV11
#define LIGHTSABER_DEFENSE	BV12
#define LINK_FEAT		BV13
#define MALEVOLENT_FEAT		BV14
#define MASTER_DEFENSE		BV15
#define MASTER_MIND		BV16
#define METTLE_FEAT		BV17
#define MIND_TRICK		BV18
#define RAGE_FEAT		BV19
#define SENSE_FEAT		BV20
#define SPIDER_WALK		BV21
#define SUMMON_STORM		BV22
#define ENSHROUD_FEAT		BV23
#define SITH_SORCERY		BV24
#define DRAIN_FORCE		BV25
#define HATRED_FEAT		BV26
#define POINT_BLANK		BV27
#define PRECISE_SHOT		BV28
#define FAR_SHOT		BV29
#define RAPID_SHOT		BV30

/* Languages */
#define LANG_BASIC      	BV00
#define LANG_ARKANIAN	        BV01  
#define LANG_BINARY		BV02
#define LANG_CEREAN	        BV03  
#define LANG_CHAGRI	        BV04  
#define LANG_DASHADI	        BV05  
#define LANG_DEFEL		BV06 
#define LANG_DOSH		BV07
#define LANG_DRALLISH	        BV08 
#define LANG_FALLEEN	        BV09 
#define LANG_HODIN		BV10 
#define LANG_HUTTESE	        BV11 
#define LANG_IKTOTCHESE		BV12 
#define LANG_JAWA	        BV13 
#define LANG_KELDOR		BV14 
#define LANG_LEKKU		BV15
#define LANG_MIRALUKESE         BV16 
#define LANG_MON_CALAMARIAN     BV17 
#define LANG_MUUN		BV18 
#define LANG_NOGHRI		BV19 
#define LANG_RODESE	        BV20 
#define LANG_RYN		BV21 
#define LANG_SHYRIIWOOK		BV22
#define LANG_SKYTRIC		BV23
#define LANG_SRILUURIAN		BV24 
#define LANG_SULLUSTESE		BV25
#define LANG_TOGORIAN           BV26
#define LANG_TOGRUTI	        BV27
#define LANG_UBESE		BV28
#define LANG_UMBARESE	        BV29
#define LANG_VERPINE	        BV30
#define LANG_CLAN		BV31
#define LANG_UNKNOWN        	0
#define VALID_LANGS	( LANG_ARKANIAN | LANG_BASIC | LANG_BINARY | LANG_CEREAN | LANG_CHAGRI \
			 | LANG_DASHADI | LANG_DEFEL | LANG_DRALLISH | LANG_FALLEEN | LANG_HODIN \
			 | LANG_HUTTESE | LANG_IKTOTCHESE | LANG_JAWA | LANG_KELDOR | LANG_MIRALUKESE \
			 | LANG_MON_CALAMARIAN | LANG_MUUN | LANG_NOGHRI | LANG_RODESE | LANG_RYN \
			 | LANG_SKYTRIC | LANG_SULLUSTESE | LANG_TOGORIAN | LANG_TOGRUTI | LANG_DOSH \
			 | LANG_LEKKU | LANG_UBESE | LANG_UMBARESE | LANG_VERPINE | LANG_SRILUURIAN \
			 | LANG_SHYRIIWOOK | LANG_CLAN )

/* Stances */
#define STANCE_NONE		0
#define	ECHANI_STANCE		1
#define KTARA_STANCE		2
#define KTHRI_STANCE		3
#define STAVA_STANCE		4
#define WRRUUSHI_STANCE		5
#define FORM1_STANCE		6
#define FORM2_STANCE		7
#define FORM3_STANCE		8
#define FORM4_STANCE		9
#define FORM5_STANCE		10
#define FORM6_STANCE		11
#define FORM7_STANCE		12

/* Stance Bit Vectors */
#define ECHANI_BASIC		BV00
#define ECHANI_EXPERTISE	BV01
#define ECHANI_MASTERY		BV02
#define KTARA_BASIC		BV03
#define KTARA_EXPERTISE		BV04
#define KTARA_MASTERY		BV05
#define KTHRI_BASIC		BV06
#define KTHRI_EXPERTISE		BV07
#define KTHRI_MASTERY		BV08
#define STAVA_BASIC		BV09
#define STAVA_EXPERTISE		BV10
#define STAVA_MASTERY		BV11
#define WRRUUSHI_BASIC		BV12
#define WRRUUSHI_EXPERTISE	BV13
#define WRRUUSHI_MASTERY	BV14
#define FORM1_MASTERY		BV15
#define FORM2_MASTERY		BV16
#define FORM3_MASTERY		BV17
#define FORM4_MASTERY		BV18
#define FORM5_MASTERY		BV19
#define FORM6_MASTERY		BV20
#define FORM7_MASTERY		BV21

/* Droid Feats */
#define ADV_MARTIAL_PROGRAMMING	BV00
#define DEF_MARTIAL_PROGRAMMING	BV01
#define IMP_MARTIAL_PROGRAMMING	BV02
#define MARTIAL_PROGRAMMING	BV03
#define ARMOR_LIGHT_DROID	BV04
#define ARMOR_MEDIUM_DROID	BV05
#define ARMOR_HEAVY_DROID	BV06
#define DROID_COMLINK		BV07
#define DIAGNOSTICS_PACKAGE	BV08
#define ELECTROSHOCK_PROBE	BV09
#define FLAMETHROWER_FEAT	BV10
#define INTERNAL_STORAGE	BV11
#define LOCKED_ACCESS		BV12
#define MAGNETIC_FEET		BV13
#define RUST_INHIBITOR		BV14
#define SELFDESTRUCT_SYSTEM	BV15
#define IMPROVED_SENSOR		BV16
#define INFRARED_VISION		BV17
#define MOTION_SENSORS		BV18
#define SONIC_SENSORS		BV19
#define DEGREE_VISION		BV20
#define SHIELD_GENERATOR	BV21
#define VOCABULATOR_FEAT	BV22
#define COMLINK_FEAT		BV23

/* Cybernetic bits */
#define CYBER_IMP_HAND		  BV01
#define CYBER_IMP_ARM		  BV02
#define CYBER_ADV_HAND		  BV03
#define CYBER_ADV_ARM		  BV04
#define CYBER_BASE_EYE		  BV05
#define CYBER_IR_EYE		  BV06
#define CYBER_OPTIC_EYE		  BV07
#define CYBER_TARGET_EYE	  BV08
#define CYBER_COMLINK		  BV09
#define CYBER_SKELETAL		  BV10
#define CYBER_TREMOR		  BV11
#define CYBER_AJ6		  BV12
#define CYBER_SENSORY		  BV13

#define CAF_IMP_ARM		1
#define CAF_ADV_ARM		2
#define CAF_IMP_HAND		3
#define CAF_ADV_HAND		4
#define CAF_IR_EYE		5
#define CAF_OPTIC_EYE		6
#define CAF_TARGET_EYE		7
#define CAF_SKELETAL		8
#define CAF_AJ6			9
#define CAF_COMLINK		10
#define CAF_SENSOR		11
#define CAF_TREMOR		12

/* Master / Trained */
#define NO_MASTER		0
#define HAS_MASTER		1
#define NOT_TRAINED		0
#define HAS_TRAINED		1
#define NO_INVEST		0
#define YES_INVEST		1

/* Force Status */
#define STATUS_NONE		0
#define STATUS_PADAWAN		1
#define STATUS_JEDI_KNIGHT	2
#define STATUS_JEDI_MASTER	3
#define STATUS_DARK_PADAWAN	4
#define STATUS_DARK_KNIGHT	5
#define STATUS_DARK_MASTER	6
#define STATUS_SITH_APPRENTICE	7
#define STATUS_SITH_LORD	8
#define STATUS_SITH_MASTER	9
#define STATUS_FORCE_SENSITIVE  10

/* TO types for act. */
#define TO_ROOM		    0
#define TO_NOTVICT	    1
#define TO_VICT		    2
#define TO_CHAR		    3
#define TO_MUD		    4

/*
 * Real action "TYPES" for act.
 */
#define AT_BLACK	    0
#define AT_BLOOD	    1
#define AT_DGREEN           2
#define AT_ORANGE	    3
#define AT_DBLUE	    4
#define AT_PURPLE	    5
#define AT_CYAN	  	    6
#define AT_GREY		    7
#define AT_DGREY	    8
#define AT_RED		    9
#define AT_GREEN	   10
#define AT_YELLOW	   11
#define AT_BLUE		   12
#define AT_PINK		   13
#define AT_LBLUE	   14
#define AT_WHITE	   15
#define AT_BLINK	   16
#define AT_PLAIN	   AT_GREY
#define AT_ACTION	   AT_GREY
#define AT_SAY		   AT_LBLUE
#define AT_GOSSIP	   AT_LBLUE
#define AT_YELL	           AT_WHITE
#define AT_TELL		   AT_BLUE
#define AT_HIT		   AT_WHITE
#define AT_HITME	   AT_YELLOW
#define AT_OOC             AT_YELLOW
#define AT_IMMORT	   AT_WHITE
#define AT_AVATAR	   AT_BLUE
#define AT_HURT		   AT_RED
#define AT_FALLING	   AT_WHITE + AT_BLINK
#define AT_DANGER	   AT_RED + AT_BLINK
#define AT_MAGIC	   AT_BLUE
#define AT_CONSIDER	   AT_GREY
#define AT_REPORT	   AT_GREY
#define AT_POISON	   AT_GREEN
#define AT_SOCIAL	   AT_CYAN
#define AT_DYING	   AT_YELLOW
#define AT_DEAD		   AT_RED
#define AT_SKILL	   AT_GREEN
#define AT_CARNAGE	   AT_BLOOD
#define AT_DAMAGE	   AT_WHITE
#define AT_FLEE		   AT_YELLOW
#define AT_RMNAME	   AT_WHITE
#define AT_RMDESC	   AT_GREY
#define AT_OBJECT	   AT_GREEN
#define AT_PERSON	   AT_PINK
#define AT_LIST		   AT_BLUE
#define AT_BYE		   AT_GREEN
#define AT_GOLD		   AT_YELLOW
#define AT_GTELL	   AT_BLUE
#define AT_NOTE		   AT_GREEN
#define AT_HUNGRY	   AT_ORANGE
#define AT_THIRSTY	   AT_BLUE
#define	AT_FIRE		   AT_RED
#define AT_SOBER	   AT_WHITE
#define AT_WEAROFF	   AT_YELLOW
#define AT_EXITS	   AT_WHITE
#define AT_SCORE	   AT_LBLUE
#define AT_RESET	   AT_DGREEN
#define AT_LOG		   AT_PURPLE
#define AT_DIEMSG	   AT_WHITE
#define AT_WARTALK         AT_RED
#define AT_SHIP            AT_PINK
#define AT_CLAN            AT_PINK

#define INIT_WEAPON_CONDITION    12
#define MAX_ITEM_IMPACT		 30

/*
 * Help table types.
 */
struct	help_data
{
    HELP_DATA *	next;
    HELP_DATA * prev;
    sh_int	level;
    char *	keyword;
    char *	text;
};



/*
 * Shop types.
 */
#define MAX_TRADE	 5

struct	shop_data
{
    SHOP_DATA *	next;			/* Next shop in list		*/
    SHOP_DATA * prev;			/* Previous shop in list	*/
    int		keeper;			/* Vnum of shop keeper mob	*/
    sh_int	buy_type [MAX_TRADE];	/* Item types shop will buy	*/
    sh_int	profit_buy;		/* Cost multiplier for buying	*/
    sh_int	profit_sell;		/* Cost multiplier for selling	*/
    sh_int	open_hour;		/* First opening hour		*/
    sh_int	close_hour;		/* First closing hour		*/
};

#define MAX_FIX		3
#define SHOP_FIX	1
#define SHOP_RECHARGE	2

struct	repairshop_data
{
    REPAIR_DATA * next;			/* Next shop in list		*/
    REPAIR_DATA * prev;			/* Previous shop in list	*/
    int		  keeper;		/* Vnum of shop keeper mob	*/
    sh_int	  fix_type [MAX_FIX];	/* Item types shop will fix	*/
    sh_int	  profit_fix;		/* Cost multiplier for fixing	*/
    sh_int	  shop_type;		/* Repair shop type		*/
    sh_int	  open_hour;		/* First opening hour		*/
    sh_int	  close_hour;		/* First closing hour		*/
};


/* Mob program structures */

/* Mob program structures and defines */ 
/* Moved these defines here from mud_prog.c as I need them -rkb */ 
#define MAX_IFS 20 /* should always be generous */ 
#define IN_IF 0 
#define IN_ELSE 1 
#define DO_IF 2 
#define DO_ELSE 3 
 
#define MAX_PROG_NEST 20 

struct  act_prog_data
{
    struct act_prog_data *next;
    void *vo;
};

struct	mob_prog_act_list
{
    MPROG_ACT_LIST * next;
    char *	     buf;
    CHAR_DATA *      ch;
    OBJ_DATA *	     obj;
    void *	     vo;
};

struct	mob_prog_data
{
    MPROG_DATA * next;
    int		 type;
    bool	 triggered;
    int		 resetdelay;
    char *	 arglist;
    char *	 comlist;
};

/* Used to store sleeping mud progs. -rkb */ 
typedef enum {MP_MOB, MP_ROOM, MP_OBJ} mp_types; 
struct mpsleep_data 
{ 
 MPSLEEP_DATA * next; 
 MPSLEEP_DATA * prev; 
 
 int timer; /* Pulses to sleep */ 
 mp_types type; /* Mob, Room or Obj prog */ 
 ROOM_INDEX_DATA*room; /* Room when type is MP_ROOM */ 
 
 /* mprog_driver state variables */ 
 int ignorelevel; 
 int iflevel; 
 bool ifstate[MAX_IFS][DO_ELSE]; 
 
 /* mprog_driver arguments */ 
 char * com_list; 
 CHAR_DATA * mob; 
 CHAR_DATA * actor; 
 OBJ_DATA * obj; 
 void * vo; 
 bool single_step; 
}; 
 
 
bool	MOBtrigger;

struct  card_type
{
    int		value;
};

struct	bonus_type
{
    int		req;
};

struct  exp_type
{
    int		exp;
};

struct  stat_type
{
    sh_int	mod;
};

/* race dedicated stuff */
struct	race_type
{
    char 	race_name	[40];	/* Race name			*/
    int		affected;		/* Default affect bitvectors	*/
    sh_int	str_plus;		/* Str bonus/penalty		*/
    sh_int	dex_plus;		/* Dex      "			*/
    sh_int	con_plus;		/* Wis      "			*/
    sh_int	int_plus;		/* Int      "			*/
    sh_int	wis_plus;		/* Con      "			*/
    sh_int	cha_plus;		/* Cha      "			*/
    int         language;               /* Default racial language      */
};

struct droid_type
{
    char	droid_degree [6];
    sh_int	str_plus;
    sh_int	dex_plus;
    sh_int	con_plus;
    sh_int	int_plus;
    sh_int	wis_plus;
    sh_int	cha_plus;
};

typedef enum {
CLAN_PLAIN, CLAN_CRIME, CLAN_GUILD, CLAN_SUBCLAN, CLAN_CORPORATION
} clan_types;


typedef enum {PLAYER_SHIP, MOB_SHIP, SHIP_HUTT, SHIP_REPUBLIC, SHIP_JEDI, SHIP_SITH } ship_types;
typedef enum {SHIP_DOCKED, SHIP_READY, SHIP_BUSY, SHIP_BUSY_2, SHIP_BUSY_3, SHIP_REFUEL,
              SHIP_LAUNCH, SHIP_LAUNCH_2, SHIP_LAND, SHIP_LAND_2, SHIP_HYPERSPACE, SHIP_DISABLED, SHIP_FLYING, SHIP_DOCKED2, SHIP_DOCKED3,
	      SHIP_IS_DOCKED, SHIP_UNDOCK, SHIP_UNDOCK2, SHIP_UNDOCK3} ship_states;
typedef enum {MISSILE_READY, MISSILE_FIRED, MISSILE_RELOAD, MISSILE_RELOAD_2, MISSILE_DAMAGED} missile_states;

typedef enum {LAND_VEHICLE, SHIP_FIGHTER, SHIP_MIDSHIP, SHIP_CAPITAL, SHIP_SPACE_STATION} ship_classes;

typedef enum {CONCUSSION_MISSILE, ASSAULT_MISSILE, ENERGY_TORPEDO, PROTON_TORPEDO} missile_types;

#define LASER_DAMAGED    -1
#define LASER_READY       0

struct  planet_data
{
    PLANET_DATA    * next;
    PLANET_DATA    * prev;
    PLANET_DATA    * next_in_system;
    PLANET_DATA    * prev_in_system;
    AREA_DATA	   * next_in_area;
    AREA_DATA	   * prev_in_area;
    GUARD_DATA     * first_guard;
    AREA_DATA      * first_area;
    AREA_DATA      * last_area;    
    GUARD_DATA     * last_guard;
    SPACE_DATA     * starsystem;
    AREA_DATA	   * area;
    char	   * governor;
    char	   * name;
    char           * filename;
    CLAN_DATA      * governed_by;
    int 	     population;
    float            pop_support;
    int		     sector;
    int 	     x, y, z;
    int              size;
    int 	     flags;    
    sh_int	     embargo[MAX_PLANET];
    long             base_value;    
    int		     taxes;
    int		     citysize;
    int              wilderness;
    int		     wildlife;
    int		     farmland;
    int		     barracks;
    int		     controls;
    int		     atmosphere_type;
};

#define PLANET_CORUSCANT	BV00

struct cargo_data
{
  int cargo0;
  int cargo1;
  int cargo2;
  int cargo3;
  int cargo4;
  int cargo5;
  int cargo6;
  int cargo7;
  int cargo8;
  int cargo9;
  int orgcargo0;
  int orgcargo1;
  int orgcargo2;
  int orgcargo3;
  int orgcargo4;
  int orgcargo5;
  int orgcargo6;
  int orgcargo7;
  int orgcargo8;
  int orgcargo9;
  int price0;
  int price1;
  int price2;
  int price3;
  int price4;
  int price5;
  int price6;
  int price7;
  int price8;
  int price9;
  bool smug;
};

struct space_data
{
    SPACE_DATA * next;
    SPACE_DATA * prev;
    SHIP_DATA  * first_ship;
    SHIP_DATA  * last_ship;
    MISSILE_DATA  * first_missile;
    MISSILE_DATA  * last_missile;
    PLANET_DATA * first_planet;
    PLANET_DATA * last_planet;
    char       * filename;
    char       * name;
    char       * star1;
    char       * star2;
    char       * planet1;
    char       * planet2;
    char       * planet3;
    char       * planet4;
    char       * planet5;
    char       * planet6;
    char       * planet7;
    char       * planet8;
    char       * planet9;
    char       * planet10;
    char       * planet11;
    char       * planet12;
    char       * planet13;
    char       * planet14;
    char       * planet15;
    char       * planet16;
    char       * planet17;
    char       * planet18;
    char       * planet19;
    char       * planet20;
    char       * planet21;
    char       * planet22;
    char       * planet23;
    char       * planet24;
    char       * planet25;
    char       * location1a;
    char       * location2a;
    char       * location3a;
    char       * location1b;
    char       * location2b;
    char       * location3b;
    char       * location1c;
    char       * location2c;
    char       * location3c;
    int          xpos;
    int          ypos;
    int		 zpos;
    int          s1x;        
    int          s1y;
    int          s1z;
    int          s2x;
    int          s2y;
    int          s2z;
    int          doc1a;
    int          doc2a;
    int		 doc3a;
    int          doc1b;
    int          doc2b;
    int		 doc3b;
    int          doc1c;
    int          doc2c;
    int		 doc3c;
    bool         seca;
    bool         secb;
    bool	 secc;    
    int          p1x;
    bool	 trainer;    
    int          p1y;
    int          p1z;
    int          p2x;
    int          p2y;
    int          p2z;
    int          p3x;
    int          p3y;    
    int          p3z;
    int          p4x;
    int          p4y;
    int          p4z;
    int          p5x;
    int          p5y;
    int          p5z;
    int          p6x;
    int          p6y;
    int          p6z;
    int          p7x;
    int          p7y;
    int          p7z;
    int          p8x;
    int          p8y;
    int          p8z;
    int          p9x;
    int          p9y;
    int          p9z;
    int          p10x;
    int          p10y;
    int          p10z;
    int          p11x;
    int          p11y;
    int          p11z;
    int          p12x;
    int          p12y;
    int          p12z;
    int          p13x;
    int          p13y;
    int          p13z;
    int          p14x;
    int          p14y;
    int          p14z;
    int          p15x;
    int          p15y;
    int          p15z;
    int          p16x;
    int          p16y;
    int          p16z;
    int          p17x;
    int          p17y;
    int          p17z;
    int          p18x;
    int          p18y;
    int          p18z;
    int          p19x;
    int          p19y;
    int          p19z;
    int          p20x;
    int          p20y;
    int          p20z;
    int          p21x;
    int          p21y;
    int          p21z;
    int          p22x;
    int          p22y;
    int          p22z;
    int          p23x;
    int          p23y;
    int          p23z;
    int          p24x;
    int          p24y;
    int          p24z;
    int          p25x;
    int          p25y;
    int          p25z;
    int          gravitys1;
    int          gravitys2;
    int          gravityp1;
    int          gravityp2;
    int          gravityp3;
    int		 gravityp4;
    int		 gravityp5;
    int		 gravityp6;
    int		 gravityp7;
    int		 gravityp8;
    int		 gravityp9;
    int		 gravityp10;
    int		 gravityp11;
    int		 gravityp12;
    int		 gravityp13;
    int		 gravityp14;
    int		 gravityp15;
    int		 gravityp16;
    int		 gravityp17;
    int		 gravityp18;
    int		 gravityp19;
    int		 gravityp20;
    int		 gravityp21;
    int		 gravityp22;
    int		 gravityp23;
    int		 gravityp24;
    int		 gravityp25;
    int          p1_low;
    int          p1_high;
    int          p2_low;
    int          p2_high;
    int          p3_low;
    int          p3_high;
    int          p4_low;
    int          p4_high;
    int          p5_low;
    int          p5_high;
    int          p6_low;
    int          p6_high;
    int          p7_low;
    int          p7_high;
    int          p8_low;
    int          p8_high;
    int          p9_low;
    int          p9_high;
    int          p10_low;
    int          p10_high;
    int          p11_low;
    int          p11_high;
    int          p12_low;
    int          p12_high;
    int          p13_low;
    int          p13_high;
    int          p14_low;
    int          p14_high;
    int          p15_low;
    int          p15_high;
    int          p16_low;
    int          p16_high;
    int          p17_low;
    int          p17_high;
    int          p18_low;
    int          p18_high;
    int          p19_low;
    int          p19_high;
    int          p20_low;
    int          p20_high;
    int          p21_low;
    int          p21_high;
    int          p22_low;
    int          p22_high;
    int          p23_low;
    int          p23_high;
    int          p24_low;
    int          p24_high;
    int          p25_low;
    int          p25_high;
    int          crash;
};

struct  bounty_data
{
    BOUNTY_DATA * next;
    BOUNTY_DATA * prev;
    char * 	  target;
    long int      amount;
};

struct  blackmarket_data
{
	BMARKET_DATA * next;
	BMARKET_DATA * prev;
	char *filename;
	int quantity;
};

struct guard_data
{
    GUARD_DATA * next;
    GUARD_DATA * prev;
    GUARD_DATA * next_on_planet;
    GUARD_DATA * prev_on_planet;
    CHAR_DATA  * mob;
    ROOM_INDEX_DATA * reset_loc;
    PLANET_DATA * planet;
};

struct  senate_data
{
    SENATE_DATA * next;
    SENATE_DATA * prev;
    char * 	  name;
};

#define PLANET_NOCAPTURE  BV00

struct	senate2_data
{
    SENATE2_DATA * next;		/* next clan in list		*/
    SENATE2_DATA * prev;		/* previous clan in list	*/
    SENATE2_DATA * first_senate;
    SENATE2_DATA * last_senate;
    SENATE2_DATA * next_subclan;
    SENATE2_DATA * prev_subclan;
    SENATE2_DATA * first_subclan;
    SENATE2_DATA * last_subclan;
    SENATE2_DATA * mainclan;   
    char *	acro;
    char *	filename;	/* Clan filename			*/
    char *	shortname;	/* Clan shortname - used in member lists*/
    char *	name;		/* Clan name				*/
    char *	description;	/* A brief description of the clan	*/
    char *	leader;		/* Head clan leader			*/
    char *	number1;	/* First officer			*/
    char *	number2;	/* Second officer			*/
    int		pkills;		/* Number of pkills on behalf of clan	*/
    int		pdeaths;	/* Number of pkills against clan	*/
    int		mkills;		/* Number of mkills on behalf of clan	*/
    int		mdeaths;	/* Number of clan deaths due to mobs	*/
    sh_int	clan_type;	/* See clan type defines		*/
    char *	atwar;		/* Clan name				*/
    char *      ally;           /* Clan name				*/
    sh_int	members;	/* Number of clan members		*/
    int		board;		/* Vnum of clan board			*/
    int		storeroom;	/* Vnum of clan's store room		*/
    int		guard1;		/* Vnum of clan guard type 1		*/
    int		guard2;		/* Vnum of clan guard type 2		*/
    int         patrol1;        /* vnum of patrol */
    int         patrol2;	/* vnum of patrol */
    int         trooper1;	/* vnum of reinforcements */
    int         trooper2;	/* vnum of elite troopers */
    long int    funds;
    int         spacecraft;
    int		troops;
    int		vehicles;
    int         jail;
    char      * tmpstr;
};


struct	jedi_data
{
    JEDI_DATA * next;		/* next clan in list			*/
    JEDI_DATA * prev;		/* previous clan in list		*/
    JEDI_DATA * next_subclan;
    JEDI_DATA * prev_subclan;
    JEDI_DATA * first_subclan;
    JEDI_DATA * last_subclan;
    JEDI_DATA * mainclan;   
    char *	acro;
    char *	filename;	/* Clan filename			*/
    char *	shortname;	/* Clan shortname - used in member lists*/
    char *	name;		/* Clan name				*/
    char *	description;	/* A brief description of the clan	*/
    char *	leader;		/* Head clan leader			*/
    char *	number1;	/* First officer			*/
    char *	number2;	/* Second officer			*/
    int		pkills;		/* Number of pkills on behalf of clan	*/
    int		pdeaths;	/* Number of pkills against clan	*/
    int		mkills;		/* Number of mkills on behalf of clan	*/
    int		mdeaths;	/* Number of clan deaths due to mobs	*/
    sh_int	clan_type;	/* See clan type defines		*/
    char *	atwar;		/* Clan name				*/
    sh_int	members;	/* Number of clan members		*/
    int		board;		/* Vnum of clan board			*/
    int		storeroom;	/* Vnum of clan's store room		*/
    int		guard1;		/* Vnum of clan guard type 1		*/
    int		guard2;		/* Vnum of clan guard type 2		*/
    int         patrol1;        /* vnum of patrol */
    int         patrol2;	/* vnum of patrol */
    int         trooper1;	/* vnum of reinforcements */
    int         trooper2;	/* vnum of elite troopers */
    long int    funds;
    int         spacecraft;
    int		troops;
    int		vehicles;
    int         jail;
    char      * tmpstr;
};

struct	clan_data
{
    CLAN_DATA * next;		/* next clan in list			*/
    CLAN_DATA * prev;		/* previous clan in list		*/
    CLAN_DATA * next_subclan;
    CLAN_DATA * prev_subclan;
    CLAN_DATA * first_subclan;
    CLAN_DATA * last_subclan;
    CLAN_DATA * mainclan;
    char *	acro;
    char *	filename;	/* Clan filename			*/
    char *	shortname;	/* Clan shortname - used in member lists*/
    char *	name;		/* Clan name				*/
    char *	description;	/* A brief description of the clan	*/
    char *	leader;		/* Head clan leader			*/
    char *	number1;	/* First officer			*/
    char *	number2;	/* Second officer			*/
    int		pkills;		/* Number of pkills on behalf of clan	*/
    int		pdeaths;	/* Number of pkills against clan	*/
    int		mkills;		/* Number of mkills on behalf of clan	*/
    int		mdeaths;	/* Number of clan deaths due to mobs	*/
    sh_int	clan_type;	/* See clan type defines		*/
    char *	atwar;		/* Clan name				*/
    sh_int	members;	/* Number of clan members		*/
    int		board;		/* Vnum of clan board			*/
    int		storeroom;	/* Vnum of clan's store room		*/
    int		guard1;		/* Vnum of clan guard type 1		*/
    int		guard2;		/* Vnum of clan guard type 2		*/
    int         patrol1;        /* vnum of patrol */
    int         patrol2;	/* vnum of patrol */
    int         trooper1;	/* vnum of reinforcements */
    int         trooper2;	/* vnum of elite troopers */
    sh_int	clan_bonus;
    int		rppoints;
    int		bonus;
    sh_int	level;
    long	experience;
    long int    funds;
    int         spacecraft;
    int		troops;
    int		vehicles;
    int         jail;
    char      * tmpstr;
};

struct ship_prototype_data
{
    SHIP_PROTOTYPE * next;
    SHIP_PROTOTYPE * prev;
    char *      filename;
    char *      name;
    char *      description;
    sh_int      class;
    sh_int      model;
    sh_int      hyperspeed;
    sh_int      realspeed;
    sh_int      maxbombs;
    sh_int      maxmissiles;
    sh_int	maxtorpedos;
    sh_int	maxrockets;
    int		max_modules;    // This is used to set what the maximum number of upgrade modules is. If none is set 10 is.
    sh_int      lasers;
    CLAN_DATA 	*clan;		// This is used to limit certain prototypes to a specific clan.
    sh_int      tractorbeam;
    sh_int      manuever;
    int         weight;
    int         maxenergy;
    int         maxshield;
    int         maxhull;
    sh_int      maxchaff;
    sh_int      maxmods;
};

struct turret_data
{
    TURRET_DATA * next;
    TURRET_DATA * prev;
    ROOM_INDEX_DATA *room;
    SHIP_DATA  *target;
    sh_int      laserstate;
};

struct hanger_data
{
    HANGER_DATA * next;
    HANGER_DATA * prev;
    ROOM_INDEX_DATA *room;
    bool        bayopen;
    int		type;
};

struct module_data{
    MODULE_DATA	*	next;
    MODULE_DATA *	prev;
    int			affect;	  // What item is it going to affect.
    int			ammount;  // How much is it going to affect it.
};    

struct ship_data
{
    SHIP_DATA * next;
    SHIP_DATA * prev;
    SHIP_DATA * next_in_starsystem;
    SHIP_DATA * prev_in_starsystem;
    SHIP_DATA * next_in_room;
    SHIP_DATA * prev_in_room;
    ROOM_INDEX_DATA *in_room;
    SPACE_DATA * starsystem;
    SHIP_DATA *	inship;
    char *	registered_to;
    char *      filename;
    char *      name;
    char *	protoname;
    char *	clanowner;
    char *      home;
    char *      description;
    char *      owner;
    char *      pilot;
    char *      copilot;
    char *      dest;
    char *	pbeacon;
    char *	cargo_bought;
    sh_int	damage_reduction;
    sh_int	armor;
    int		life_support;
    int		ion_engines;
    int		weapons_suite;
    int		construct_pts;
    sh_int	cloak;
    sh_int	sensor_masks;
    sh_int	size;
    sh_int      type;
    sh_int      class;
    sh_int	blasters[MAX_BLASTERS];
    sh_int	blaster_state[MAX_BLASTERS];
    sh_int	blasterstate[MAX_BLASTERS];
    sh_int	lasers[MAX_LASERS];
    sh_int	laser_state[MAX_LASERS];
    sh_int	laserstate[MAX_LASERS];
    sh_int	turbolasers[MAX_TURBO];
    sh_int	turbo_state[MAX_TURBO];
    sh_int	turbostate[MAX_TURBO];
    sh_int	missile[MAX_MISSILES];
    sh_int	missile_state[MAX_MISSILES];
    sh_int	missilestate[MAX_MISSILES];
    sh_int	missiles;
    sh_int	missile_quant[MAX_MISSILES];
    sh_int	ions[MAX_IONS];
    sh_int	ion_state[MAX_IONS];
    sh_int	ionstate[MAX_IONS];
    sh_int      comm;
    int		cost;
    sh_int      sensor;
    sh_int      astro_array;
    sh_int      hyperspeed;
    int         hyperdistance;
    sh_int      realspeed;
    sh_int	currspeed;
    sh_int	shipstate;
    sh_int	hyperstate;

/* New ship shit by || && Tawnos for FotE */

    bool juking; bool rolling;
    sh_int  primaryState;  // (was statet0) Primary beam state   (Damaged/charging)
    sh_int	secondaryState;  // (was statet0i) Secondary beam state
 
	sh_int  primaryType;   // Primary weapon type, defined in beam_types
	sh_int  secondaryType; // Secondary weapon type, defined in beam_types

	bool    primaryLinked; // Linked fire, if !single can fire all available (up to 4 at once)
	bool	secondaryLinked;   // Linked fire, if !single will fire all available
	bool	warheadLinked; // Linked fire, if !single will fire all available

    sh_int      primaryCount; // (was lasers) Number of primaries
    sh_int		secondaryCount;   // (was ions) Number of secondaries

    sh_int  statet1; // Begin turbolaser turret states
    sh_int  statet2;
    sh_int	statet3;
    sh_int	statet4;
    sh_int	statet5;
    sh_int	statet6;
    sh_int	statet7;
    sh_int	statet8;
    sh_int	statet9;
    sh_int	statet10; // End turbolaser turret states

    sh_int      missiletype;

    sh_int		torpedostate;
    sh_int		rocketstate;

    sh_int      bombs;
    sh_int      maxbombs;
    sh_int      alarm;
    sh_int      maxmissiles;
    sh_int      torpedos;
    sh_int      maxtorpedos;
    sh_int      rockets;
    sh_int      maxrockets;
    sh_int	maxmod;
    sh_int      tractorbeam;
    sh_int      manuever;
    bool        bayopen;
    bool        hatchopen;
    bool 	autorecharge;
    bool        autotrack;
    bool 	autospeed;
    float       vx, vy, vz;
    float       hx, hy, hz;
    float       jx, jy, jz;
    int         maxenergy;
    int         energy;
    int         shield;
    int         maxshield;
    int         hull;
    int         maxhull;
    int         cockpit;
    int         turret1;
    int         turret2;
    int		turret3;
    int		turret4;
    int		turret5;
    int		turret6;
    int		turret7;
    int		turret8;
    int		turret9;
    int		turret10;
    int		docking_bay;
    int         location;
    int         lastdoc;
    int         shipyard;
    int         entrance;
    int         engineroom;
    int         firstroom;
    int         lastroom;
    int         navseat;
    int         pilotseat;
    int         coseat;
    int         gunseat;
    long        collision;
    SHIP_DATA  *target0;
    SHIP_DATA  *target1;
    SHIP_DATA  *target2;
    SHIP_DATA  *target3;
    SHIP_DATA  *target4;
    SHIP_DATA  *target5;
    SHIP_DATA  *target6;
    SHIP_DATA  *target7;
    SHIP_DATA  *target8;
    SHIP_DATA  *target9;
    SHIP_DATA  *target10;
    SHIP_DATA  *docked_to;
    SPACE_DATA *currjump;
    sh_int      chaff;
    sh_int      maxchaff;
    sh_int	cargohold;
    int		holdsize;
    sh_int	cargo_type;
    int		cargo_quant;
    bool        chaff_released;
    bool        autopilot;
    int		channel;
    int		password;
    int		flags;
    MODULE_DATA *first_module;
    MODULE_DATA *last_module;
    sh_int	maxmods;
    TURRET_DATA *first_turret;
    TURRET_DATA *last_turret;
    int		hanger1;
    int		hanger2;
    int		hanger3;
    int		hanger4;
    int		exlocation;
    int		sim_vnum;
    int		max_modules;
    int		baycode;
    int		hibombstr;
    int		lowbombstr;
    SHIP_DATA  *tractored_by;
    SHIP_DATA  *tractoring;

};

#define SIZE_FINE		0
#define SIZE_DIMINUTIVE		1
#define SIZE_TINY		2
#define SIZE_SMALL		3
#define SIZE_MEDIUM		4
#define SIZE_LARGE		5
#define SIZE_HUGE		6
#define SIZE_GARGANTUAN		7
#define SIZE_COLOSSAL		8

#define AUTOBLASTER		0
#define TRIPLE_BLASTER		1
#define LIGHT_BLASTER		2
#define BLASTER_CANNON		3
#define HEAVY_BLASTER		4

#define TWIN_LASER		0
#define POINT_LASER		1
#define LIGHT_LASER		2
#define HEAVY_LASER		3
#define ASSAULT_LASER		4
#define QUAD_LASER		5
#define ESCORT_LASER		6
#define LONGSHOT_LASER		7

#define DOUBLE_TURBO		0
#define HEAVY_QUAD		1
#define LIGHT_QUAD		2
#define TURBO_QUAD		3
#define TURBO_CANNON		4
#define LIGHT_TURBO		5
#define MEDIUM_TURBO		6
#define TURBO_LASER		7
#define HEAVY_TURBO		8

#define SMALL_CONCUSSION	0
#define CONCUSSION_LAUNCHER	1
#define ASSAULT_CONCUSSION	2
#define ENERGY_TORPEDO		3
#define PROTON_TORPEDO		4

#define LIGHT_ION		0
#define ION_CANNON		1
#define HEAVY_ION		2

struct missile_data
{
    MISSILE_DATA * next;
    MISSILE_DATA * prev;
    MISSILE_DATA * next_in_starsystem;
    MISSILE_DATA * prev_in_starsystem;
    SPACE_DATA * starsystem;
    SHIP_DATA * target;
    SHIP_DATA * fired_from;
    char      * fired_by;
    sh_int      missiletype;
    sh_int      age;
    int         speed;
    int         mx, my, mz;
};


struct tourney_data
{
    int    open;
    int    low_level;
    int    hi_level;
};

/*
 * Data structure for notes.
 */
struct	note_data
{
    NOTE_DATA *	next;
    NOTE_DATA * prev;
    char *	sender;
    char *	date;
    char *	to_list;
    char *	subject;
    int         voting;
    char *	yesvotes;
    char *	novotes;
    char *	abstentions;
    char *	text;
};

struct	board_data
{
    BOARD_DATA * next;			/* Next board in list		   */
    BOARD_DATA * prev;			/* Previous board in list	   */
    NOTE_DATA *  first_note;		/* First note on board		   */
    NOTE_DATA *  last_note;		/* Last note on board		   */
    char *	 note_file;		/* Filename to save notes to	   */
    char *	 read_group;		/* Can restrict a board to a       */
    char *	 post_group;		/* council, clan, guild etc        */
    char *	 extra_readers;		/* Can give read rights to players */
    char *       extra_removers;        /* Can give remove rights to players */
    int		 board_obj;		/* Vnum of board object		   */
    sh_int	 num_posts;		/* Number of notes on this board   */
    sh_int	 min_read_level;	/* Minimum level to read a note	   */
    sh_int	 min_post_level;	/* Minimum level to post a note    */
    sh_int	 min_remove_level;	/* Minimum level to remove a note  */
    sh_int	 max_posts;		/* Maximum amount of notes allowed */
    int          type;                  /* Normal board or mail board? */
};


/*
 * An affect.
 */
struct	affect_data
{
    AFFECT_DATA *	next;
    AFFECT_DATA *	prev;
    sh_int		type;
    sh_int		duration;
    sh_int		location;
    int			modifier;
    int			bitvector;
};

struct  quest_data
{
    QUEST_DATA *	next;
    QUEST_DATA *	prev;
    char *		name;
    sh_int		value;
};

#define QUEST_UNFINISHED	0
#define QUEST_COMPLETE		1

/*
 * A SMAUG spell
 */
struct	smaug_affect
{
    SMAUG_AFF *		next;
    char *		duration;
    sh_int		location;
    char *		modifier;
    int			bitvector;
};


/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (Start of section ... start here)                     *
 *                                                                         *
 ***************************************************************************/

/*
 * Well known mob virtual numbers.
 * Defined in #MOBILES.
 */
#define MOB_VNUM_ANIMATED_CORPSE   5
#define MOB_VNUM_POLY_WOLF	   10

#define MOB_VNUM_STORMTROOPER	20
#define MOB_VNUM_IMP_GUARD	21
#define MOB_VNUM_NR_GUARD	22
#define MOB_VNUM_NR_TROOPER	23
#define MOB_VNUM_MERCINARY	24
#define MOB_VNUM_BOUNCER	25
#define MOB_VNUM_IMP_ELITE 	26
#define MOB_VNUM_IMP_PATROL 	27
#define MOB_VNUM_IMP_FORCES 	28
#define MOB_VNUM_NR_ELITE 	29
#define MOB_VNUM_NR_PATROL 	30
#define MOB_VNUM_NR_FORCES 	31
#define MOB_VNUM_MERC_ELITE 	32
#define MOB_VNUM_MERC_PATROL 	33
#define MOB_VNUM_MERC_FORCES 	34
#define MOB_VNUM_SHIP_GUARD	35

/* Ship Flags */
#define SHIP_NOHIJACK           BV00
#define SHIP_SHIELD_BOOST	BV01
#define SHIP_TORP_BOOST		BV02
#define SHIP_CHAFF_BOOST	BV03
#define SHIP_HULL_BOOST		BV04
#define SHIP_LASER_BOOST	BV05
#define SHIP_MISSILE_BOOST	BV06
#define SHIP_ROCKET_BOOST	BV07
#define SHIP_SIMULATOR		BV08
#define SHIP_NODESTROY		BV09
#define SHIP_NOSLICER		BV10
#define XSHIP_ION_LASERS	BV11
#define XSHIP_ION_DRIVE		BV12
#define XSHIP_ION_ION		BV13
#define XSHIP_ION_TURRET1        BV14
#define XSHIP_ION_TURRET2        BV15
#define XSHIP_ION_TURRET3        BV16
#define XSHIP_ION_TURRET4        BV17
#define XSHIP_ION_TURRET5        BV18
#define XSHIP_ION_TURRET6        BV19
#define XSHIP_ION_TURRET7        BV20
#define XSHIP_ION_TURRET8        BV21
#define XSHIP_ION_TURRET9        BV22
#define XSHIP_ION_TURRET10       BV23
#define SHIP_RESPAWN             BV24
#define XSHIP_ION_HYPER		 BV25
#define XSHIP_ION_MISSILES	 BV26
#define SHIP_CLOAK		 BV27
#define SHIP_ARMOR_BOOST	 BV28
#define SHIP_PROTOTYPE		 BV29

#define SHIP_DAMAGE_DRIVE         BV00
#define SHIP_DAMAGE_HYPERDRIVE    BV01
#define SHIP_DAMAGE_LASER         BV02
#define SHIP_DAMAGE_ION           BV03
#define SHIP_DAMAGE_TURRET1       BV04
#define SHIP_DAMAGE_TURRET2       BV05
#define SHIP_DAMAGE_TURRET3       BV06
#define SHIP_DAMAGE_TURRET4       BV07
#define SHIP_DAMAGE_TURRET5       BV08
#define SHIP_DAMAGE_TURRET6       BV09
#define SHIP_DAMAGE_TURRET7       BV10
#define SHIP_DAMAGE_TURRET8       BV11
#define SHIP_DAMAGE_TURRET9       BV12
#define SHIP_DAMAGE_TURRET10      BV13
#define SHIP_DAMAGE_SHIELD        BV14
#define SHIP_DAMAGE_PLASMASHIELD  BV15
#define SHIP_DAMAGE_LIFESUPPORT   BV16
#define SHIP_DAMAGE_MISSILE       BV17

/*
 * ACT bits for mobs.
 * Used in #MOBILES.
 */
#define ACT_IS_NPC		 BV00		/* Auto set for mobs	*/
#define ACT_SENTINEL		 BV01		/* Stays in one room	*/
#define ACT_SCAVENGER		 BV02		/* Picks up objects	*/
#define ACT_NOFLEE		 BV03		/* Mobs don't flee. -T  */
#define ACT_AGGRESSIVE		 BV05		/* Attacks PC's		*/
#define ACT_STAY_AREA		 BV06		/* Won't leave area	*/
#define ACT_WIMPY		 BV07		/* Flees when hurt	*/
#define ACT_PET			 BV08		/* Auto set for pets	*/
#define ACT_TRAIN		 BV09		/* Can train PC's	*/
#define ACT_PAZAKK		 BV10		/* Can practice PC's	*/
#define ACT_IMMORTAL		 BV11		/* Cannot be killed	*/
#define ACT_DEADLY		 BV12		
#define ACT_POLYSELF		 BV13
#define ACT_META_AGGR		 BV14		/* Extremely aggressive */
#define ACT_GUARDIAN		 BV15		/* Protects master	*/
#define ACT_RUNNING		 BV16		/* Hunts quickly	*/
#define ACT_NOWANDER		 BV17		/* Doesn't wander	*/
#define ACT_MOUNTABLE		 BV18		/* Can be mounted	*/
#define ACT_MOUNTED		 BV19		/* Is mounted		*/
#define ACT_SCHOLAR              BV20           /* Can teach languages  */
#define ACT_SECRETIVE		 BV21		/* actions aren't seen	*/
#define ACT_POLYMORPHED		 BV22		/* Mob is a ch		*/
#define ACT_MOBINVIS		 BV23		/* Like wizinvis	*/
#define ACT_NOASSIST		 BV24		/* Doesn't assist mobs	*/
#define ACT_NOKILL               BV25           /* Mob can't die */
#define ACT_DROID                BV26           /* mob is a droid */
#define ACT_NOCORPSE             BV27
#define ACT_PUEBLO		 BV28		/* This is the pueblo flag */           
#define ACT_PROTOTYPE		 BV30		/* A prototype mob	*/

/* Act2 Flags */
#define	ACT_BOUND		 BV00		/* This is the bind flag */
#define	ACT_EXEMPT		 BV01		/* Makes a player exampt from pfile deletion */
#define ACT_JEDI		 BV02		/* This is a light jedi */
#define	ACT_SITH		 BV03		/* This is a dark jedi */
#define	ACT_GAGGED		 BV04		/* This is a gagged flag */
/* 21 acts */

/* bits for vip flags */

#define VIP_CORUSCANT           BV00
#define VIP_YAVIN_IV		BV01
#define VIP_TATOOINE            BV02
#define VIP_KASHYYYK          	BV03
#define VIP_MON_CALAMARI       	BV04
#define VIP_ENDOR		BV05
#define VIP_ORD_MANTELL         BV06
#define VIP_NAL_HUTTA           BV07
#define VIP_CORELLIA            BV08
#define VIP_BAKURA	        BV09

/* player wanted bits */

#define WANTED_CORUSCANT   	VIP_CORUSCANT
#define WANTED_YAVIN_IV		VIP_YAVIN_IV
#define WANTED_TATOOINE   	VIP_TATOOINE
#define WANTED_KASHYYYK   	VIP_KASHYYYK
#define WANTED_MON_CALAMARI   	VIP_MON_CALAMARI
#define WANTED_ENDOR		VIP_ENDOR
#define WANTED_ORD_MANTELL   	VIP_ORD_MANTELL
#define WANTED_NAL_HUTTA   	VIP_NAL_HUTTA
#define WANTED_CORELLIA   	VIP_CORELLIA
#define WANTED_BAKURA   	VIP_BAKURA

#define VNUM_FALLEEN		1339
#define VNUM_DRALL		1338
#define VNUM_CHANCELLOR		1397
#define VNUM_YABLARI		1332
#define VNUM_ALDERAAN		1329
#define VNUM_CEREA		1356
#define VNUM_CHAMPALA		1357
#define VNUM_URKUPP		1341
#define VNUM_DORIN		1345
#define VNUM_ALPHERIDIES	1348
#define VNUM_RODIA		1351
#define VNUM_MON_CALAMARI	1353
#define VNUM_MUUNILINST		1361
#define VNUM_SKYE		1366
#define VNUM_SULLUST		1367
#define VNUM_UMBARA		1370
#define VNUM_KASHYYYK		1373
#define VNUM_WOOSTRI		1375
#define VNUM_CORELLIA		1378
#define VNUM_NABOO		1362
#define VNUM_UBA_111		1381
#define VNUM_ROCHE		1382
#define VNUM_IKTOTCH		1344

/*
 * Bits for 'affected_by'.
 * Used in #MOBILES.
 */
#define AFF_NONE                  0 
 
#define AFF_BLIND		  BV00
#define AFF_INVISIBLE		  BV01
#define AFF_GAS_BREATH		  BV02
#define AFF_DARKVISION		  BV03
#define AFF_COLD_RESIST		  BV04
#define AFF_HEAT_RESIST 	  BV05
#define AFF_FDEFENSE		  BV06		
#define AFF_SANCTUARY		  BV07
#define AFF_BATTLEMIND		  BV08
#define AFF_INFRARED		  BV09
#define AFF_CURSE		  BV10
#define AFF_COVER_TRAIL		  BV11
#define AFF_POISON		  BV12
#define AFF_MIND		  BV13
#define AFF_PARALYSIS		  BV14
#define AFF_SNEAK		  BV15
#define AFF_HIDE		  BV16
#define AFF_SLEEP		  BV17
#define AFF_CHARM		  BV18
#define AFF_FLYING		  BV19
#define AFF_ENHANCE		  BV20
#define AFF_FLOATING		  BV21
#define AFF_TRUESIGHT		  BV22
#define AFF_ENHANCESENSES	  BV23
#define AFF_FORCE	          BV24
#define AFF_SORCERY	          BV25
#define AFF_FEAR	          BV26
#define AFF_FASTHEAL              BV27
#define AFF_FORCE_RESIST	  BV28
#define AFF_POSSESS		  BV29
#define AFF_RAGE		  BV30
#define AFF_AQUA_BREATH		  BV31

/* 31 aff's (1 left.. :P) */
/* make that none - ugh - time for another field? :P */
/*
 * Resistant Immune Susceptible flags
 */
#define RIS_FIRE		  BV00
#define RIS_COLD		  BV01
#define RIS_ELECTRICITY		  BV02
#define RIS_ENERGY		  BV03
#define RIS_BLUNT		  BV04
#define RIS_PIERCE		  BV05
#define RIS_SLASH		  BV06
#define RIS_ACID		  BV07
#define RIS_POISON		  BV08
#define RIS_DRAIN		  BV09
#define RIS_SLEEP		  BV10
#define RIS_CHARM		  BV11
#define RIS_HOLD		  BV12
#define RIS_NONMAGIC		  BV13
#define RIS_PLUS1		  BV14
#define RIS_PLUS2		  BV15
#define RIS_PLUS3		  BV16
#define RIS_PLUS4		  BV17
#define RIS_PLUS5		  BV18
#define RIS_PLUS6		  BV19
#define RIS_MAGIC		  BV20
#define RIS_PARALYSIS		  BV21
/* 21 RIS's*/

/* 
 * Attack types
 */
#define ATCK_BITE		  BV00
#define ATCK_CLAWS		  BV01
#define ATCK_TAIL		  BV02
#define ATCK_STING		  BV03
#define ATCK_PUNCH		  BV04
#define ATCK_KICK		  BV05
#define ATCK_TRIP		  BV06
#define ATCK_BASH		  BV07
#define ATCK_STUN		  BV08
#define ATCK_GOUGE		  BV09
#define ATCK_BACKSTAB		  BV10
#define ATCK_FEED		  BV11
#define ATCK_DRAIN		  BV12
#define ATCK_FIREBREATH		  BV13
#define ATCK_FROSTBREATH	  BV14
#define ATCK_ACIDBREATH		  BV15
#define ATCK_LIGHTNBREATH	  BV16
#define ATCK_GASBREATH		  BV17
#define ATCK_POISON		  BV18
#define ATCK_NASTYPOISON	  BV19
#define ATCK_GAZE		  BV20
#define ATCK_BLINDNESS		  BV21
#define ATCK_CAUSESERIOUS	  BV22
#define ATCK_EARTHQUAKE		  BV23
#define ATCK_CAUSECRITICAL	  BV24
#define ATCK_CURSE		  BV25
#define ATCK_FLAMESTRIKE	  BV26
#define ATCK_HARM		  BV27
#define ATCK_FIREBALL		  BV28
#define ATCK_COLORSPRAY		  BV29
#define ATCK_WEAKEN		  BV30
#define ATCK_SPIRALBLAST	  BV31
/* 32 USED! DO NOT ADD MORE! SB */

/*
 * Defense types
 */
#define DFND_PARRY		  BV00
#define DFND_DODGE		  BV01
#define DFND_HEAL		  BV02
#define DFND_CURELIGHT		  BV03
#define DFND_CURESERIOUS	  BV04
#define DFND_CURECRITICAL	  BV05
#define DFND_DISPELMAGIC	  BV06
#define DFND_DISPELEVIL		  BV07
#define DFND_SANCTUARY		  BV08
#define DFND_FIRESHIELD		  BV09
#define DFND_SHOCKSHIELD	  BV10
#define DFND_SHIELD		  BV11
#define DFND_BLESS		  BV12
#define DFND_STONESKIN		  BV13
#define DFND_TELEPORT		  BV14
#define DFND_MONSUM1		  BV15
#define DFND_MONSUM2		  BV16
#define DFND_MONSUM3		  BV17
#define DFND_MONSUM4		  BV18
#define DFND_DISARM		  BV19
#define DFND_ICESHIELD 		  BV20
#define DFND_GRIP		  BV21
/* 21 def's */

#define CARGO_NONE		  0
#define CARGO_ART		  1
#define CARGO_BACTA		  2
#define CARGO_GEMS_SEMI		  3
#define CARGO_GEMS_PRECIOUS	  4
#define CARGO_ORE_COMMON	  5
#define CARGO_ORE_RARE	          6
#define CARGO_SPICE		  7
#define CARGO_SLAVES		  8
#define CARGO_WEAPONS		  9

#define CLOTHES_ARMOR		0
#define LIGHT_ARMOR		1
#define MEDIUM_ARMOR		2
#define HEAVY_ARMOR		3
#define POWERED_ARMOR		4

#define ATMO_NORMAL		0
#define ATMO_GASEOUS		1
#define ATMO_HEAT		2
#define ATMO_BLIZZARD		3
#define ATMO_THINAIR		4
#define ATMO_OXGENIZED		5
#define ATMO_TOXIC		6
#define ATMO_WIND		7

#define BONUS_NONE		0
#define BONUS_HITROLL		1
#define BONUS_DAMROLL		2
#define BONUS_ARMOR		3
#define BONUS_EXP		4

/*
 * Body parts
 */
#define PART_HEAD		  BV00
#define PART_ARM_R1		  BV01
#define PART_ARM_L1		  BV02
#define PART_ARM_R2		  BV03
#define PART_ARM_L2		  BV04
#define PART_LEG_R		  BV05
#define PART_LEG_L		  BV06
#define PART_FEET		  BV07
#define PART_WINGS		  BV08
#define PART_HAND_R1		  BV09
#define PART_HAND_L1		  BV10
#define PART_HAND_R2		  BV11
#define PART_HAND_L2		  BV12
#define PART_EYE_R		  BV13
#define PART_EYE_L		  BV14
#define PART_CLAWS		  BV15
#define PART_HORNS		  BV16

#define HEAD_PART		  0
#define ARMR1_PART		  1
#define ARML1_PART		  2
#define ARMR2_PART		  3
#define ARML2_PART		  4
#define LEGR_PART		  5
#define LEGL_PART		  6
#define FEET_PART		  7
#define WING_PART		  8
#define HANDR1_PART		  9
#define HANDL1_PART		  10
#define HANDR2_PART		  11
#define HANDL2_PART		  12
#define EYER_PART		  13
#define EYEL_PART		  14

/*
 * Autosave flags
 */
#define SV_DEATH		  BV00
#define SV_KILL			  BV01
#define SV_PASSCHG		  BV02
#define SV_DROP			  BV03
#define SV_PUT			  BV04
#define SV_GIVE			  BV05
#define SV_AUTO			  BV06
#define SV_ZAPDROP		  BV07
#define SV_AUCTION		  BV08
#define SV_GET			  BV09
#define SV_RECEIVE		  BV10
#define SV_IDLE			  BV11
#define SV_BACKUP		  BV12

/*
 * Pipe flags
 */
#define PIPE_TAMPED		  BV01
#define PIPE_LIT		  BV02
#define PIPE_HOT		  BV03
#define PIPE_DIRTY		  BV04
#define PIPE_FILTHY		  BV05
#define PIPE_GOINGOUT		  BV06
#define PIPE_BURNT		  BV07
#define PIPE_FULLOFASH		  BV08

/*
 * Skill/Spell flags	The minimum BV *MUST* be 11!
 */
#define SF_WATER		  BV11
#define SF_EARTH		  BV12
#define SF_AIR			  BV13
#define SF_ASTRAL		  BV14
#define SF_AREA			  BV15  /* is an area spell		*/
#define SF_DISTANT		  BV16  /* affects something far away	*/
#define SF_REVERSE		  BV17
#define SF_SAVE_HALF_DAMAGE	  BV18  /* save for half damage		*/
#define SF_SAVE_NEGATES		  BV19  /* save negates affect		*/
#define SF_ACCUMULATIVE		  BV20  /* is accumulative		*/
#define SF_RECASTABLE		  BV21  /* can be refreshed		*/
#define SF_NOSCRIBE		  BV22  /* cannot be scribed		*/
#define SF_NOBREW		  BV23  /* cannot be brewed		*/
#define SF_GROUPSPELL		  BV24  /* only affects group members	*/
#define SF_OBJECT		  BV25	/* directed at an object	*/
#define SF_CHARACTER		  BV26  /* directed at a character	*/
#define SF_SECRETSKILL		  BV27	/* hidden unless learned	*/
#define SF_PKSENSITIVE		  BV28	/* much harder for plr vs. plr	*/
#define SF_STOPONFAIL		  BV29	/* stops spell on first failure */

typedef enum { SS_NONE, SS_POISON_DEATH, SS_ROD_WANDS, SS_PARA_PETRI,
	       SS_BREATH, SS_SPELL_STAFF } save_types;

#define ALL_BITS		INT_MAX
#define SDAM_MASK		ALL_BITS & ~(BV00 | BV01 | BV02)
#define SACT_MASK		ALL_BITS & ~(BV03 | BV04 | BV05)
#define SCLA_MASK		ALL_BITS & ~(BV06 | BV07 | BV08)
#define SPOW_MASK		ALL_BITS & ~(BV09 | BV10)

typedef enum { SD_NONE, SD_FIRE, SD_COLD, SD_ELECTRICITY, SD_ENERGY, SD_ACID,
	       SD_POISON, SD_DRAIN } spell_dam_types;

typedef enum { SA_NONE, SA_CREATE, SA_DESTROY, SA_RESIST, SA_SUSCEPT,
	       SA_DIVINATE, SA_OBSCURE, SA_CHANGE } spell_act_types;

typedef enum { SP_NONE, SP_MINOR, SP_GREATER, SP_MAJOR } spell_power_types;

typedef enum { SC_NONE, SC_LUNAR, SC_SOLAR, SC_TRAVEL, SC_SUMMON,
	       SC_LIFE, SC_DEATH, SC_ILLUSION } spell_class_types;

/*
 * Sex.
 * Used in #MOBILES.
 */
typedef enum { SEX_NEUTRAL, SEX_MALE, SEX_FEMALE } sex_types;

typedef enum {
  TRAP_TYPE_POISON_GAS = 1, TRAP_TYPE_POISON_DART,    TRAP_TYPE_POISON_NEEDLE,
  TRAP_TYPE_POISON_DAGGER,  TRAP_TYPE_POISON_ARROW,   TRAP_TYPE_BLINDNESS_GAS,
  TRAP_TYPE_SLEEPING_GAS,   TRAP_TYPE_FLAME,	      TRAP_TYPE_EXPLOSION,
  TRAP_TYPE_ACID_SPRAY,	    TRAP_TYPE_ELECTRIC_SHOCK, TRAP_TYPE_BLADE,
  TRAP_TYPE_SEX_CHANGE } trap_types;

#define MAX_TRAPTYPE		   TRAP_TYPE_SEX_CHANGE

#define TRAP_ROOM      		   BV00
#define TRAP_OBJ	      	   BV01
#define TRAP_ENTER_ROOM		   BV02
#define TRAP_LEAVE_ROOM		   BV03
#define TRAP_OPEN		   BV04 
#define TRAP_CLOSE		   BV05
#define TRAP_GET		   BV06
#define TRAP_PUT		   BV07
#define TRAP_PICK		   BV08
#define TRAP_UNLOCK		   BV09
#define TRAP_N			   BV10
#define TRAP_S			   BV11 
#define TRAP_E	      		   BV12
#define TRAP_W	      		   BV13
#define TRAP_U	      		   BV14
#define TRAP_D	      		   BV15
#define TRAP_EXAMINE		   BV16
#define TRAP_NE			   BV17
#define TRAP_NW			   BV18
#define TRAP_SE			   BV19
#define TRAP_SW			   BV20

/*
 * Well known object virtual numbers.
 * Defined in #OBJECTS.
 */
#define OBJ_VNUM_MONEY_ONE	      2
#define OBJ_VNUM_MONEY_SOME	      3

#define COMMSYS_VNUM		     62
#define DATAPAD_VNUM		     63

#define	MODULE_VNUM		     73
#define SABER_VNUM    		     72
#define IMPLANT_VNUM		     87

#define OBJ_VNUM_DROID_CORPSE        9
#define OBJ_VNUM_CORPSE_NPC	     10
#define OBJ_VNUM_CORPSE_PC	     11
#define OBJ_VNUM_SEVERED_HEAD	     12
#define OBJ_VNUM_TORN_HEART	     13
#define OBJ_VNUM_SLICED_ARM	     14
#define OBJ_VNUM_SLICED_LEG	     15
#define OBJ_VNUM_SPILLED_GUTS	     16
#define OBJ_VNUM_BLOOD		     17
#define OBJ_VNUM_BLOODSTAIN	     18
#define OBJ_VNUM_SCRAPS		     19

#define OBJ_VNUM_MUSHROOM	     20
#define OBJ_VNUM_LIGHT_BALL	     21
#define OBJ_VNUM_SPRING		     22

#define OBJ_VNUM_SLICE		     24
#define OBJ_VNUM_SHOPPING_BAG	     25

#define OBJ_VNUM_FIRE		     30
#define OBJ_VNUM_TRAP		     31
#define OBJ_VNUM_PORTAL		     32

#define OBJ_VNUM_BLACK_POWDER	     33
#define OBJ_VNUM_SCROLL_SCRIBING     34
#define OBJ_VNUM_FLASK_BREWING       35
#define OBJ_VNUM_NOTE		     36

/* Academy eq */
#define OBJ_VNUM_SCHOOL_MACE	  10315
#define OBJ_VNUM_SCHOOL_DAGGER	  10312
#define OBJ_VNUM_SCHOOL_SWORD	  10313
#define OBJ_VNUM_SCHOOL_VEST	  10308
#define OBJ_VNUM_SCHOOL_SHIELD	  10310
#define OBJ_VNUM_SCHOOL_BANNER    10311
#define OBJ_VNUM_SCHOOL_DIPLOMA   10321

#define OBJ_VNUM_BLASTECH_E11     50
#define OBJ_VNUM_SHIPBOMB     	  68
#define OBJ_VNUM_MONITOR	  88
#define OBJ_VNUM_CAMERA		  89

/* These are some defines for modules */
#define AFFECT_PRIMARY		1
#define AFFECT_SECONDARY        2
#define AFFECT_MISSILE		3
#define AFFECT_ROCKET		4
#define AFFECT_TORPEDO		5
#define AFFECT_HULL		6
#define AFFECT_SHIELD		7
#define AFFECT_SPEED		8
#define AFFECT_HYPER		9
#define AFFECT_ENERGY		10
#define AFFECT_MANUEVER		11
#define AFFECT_CHAFF		12
#define AFFECT_ALARM		13

/*
 * Item types.
 * Used in #OBJECTS.
 */
typedef enum
{
  ITEM_NONE, ITEM_LIGHT, ITEM_IMPLANT, ITEM_CAMERA, ITEM_MONITOR, ITEM_WEAPON,
  ITEM_FIREWEAPON, ITEM_MISSILE, ITEM_TREASURE, ITEM_ARMOR, ITEM_POTION,
  ITEM_WORN, ITEM_FURNITURE, ITEM_TRASH, ITEM_OLDTRAP, ITEM_CONTAINER,
  ITEM_NOTE, ITEM_DRINK_CON, ITEM_KEY, ITEM_FOOD, ITEM_MONEY, ITEM_PEN,
  ITEM_BOAT, ITEM_CORPSE_NPC, ITEM_CORPSE_PC, ITEM_FOUNTAIN, ITEM_PILL,
  ITEM_BLOOD, ITEM_BLOODSTAIN, ITEM_SCRAPS, ITEM_PIPE, ITEM_HERB_CON,
  ITEM_HERB, ITEM_INCENSE, ITEM_FIRE, ITEM_BOOK, ITEM_SWITCH, ITEM_LEVER,
  ITEM_PULLCHAIN, ITEM_BUTTON, ITEM_DIAL, ITEM_LOCKER, ITEM_RUNEPOUCH,
  ITEM_MATCH, ITEM_TRAP, ITEM_MAP, ITEM_PORTAL, ITEM_PAPER,
  ITEM_CARD, ITEM_LOCKPICK, ITEM_SPIKE, ITEM_DISEASE, ITEM_OIL, ITEM_FUEL,
  ITEM_SHORT_BOW, ITEM_LONG_BOW, ITEM_CROSSBOW, ITEM_AMMO, ITEM_QUIVER,
  ITEM_SHOVEL, ITEM_SALVE, ITEM_RAWSPICE, ITEM_LENS, ITEM_CRYSTAL, ITEM_DURAPLAST,
  ITEM_BATTERY, ITEM_TOOLKIT, ITEM_DURASTEEL, ITEM_OVEN, ITEM_MIRROR,
  ITEM_CIRCUIT, ITEM_SUPERCONDUCTOR, ITEM_COMLINK, ITEM_MEDPAC, ITEM_FABRIC,
  ITEM_RARE_METAL, ITEM_MAGNET, ITEM_THREAD, ITEM_SPICE, ITEM_SMUT, ITEM_DEVICE, ITEM_SPACECRAFT,
  ITEM_GRENADE, ITEM_LANDMINE, ITEM_GOVERNMENT, ITEM_DROID_CORPSE, ITEM_BOLT, ITEM_CHEMICAL, ITEM_COMMSYSTEM,
  ITEM_DATAPAD, ITEM_MODULE, ITEM_BUG, ITEM_BEACON, ITEM_GLAUNCHER,
  ITEM_RLAUNCHER, ITEM_BINDERS, ITEM_GOGGLES, ITEM_SHIPBOMB, ITEM_EMP_GRENADE
} item_types;


#define MAX_ITEM_TYPE		     ITEM_EMP_GRENADE
/*
 * Extra flags.
 * Used in #OBJECTS.
 */
#define ITEM_GLOW		BV00
#define ITEM_HUM		BV01
#define ITEM_DARK		BV02
#define ITEM_HUTT_SIZE		BV03
#define ITEM_CONTRABAND		BV04
#define ITEM_INVIS		BV05
#define ITEM_RENTED		BV06
#define ITEM_NODROP		BV07
#define ITEM_BLESS		BV08
#define ITEM_IMP_CRITICAL	BV09
#define ITEM_STUN		BV10
#define ITEM_ANTI_NEUTRAL	BV11
#define ITEM_NOREMOVE		BV12
#define ITEM_INVENTORY		BV13
#define ITEM_ANTI_SOLDIER	BV14
#define ITEM_ANTI_THIEF	        BV15
#define ITEM_ANTI_HUNTER	BV16
#define ITEM_INSTALLED  	BV17
#define ITEM_SMALL_SIZE		BV18
#define ITEM_LARGE_SIZE		BV19
#define ITEM_DONATION		BV20
#define ITEM_CLANOBJECT		BV21
#define ITEM_IMBUED		BV22
#define ITEM_ANTI_SITH  	BV23
#define ITEM_IGNITED	        BV24
#define ITEM_HIDDEN		BV25
#define ITEM_POISONED		BV26
#define ITEM_COVERING		BV27
#define ITEM_DEATHROT		BV28
#define ITEM_BURRIED		BV29	/* item is underground */
#define ITEM_PROTOTYPE		BV30
#define ITEM_HUMAN_SIZE         BV31

/* Magic flags - extra extra_flags for objects that are used in spells */
#define ITEM_RETURNING		BV00
#define ITEM_BACKSTABBER  	BV01
#define ITEM_BANE		BV02
#define ITEM_LOYAL		BV03
#define ITEM_HASTE		BV04
#define ITEM_DRAIN		BV05
#define ITEM_LIGHTNING_BLADE  	BV06

/* Blaster settings - only saves on characters */
#define BLASTER_NORMAL          0
#define BLASTER_HALF		2
#define BLASTER_FULL            5
#define BLASTER_LOW		1	
#define	BLASTER_STUN		3
#define BLASTER_HIGH            4

/* Weapon Types */

#define WEAPON_NONE     	0
#define WEAPON_VIBRO		1
#define WEAPON_LIGHTSABER	2
#define WEAPON_BLASTER		3
#define WEAPON_BLASTER_RIFLE	4
#define WEAPON_HEAVY		5
#define WEAPON_BOWCASTER	6
#define WEAPON_PRIMITIVE	7
#define WEAPON_FORCE_PIKE	8
#define WEAPON_SIMPLE		9
#define WEAPON_DUAL_LIGHTSABER	10
#define WEAPON_SLUGTHROWER	11

/* Lever/dial/switch/button/pullchain flags */
#define TRIG_UP			BV00
#define TRIG_UNLOCK		BV01
#define TRIG_LOCK		BV02
#define TRIG_D_NORTH		BV03
#define TRIG_D_SOUTH		BV04
#define TRIG_D_EAST		BV05
#define TRIG_D_WEST		BV06
#define TRIG_D_UP		BV07
#define TRIG_D_DOWN		BV08
#define TRIG_DOOR		BV09
#define TRIG_CONTAINER		BV10
#define TRIG_OPEN		BV11
#define TRIG_CLOSE		BV12
#define TRIG_PASSAGE		BV13
#define TRIG_OLOAD		BV14
#define TRIG_MLOAD		BV15
#define TRIG_TELEPORT		BV16
#define TRIG_TELEPORTALL	BV17
#define TRIG_TELEPORTPLUS	BV18
#define TRIG_DEATH		BV19
#define TRIG_CAST		BV20
#define TRIG_FAKEBLADE		BV21
#define TRIG_RAND4		BV22
#define TRIG_RAND6		BV23
#define TRIG_TRAPDOOR		BV24
#define TRIG_ANOTHEROOM		BV25
#define TRIG_USEDIAL		BV26
#define TRIG_ABSOLUTEVNUM	BV27
#define TRIG_SHOWROOMDESC	BV28
#define TRIG_AUTORETURN		BV29

#define TELE_SHOWDESC		BV00
#define TELE_TRANSALL		BV01
#define TELE_TRANSALLPLUS	BV02

/* drug types */
#define SPICE_GLITTERSTIM        0
#define SPICE_CARSANUM           1
#define SPICE_RYLL               2
#define SPICE_ANDRIS             3

/* crystal types */
#define CRYSTAL_BLUE		 0
#define CRYSTAL_GREEN		 1
#define CRYSTAL_PURPLE		 2
#define CRYSTAL_RED		 3
#define CRYSTAL_YELLOW		 4
#define CRYSTAL_OPILA		 5
#define CRYSTAL_SIGIL		 6
#define CRYSTAL_BONDAR		 7
#define CRYSTAL_PHOND		 8
#define CRYSTAL_SOLARI 		 9
#define CRYSTAL_DAMIND		10
#define CRYSTAL_JENRUAX		11
#define CRYSTAL_UPARI		12
#define CRYSTAL_ERALAM		13
#define CRYSTAL_RUBAT		14
#define CRYSTAL_SAPITH		15

/*
 * Wear flags.
 * Used in #OBJECTS.
 */
#define ITEM_TAKE		BV00
#define ITEM_WEAR_FINGER	BV01
#define ITEM_WEAR_NECK		BV02
#define ITEM_WEAR_BODY		BV03
#define ITEM_WEAR_HEAD		BV04
#define ITEM_WEAR_LEGS		BV05
#define ITEM_WEAR_FEET		BV06
#define ITEM_WEAR_HANDS		BV07
#define ITEM_WEAR_ARMS		BV08
#define ITEM_WEAR_SHIELD	BV09
#define ITEM_WEAR_ABOUT		BV10
#define ITEM_WEAR_WAIST		BV11
#define ITEM_WEAR_WRIST		BV12
#define ITEM_WIELD		BV13
#define ITEM_HOLD		BV14
#define ITEM_DUAL_WIELD		BV15
#define ITEM_WEAR_EARS		BV16
#define ITEM_WEAR_EYES		BV17
#define ITEM_MISSILE_WIELD	BV18
#define	ITEM_WEAR_BACK		BV19
#define	ITEM_WEAR_HOLSTER1	BV20
#define	ITEM_WEAR_HOLSTER2	BV21
#define	ITEM_WEAR_BOTHWRISTS	BV22


/*
 * Apply types (for affects).
 * Used in #OBJECTS.
 */
typedef enum
{
  APPLY_NONE, APPLY_STR, APPLY_DEX, APPLY_INT, APPLY_WIS, APPLY_CON,
  APPLY_SEX, APPLY_NULL , APPLY_LEVEL, APPLY_AGE, APPLY_HEIGHT, APPLY_WEIGHT,
  APPLY_MANA, APPLY_HIT, APPLY_MOVE, APPLY_GOLD, APPLY_EXP, APPLY_AC,
  APPLY_HITROLL, APPLY_DAMROLL, APPLY_INJURY, APPLY_FORT, APPLY_REFL, 
  APPLY_WILL, APPLY_SAVING_SPELL, APPLY_CHA,
  APPLY_AFFECT, APPLY_RESISTANT, APPLY_IMMUNE, APPLY_SUSCEPTIBLE,
  APPLY_WEAPONSPELL, APPLY_LCK, APPLY_DISABLE, APPLY_TRACK, APPLY_SLEIGHT, 
  APPLY_SNEAK, APPLY_HIDE, APPLY_SPOT, APPLY_SEARCH, APPLY_LISTEN,
  APPLY_CLIMB, APPLY_SCRIBE, APPLY_COVER_TRAIL, APPLY_WEARSPELL, APPLY_WILLPOWER,
  APPLY_REMOVESPELL, APPLY_EMOTION, APPLY_MENTALSTATE, APPLY_STRIPSN, 
  APPLY_REMOVE, APPLY_FULL, APPLY_THIRST, APPLY_DRUNK, APPLY_BLOOD, 
  MAX_APPLY_TYPE
} apply_types;

#define REVERSE_APPLY		   1000

/*
 * Values for containers (value[1]).
 * Used in #OBJECTS.
 */
#define CONT_CLOSEABLE		      1
#define CONT_PICKPROOF		      2
#define CONT_CLOSED		      4
#define CONT_LOCKED		      8

/*
 * Well known room virtual numbers.
 * Defined in #ROOMS.
 */
#define ROOM_VNUM_LIMBO		      2
#define ROOM_VNUM_POLY		      3
#define ROOM_VNUM_CHAT		  32144
#define ROOM_VNUM_TEMPLE	  32144
#define ROOM_VNUM_ALTAR		  32144 
#define ROOM_VNUM_SCHOOL	    115
#define ROOM_AUTH_START		  10300
#define ROOM_START_HUMAN            211
#define ROOM_START_WOOKIEE        28600
#define ROOM_START_TWILEK         32148
#define ROOM_START_RODIAN         32148
#define ROOM_START_HUTT           32148
#define ROOM_START_MON_CALAMARIAN 21069
#define ROOM_START_NOGHRI          1015
#define ROOM_START_GAMORREAN      28100
#define ROOM_START_JAWA           31819
#define ROOM_START_ADARIAN        29000
#define ROOM_START_EWOK           32148
#define ROOM_START_VERPINE        32148
#define ROOM_START_DEFEL          32148
#define ROOM_START_TRANDOSHAN     32148
#define ROOM_START_HAPAN     32148
#define ROOM_START_DUINUOGWUIN    32148
#define ROOM_START_QUARREN        21069
#define ROOM_START_IMMORTAL         100
#define ROOM_LIMBO_SHIPYARD          45
#define ROOM_DEFAULT_CRASH        28025

#define ROOM_PLUOGUS_QUIT         905

#define ROOM_SHUTTLE_BUS           907  /* Sol */
#define ROOM_SHUTTLE_BUS_2         914  /* Monir*/
#define ROOM_SHUTTLE_BUS_3		   921 /* Fau */
#define ROOM_SHUTTLE_BUS_4		   928 /* Taw */

#define ROOM_CORUSCANT_SHUTTLE     199
#define ROOM_SENATE_SHUTTLE      10197
#define ROOM_CORUSCANT_TURBOCAR    226  

#define SHIP_AREA               "shipvnum.are"

/*
 * Room flags.           Holy cow!  Talked about stripped away..
 * Used in #ROOMS.       Those merc guys know how to strip code down.
 *			 Lets put it all back... ;)
 */

#define ROOM_DARK		BV00
/* BV01 now reserved for track  BV01  and hunt */
#define ROOM_NO_MOB		BV02
#define ROOM_INDOORS		BV03
#define ROOM_CAN_LAND		BV04
#define ROOM_CAN_FLY		BV05
#define ROOM_NO_DRIVING 	BV06  
#define ROOM_NO_MAGIC		BV07
#define ROOM_BANK		BV08
#define ROOM_PRIVATE		BV09
#define ROOM_SAFE		BV10
#define ROOM_SOLITARY		BV11
#define ROOM_PET_SHOP		BV12
#define ROOM_NO_RECALL		BV13
#define ROOM_DONATION		BV14
#define ROOM_NODROPALL		BV15
#define ROOM_SILENCE		BV16
#define ROOM_LOGSPEECH		BV17
#define ROOM_NODROP		BV18
#define ROOM_CLANSTOREROOM	BV19
#define ROOM_PLR_HOME		BV20
#define ROOM_EMPTY_HOME 	BV21
#define ROOM_TELEPORT		BV22
#define ROOM_HOTEL      	BV23
#define ROOM_NOFLOOR		BV24
#define ROOM_REFINERY           BV25
#define ROOM_FACTORY            BV26
#define ROOM_R_RECRUIT          BV27
#define ROOM_E_RECRUIT          BV28
#define ROOM_SPACECRAFT         BV29
#define ROOM_PROTOTYPE	     	BV30
#define ROOM_AUCTION            BV31

/* Second Set of Room Flags */
#define ROOM_EMPTY_SHOP		BV00
#define ROOM_PLR_SHOP		BV01
#define ROOM_SHIPYARD		BV02
#define ROOM_GARAGE		BV03
#define ROOM_BARRACKS		BV04
#define ROOM_CONTROL		BV05
#define ROOM_CLANLAND		BV06
#define ROOM_ARENA		BV07
#define ROOM_CLANJAIL		BV08
#define ROOM_BLACKMARKET	BV09
#define ROOM_HIDDENPAD		BV10
#define ROOM_DROIDSHOP		BV11
#define ROOM_SENATE		BV12
#define ROOM_CARGOSHOP	 	BV13
#define ROOM_AUDITORIUM		BV14
#define ROOM_PAZAAK		BV15

#define SELL_CARGO_ART		BV00
#define SELL_CARGO_BACTA	BV01
#define SELL_CARGO_GEMS_SEMI	BV02
#define SELL_CARGO_GEMS_PREC	BV03
#define SELL_CARGO_ORE_COMMON   BV04
#define SELL_CARGO_ORE_RARE	BV05
#define SELL_CARGO_SPICE	BV06
#define SELL_CARGO_SLAVES	BV07
#define SELL_CARGO_WEAPONS	BV08

/*
 * Directions.
 * Used in #ROOMS.
 */
typedef enum
{
  DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST, DIR_UP, DIR_DOWN,
  DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHEAST, DIR_SOUTHWEST, DIR_SOMEWHERE
} dir_types;

#define MAX_DIR			DIR_SOUTHWEST	/* max for normal walking */
#define DIR_PORTAL		DIR_SOMEWHERE	/* portal direction	  */


/*
 * Exit flags.
 * Used in #ROOMS.
 */
#define EX_ISDOOR		  BV00
#define EX_CLOSED		  BV01
#define EX_LOCKED		  BV02
#define EX_SECRET		  BV03
#define EX_SWIM			  BV04
#define EX_PICKPROOF		  BV05
#define EX_FLY			  BV06
#define EX_CLIMB		  BV07
#define EX_DIG			  BV08
#define EX_RES1                   BV09	/* are these res[1-4] important? */
#define EX_NOPASSDOOR		  BV10
#define EX_HIDDEN		  BV11
#define EX_PASSAGE		  BV12
#define EX_PORTAL 		  BV13
#define EX_RES2			  BV14
#define EX_RES3			  BV15
#define EX_xCLIMB		  BV16
#define EX_xENTER		  BV17
#define EX_xLEAVE		  BV18
#define EX_xAUTO		  BV19
#define EX_RES4	  		  BV20
#define EX_xSEARCHABLE		  BV21
#define EX_BASHED                 BV22
#define EX_BASHPROOF              BV23
#define EX_NOMOB		  BV24
#define EX_WINDOW		  BV25
#define EX_xLOOK		  BV26
#define EX_AUTOCLOSE		  BV27
#define MAX_EXFLAG		  27


/*
 * Sector types.
 * Used in #ROOMS.
 */
typedef enum
{
  SECT_INSIDE, SECT_CITY, SECT_FIELD, SECT_FOREST, SECT_HILLS, SECT_MOUNTAIN,
  SECT_WATER_SWIM, SECT_WATER_NOSWIM, SECT_UNDERWATER, SECT_AIR, SECT_DESERT,
  SECT_DUNNO, SECT_OCEANFLOOR, SECT_UNDERGROUND, SECT_SCRUB, SECT_ROCKY,
  SECT_SAVANNA, SECT_TUNDRA, SECT_GLACIAL, SECT_RAINFOREST, SECT_JUNGLE, 
  SECT_SWAMP, SECT_WETLANDS, SECT_BRUSH, SECT_STEPPE, SECT_FARMLAND, SECT_VOLCANIC,
  SECT_MAX
} sector_types;

/*
 * Equpiment wear locations.
 * Used in #RESETS.
 */
typedef enum
{
  WEAR_NONE = -1, WEAR_LIGHT = 0, WEAR_FINGER_L, WEAR_FINGER_R, WEAR_NECK_1,
  WEAR_NECK_2, WEAR_BODY, WEAR_HEAD, WEAR_LEGS, WEAR_FEET, WEAR_HANDS,
  WEAR_ARMS, WEAR_SHIELD, WEAR_ABOUT, WEAR_WAIST, WEAR_WRIST_L, WEAR_WRIST_R,
  WEAR_WIELD, WEAR_HOLD, WEAR_DUAL_WIELD, WEAR_EARS, WEAR_EYES,
  WEAR_MISSILE_WIELD, WEAR_BACK, WEAR_HOLSTER_L, WEAR_HOLSTER_R, WEAR_BOTH_WRISTS,
  MAX_WEAR
} wear_locations;

/* Board Types */
typedef enum { BOARD_NOTE, BOARD_MAIL } board_types;

/* Auth Flags */
#define FLAG_WRAUTH		      1
#define FLAG_AUTH		      2

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (End of this section ... stop here)                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Conditions.
 */
typedef enum
{
  COND_DRUNK, COND_FULL, COND_THIRST, COND_BLOODTHIRST, MAX_CONDS
} conditions;

/*
 * Positions.
 */
typedef enum
{
  POS_DEAD, POS_MORTAL, POS_INCAP, POS_STUNNED, POS_SLEEPING, POS_MEDITATING, POS_RESTING,
  POS_SITTING, POS_FIGHTING, POS_STANDING, POS_MOUNTED, POS_SHOVE, POS_DRAG, POS_PLAYING
} positions;

typedef enum
{
  CARD_NONE, CARD_FOLD, CARD_BET, CARD_CHECK, CARD_CALL
} cards;

/* 
 * Duck And Cover Positions
 */
#define COVER_NONE  0
#define COVER_DUCK  1
#define COVER_LEFT  2
#define COVER_RIGHT 3
#define COVER_FULL  4

/*
 * ACT bits for players.
 */
#define PLR_IS_NPC		      BV00	/* Don't EVER set.	*/
#define PLR_CONVICT		      BV01
#define PLR_SHOVEDRAG		      BV02
#define PLR_AUTOEXIT		      BV03
#define PLR_AUTOLOOT		      BV04
#define PLR_AUTOSAC                   BV05
#define PLR_BLANK		      BV06
#define PLR_OUTCAST 		      BV07
#define PLR_BRIEF		      BV08
#define PLR_COMBINE		      BV09
#define PLR_PROMPT		      BV10
#define PLR_TELNET_GA		      BV11

#define PLR_HOLYLIGHT		   BV12
#define PLR_WIZINVIS		   BV13
#define PLR_ROOMVNUM		   BV14

#define	PLR_SILENCE		   BV15
#define PLR_NO_EMOTE		   BV16
#define PLR_ATTACKER    	   BV17
#define PLR_NO_TELL		   BV18
#define PLR_LOG			   BV19
#define PLR_DENY		   BV20
#define PLR_FREEZE		   BV21
#define PLR_KILLER    	           BV22
#define PLR_WHOINVIS 	           BV23
#define PLR_LITTERBUG	           BV24
#define PLR_ANSI	           BV25
#define PLR_SOUND	           BV26
#define PLR_NICE	           BV27
#define PLR_FLEE	           BV28
#define PLR_AUTOGOLD               BV29
#define PLR_SLOG                   BV30
#define PLR_AFK                    BV31

/* Bits for pc_data->flags. */
#define PCFLAG_R1                  BV00
/*
#define PCFLAG_                    BV01     extra flag
*/
#define PCFLAG_UNAUTHED		   BV02
#define PCFLAG_NORECALL            BV03
#define PCFLAG_NOINTRO             BV04
#define PCFLAG_GAG		   BV05
#define PCFLAG_RETIRED             BV06
#define PCFLAG_GUEST               BV07
#define PCFLAG_HASSLUG             BV08
#define PCFLAG_PAGERON		   BV09
#define PCFLAG_NOTITLE             BV10
#define PCFLAG_ROOM                BV11

typedef enum
{
  TIMER_NONE, TIMER_RECENTFIGHT, TIMER_SHOVEDRAG, TIMER_DO_FUN, 
TIMER_APPLIED, TIMER_PKILLED } timer_types;

struct timer_data
{
    TIMER  *	prev;
    TIMER  *	next;
    DO_FUN *	do_fun;
    int		value;
    sh_int	type;
    sh_int	count;
};


/*
 * Channel bits.
 */
#define	CHANNEL_AUCTION		   BV00
#define	CHANNEL_CHAT		   BV01
#define	CHANNEL_QUEST		   BV02
#define	CHANNEL_IMMTALK		   BV03
#define	CHANNEL_VERPINE		   BV04
#define	CHANNEL_ASK		   BV05
#define	CHANNEL_SHOUT		   BV06
#define	CHANNEL_YELL		   BV07
#define CHANNEL_MONITOR		   BV08
#define CHANNEL_LOG		   BV09
#define CHANNEL_SITH		   BV10
#define CHANNEL_CLAN		   BV11
#define CHANNEL_BUILD		   BV12
#define CHANNEL_105		   BV13
#define CHANNEL_AVTALK		   BV14
#define CHANNEL_PRAY		   BV15
#define CHANNEL_COUNCIL 	   BV16
#define CHANNEL_GUILD              BV17
#define CHANNEL_COMM		   BV18
#define CHANNEL_TELLS		   BV19
#define CHANNEL_ORDER              BV20
#define CHANNEL_NEWBIE             BV21
#define CHANNEL_BARTOKK            BV22
#define CHANNEL_OOC                BV23
#define CHANNEL_SHIP               BV24
#define CHANNEL_SYSTEM             BV25
#define CHANNEL_SPACE              BV26
#define CHANNEL_104		   BV27
#define CHANNEL_SPORTS		   BV27
#define CHANNEL_HOLONET		   BV31

#define CHANNEL_CLANTALK	   CHANNEL_CLAN

/* Area defines - Scryn 8/11
 *
 */
#define AREA_DELETED		   BV00
#define AREA_LOADED                BV01

/* Area flags - Narn Mar/96 */
#define AFLAG_NOPKILL               BV00

/*
 * Prototype for a mob.
 * This is the in-memory version of #MOBILES.
 */
struct	mob_index_data
{
    MOB_INDEX_DATA *	next;
    MOB_INDEX_DATA *	next_sort;
    SPEC_FUN *		spec_fun;
    SPEC_FUN *          spec_2;
    SHOP_DATA *		pShop;
    REPAIR_DATA *	rShop;
    MPROG_DATA *	mudprogs;
    int			progtypes;
    char *		player_name;
    char *		short_descr;
    char *		long_descr;
    char *		description;
    sh_int		vnum;
    sh_int		count;
    sh_int		killed;
    sh_int		sex;
    sh_int		level;
    int			act;
    int			affected_by;
    sh_int		alignment;
    sh_int		mobthac0;		/* Unused */
    sh_int		ac;
    sh_int		hitnodice;
    sh_int		hitsizedice;
    sh_int		hitplus;
    sh_int		damnodice;
    sh_int		damsizedice;
    sh_int		damplus;
    sh_int		numattacks;
    int			gold;
    int			exp;
    int			xflags;
    int			resistant;
    int			immune;
    int			susceptible;
    int			attacks;
    int			defenses;
    int			speaks;
    int 		speaking;
    sh_int		position;
    sh_int		defposition;
    sh_int		height;
    sh_int		weight;
    sh_int		race;
    sh_int		hitroll;
    sh_int		damroll;
    sh_int		perm_str;
    sh_int		perm_int;
    sh_int		perm_wis;
    sh_int		perm_dex;
    sh_int		perm_con;
    sh_int		perm_cha;
    sh_int		perm_lck;
    sh_int		perm_frc;
    sh_int		saving_poison_death;
    sh_int		saving_wand;
    sh_int		saving_para_petri;
    sh_int		saving_breath;
    sh_int		saving_spell_staff;
    int                 vip_flags;
};


struct hunt_hate_fear
{
    char *		name;
    CHAR_DATA *		who;
};

struct fighting_data
{
    CHAR_DATA *		who;
    int			xp;
    sh_int		align;
    sh_int		duration;
    sh_int		timeskilled;
};

struct	extracted_char_data
{
    EXTRACT_CHAR_DATA *	next;
    CHAR_DATA *		ch;
    ROOM_INDEX_DATA *	room;
    ch_ret		retcode;
    bool		extract;
};

/*
 * One character (PC or NPC).
 * (Shouldn't most of that build interface stuff use substate, dest_buf,
 * spare_ptr and tempnum?  Seems a little redundant)
 */
struct	char_data
{
    CHAR_DATA *		next;
    CHAR_DATA *		prev;
    CHAR_DATA *		next_in_room;
    CHAR_DATA *		prev_in_room;
    CHAR_DATA *		master;
    CHAR_DATA *		leader;
    FIGHT_DATA *	fighting;
    CHAR_DATA *		reply;
    char * 		owner;
    ROOM_INDEX_DATA *	home;    
    CHAR_DATA *		switched;
    BUG_DATA *		first_bug;
    BUG_DATA *		last_bug;
    CONTRACT_DATA *	first_contract;
    CONTRACT_DATA *	last_contract;
    FELLOW_DATA *	first_fellow;
    FELLOW_DATA *	last_fellow;
    CHAR_DATA *		mount;
    HHF_DATA *		hunting;
    HHF_DATA *		fearing;
    HHF_DATA *		hating;
    SPEC_FUN *		spec_fun;
    SPEC_FUN *		spec_2;
    MPROG_ACT_LIST *	mpact;
    int			mpactnum;
    sh_int		mpscriptpos;
    MOB_INDEX_DATA *	pIndexData;
    DESCRIPTOR_DATA *	desc;
    AFFECT_DATA *	first_affect;
    AFFECT_DATA *	last_affect;
    QUEST_DATA *	first_quest;
    QUEST_DATA *	last_quest;
    NOTE_DATA *		pnote;
    NOTE_DATA *		comments;
    OBJ_DATA *		first_carrying;
    OBJ_DATA *		last_carrying;
    ROOM_INDEX_DATA *	in_room;
    ROOM_INDEX_DATA *	was_in_room;
    ROOM_INDEX_DATA *   was_sentinel;
    ROOM_INDEX_DATA *   plr_home;
    PC_DATA *		pcdata;
    DO_FUN *		last_cmd;
    DO_FUN *		prev_cmd;   /* mapping */
    CHAR_DATA         *challenged;
    CHAR_DATA	      *pazaak_challenged;
    CHAR_DATA	      *pazaak_betted_on;
    CHAR_DATA *       betted_on;
    int		      pazaak_bet_amt;
    int               bet_amt;
    void *		dest_buf;
    void *		dest_buf_2;
    void *		spare_ptr;
    int			tempnum;
    EDITOR_DATA *	editor;
    TIMER	*	first_timer;
    TIMER	*	last_timer;
    char *		name;
    char *		short_descr;
    char *		long_descr;
    char *		description;
    sh_int		num_fighting;
    sh_int		substate;
    sh_int		sex;
    sh_int		race;
    sh_int              top_level;
    sh_int		skill_level[MAX_NSKILL];
    sh_int		skill_percent[MAX_NSKILL];
    sh_int		force_level[MAX_FSKILL];
    sh_int		force_percent[MAX_FSKILL];
    sh_int		class_level[MAX_ABILITY];
    sh_int		trust;
    int			played;
    time_t		logon;
    time_t		save_time;
    sh_int		timer;
    sh_int		wait;
    sh_int		hit;
    sh_int		max_hit;
	int                 force_skill[MAX_FORCE_SKILL];
    sh_int              force_control;
    sh_int              force_sense;
    sh_int              force_alter;
    sh_int              force_chance;
    sh_int              force_identified;
    sh_int              force_level_status;
    sh_int              force_align;
    sh_int              force_converted;
    sh_int              force_type;
    char                *force_master;
    char                *force_temp_master;
    char                *force_disguise;
    int                 force_disguise_count;
	int			wait_state;
    sh_int		mana;
    sh_int		max_mana;
    sh_int		move;
    sh_int		max_move;
    sh_int		numattacks;
    int			gold;
    long		experience;
    int 		act;
    int			feats;
    int			feats2;
    int			feats3;
    int			has_stance;
    sh_int		stance;
    int			droid_feat;
    sh_int		damage_reduction;
    int			force_feats;
    int			affected_by;
    int			carry_weight;
    int			carry_number;
    int			xflags;
    int			resistant;
    int			immune;
    int			susceptible;
    int			attacks;
    int			defenses;
    int			speaks;
    int			speaking;
    sh_int		saving_poison_death;
    sh_int		saving_wand;
    sh_int		saving_para_petri;
    sh_int		saving_breath;
    sh_int		saving_spell_staff;
    sh_int		alignment;
    sh_int		barenumdie;
    sh_int		baresizedie;
    sh_int		mobthac0;
    sh_int		hitroll;
    sh_int		damroll;
    sh_int		hitplus;
    sh_int		damplus;
    sh_int		position;
    sh_int		defposition;
    sh_int		cards;
    sh_int		cover;
    sh_int		height;
    sh_int		weight;
    sh_int		armor;
    sh_int		wimpy;
    int			deaf;
    sh_int		droid_type;
    sh_int		skillpoints;
    sh_int		forcepoints;
    sh_int		darkpoints;
    sh_int		willpower;
    sh_int		resources;
    sh_int		resources_temp;
    sh_int		aerial_defense;
    sh_int		trains;
    sh_int		implant;
    sh_int		enemy_bonus;
    sh_int		efficiency;
    sh_int		familiarity;
    sh_int		target;
    sh_int		sneak_attack;
    sh_int		heart;
    sh_int		heart_use;
    sh_int		coordinate;
    sh_int		precise_attack;
    sh_int		deflect_defense;
    sh_int		deflect_attack;
    sh_int		force_weapon;
    sh_int		secret;
    sh_int		talisman;
    sh_int		inspire_fear;
    sh_int		mastercraft;
    sh_int		specialty;
    sh_int		jury_rig;
    sh_int		lightsaber_defense;
    sh_int		reputation;
    sh_int		dodge_bonus;
    sh_int		unused_feats;
    sh_int		fortitude;
    sh_int		reflexes;
    sh_int		perm_str;
    sh_int		perm_int;
    sh_int		perm_wis;
    sh_int		perm_dex;
    sh_int		perm_con;
    sh_int		perm_cha;
    sh_int		perm_lck;
    sh_int		perm_frc;
    sh_int		mod_str;
    sh_int		mod_int;
    sh_int		mod_wis;
    sh_int		mod_dex;
    sh_int		mod_con;
    sh_int		mod_cha;
    sh_int		mod_lck;
    sh_int		mod_frc;
    sh_int		mental_state;		/* simplified */
    sh_int		emotional_state;	/* simplified */
    int			pagelen;                        /* BUILD INTERFACE */
    sh_int		inter_page;                     /* BUILD INTERFACE */
    sh_int		inter_type;                     /* BUILD INTERFACE */
    char  		*inter_editing;                 /* BUILD INTERFACE */
    int			inter_editing_vnum;             /* BUILD INTERFACE */
    sh_int		inter_substate;                 /* BUILD INTERFACE */
    int			retran;
    int			regoto;
    sh_int		mobinvis;	/* Mobinvis level SB */
    int                 vip_flags;
    sh_int              backup_wait;	/* reinforcements */
    int                 backup_mob;     /* reinforcements */
    sh_int              was_stunned;
    char            *   mob_clan;    /* for spec_clan_guard.. set by postguard */
    GUARD_DATA      *   guard_data;
    sh_int              main_ability;
    sh_int		secondary_ability;
    sh_int		rppoints;
    char * comfreq;
    char * rank;
    int pheight, build;
    CHAR_DATA * aiming_at;
};


struct killed_data
{
    sh_int		vnum;
    char		count;
};

struct  bug_data
{
    char *		name;
    BUG_DATA *		next_in_bug;    
    BUG_DATA *		prev_in_bug;
};

struct  contract_data
{
    char *		target;
    int			amount;
    CONTRACT_DATA *	next_in_contract;
    CONTRACT_DATA *	prev_in_contract;
};

struct  fellow_data
{

    char *		victim;
    char *		knownas;
    FELLOW_DATA *	next;
    FELLOW_DATA *	prev;
};

/*
 * Data which only PC's have.
 */
struct	pc_data
{
    CLAN_DATA *		clan;
    AREA_DATA *		area;
    ROOM_INDEX_DATA *   roomarena;
    char *		student;
    char *		master;
    char *		homepage;
    char *		screenname;
    char *		image;
    char *		clan_name;
    char *		pwd;
    char *		email;
    char *		bamfin;
    char *		bamfout;
	int   lost_attacks;
    char *              rank;
    int			shipnum;
    char *		shipname;
    char *		title;
    char *		disguise;
    char *		protector;
    char * 		protected;
    char *		bestowments;	/* Special bestowed commands	   */
    sh_int		force_status;
    sh_int		trials;
    int			act2;
    int                 flags;		/* Whether the player is deadly and whatever else we add.      */
    int			pkills;		/* Number of pkills on behalf of clan */
    int			pdeaths;	/* Number of times pkilled (legally)  */
    int			mkills;		/* Number of mobs killed		   */
    int			mdeaths;	/* Number of deaths due to mobs       */
    int			illegal_pk;	/* Number of illegal pk's committed   */
    long		loan;
    sh_int		has_master;
    sh_int		has_trained;
    sh_int		can_invest;
    sh_int		age;
    char *		fiance;
    char *		propose;
    char *		proposed;
    char *		spouse;
    int			forcerank;
    char * 		last_name;    
    long int            outcast_time;	/* The time at which the char was outcast */
    long int            restore_time;	/* The last time the char did a restore all */
    sh_int		alchemy_mod;
    int			alchemy;
    sh_int		r_range_lo;	/* room range */
    sh_int		r_range_hi;
    sh_int		m_range_lo;	/* mob range  */
    sh_int		m_range_hi;
    sh_int		o_range_lo;	/* obj range  */
    sh_int		o_range_hi;		
    char *		tell_snoop;	/* Tell snoop */
    sh_int		wizinvis;	/* wizinvis level */
    sh_int		min_snoop;	/* minimum snoop level */
    sh_int		condition	[MAX_CONDS];
    sh_int		learned		[MAX_SKILL];
    KILLED_DATA		killed		[MAX_KILLTRACK];
    sh_int		quest_number;	/* current *QUEST BEING DONE* DON'T REMOVE! */
    sh_int		quest_curr;	/* current number of quest points */
    int			quest_accum;	/* quest points accumulated in players life */
    int			auth_state;
    time_t		release_date;	/* Auto-helling.. Altrag */
    char *		helled_by;
    char *		bio;		/* Personal Bio */
    char *		authed_by;	/* what crazy imm authed this name ;) */
    SKILLTYPE *		special_skills[5]; /* personalized skills/spells */
    char *		prompt;		/* User config prompts */
    char *		subprompt;	/* Substate prompt */
    sh_int		pagerlen;	/* For pager (NOT menus) */
    bool		openedtourney;
    sh_int              addiction[10];
    sh_int              drug_level[10];
    char *		store_title;
    bool		is_hacking;
    int                 wanted_flags;
    long		bank;
    int			salary;
    int			force_bonus;
    sh_int		reputation;
};

#define IS_ADULT		0
#define IS_CHILD		1

#define ALCHEMY_CLAWS		BV00
#define ALCHEMY_HORNS		BV01
#define ALCHEMY_DARKVISION	BV02
#define ALCHEMY_DEFENSE		BV03
#define ALCHEMY_STRENGTH	BV04
#define ALCHEMY_DEXTERITY	BV05
#define ALCHEMY_CONSTITUTION	BV06
#define ALCHEMY_INTELLIGENCE	BV07
#define ALCHEMY_WISDOM		BV08
#define ALCHEMY_CHARISMA	BV09

#define IS_FAMOUS	0
#define IS_INFAMOUS	1

#define NOT_PASSED	0
#define HAS_PASSED	1


/*
 * Liquids.
 */
#define LIQ_WATER        0
#define LIQ_MAX		19

struct	liq_type
{
    char *	liq_name;
    char *	liq_color;
    sh_int	liq_affect[3];
};



/*
 * Extra description data for a room or object.
 */
struct	extra_descr_data
{
    EXTRA_DESCR_DATA *next;	/* Next in list                     */
    EXTRA_DESCR_DATA *prev;	/* Previous in list                 */
    char *keyword;              /* Keyword in look/examine          */
    char *description;          /* What to see                      */
};



/*
 * Prototype for an object.
 */
struct	obj_index_data
{
    OBJ_INDEX_DATA *	next;
    OBJ_INDEX_DATA *	next_sort;
    EXTRA_DESCR_DATA *	first_extradesc;
    EXTRA_DESCR_DATA *	last_extradesc;
    AFFECT_DATA *	first_affect;
    AFFECT_DATA *	last_affect;
    MPROG_DATA *	mudprogs;               /* objprogs */
    int			progtypes;              /* objprogs */
    char *		name;
    char *		short_descr;
    char *		description;
    char *		action_desc;
    int			vnum;
    sh_int              level;
    sh_int		item_type;
    int			extra_flags;
    int			magic_flags; /*Need more bitvectors for spells - Scryn*/
    int			wear_flags;
    sh_int		count;
    sh_int		weight;
    int			cost;
    int			value	[6];
    int			serial;
    sh_int		layers;
    int			rent;			/* Unused */
};


/*
 * One object.
 */
struct	obj_data
{
    OBJ_DATA *		next;
    OBJ_DATA *		prev;
    OBJ_DATA *		next_content;
    OBJ_DATA *		prev_content;
    OBJ_DATA *		first_content;
    OBJ_DATA *		last_content;
    OBJ_DATA *		in_obj;
    CHAR_DATA *		carried_by;
    EXTRA_DESCR_DATA *	first_extradesc;
    EXTRA_DESCR_DATA *	last_extradesc;
    AFFECT_DATA *	first_affect;
    AFFECT_DATA *	last_affect;
    OBJ_INDEX_DATA *	pIndexData;
    ROOM_INDEX_DATA *	in_room;
    char *		armed_by;
    char *		name;
    char *		short_descr;
    char *		description;
    char *		action_desc;
    sh_int		item_type;
    sh_int		mpscriptpos;
    int			extra_flags;
    int			magic_flags; /*Need more bitvectors for spells - Scryn*/
    int			wear_flags; 
    int                 blaster_setting;
    MPROG_ACT_LIST *	mpact;		/* mudprogs */
    int			mpactnum;	/* mudprogs */
    sh_int		wear_loc;
    sh_int		weight;
    char	*	killer;		/* This serves one real purpose. When making a corpse we assign the killers name to it. */
    int			cost;
    sh_int		level;
    sh_int		timer;
    int			value	[6];
    sh_int		count;		/* support for object grouping */
    int			serial;		/* serial number	       */
};


/*
 * Exit data.
 */
struct	exit_data
{
    EXIT_DATA *		prev;		/* previous exit in linked list	*/
    EXIT_DATA *		next;		/* next exit in linked list	*/
    EXIT_DATA *		rexit;		/* Reverse exit pointer		*/
    ROOM_INDEX_DATA *	to_room;	/* Pointer to destination room	*/
    char *		keyword;	/* Keywords for exit or door	*/
    char *		description;	/* Description of exit		*/
    int			vnum;		/* Vnum of room exit leads to	*/
    int			rvnum;		/* Vnum of room in opposite dir	*/
    int			exit_info;	/* door states & other flags	*/
    int			key;		/* Key vnum			*/
    sh_int		vdir;		/* Physical "direction"		*/
    sh_int		distance;	/* how far to the next room	*/
};



/*
 * Reset commands:
 *   '*': comment
 *   'M': read a mobile
 *   'O': read an object
 *   'P': put object in object
 *   'G': give object to mobile
 *   'E': equip object to mobile
 *   'H': hide an object
 *   'B': set a bitvector
 *   'T': trap an object
 *   'D': set state of door
 *   'R': randomize room exits
 *   'S': stop (end of list)
 */

/*
 * Area-reset definition.
 */
struct	reset_data
{
    RESET_DATA *	next;
    RESET_DATA *	prev;
    char		command;
    int			extra;
    int			arg1;
    int			arg2;
    int			arg3;
};

/* Constants for arg2 of 'B' resets. */
#define	BIT_RESET_DOOR			0
#define BIT_RESET_OBJECT		1
#define BIT_RESET_MOBILE		2
#define BIT_RESET_ROOM			3
#define BIT_RESET_TYPE_MASK		0xFF	/* 256 should be enough */
#define BIT_RESET_DOOR_THRESHOLD	8
#define BIT_RESET_DOOR_MASK		0xFF00	/* 256 should be enough */
#define BIT_RESET_SET			BV30
#define BIT_RESET_TOGGLE		BV31
#define BIT_RESET_FREEBITS	  0x3FFF0000	/* For reference */



/*
 * Area definition.
 */
struct	area_data
{
    AREA_DATA *		next;
    AREA_DATA *		prev;
    AREA_DATA *		next_sort;
    AREA_DATA *		prev_sort;
    RESET_DATA *	first_reset;
    ROOM_INDEX_DATA *   first_room;
    ROOM_INDEX_DATA *   last_room;    
    RESET_DATA *	last_reset;
    PLANET_DATA *       planet;
    AREA_DATA *   	next_on_planet;
    AREA_DATA *    	prev_on_planet;
    char *		name;
    char *		filename;
    int                 flags;
    sh_int              status;  /* h, 8/11 */
    sh_int		age;
    sh_int		nplayer;
    sh_int		reset_frequency;
    int			low_r_vnum;
    int			hi_r_vnum;
    int			low_o_vnum;
    int			hi_o_vnum;
    sh_int		low_m_vnum;
    sh_int		hi_m_vnum;
    int			low_soft_range;
    int			hi_soft_range;
    int			low_hard_range;
    int			hi_hard_range;
    char *		author; /* Scryn */
    char *              resetmsg; /* Rennard */
    RESET_DATA *	last_mob_reset;
    RESET_DATA *	last_obj_reset;
    sh_int		max_players;
    int			mkills;
    int			mdeaths;
    int			pkills;
    int			pdeaths;
    int			gold_looted;
    int			illegal_pk;
    int			high_economy;
    int			low_economy;
};



/*
 * Load in the gods building data. -- Altrag
 */
struct	godlist_data
{
    GOD_DATA *		next;
    GOD_DATA *		prev;
    int			level;
    int			low_r_vnum;
    int			hi_r_vnum;
    int			low_o_vnum;
    int			hi_o_vnum;
    sh_int		low_m_vnum;
    sh_int		hi_m_vnum;
};


/*
 * Used to keep track of system settings and statistics		-Thoric
 */
struct	system_data
{
    int		maxplayers;		/* Maximum players this boot   */
    int		alltimemax;		/* Maximum players ever	  */
    char *	time_of_max;		/* Time of max ever */
    bool	NO_NAME_RESOLVING;	/* Hostnames are not resolved  */
    bool    	DENY_NEW_PLAYERS;	/* New players cannot connect  */
    bool	WAIT_FOR_AUTH;		/* New players must be auth'ed */
    bool	WIZLOCK;
    sh_int 	newbie_purge; /* Level to auto-purge newbies at - Samson 12-27-98 */
    sh_int  	regular_purge; /* Level to purge normal players at - Samson 12-27-98 */
    bool	CLEANPFILES; /* Should the mud clean up pfiles daily? - Samson 12-27-98 */    
    sh_int	read_all_mail;		/* Read all player mail(was 54)*/
    sh_int	read_mail_free;		/* Read mail for free (was 51) */
    sh_int	write_mail_free;	/* Write mail for free(was 51) */
    sh_int	take_others_mail;	/* Take others mail (was 54)   */
    sh_int	muse_level;		/* Level of muse channel */
    sh_int	think_level;		/* Level of think channel LEVEL_HIGOD*/
    sh_int	build_level;		/* Level of build channel LEVEL_BUILD*/
    sh_int	log_level;		/* Level of log channel LEVEL LOG*/
    sh_int	level_modify_proto;	/* Level to modify prototype stuff LEVEL_LESSER */
    sh_int	level_override_private;	/* override private flag */
    sh_int	level_mset_player;	/* Level to mset a player */
    sh_int	stun_plr_vs_plr;	/* Stun mod player vs. player */
    sh_int	stun_regular;		/* Stun difficult */
    sh_int	dam_plr_vs_plr;		/* Damage mod player vs. player */
    sh_int	dam_plr_vs_mob;		/* Damage mod player vs. mobile */
    sh_int	dam_mob_vs_plr;		/* Damage mod mobile vs. player */
    sh_int	dam_mob_vs_mob;		/* Damage mod mobile vs. mobile */
    sh_int	level_getobjnotake;     /* Get objects without take flag */
    sh_int      level_forcepc;          /* The level at which you can use force on players. */
    sh_int	max_sn;			/* Max skills */
    char       *guild_overseer;         /* Pointer to char containing the name of the */
    char       *guild_advisor;		/* guild overseer and advisor. */ 
    int		save_flags;		/* Toggles for saving conditions */
    sh_int	save_frequency;		/* How old to autosave someone */
};


/*
 * Room type.
 */
struct	room_index_data
{
    ROOM_INDEX_DATA *	next;
    ROOM_INDEX_DATA *	next_sort;
    CHAR_DATA *		first_person;
    CHAR_DATA *		last_person;
    OBJ_DATA *		first_content;
    OBJ_DATA *		last_content;
    EXTRA_DESCR_DATA *	first_extradesc;
    EXTRA_DESCR_DATA *	last_extradesc;
    AREA_DATA *		area;
    EXIT_DATA *		first_exit;
    EXIT_DATA *		last_exit;
    ROOM_INDEX_DATA *	next_in_area;
    ROOM_INDEX_DATA *	prev_in_area;
    ROOM_INDEX_DATA *	next_in_ship;
    ROOM_INDEX_DATA *	prev_in_ship;    
    char *		name;
    int			exvnum;
    MAP_DATA *		map;                 /* maps */
    SHIP_DATA * 	first_ship;
    SHIP_DATA * 	last_ship;	    
    char *		description;
    int			vnum;
    int			room_flags;
    int			room_flags2;
    int			cargo_flags;
    int			art;
    int			bacta;
    int			semi_gem;
    int			prec_gem;
    int			comm_ore;
    int			rare_ore;
    int			spice;
    int			slaves;
    int			weapons;
    MPROG_ACT_LIST *	mpact;               /* mudprogs */
    int			mpactnum;            /* mudprogs */
    MPROG_DATA *	mudprogs;            /* mudprogs */
    sh_int		mpscriptpos;
    int			progtypes;           /* mudprogs */
    sh_int		light;
    sh_int		sector_type;
    int			tele_vnum;
    sh_int		tele_delay;
    sh_int		tunnel;		     /* max people that will fit */
};

/*
 * Delayed teleport type.
 */
struct	teleport_data
{
    TELEPORT_DATA *	next;
    TELEPORT_DATA *	prev;
    ROOM_INDEX_DATA *	room;
    sh_int		timer;
};


/*
 * Types of skill numbers.  Used to keep separate lists of sn's
 * Must be non-overlapping with spell/skill types,
 * but may be arbitrary beyond that.
 */
#define TYPE_UNDEFINED               -1
#define TYPE_MISSILE			111
#define TYPE_HIT                     1000  /* allows for 1000 skills/spells */
#define TYPE_HERB		     2000  /* allows for 1000 attack types  */
#define TYPE_PERSONAL		     3000  /* allows for 1000 herb types    */

/*
 *  Target types.
 */
typedef enum
{
  TAR_IGNORE, TAR_CHAR_OFFENSIVE, TAR_CHAR_DEFENSIVE, TAR_CHAR_SELF,
  TAR_OBJ_INV
} target_types;

typedef enum
{
  SKILL_UNKNOWN, SKILL_SPELL, SKILL_SKILL, SKILL_WEAPON, SKILL_TONGUE,
  SKILL_HERB
} skill_types;



struct timerset
{
  int num_uses;
  struct timeval total_time;
  struct timeval min_time;
  struct timeval max_time;
};



/*
 * Skills include spells as a particular case.
 */
struct	skill_type
{
    char *	name;			/* Name of skill		*/
    SPELL_FUN *	spell_fun;		/* Spell pointer (for spells)	*/
    DO_FUN *	skill_fun;		/* Skill pointer (for skills)	*/
    sh_int	target;			/* Legal targets		*/
    sh_int	minimum_position;	/* Position for caster / user	*/
    sh_int	slot;			/* Slot for #OBJECT loading	*/
    sh_int	min_mana;		/* Minimum mana used		*/
    sh_int	beats;			/* Rounds required to use skill	*/
    char *	noun_damage;		/* Damage message		*/
    char *	msg_off;		/* Wear off message		*/
    sh_int	guild;			/* Which guild the skill belongs to */
    sh_int	min_level;		/* Minimum level to be able to cast */
    sh_int	type;			/* Spell/Skill/Weapon/Tongue	*/
    int		flags;			/* extra stuff			*/
    char *	hit_char;		/* Success message to caster	*/
    char *	hit_vict;		/* Success message to victim	*/
    char *	hit_room;		/* Success message to room	*/
    char *	miss_char;		/* Failure message to caster	*/
    char *	miss_vict;		/* Failure message to victim	*/
    char *	miss_room;		/* Failure message to room	*/
    char *	die_char;		/* Victim death msg to caster	*/
    char *	die_vict;		/* Victim death msg to victim	*/
    char *	die_room;		/* Victim death msg to room	*/
    char *	imm_char;		/* Victim immune msg to caster	*/
    char *	imm_vict;		/* Victim immune msg to victim	*/
    char *	imm_room;		/* Victim immune msg to room	*/
    char *	dice;			/* Dice roll			*/
    int		value;			/* Misc value			*/
    char	saves;			/* What saving spell applies	*/
    char	difficulty;		/* Difficulty of casting/learning */
    SMAUG_AFF *	affects;		/* Spell affects, if any	*/
    char *	components;		/* Spell components, if any	*/
    char *	teachers;		/* Skill requires a special teacher */
    char	participants;		/* # of required participants	*/
    struct	timerset	userec;	/* Usage record			*/
    int         alignment;              /* for jedi powers */
};


struct  auction_data
{
    OBJ_DATA  * item;   /* a pointer to the item */
    CHAR_DATA * seller; /* a pointer to the seller - which may NOT quit */
    CHAR_DATA * buyer;  /* a pointer to the buyer - which may NOT quit */
    int         bet;    /* last bet - or 0 if noone has bet anything */
    sh_int      going;  /* 1,2, sold */
    sh_int      pulse;  /* how many pulses (.25 sec) until another call-out ? */
    int 	starting;
};

/*
 * These are skill_lookup return values for basic skills and spells.
 */
extern sh_int	gsn_rage;
extern sh_int	gsn_battlemind;
extern sh_int	gsn_enhance_ability;
extern sh_int	gsn_enhance_senses;
extern sh_int	gsn_sithsorcery;
extern sh_int	gsn_forcemind;
extern sh_int	gsn_fear;
extern sh_int   gsn_force_defense;
extern sh_int	gsn_intimidate;
extern sh_int	gsn_callforce;
extern sh_int	gsn_smallspace;
extern sh_int	gsn_mediumspace;
extern sh_int   gsn_largespace;
extern sh_int   gsn_weaponsystems;
extern sh_int   gsn_navigation;
extern sh_int   gsn_shipsystems;
extern sh_int   gsn_tractorbeams;
extern sh_int   gsn_spacecombat;
extern sh_int   gsn_spacecombat2;
extern sh_int   gsn_spacecombat3;
extern sh_int   gsn_bomb;

extern sh_int   gsn_shipdesign;

/* Technician skills */
extern sh_int	gsn_makemodule;
extern sh_int	gsn_installmodule;
extern sh_int	gsn_showmodules;
extern sh_int   gsn_shipmaintenance; 
extern sh_int   gsn_scanbugs; 
extern sh_int	gsn_removebug;
extern sh_int	gsn_removemodule;

/* These are bh skills */
extern sh_int	gsn_ambush;
extern sh_int	gsn_bind;
extern sh_int	gsn_gag;

extern sh_int   gsn_battle_command;
extern sh_int   gsn_reinforcements;
extern sh_int   gsn_postguard;

extern sh_int   gsn_addpatrol;
extern sh_int   gsn_eliteguard;
extern sh_int   gsn_specialforces;
extern sh_int   gsn_jail;
extern sh_int   gsn_smalltalk;
extern sh_int   gsn_propeganda;
extern sh_int   gsn_bribe;
extern sh_int   gsn_seduce;
extern sh_int   gsn_masspropeganda;
extern sh_int   gsn_gather_intelligence;

/* hunter assassin gsn ints */
extern sh_int	gsn_plantbug;
extern sh_int	gsn_showbugs;
extern sh_int	gsn_silent;
extern sh_int	gsn_retreat;

/* The gsn ints for the slicers */
extern sh_int   gsn_spy;
extern sh_int   gsn_makecommsystem;
extern sh_int   gsn_sabotage;
extern sh_int   gsn_commsystem;
extern sh_int   gsn_codecrack;
extern sh_int   gsn_slicebank;
extern sh_int   gsn_inquire;
extern sh_int   gsn_makedatapad;
extern sh_int   gsn_disable;
extern sh_int   gsn_assignpilot;
extern sh_int   gsn_checkprints;


extern sh_int   gsn_torture;
extern sh_int   gsn_snipe;
extern sh_int   gsn_throw;
extern sh_int   gsn_deception;
extern sh_int   gsn_disguise;
extern sh_int   gsn_mine;
extern sh_int   gsn_first_aid;

extern sh_int   gsn_beg;
extern sh_int   gsn_makeblade;
extern sh_int	gsn_makebug;
extern sh_int	gsn_makebeacon;
extern sh_int   gsn_makepike;
extern sh_int   gsn_makejewelry;
extern sh_int   gsn_makeblaster;
extern sh_int   gsn_makelight;
extern sh_int   gsn_makecomlink;
extern sh_int   gsn_makegrenade;
extern sh_int   gsn_makeshipbomb;
extern sh_int   gsn_makelandmine;
extern sh_int   gsn_makearmor;
extern sh_int   gsn_makeshield;
extern sh_int   gsn_makecontainer;
extern sh_int   gsn_gemcutting;
extern sh_int   gsn_makelightsaber;
extern sh_int   gsn_makeduallightsaber;
extern sh_int   gsn_repair;
extern sh_int   gsn_shiprepair;
extern sh_int   gsn_spice_refining;
 
extern	sh_int	gsn_detrap;
extern	sh_int	gsn_backstab;
extern	sh_int	gsn_dualstab;
extern	sh_int	gsn_bargain;
extern  sh_int  gsn_circle;
extern	sh_int	gsn_dodge;
extern	sh_int	gsn_hide;
extern	sh_int	gsn_concealment;
extern	sh_int	gsn_peek;
extern	sh_int	gsn_pick_lock;
extern  sh_int  gsn_scan;
extern	sh_int	gsn_sneak;
extern	sh_int	gsn_steal;
extern	sh_int	gsn_gouge;
extern	sh_int	gsn_track;
extern	sh_int	gsn_search;
extern  sh_int  gsn_dig;
extern	sh_int	gsn_mount;
extern  sh_int  gsn_bashdoor;
extern	sh_int	gsn_berserk;
extern	sh_int	gsn_hitall;
extern	sh_int	gsn_pickshiplock;
extern	sh_int	gsn_hijack;

extern	sh_int	gsn_disarm;
extern	sh_int	gsn_enhanced_damage;
extern	sh_int	gsn_kick;
extern	sh_int	gsn_parry;
extern	sh_int	gsn_rescue;
extern	sh_int	gsn_second_attack;
extern	sh_int	gsn_third_attack;
extern	sh_int	gsn_dual_wield;
extern  sh_int  gsn_reflect;


extern	sh_int	gsn_aid;
extern  sh_int  gsn_plantbeacon;
extern  sh_int  gsn_showbeacons;
extern  sh_int  gsn_checkbeacons;
extern  sh_int  gsn_nullifybeacons;
extern  sh_int  gsn_makebinders;
extern 	sh_int	gsn_launchers;
extern	sh_int	gsn_makemissile;
extern	sh_int	gsn_makeempgrenade;
extern  sh_int	gsn_makegoggles;
extern  sh_int	gsn_truesight;
extern  sh_int  gsn_barrelroll;
extern  sh_int  gsn_juke;

/* used to do specific lookups */
extern	sh_int	gsn_first_spell;
extern	sh_int	gsn_first_skill;
extern	sh_int	gsn_first_weapon;
extern	sh_int	gsn_first_tongue;
extern	sh_int	gsn_top_sn;

/* spells */
extern	sh_int	gsn_blindness;
extern	sh_int	gsn_charm_person;
extern  sh_int  gsn_aqua_breath;
extern	sh_int	gsn_invis;
extern	sh_int	gsn_mass_invis;
extern	sh_int	gsn_poison;
extern	sh_int	gsn_sleep;
extern  sh_int  gsn_possess;
extern	sh_int	gsn_fireball;		/* for fireshield  */
extern	sh_int	gsn_lightning_bolt;	/* for shockshield */

/* newer attack skills */
extern	sh_int	gsn_punch;
extern	sh_int	gsn_bash;
extern	sh_int	gsn_stun;

extern  sh_int  gsn_poison_weapon;
extern	sh_int	gsn_climb;

extern	sh_int	gsn_blasters;
extern	sh_int	gsn_force_pikes;
extern	sh_int	gsn_bowcasters;
extern	sh_int	gsn_lightsabers;
extern	sh_int	gsn_vibro_blades;
extern	sh_int	gsn_flexible_arms;
extern	sh_int	gsn_talonous_arms;
extern	sh_int	gsn_bludgeons;

extern  sh_int  gsn_grip;

/* languages */
extern sh_int                  gsn_basic;
extern sh_int                  gsn_wookiee;
extern sh_int                  gsn_twilek;
extern sh_int                  gsn_rodian;
extern sh_int                  gsn_hutt;
extern sh_int                  gsn_mon_calamari;
extern sh_int                  gsn_noghri;
extern sh_int                  gsn_ewok;
extern sh_int                  gsn_ithorian;
extern sh_int                  gsn_gotal;
extern sh_int                  gsn_devaronian;
extern sh_int                  gsn_binary;
extern sh_int                  gsn_firrerreo;
extern sh_int                  gsn_gamorrean;
extern sh_int                  gsn_togorian;
extern sh_int                  gsn_shistavanen;
extern sh_int                  gsn_jawa;
extern sh_int                  gsn_kubaz;
extern sh_int                  gsn_adarian;
extern sh_int                  gsn_verpine;
extern sh_int                  gsn_defel;
extern sh_int                  gsn_trandoshan;
extern sh_int                  gsn_hapan;
extern sh_int                  gsn_quarren;
extern sh_int                  gsn_sullustan;
extern sh_int                  gsn_falleen;
extern sh_int                  gsn_barabel;
extern sh_int                  gsn_yevethan;
extern sh_int                  gsn_gand;
extern sh_int                  gsn_coynite;
extern sh_int                  gsn_duinuogwuin;
extern sh_int                  gsn_droid;

/*
 * Utility macros.
 */
#define UMIN(a, b)		((a) < (b) ? (a) : (b))
#define UMAX(a, b)		((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)		((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)		((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)		((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_SET(flag, bit)	((flag) & (bit))
#define SET_BIT(var, bit)	((var) |= (bit))
#define REMOVE_BIT(var, bit)	((var) &= ~(bit))
#define TOGGLE_BIT(var, bit)	((var) ^= (bit))
#define CH(d)			((d)->original ? (d)->original : (d)->character)

/*
 * Memory allocation macros.
 */

#define CREATE(result, type, number)				\
do								\
{								\
   if (!((result) = (type *) calloc ((number), sizeof(type))))	\
	{ perror("malloc failure"); abort(); }			\
} while(0)

#define RECREATE(result,type,number)				\
do								\
{								\
  if (!((result) = (type *) realloc ((result), sizeof(type) * (number))))\
	{ perror("realloc failure"); abort(); }			\
} while(0)


#define DISPOSE(point) 						\
do								\
{								\
  if (!(point))							\
  {								\
	bug( "Freeing null pointer" ); \
	fprintf( stderr, "DISPOSEing NULL in %s, line %d\n", __FILE__, __LINE__ ); \
  }								\
  else free(point);						\
  point = NULL;							\
} while(0)

#ifdef HASHSTR
#define STRALLOC(point)  str_alloc((point))
#define QUICKLINK(point)	quick_link((point))
#define QUICKMATCH(p1, p2)	(int) (p1) == (int) (p2)
#define STRFREE(point)						\
do								\
{								\
  if (!(point))							\
  {								\
	bug( "Freeing null pointer" );	 			\
	fprintf( stderr, "STRFREEing NULL in %s, line %d\n", __FILE__, __LINE__ ); \
  }								\
  else if (str_free((point))==-1) 				\
    fprintf( stderr, "STRFREEing bad pointer in %s, line %d\n", __FILE__, __LINE__ ); \
} while(0)
#else
#define STRALLOC(point)		str_dup((point))
#define QUICKLINK(point)	str_dup((point))
#define QUICKMATCH(p1, p2)	strcmp((p1), (p2)) == 0
#define STRFREE(point)						\
do								\
{								\
  if (!(point))							\
  {								\
	bug( "Freeing null pointer" );				\
	fprintf( stderr, "STRFREEing NULL in %s, line %d\n", __FILE__, __LINE__ ); \
  }								\
  else free((point));						\
} while(0)
#endif

/* double-linked list handling macros -Thoric */

#define LINK(link, first, last, next, prev)			\
do								\
{								\
    if ( !(first) )						\
      (first)			= (link);			\
    else							\
      (last)->next		= (link);			\
    (link)->next		= NULL;				\
    (link)->prev		= (last);			\
    (last)			= (link);			\
} while(0)

#define INSERT(link, insert, first, next, prev)			\
do								\
{								\
    (link)->prev		= (insert)->prev;		\
    if ( !(insert)->prev )					\
      (first)			= (link);			\
    else							\
      (insert)->prev->next	= (link);			\
    (insert)->prev		= (link);			\
    (link)->next		= (insert);			\
} while(0)

#define UNLINK(link, first, last, next, prev)			\
do								\
{								\
    if ( !(link)->prev )					\
      (first)			= (link)->next;			\
    else							\
      (link)->prev->next	= (link)->next;			\
    if ( !(link)->next )					\
      (last)			= (link)->prev;			\
    else							\
      (link)->next->prev	= (link)->prev;			\
} while(0)


#define CHECK_LINKS(first, last, next, prev, type)		\
do {								\
  type *ptr, *pptr = NULL;					\
  if ( !(first) && !(last) )					\
    break;							\
  if ( !(first) )						\
  {								\
    bug( "CHECK_LINKS: last with NULL first!  %s.",		\
        __STRING(first) );					\
    for ( ptr = (last); ptr->prev; ptr = ptr->prev );		\
    (first) = ptr;						\
  }								\
  else if ( !(last) )						\
  {								\
    bug( "CHECK_LINKS: first with NULL last!  %s.",		\
        __STRING(first) );					\
    for ( ptr = (first); ptr->next; ptr = ptr->next );		\
    (last) = ptr;						\
  }								\
  if ( (first) )						\
  {								\
    for ( ptr = (first); ptr; ptr = ptr->next )			\
    {								\
      if ( ptr->prev != pptr )					\
      {								\
        bug( "CHECK_LINKS(%s): %p:->prev != %p.  Fixing.",	\
            __STRING(first), ptr, pptr );			\
        ptr->prev = pptr;					\
      }								\
      if ( ptr->prev && ptr->prev->next != ptr )		\
      {								\
        bug( "CHECK_LINKS(%s): %p:->prev->next != %p.  Fixing.",\
            __STRING(first), ptr, ptr );			\
        ptr->prev->next = ptr;					\
      }								\
      pptr = ptr;						\
    }								\
    pptr = NULL;						\
  }								\
  if ( (last) )							\
  {								\
    for ( ptr = (last); ptr; ptr = ptr->prev )			\
    {								\
      if ( ptr->next != pptr )					\
      {								\
        bug( "CHECK_LINKS (%s): %p:->next != %p.  Fixing.",	\
            __STRING(first), ptr, pptr );			\
        ptr->next = pptr;					\
      }								\
      if ( ptr->next && ptr->next->prev != ptr )		\
      {								\
        bug( "CHECK_LINKS(%s): %p:->next->prev != %p.  Fixing.",\
            __STRING(first), ptr, ptr );			\
        ptr->next->prev = ptr;					\
      }								\
      pptr = ptr;						\
    }								\
  }								\
} while(0)


#define ASSIGN_GSN(gsn, skill)					\
do								\
{								\
    if ( ((gsn) = skill_lookup((skill))) == -1 )		\
	fprintf( stderr, "ASSIGN_GSN: Skill %s not found.\n",	\
		(skill) );					\
} while(0)

#define CHECK_SUBRESTRICTED(ch)					\
do								\
{								\
    if ( (ch)->substate == SUB_RESTRICTED )			\
    {								\
	send_to_char( "You cannot use this command from within another command.\n\r", ch );	\
	return;							\
    }								\
} while(0)


/*
 * Character macros.
 */
#define IS_NPC(ch)		(IS_SET((ch)->act, ACT_IS_NPC))
#define HAS_EMBARGO(planet, sn) (IS_SET(planet->embargo, sn) )
#define IS_IMMORTAL(ch)		(get_trust((ch)) >= LEVEL_IMMORTAL)
#define IS_DROID(ch)		(ch->race == RACE_DROID)
#define IS_DARK(ch)		( ( !IS_NPC(ch) && ch->darkpoints >= get_curr_wis(ch) ) || ( IS_NPC(ch) && ch->alignment < 0 ) )
#define IS_TAINTED(ch)		( ch->darkpoints >= ( get_curr_wis(ch)/2) && ch->darkpoints < get_curr_wis(ch) )
#define IS_FORCER(ch)		( ch->class_level[FORCE_ADEPT_ABILITY] != 0 || ch->class_level[JEDICONSULAR_ABILITY] != 0 || ch->class_level[JEDIGUARDIAN_ABILITY] != 0 )
#define GET_FORT(ch)		( ch->fortitude + stat_table[get_curr_con(ch)].mod )
#define GET_REFL(ch)		( ch->reflexes + stat_table[get_curr_dex(ch)].mod )
#define GET_WILL(ch)		( ch->willpower + stat_table[get_curr_wis(ch)].mod )
#define HAS_DROID(ch, sn)	(IS_SET((ch)->droid_feat, (sn)))
#define HAS_CYBER(ch, sn)	(IS_SET((ch)->implant, (sn)))
#define HAS_STANCE(ch, sn)	(IS_SET((ch)->has_stance, (sn)))
#define HAS_FEAT(ch, sn)	(IS_SET((ch)->feats, (sn)))
#define HAS_FEAT2(ch, sn)	(IS_SET((ch)->feats2, (sn)))
#define HAS_FEAT3(ch, sn)	(IS_SET((ch)->feats3, (sn)))
#define HAS_FFEAT(ch, sn)	(IS_SET((ch)->force_feats, (sn)))
#define IS_JEDI(ch)		(ch->class_level[JEDICONSULAR_ABILITY] != 0 || ch->class_level[JEDIGUARDIAN_ABILITY] != 0)
#define IS_HERO(ch)		(get_trust((ch)) >= LEVEL_HERO)
#define IS_AFFECTED(ch, sn)	(IS_SET((ch)->affected_by, (sn)))
#define HAS_BODYPART(ch, part)	(ch->xflags == 0 || IS_SET((ch)->xflags, (part)))

#define IS_GOOD(ch)		((ch)->alignment >= 350)
#define IS_EVIL(ch)		((ch)->alignment <= -350)
#define IS_NEUTRAL(ch)		(!IS_GOOD(ch) && !IS_EVIL(ch))

#define IS_AWAKE(ch)		((ch)->position > POS_SLEEPING)
#define GET_HITROLL(ch)		((ch)->hitroll )
#define GET_DAMROLL(ch)		((ch)->damroll )

#define IS_OUTSIDE(ch)		(!IS_SET(				    \
				    (ch)->in_room->room_flags,		    \
				    ROOM_INDOORS) && !IS_SET(               \
				    (ch)->in_room->room_flags,              \
				    ROOM_SPACECRAFT) )

#define IS_DRUNK(ch, drunk)     (number_percent() < \
			        ( (ch)->pcdata->condition[COND_DRUNK] \
				* 2 / (drunk) ) )

#define IS_CLANNED(ch)		(!IS_NPC((ch))				    \
				&& (ch)->pcdata->clan			    )

#define WAIT_STATE(ch, npulse)	((ch)->wait = UMAX((ch)->wait, (npulse)))


#define EXIT(ch, door)		( get_exit( (ch)->in_room, door ) )

#define CAN_GO(ch, door)	(EXIT((ch),(door))			 \
				&& (EXIT((ch),(door))->to_room != NULL)  \
                          	&& !IS_SET(EXIT((ch), (door))->exit_info, EX_CLOSED))

#define IS_VALID_SN(sn)		( (sn) >=0 && (sn) < MAX_SKILL		     \
				&& skill_table[(sn)]			     \
				&& skill_table[(sn)]->name )

#define IS_VALID_HERB(sn)	( (sn) >=0 && (sn) < MAX_HERB		     \
				&& herb_table[(sn)]			     \
				&& herb_table[(sn)]->name )

#define SPELL_FLAG(skill, flag)	( IS_SET((skill)->flags, (flag)) )
#define SPELL_DAMAGE(skill)	( ((skill)->flags     ) & 7 )
#define SPELL_ACTION(skill)	( ((skill)->flags >> 3) & 7 )
#define SPELL_CLASS(skill)	( ((skill)->flags >> 6) & 7 )
#define SPELL_POWER(skill)	( ((skill)->flags >> 9) & 3 )
#define SET_SDAM(skill, val)	( (skill)->flags =  ((skill)->flags & SDAM_MASK) + ((val) & 7) )
#define SET_SACT(skill, val)	( (skill)->flags =  ((skill)->flags & SACT_MASK) + (((val) & 7) << 3) )
#define SET_SCLA(skill, val)	( (skill)->flags =  ((skill)->flags & SCLA_MASK) + (((val) & 7) << 6) )
#define SET_SPOW(skill, val)	( (skill)->flags =  ((skill)->flags & SPOW_MASK) + (((val) & 3) << 9) )

/* Retired and guest imms. */
#define IS_RETIRED(ch) (ch->pcdata && IS_SET(ch->pcdata->flags,PCFLAG_RETIRED))
#define IS_GUEST(ch) (ch->pcdata && IS_SET(ch->pcdata->flags,PCFLAG_GUEST))

/* RIS by gsn lookups. -- Altrag.
   Will need to add some || stuff for spells that need a special GSN. */

#define IS_FIRE(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_FIRE )
#define IS_COLD(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_COLD )
#define IS_ACID(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_ACID )
#define IS_ELECTRICITY(dt)	( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_ELECTRICITY )
#define IS_ENERGY(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_ENERGY )

#define IS_DRAIN(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_DRAIN )

#define IS_POISON(dt)		( IS_VALID_SN(dt) &&			     \
				SPELL_DAMAGE(skill_table[(dt)]) == SD_POISON )


#define NOT_AUTHED(ch)		(!IS_NPC(ch) && ch->pcdata->auth_state <= 3  \
			      && IS_SET(ch->pcdata->flags, PCFLAG_UNAUTHED) )

#define HAS_SLUG(ch)		(!IS_NPC(ch) && IS_SET(ch->pcdata->flags, \
				PCFLAG_HASSLUG) )
#define IS_WAITING_FOR_AUTH(ch) (!IS_NPC(ch) && ch->desc		     \
			      && ch->pcdata->auth_state == 1		     \
			      && IS_SET(ch->pcdata->flags, PCFLAG_UNAUTHED) ) 

/*
 * Object macros.
 */
#define CAN_WEAR(obj, part)	(IS_SET((obj)->wear_flags,  (part)))
#define IS_OBJ_STAT(obj, stat)	(IS_SET((obj)->extra_flags, (stat)))



/*
 * Description macros.
 */
/* PERS WILL NOW BE HANDLED IN COMM.C
#define PERS(ch, looker)	( can_see( (looker), (ch) ) ?		\
				( IS_NPC(ch) ? (ch)->short_descr	\
				: (ch)->name ) : IS_IMMORTAL(ch) ? "Immortal" : "someone" )

*/

#define log_string( txt )	( log_string_plus( (txt), LOG_NORMAL, LEVEL_LOG ) )


/*
 * Structure for a command in the command lookup table.
 */
struct	cmd_type
{
    CMDTYPE *		next;
    char *		name;
    DO_FUN *		do_fun;
    sh_int		position;
    sh_int		level;
    sh_int		log;
    struct		timerset	userec;
};



/*
 * Structure for a social in the socials table.
 */
struct	social_type
{
    SOCIALTYPE *	next;
    char *		name;
    char *		char_no_arg;
    char *		others_no_arg;
    char *		char_found;
    char *		others_found;
    char *		vict_found;
    char *		char_auto;
    char *		others_auto;
};



/*
 * Global constants.
 */
extern  time_t last_restore_all_time;
extern  time_t boot_time;  /* this should be moved down */
extern  HOUR_MIN_SEC * set_boot_time; 
extern  struct  tm *new_boot_time;
extern  time_t new_boot_time_t;



extern	const	struct	str_app_type	str_app		[26];
extern	const	struct	int_app_type	int_app		[26];
extern	const	struct	wis_app_type	wis_app		[26];
extern	const	struct	dex_app_type	dex_app		[30];
extern	const	struct	con_app_type	con_app		[26];
extern	const	struct	cha_app_type	cha_app		[26];
extern  const	struct	lck_app_type	lck_app		[26];
extern  const	struct	frc_app_type	frc_app		[26];
extern	const	struct	race_type	race_table	[MAX_RACE];
extern	const	struct	droid_type	droid_table	[MAX_DROID];
extern	const	struct	liq_type	liq_table	[LIQ_MAX];
extern	const	struct	stat_type	stat_table	[MAX_STAT];
extern	const	struct	exp_type	exp_table	[31];
extern	const	struct	exp_type	clan_exp	[31];
extern	const	struct	bonus_type	bonus_req	[16];
extern	const	struct	card_type	card_table	[12];
extern  char *	const			nskill_name	[MAX_NSKILL];
extern	char *	const			fskill_name	[MAX_FSKILL];
extern	char *	const			attack_table	[12];
extern	char *  const	        	ability_name	[MAX_ABILITY];
extern  char *  const			crystal_name    [16];
extern	char *	const			alchemy_name	[10];
extern	char *	const			blaster_name	[MAX_BLASTERS];
extern	char *	const			laser_name	[MAX_LASERS];
extern	char *	const			turbo_name	[MAX_TURBO];
extern	char *	const			missile_name	[MAX_MISSILES];
extern	char *	const			ion_name	[MAX_IONS];
extern	char *	const			atmo_name [MAX_ATMO];
extern	char *  const			bonus_clan	[];
extern	char *	const			ship_size	[MAX_SIZE];
extern	char *	const			planet_name	[];
extern	char *	const			cargo_name	[10];
extern	char *	const			stance_name	[MAX_STANCE];
extern	char *  const			base_name	[BASE_CLASS];
extern	char *	const			part_name	[MAX_PART];
extern  char *  const			height_name[4];
extern  char *  const			build_name[6];
extern  char *  const			droid_name[8];
extern	char *	const			feat_name[32];
extern  char *  const			feat2_name[32];

extern	char *	const	skill_tname	[];
extern	sh_int	const	movement_loss	[SECT_MAX];
extern	char *	const	dir_name	[];
extern	char *	const	where_name	[];
extern	const	sh_int	rev_dir		[];
extern	const	int	trap_door	[];
extern	char *	const	r_flags		[];
extern  char *  const   r_flags2	[];
extern	char *	const	c_flags		[];
extern  char *  const	c_flags2	[];
extern	char *	const	w_flags		[];
extern	char *	const	o_flags		[];
extern	char *	const	a_flags		[];
extern	char *	const	o_types		[];
extern	char *	const	a_types		[];
extern	char *	const	act_flags	[];
extern  char *  const   planet_flags    [];
extern  char *  const   mprog_flags    [];
extern  char *  const   weapon_table    [12];
extern  char *  const   spice_table     [];
extern	char *	const	plr_flags	[];
extern	char *	const	pc_flags	[];
extern	char *	const	trap_flags	[];
extern	char *	const	ris_flags	[];
extern	char *	const	trig_flags	[];
extern	char *	const	part_flags	[];
extern	char *	const	npc_race	[];
extern	char *	const	defense_flags	[];
extern	char *	const	attack_flags	[];
extern	char *	const	area_flags	[];

extern	int	const	lang_array      [];
extern	char *	const	lang_names      [];

extern bool bootup;
extern char namefreq[MAX_STRING_LENGTH];
extern char bname[MAX_STRING_LENGTH];

/*
 * Global variables.
 */

extern MPSLEEP_DATA * first_mpwait; /* Storing sleeping mud progs */ 
extern MPSLEEP_DATA * last_mpwait; /* - */ 
extern MPSLEEP_DATA * current_mpwait; /* - */ 
extern	int	numobjsloaded;
extern	int	nummobsloaded;
extern	int	physicalobjects;
extern	int	num_descriptors;
extern	struct	system_data		sysdata;
extern	int	top_sn;
extern	int	top_vroom;
extern	int	top_herb;

extern		CMDTYPE		  *	command_hash	[126];

extern		SKILLTYPE	  *	skill_table	[MAX_SKILL];
extern		SOCIALTYPE	  *	social_index	[27];
extern		CHAR_DATA	  *	cur_char;
extern		ROOM_INDEX_DATA	  *	cur_room;
extern		bool			cur_char_died;
extern		ch_ret			global_retcode;
extern		SKILLTYPE	  *	herb_table	[MAX_HERB];

extern		int			cur_obj;
extern		int			cur_obj_serial;
extern		bool			cur_obj_extracted;
extern		obj_ret			global_objcode;

extern		HELP_DATA	  *	first_help;
extern		HELP_DATA	  *	last_help;
extern		SHOP_DATA	  *	first_shop;
extern		SHOP_DATA	  *	last_shop;
extern		REPAIR_DATA	  *	first_repair;
extern		REPAIR_DATA	  *	last_repair;

extern		BAN_DATA	  *	first_ban;
extern		BAN_DATA	  *	last_ban;
extern		CHAR_DATA	  *	first_char;
extern		CHAR_DATA	  *	last_char;
extern		DESCRIPTOR_DATA   *	first_descriptor;
extern		DESCRIPTOR_DATA   *	last_descriptor;
extern		BOARD_DATA	  *	first_board;
extern		BOARD_DATA	  *	last_board;
extern		OBJ_DATA	  *	first_object;
extern		OBJ_DATA	  *	last_object;
extern		CLAN_DATA	  *	first_clan;
extern		CLAN_DATA	  *	last_clan;
extern		GUARD_DATA	  *	first_guard;
extern		GUARD_DATA	  *	last_guard;
extern          SHIP_DATA         *     first_ship;
extern          SHIP_DATA         *     last_ship;
//extern          SHIP_PROTOTYPE    *     first_ship_prototype;
//extern          SHIP_PROTOTYPE    *     last_ship_prototype;
extern          SPACE_DATA        *     first_starsystem;
extern          SPACE_DATA        *     last_starsystem;
extern          PLANET_DATA       *     first_planet;
extern          PLANET_DATA       *     last_planet;
extern          SENATE_DATA       *     first_senator;
extern          SENATE_DATA       *     last_senator;
extern          BOUNTY_DATA       *     first_bounty;
extern          BOUNTY_DATA       *     last_bounty;
extern          BOUNTY_DATA       *     first_disintegration;
extern          BOUNTY_DATA       *     last_disintegration;
extern		AREA_DATA	  *	first_area;
extern		AREA_DATA	  *	last_area;
extern		AREA_DATA	  *	first_build;
extern		AREA_DATA	  *	last_build;
extern		AREA_DATA	  *	first_asort;
extern		AREA_DATA	  *	last_asort;
extern		AREA_DATA	  *	first_bsort;
extern		AREA_DATA	  *	last_bsort;

/*
extern		GOD_DATA	  *	first_imm;
extern		GOD_DATA	  *	last_imm;
*/
extern		TELEPORT_DATA	  *	first_teleport;
extern		TELEPORT_DATA	  *	last_teleport;
extern		OBJ_DATA	  *	extracted_obj_queue;
extern		EXTRACT_CHAR_DATA *	extracted_char_queue;
extern		OBJ_DATA	  *	save_equipment[MAX_WEAR][MAX_LAYERS];
extern		CHAR_DATA	  *	quitting_char;
extern		CHAR_DATA	  *	loading_char;
extern		CHAR_DATA	  *	saving_char;
extern		OBJ_DATA	  *	all_obj;

extern		char			bug_buf		[];
extern		time_t			current_time;
extern		bool			fLogAll;
extern		bool			fLogPC;
extern		FILE *			fpReserve;
extern		FILE *			fpLOG;
extern		char			log_buf		[];
extern		TIME_INFO_DATA		time_info;
extern		WEATHER_DATA		weather_info;

extern          AUCTION_DATA      *     auction;
extern		struct act_prog_data *	mob_act_list;

extern		BMARKET_DATA	  *	first_market_ship;
extern		BMARKET_DATA	  *     last_market_ship;

/*
 * Command functions.
 * Defined in act_*.c (mostly).
 */
DECLARE_DO_FUN( do_patron	);
DECLARE_DO_FUN( do_specialty	);
DECLARE_DO_FUN( do_secret	);
DECLARE_DO_FUN( do_skills 	);
DECLARE_DO_FUN( do_makecybernetic );
DECLARE_DO_FUN( do_fskills	);
DECLARE_DO_FUN( do_showquests	);
DECLARE_DO_FUN( do_drainenergy	);
DECLARE_DO_FUN( do_drainforce	);
DECLARE_DO_FUN( do_forcemind	);
DECLARE_DO_FUN( do_gatherinfo	);
DECLARE_DO_FUN( do_promote	);
DECLARE_DO_FUN( do_sithsorcery	);
DECLARE_DO_FUN( do_callforce	);
DECLARE_DO_FUN( do_heal 	);
DECLARE_DO_FUN( do_forcestrike	);
DECLARE_DO_FUN( do_forcelightning);
DECLARE_DO_FUN( do_forcegrip	);
DECLARE_DO_FUN( do_forcedefense );
DECLARE_DO_FUN( do_fear		);
DECLARE_DO_FUN( do_farseeing	);
DECLARE_DO_FUN( do_enhancesenses);
DECLARE_DO_FUN( do_enhance	);
DECLARE_DO_FUN( do_battlemind	);
DECLARE_DO_FUN( do_alchemy	);
DECLARE_DO_FUN( do_setreputation);
DECLARE_DO_FUN( do_makesith	);
DECLARE_DO_FUN( do_test 	);
DECLARE_DO_FUN( do_padawan	);
DECLARE_DO_FUN( do_rentlocker	);
DECLARE_DO_FUN( do_lockercode	);
DECLARE_DO_FUN( do_makecamera	);
DECLARE_DO_FUN( do_checkmonitor );
DECLARE_DO_FUN( do_tunemonitor  );
DECLARE_DO_FUN( do_linkcamera	);
DECLARE_DO_FUN( do_plantcamera	);
DECLARE_DO_FUN( do_plantmonitor );
DECLARE_DO_FUN( do_resources	);
DECLARE_DO_FUN( do_setsith	);
DECLARE_DO_FUN( do_embargo	);
DECLARE_DO_FUN( do_settaxrate	);
DECLARE_DO_FUN( do_setgovernor	);
DECLARE_DO_FUN( do_setprototype	);
DECLARE_DO_FUN( do_showprototype);
DECLARE_DO_FUN( do_upgradebonus );
DECLARE_DO_FUN( do_penalizeclan );
DECLARE_DO_FUN( do_clanbestow	);
DECLARE_DO_FUN( do_bonuses	);
DECLARE_DO_FUN( do_setbonus	);
DECLARE_DO_FUN( do_ignite	);
DECLARE_DO_FUN( do_imbue	);
DECLARE_DO_FUN( do_osay		);
DECLARE_DO_FUN( do_sellcargo 	);
DECLARE_DO_FUN( do_buycargo	);
DECLARE_DO_FUN( do_listcargo	);
DECLARE_DO_FUN( do_pirate	);
DECLARE_DO_FUN( do_dumpcargo	);
DECLARE_DO_FUN( do_checksenate	);
DECLARE_DO_FUN( do_scanship	);
DECLARE_DO_FUN( do_cargo	);
DECLARE_DO_FUN( do_cover	);
DECLARE_DO_FUN( do_duck		);
DECLARE_DO_FUN( do_lean		);
DECLARE_DO_FUN( do_dock		);
DECLARE_DO_FUN( do_undock	);
DECLARE_DO_FUN( do_cybernetics	);
DECLARE_DO_FUN( do_senatesay	);
DECLARE_DO_FUN( do_audsay	);
DECLARE_DO_FUN( do_dfeats	);
DECLARE_DO_FUN( do_stance	);
DECLARE_DO_FUN( do_feats	);
DECLARE_DO_FUN( do_ffeats	);
DECLARE_DO_FUN( do_rcopy	);
DECLARE_DO_FUN( do_buymobship 	);
DECLARE_DO_FUN( do_aaccept      );
DECLARE_DO_FUN( do_ahall        );
DECLARE_DO_FUN( do_arena        );
DECLARE_DO_FUN( do_awho         );
DECLARE_DO_FUN( do_bet          );
DECLARE_DO_FUN( do_challenge    );
DECLARE_DO_FUN( do_chaos        );
DECLARE_DO_FUN( do_cut		);
DECLARE_DO_FUN( do_adecline     );
DECLARE_DO_FUN( do_setplanet 	);
DECLARE_DO_FUN( do_setrank 	);
DECLARE_DO_FUN( do_setinfrared  );
DECLARE_DO_FUN( do_makefree 	);
DECLARE_DO_FUN( do_makeplanet 	);
DECLARE_DO_FUN( do_remplanet	);
DECLARE_DO_FUN( do_makeprototypeship );
DECLARE_DO_FUN( do_planets 	);
DECLARE_DO_FUN( do_gather_intelligence );
DECLARE_DO_FUN( do_generate_market );
DECLARE_DO_FUN( do_add_patrol );
DECLARE_DO_FUN( do_special_forces );
DECLARE_DO_FUN( do_jail );
DECLARE_DO_FUN( do_checkwar   );
DECLARE_DO_FUN( do_elite_guard );
DECLARE_DO_FUN( do_smalltalk );
DECLARE_DO_FUN( do_propeganda );
DECLARE_DO_FUN( do_bribe );
DECLARE_DO_FUN( do_bind );
DECLARE_DO_FUN( do_seduce );
DECLARE_DO_FUN( do_mass_propeganda );
DECLARE_DO_FUN( do_copyship  );
DECLARE_DO_FUN( do_sound  );
DECLARE_DO_FUN( do_autopilot  );
DECLARE_DO_FUN( do_allspeeders  );
DECLARE_DO_FUN( do_speeders  );
DECLARE_DO_FUN( do_suicide  );
DECLARE_DO_FUN( do_gain  );
DECLARE_DO_FUN( do_train  );
DECLARE_DO_FUN( do_beg  );
DECLARE_DO_FUN( do_bank  );
DECLARE_DO_FUN( do_hijack  );
DECLARE_DO_FUN( do_pickshiplock  );
DECLARE_DO_FUN( do_shipstat  );
DECLARE_DO_FUN( do_shiptalk  );
DECLARE_DO_FUN( do_clone  );
DECLARE_DO_FUN( do_systemtalk );
DECLARE_DO_FUN( do_spacetalk );
DECLARE_DO_FUN( do_hail );
DECLARE_DO_FUN( do_allships );
DECLARE_DO_FUN( do_newclan );
DECLARE_DO_FUN( do_appoint );
DECLARE_DO_FUN( do_demote );
DECLARE_DO_FUN( do_empower );
DECLARE_DO_FUN( do_capture );
DECLARE_DO_FUN( do_arm );
DECLARE_DO_FUN( do_addchange );
DECLARE_DO_FUN( do_changes );
DECLARE_DO_FUN( do_chaff );
DECLARE_DO_FUN( do_clan_donate );
DECLARE_DO_FUN( do_clan_withdraw );
DECLARE_DO_FUN( do_fly );
DECLARE_DO_FUN( do_drive );
DECLARE_DO_FUN( do_bomb );
DECLARE_DO_FUN( do_setblaster );
DECLARE_DO_FUN( do_ammo );
DECLARE_DO_FUN( do_ambush );
DECLARE_DO_FUN( do_takedrug );
DECLARE_DO_FUN( do_use ); 
DECLARE_DO_FUN( do_link );
DECLARE_DO_FUN( do_unlink );
DECLARE_DO_FUN( do_load );
DECLARE_DO_FUN( do_unload );
DECLARE_DO_FUN( do_enlist );
DECLARE_DO_FUN( do_resign );
DECLARE_DO_FUN( do_retune );
DECLARE_DO_FUN( do_reward );
DECLARE_DO_FUN( do_pluogus ); 
DECLARE_DO_FUN( do_makemodule );
DECLARE_DO_FUN( do_showmodules );
DECLARE_DO_FUN( do_installmodule );
DECLARE_DO_FUN( do_removebug );
DECLARE_DO_FUN( do_removemodule );
DECLARE_DO_FUN( do_tractorbeam );
DECLARE_DO_FUN( do_makearmor );
DECLARE_DO_FUN( do_makejewelry );
DECLARE_DO_FUN( do_makegrenade );
DECLARE_DO_FUN( do_makeshipbomb );
DECLARE_DO_FUN( do_makelandmine );
DECLARE_DO_FUN( do_makelight );
DECLARE_DO_FUN( do_makecomlink );
DECLARE_DO_FUN( do_makeshield );
DECLARE_DO_FUN( do_makecontainer );
DECLARE_DO_FUN( do_makemissile );
DECLARE_DO_FUN( do_gemcutting );
DECLARE_DO_FUN( do_reinforcements );
DECLARE_DO_FUN( do_postguard );
DECLARE_DO_FUN( do_torture );
DECLARE_DO_FUN( do_snipe );
DECLARE_DO_FUN( do_throw );
DECLARE_DO_FUN( do_deception );
DECLARE_DO_FUN( do_disguise );
DECLARE_DO_FUN( do_mine );
DECLARE_DO_FUN( do_first_aid);
DECLARE_DO_FUN( do_make_master); 
DECLARE_DO_FUN( do_makeblade ); 
DECLARE_DO_FUN( do_makebeacon );
DECLARE_DO_FUN( do_makebinders );
DECLARE_DO_FUN( do_makebug );
DECLARE_DO_FUN( do_makegoggles );
DECLARE_DO_FUN( do_spousetalk );
DECLARE_DO_FUN( do_makepike ); 
DECLARE_DO_FUN( do_makeblaster );
DECLARE_DO_FUN( do_makelightsaber );
DECLARE_DO_FUN( do_makespice );
DECLARE_DO_FUN( do_closebay );
DECLARE_DO_FUN( do_openbay );
DECLARE_DO_FUN( do_autotrack );
DECLARE_DO_FUN( do_jumpvector ); 
DECLARE_DO_FUN( do_reload );
DECLARE_DO_FUN( do_tractorbeam ); 
DECLARE_DO_FUN( do_radar );
DECLARE_DO_FUN( do_recall ); 
DECLARE_DO_FUN( do_buyship );
DECLARE_DO_FUN( do_buytroops );
DECLARE_DO_FUN( do_buyhome );
DECLARE_DO_FUN( do_clanbuyship );
DECLARE_DO_FUN( do_clangiveship );
DECLARE_DO_FUN( do_clansalvage );
DECLARE_DO_FUN( do_clanbuytroops );
DECLARE_DO_FUN( do_gatherclans );
DECLARE_DO_FUN( do_sellship );
DECLARE_DO_FUN( do_autorecharge );
DECLARE_DO_FUN( do_openhatch );
DECLARE_DO_FUN( do_closehatch );
DECLARE_DO_FUN( do_status );
DECLARE_DO_FUN( do_std );
DECLARE_DO_FUN( do_info );
DECLARE_DO_FUN( do_introduce );
DECLARE_DO_FUN( do_remember );
DECLARE_DO_FUN( do_describe );
DECLARE_DO_FUN( do_hyperspace );
DECLARE_DO_FUN( do_target );
DECLARE_DO_FUN( do_fire );
DECLARE_DO_FUN( do_calculate );
DECLARE_DO_FUN( do_recharge );
DECLARE_DO_FUN( do_shiprepair );
DECLARE_DO_FUN( do_shipmaintenance );
DECLARE_DO_FUN( do_shiplist );
DECLARE_DO_FUN( do_refuel );
DECLARE_DO_FUN( do_addpilot );
DECLARE_DO_FUN( do_rempilot);
DECLARE_DO_FUN( do_remclan);
DECLARE_DO_FUN( do_removeship);
DECLARE_DO_FUN( do_trajectory );
DECLARE_DO_FUN( do_accelerate );
DECLARE_DO_FUN( do_launch );
DECLARE_DO_FUN( do_land ); 
DECLARE_DO_FUN( do_leaveship ); 
DECLARE_DO_FUN( do_setstarsystem );
DECLARE_DO_FUN( do_makestarsystem );
DECLARE_DO_FUN( do_makesimulator );
DECLARE_DO_FUN( do_makemobship );
DECLARE_DO_FUN( do_starsystems ); 
DECLARE_DO_FUN( do_showstarsystem );
DECLARE_DO_FUN( skill_notfound	);
DECLARE_DO_FUN( do_aassign	);
DECLARE_DO_FUN( do_addbounty    );
DECLARE_DO_FUN( do_contract    );
DECLARE_DO_FUN( do_showcontracts    );
DECLARE_DO_FUN( do_remcontract    );
DECLARE_DO_FUN( do_vassign      );
DECLARE_DO_FUN( do_rassign      );
DECLARE_DO_FUN( do_massign      );
DECLARE_DO_FUN( do_oassign      );
DECLARE_DO_FUN(	do_advance	);
DECLARE_DO_FUN( do_affected     );
DECLARE_DO_FUN( do_afk          );
DECLARE_DO_FUN(	do_aid		);
DECLARE_DO_FUN( do_rembounty	);
DECLARE_DO_FUN(	do_allow	);
DECLARE_DO_FUN( do_ansi		);
DECLARE_DO_FUN(	do_answer	);
DECLARE_DO_FUN( do_apply	);
DECLARE_DO_FUN(	do_appraise	);
DECLARE_DO_FUN(	do_areas	);
DECLARE_DO_FUN( do_aset		);
DECLARE_DO_FUN(	do_ask		);
DECLARE_DO_FUN( do_astat	);
DECLARE_DO_FUN(	do_at		);
DECLARE_DO_FUN(	do_auction	);
DECLARE_DO_FUN( do_authorize	);
DECLARE_DO_FUN( do_avtalk	);
DECLARE_DO_FUN(	do_backstab	);
DECLARE_DO_FUN(	do_backup	);
DECLARE_DO_FUN(	do_balzhur	);
DECLARE_DO_FUN(	do_bamfin	);
DECLARE_DO_FUN(	do_bamfout	);
DECLARE_DO_FUN(	do_ban		);
DECLARE_DO_FUN( do_bashdoor     );
DECLARE_DO_FUN( do_beep         );
DECLARE_DO_FUN( do_berserk	);
DECLARE_DO_FUN( do_bestow	);
DECLARE_DO_FUN( do_bestowarea	);
DECLARE_DO_FUN(	do_bio		);
DECLARE_DO_FUN(	do_bite		);
DECLARE_DO_FUN( do_board        );
DECLARE_DO_FUN( do_boards	);
DECLARE_DO_FUN( do_bodybag	);
DECLARE_DO_FUN( do_bounties     );
DECLARE_DO_FUN( do_bset		);
DECLARE_DO_FUN( do_bstat	);
DECLARE_DO_FUN(	do_bug		);
DECLARE_DO_FUN( do_bury		);
DECLARE_DO_FUN(	do_buy		);
DECLARE_DO_FUN(	do_cast		);
DECLARE_DO_FUN(	do_cedit	);
DECLARE_DO_FUN(	do_channels	);
DECLARE_DO_FUN(	do_chat		);
DECLARE_DO_FUN(	do_ooc		);
DECLARE_DO_FUN(	do_check_vnums  );
DECLARE_DO_FUN(	do_clans	);
DECLARE_DO_FUN(	do_clanstat	);
DECLARE_DO_FUN( do_ships        );
DECLARE_DO_FUN(	do_clantalk	);
DECLARE_DO_FUN(	do_cleanroom	);
DECLARE_DO_FUN(	do_climb	);
DECLARE_DO_FUN(	do_close	);
DECLARE_DO_FUN(	do_cmdtable	);
DECLARE_DO_FUN(	do_cmenu	);
DECLARE_DO_FUN(	do_commands	);
DECLARE_DO_FUN(	do_comment	);
DECLARE_DO_FUN(	do_compare	);
DECLARE_DO_FUN(	do_config	);
DECLARE_DO_FUN(	do_consider	);
DECLARE_DO_FUN( do_copyover	);
DECLARE_DO_FUN( do_senate	);
DECLARE_DO_FUN( do_jedicouncil	);
DECLARE_DO_FUN( do_addsenator	);
DECLARE_DO_FUN( do_remsenator	);
DECLARE_DO_FUN( do_remcouncil	);
DECLARE_DO_FUN( do_setjedi	);
DECLARE_DO_FUN( do_showjedi	);
DECLARE_DO_FUN( do_showsenate	);
DECLARE_DO_FUN( do_makecouncil	);
DECLARE_DO_FUN( do_makesenate	);
DECLARE_DO_FUN( do_setsenate	);
DECLARE_DO_FUN( do_credits	);
DECLARE_DO_FUN(	do_cset		);
DECLARE_DO_FUN( do_deities	);
DECLARE_DO_FUN(	do_deny		);
DECLARE_DO_FUN(	do_description	);
DECLARE_DO_FUN( do_destro       );
DECLARE_DO_FUN( do_destroy      );
DECLARE_DO_FUN(	do_detrap	);
DECLARE_DO_FUN( do_devote	);
DECLARE_DO_FUN( do_dig		);
DECLARE_DO_FUN(	do_disarm	);
DECLARE_DO_FUN(	do_disconnect	);
DECLARE_DO_FUN( do_dismount	);
DECLARE_DO_FUN(	do_dmesg	);
DECLARE_DO_FUN(	do_down		);
DECLARE_DO_FUN( do_drag 	);
DECLARE_DO_FUN(	do_drink	);
DECLARE_DO_FUN(	do_drop		);
DECLARE_DO_FUN(	do_droptroops	);
DECLARE_DO_FUN(	do_diagnose	);
DECLARE_DO_FUN(	do_east		);
DECLARE_DO_FUN(	do_eat		);
DECLARE_DO_FUN(	do_echo		);
DECLARE_DO_FUN(	do_email	);
DECLARE_DO_FUN(	do_emote	);
DECLARE_DO_FUN(	do_empty	);
DECLARE_DO_FUN(	do_enter	);
DECLARE_DO_FUN(	do_equipment	);
DECLARE_DO_FUN(	do_examine	);
DECLARE_DO_FUN(	do_exempt	);
DECLARE_DO_FUN(	do_exits	);
DECLARE_DO_FUN(	do_endsimulator	);
DECLARE_DO_FUN(	do_fill		);
DECLARE_DO_FUN(	do_fixchar	);
DECLARE_DO_FUN(	do_flee		);
DECLARE_DO_FUN( do_foldarea	);
DECLARE_DO_FUN(	do_follow	);
DECLARE_DO_FUN( do_for          );
DECLARE_DO_FUN(	do_force	);
DECLARE_DO_FUN(	do_fset		);
DECLARE_DO_FUN( do_forceclose	);
DECLARE_DO_FUN( do_fquit	);     /* Gorog */
DECLARE_DO_FUN( do_form_password);
DECLARE_DO_FUN(	do_freeze	);
DECLARE_DO_FUN(	do_fslay	);
DECLARE_DO_FUN(	do_gag		);
DECLARE_DO_FUN(	do_get		);
DECLARE_DO_FUN(	do_give		);
DECLARE_DO_FUN( do_giveship	);
DECLARE_DO_FUN(	do_giveslug	);
DECLARE_DO_FUN(	do_glance	);
DECLARE_DO_FUN( do_gold         );
DECLARE_DO_FUN(	do_goto		);
DECLARE_DO_FUN(	do_group	);
DECLARE_DO_FUN(	do_grub 	);
DECLARE_DO_FUN(	do_gtell	);
DECLARE_DO_FUN( do_guilds       );
DECLARE_DO_FUN( do_guildtalk    );
DECLARE_DO_FUN( do_hedit	);
DECLARE_DO_FUN( do_hell		);
DECLARE_DO_FUN(	do_help		);
DECLARE_DO_FUN(	do_hide		);
DECLARE_DO_FUN( do_hlist	);
DECLARE_DO_FUN(	do_holylight	);
DECLARE_DO_FUN(	do_holonet	);
DECLARE_DO_FUN(	do_homepage	);
DECLARE_DO_FUN( do_hset		);
DECLARE_DO_FUN(	do_sith		);
DECLARE_DO_FUN(	do_i104		);
DECLARE_DO_FUN(	do_i105		);
DECLARE_DO_FUN(	do_ide		);
DECLARE_DO_FUN(	do_idea		);
DECLARE_DO_FUN(	do_idealog	);
DECLARE_DO_FUN(	do_immortalize	);
DECLARE_DO_FUN(	do_immtalk	);
DECLARE_DO_FUN(	do_induct	);
DECLARE_DO_FUN( do_installarea	);
DECLARE_DO_FUN( do_instaroom	);
DECLARE_DO_FUN( do_instazone	);
DECLARE_DO_FUN(	do_inventory	);
DECLARE_DO_FUN(	do_invis	);
DECLARE_DO_FUN(	do_kill		);
DECLARE_DO_FUN( do_languages    );
DECLARE_DO_FUN( do_last		);
DECLARE_DO_FUN(	do_leave	);
DECLARE_DO_FUN(	do_level	);
DECLARE_DO_FUN(	do_light	);
DECLARE_DO_FUN(	do_list		);
DECLARE_DO_FUN(	do_litterbug	);
DECLARE_DO_FUN( do_loadarea	);
DECLARE_DO_FUN( do_loadup	);
DECLARE_DO_FUN(	do_lock		);
DECLARE_DO_FUN(	do_log		);
DECLARE_DO_FUN(	do_look		);
DECLARE_DO_FUN(	do_low_purge	);
DECLARE_DO_FUN( do_mailroom	);
DECLARE_DO_FUN(	do_make		);
DECLARE_DO_FUN(	do_makeboard	);
DECLARE_DO_FUN(	do_makeclan	);
DECLARE_DO_FUN( do_makeship     );
DECLARE_DO_FUN( do_makeship2     );
DECLARE_DO_FUN( do_makeguild    );
DECLARE_DO_FUN( do_makerepair	);
DECLARE_DO_FUN( do_makeshop	);
DECLARE_DO_FUN( do_makewizlist	);
DECLARE_DO_FUN(	do_members	);
DECLARE_DO_FUN(	do_memory	);
DECLARE_DO_FUN( do_mcreate	);
DECLARE_DO_FUN( do_mdelete	);
DECLARE_DO_FUN(	do_mfind	);
DECLARE_DO_FUN(	do_minvoke	);
DECLARE_DO_FUN( do_mlist	);
DECLARE_DO_FUN( do_mount	);
DECLARE_DO_FUN(	do_mset		);
DECLARE_DO_FUN(	do_mstat	);
DECLARE_DO_FUN(	do_murde	);
DECLARE_DO_FUN(	do_murder	);
DECLARE_DO_FUN(	do_verpine	);
DECLARE_DO_FUN(	do_mwhere	);
DECLARE_DO_FUN( do_name		);
DECLARE_DO_FUN( do_newbiechat   );
DECLARE_DO_FUN( do_newbieset    );
DECLARE_DO_FUN( do_newzones	);
DECLARE_DO_FUN(	do_noemote	);
DECLARE_DO_FUN( do_noresolve	);
DECLARE_DO_FUN(	do_north	);
DECLARE_DO_FUN( do_northeast	);
DECLARE_DO_FUN( do_northwest	);
DECLARE_DO_FUN(	do_notell	);
DECLARE_DO_FUN( do_notitle      );
DECLARE_DO_FUN(	do_noteroom	);
DECLARE_DO_FUN( do_ocreate	);
DECLARE_DO_FUN( do_odelete	);
DECLARE_DO_FUN(	do_ofind	);
DECLARE_DO_FUN(	do_ogrub 	);
DECLARE_DO_FUN(	do_oinvoke	);
DECLARE_DO_FUN(	do_oldmstat	);
DECLARE_DO_FUN(	do_oldscore	);
DECLARE_DO_FUN( do_olist	);
DECLARE_DO_FUN(	do_open		);
DECLARE_DO_FUN( do_opentourney  );
DECLARE_DO_FUN(	do_order	);
DECLARE_DO_FUN(	do_orders	);
DECLARE_DO_FUN( do_ordership    );
DECLARE_DO_FUN( do_orderclanship);
DECLARE_DO_FUN(	do_ordertalk	);
DECLARE_DO_FUN(	do_oset		);
DECLARE_DO_FUN(	do_ostat	);
DECLARE_DO_FUN(	do_ot		);
DECLARE_DO_FUN(	do_outcast	);
DECLARE_DO_FUN(	do_outlaw	);
DECLARE_DO_FUN(	do_owhere	);
DECLARE_DO_FUN( do_pager	);
DECLARE_DO_FUN(	do_pardon	);
DECLARE_DO_FUN(	do_password	);
DECLARE_DO_FUN(	do_peace	);
DECLARE_DO_FUN(	do_pick		);
DECLARE_DO_FUN(	do_pose		);
DECLARE_DO_FUN( do_prompt	);
DECLARE_DO_FUN( do_pull		);
DECLARE_DO_FUN(	do_purge	);
DECLARE_DO_FUN( do_push		);
DECLARE_DO_FUN(	do_put		);
DECLARE_DO_FUN( do_qpset	);
DECLARE_DO_FUN(	do_quaff	);
DECLARE_DO_FUN(	do_quest	);
DECLARE_DO_FUN(	do_qui		);
DECLARE_DO_FUN(	do_quit		);
DECLARE_DO_FUN(	do_rank	        );
DECLARE_DO_FUN( do_rat		);
DECLARE_DO_FUN( do_rdelete	);
DECLARE_DO_FUN(	do_reboo	);
DECLARE_DO_FUN(	do_reboot	);
DECLARE_DO_FUN( do_recall	);
DECLARE_DO_FUN(	do_recho	);
DECLARE_DO_FUN(	do_recite	);
DECLARE_DO_FUN(	do_redit	);
DECLARE_DO_FUN( do_regoto       );
DECLARE_DO_FUN(	do_remove	);
DECLARE_DO_FUN(	do_rent		);
DECLARE_DO_FUN(	do_mobrepair	);
DECLARE_DO_FUN(	do_repair	);
DECLARE_DO_FUN(	do_repairset	);
DECLARE_DO_FUN(	do_repairshops	);
DECLARE_DO_FUN(	do_repairstat	);
DECLARE_DO_FUN(	do_reply	);
DECLARE_DO_FUN(	do_report	);
DECLARE_DO_FUN(	do_rescue	);
DECLARE_DO_FUN(	do_rest		);
DECLARE_DO_FUN( do_meditate	);
DECLARE_DO_FUN( do_reset	);
DECLARE_DO_FUN( do_resetship	);
DECLARE_DO_FUN(	do_restore	);
DECLARE_DO_FUN(	do_restorefile	);
DECLARE_DO_FUN(	do_restoretime	);
DECLARE_DO_FUN(	do_restrict	);
DECLARE_DO_FUN( do_request	);
DECLARE_DO_FUN( do_retire       );
DECLARE_DO_FUN( do_retran       );
DECLARE_DO_FUN(	do_return	);
DECLARE_DO_FUN(	do_revert	);
DECLARE_DO_FUN( do_rip		);
DECLARE_DO_FUN( do_rlist	);
DECLARE_DO_FUN( do_rreset	);
DECLARE_DO_FUN(	do_rset		);
DECLARE_DO_FUN(	do_rstat	);
DECLARE_DO_FUN(	do_sacrifice	);
DECLARE_DO_FUN(	do_save		);
DECLARE_DO_FUN( do_savearea	);
DECLARE_DO_FUN(	do_say		);
DECLARE_DO_FUN( do_scan         );
DECLARE_DO_FUN( do_scanbugs     );
DECLARE_DO_FUN(	do_score	);
DECLARE_DO_FUN( do_screenname   );
DECLARE_DO_FUN( do_search	);
DECLARE_DO_FUN(	do_sedit	);
DECLARE_DO_FUN(	do_sell		);
DECLARE_DO_FUN(	do_sellhome	);
DECLARE_DO_FUN( do_set_boot_time);
DECLARE_DO_FUN( do_setclan	);
DECLARE_DO_FUN( do_setship      );
DECLARE_DO_FUN(	do_shops	);
DECLARE_DO_FUN(	do_shopset	);
DECLARE_DO_FUN(	do_shopstat	);
DECLARE_DO_FUN(	do_shout	);
DECLARE_DO_FUN( do_shove  	);
DECLARE_DO_FUN( do_showclan	);
DECLARE_DO_FUN( do_showship     );
DECLARE_DO_FUN( do_showplanet   );
DECLARE_DO_FUN( do_showsocial   );
DECLARE_DO_FUN(	do_shutdow	);
DECLARE_DO_FUN(	do_shutdown	);
DECLARE_DO_FUN(	do_silence	);
DECLARE_DO_FUN(	do_sit		);
DECLARE_DO_FUN(	do_tune		);
DECLARE_DO_FUN(	do_shiplock	);
DECLARE_DO_FUN(	do_salvage	);
DECLARE_DO_FUN(	do_plantbug	);
DECLARE_DO_FUN( do_plantbeacon  );
DECLARE_DO_FUN(	do_showbugs	);
DECLARE_DO_FUN( do_showbeacons  );
DECLARE_DO_FUN( do_checkbeacons );
DECLARE_DO_FUN( do_nullifybeacons );
DECLARE_DO_FUN( do_juke );
DECLARE_DO_FUN(do_barrel_roll);
DECLARE_DO_FUN( do_launch2 );
DECLARE_DO_FUN(	do_sabotage	);
DECLARE_DO_FUN(	do_freeship	);
DECLARE_DO_FUN(	do_hale		);
DECLARE_DO_FUN(	do_wwwimage	);
DECLARE_DO_FUN(	do_whisper	);
DECLARE_DO_FUN(	do_marry	);
DECLARE_DO_FUN(	do_propose	);
DECLARE_DO_FUN(	do_divorce	);
DECLARE_DO_FUN(	do_accept	);
DECLARE_DO_FUN(	do_decline	);
DECLARE_DO_FUN(	do_tellsnoop	);
DECLARE_DO_FUN(	do_makecommsystem);
DECLARE_DO_FUN(	do_makedatapad	);
DECLARE_DO_FUN(	do_codecrack	);
DECLARE_DO_FUN(	do_inquire	);
DECLARE_DO_FUN(	do_checkprints	);
DECLARE_DO_FUN(	do_disableship	);
DECLARE_DO_FUN(	do_assignpilot	);
DECLARE_DO_FUN(	do_bomb		);
DECLARE_DO_FUN( do_setwage	);
DECLARE_DO_FUN(	do_sla		);
DECLARE_DO_FUN(	do_slay		);
DECLARE_DO_FUN(	do_slicebank	);
DECLARE_DO_FUN(	do_sleep	);
DECLARE_DO_FUN( do_slist        );
DECLARE_DO_FUN(	do_slog  	);
DECLARE_DO_FUN(	do_slookup	);
DECLARE_DO_FUN(	do_smoke	);
DECLARE_DO_FUN(	do_sneak	);
DECLARE_DO_FUN(	do_snoop	);
DECLARE_DO_FUN(	do_sober	);
DECLARE_DO_FUN(	do_socials	);
DECLARE_DO_FUN(	do_south	);
DECLARE_DO_FUN(	do_southeast	);
DECLARE_DO_FUN(	do_southwest	);
DECLARE_DO_FUN( do_speak        );
DECLARE_DO_FUN(	do_split	);
DECLARE_DO_FUN(	do_sset		);
DECLARE_DO_FUN(	do_stand	);
DECLARE_DO_FUN( do_starttourney );
DECLARE_DO_FUN(	do_steal	);
DECLARE_DO_FUN(	do_stun		);
DECLARE_DO_FUN( do_supplicate	);
DECLARE_DO_FUN(	do_switch	);
DECLARE_DO_FUN(	do_tail		);
DECLARE_DO_FUN(	do_tamp		);
DECLARE_DO_FUN(	do_tell		);
DECLARE_DO_FUN(	do_time		);
DECLARE_DO_FUN(	do_timecmd	);
DECLARE_DO_FUN(	do_title	);
DECLARE_DO_FUN( do_track	);
DECLARE_DO_FUN(	do_transfer	);
DECLARE_DO_FUN( do_transship	);
DECLARE_DO_FUN( do_transshipss  );
DECLARE_DO_FUN(	do_trust	);
DECLARE_DO_FUN(	do_typo		);
DECLARE_DO_FUN( do_unhell	);
DECLARE_DO_FUN( do_unbind	);
DECLARE_DO_FUN( do_ungag	);
DECLARE_DO_FUN(	do_unlock	);
DECLARE_DO_FUN( do_unsilence    );
DECLARE_DO_FUN( do_unoutlaw     );
DECLARE_DO_FUN(	do_up		);
DECLARE_DO_FUN(	do_users	);
DECLARE_DO_FUN(	do_value	);
DECLARE_DO_FUN(	do_visible	);
DECLARE_DO_FUN( do_vnums	);
DECLARE_DO_FUN( do_vsearch	);
DECLARE_DO_FUN(	do_wake		);
DECLARE_DO_FUN( do_bartokk      );
DECLARE_DO_FUN( do_war	        );
DECLARE_DO_FUN( do_prototypes   );
DECLARE_DO_FUN( do_setprototype );
DECLARE_DO_FUN( do_showprototype);
DECLARE_DO_FUN( do_designship   );
DECLARE_DO_FUN(	do_wear		);
DECLARE_DO_FUN(	do_weather	);
DECLARE_DO_FUN(	do_west		);
DECLARE_DO_FUN(	do_where	);
DECLARE_DO_FUN(	do_who		);
DECLARE_DO_FUN(	do_whoinvis	);
DECLARE_DO_FUN(	do_whois	);
DECLARE_DO_FUN(	do_wimpy	);
DECLARE_DO_FUN(	do_wizhelp	);
DECLARE_DO_FUN( do_wizlist	);
DECLARE_DO_FUN(	do_wizlock	);
DECLARE_DO_FUN(	do_yell		);
DECLARE_DO_FUN( do_zones	);

/* mob prog stuff */
DECLARE_DO_FUN( do_mp_close_passage );
DECLARE_DO_FUN( do_mpquest	);
DECLARE_DO_FUN( do_mptrials	);
DECLARE_DO_FUN( do_mpquestcomplete );
DECLARE_DO_FUN( do_mp_damage );
DECLARE_DO_FUN( do_mp_restore );
DECLARE_DO_FUN( do_mp_open_passage );
DECLARE_DO_FUN( do_mp_practice );
DECLARE_DO_FUN( do_mp_slay);
DECLARE_DO_FUN( do_mpadvance    );
DECLARE_DO_FUN( do_mpasound     );
DECLARE_DO_FUN( do_mpat         );
DECLARE_DO_FUN( do_mpdream	);
DECLARE_DO_FUN( do_mp_deposit	);
DECLARE_DO_FUN( do_mp_withdraw	);
DECLARE_DO_FUN( do_mpecho       );
DECLARE_DO_FUN( do_mpechoaround );
DECLARE_DO_FUN( do_mpechoat     );
DECLARE_DO_FUN( do_mpedit       );
DECLARE_DO_FUN( do_mrange       );
DECLARE_DO_FUN( do_opedit       );
DECLARE_DO_FUN( do_orange       );
DECLARE_DO_FUN( do_rpconvert    );
DECLARE_DO_FUN( do_rpedit       );
DECLARE_DO_FUN( do_mpforce      );
DECLARE_DO_FUN( do_mpinvis	);
DECLARE_DO_FUN( do_mpgoto       );
DECLARE_DO_FUN( do_mpjunk       );
DECLARE_DO_FUN( do_mpkill       );
DECLARE_DO_FUN( do_mpmload      );
DECLARE_DO_FUN( do_mpmset	);
DECLARE_DO_FUN( do_mpnothing	);
DECLARE_DO_FUN( do_mpoload      );
DECLARE_DO_FUN( do_mposet	);
DECLARE_DO_FUN( do_mppurge      );
DECLARE_DO_FUN( do_mpstat       );
DECLARE_DO_FUN( do_opstat       );
DECLARE_DO_FUN( do_rpstat       );
DECLARE_DO_FUN( do_mptransfer   );
DECLARE_DO_FUN( do_mpapply	);
DECLARE_DO_FUN( do_mpapplyb  	);
DECLARE_DO_FUN( do_mppkset	);
DECLARE_DO_FUN( do_mpgain	);

/*
 * Spell functions.
 * Defined in magic.c.
 */
DECLARE_SPELL_FUN(	spell_null		);
DECLARE_SPELL_FUN(	spell_notfound		);
DECLARE_SPELL_FUN(	spell_acid_blast	);
DECLARE_SPELL_FUN(	spell_animate_dead	);
DECLARE_SPELL_FUN(	spell_astral_walk	);
DECLARE_SPELL_FUN(	spell_blindness		);
DECLARE_SPELL_FUN(	spell_burning_hands	);
DECLARE_SPELL_FUN(	spell_call_lightning	);
DECLARE_SPELL_FUN(	spell_cause_critical	);
DECLARE_SPELL_FUN(	spell_cause_light	);
DECLARE_SPELL_FUN(	spell_cause_serious	);
DECLARE_SPELL_FUN(	spell_change_sex	);
DECLARE_SPELL_FUN(	spell_charm_person	);
DECLARE_SPELL_FUN(	spell_chill_touch	);
DECLARE_SPELL_FUN(	spell_colour_spray	);
DECLARE_SPELL_FUN(	spell_control_weather	);
DECLARE_SPELL_FUN(	spell_create_food	);
DECLARE_SPELL_FUN(	spell_create_water	);
DECLARE_SPELL_FUN(	spell_cure_blindness	);
DECLARE_SPELL_FUN(	spell_cure_poison	);
DECLARE_SPELL_FUN(	spell_curse		);
DECLARE_SPELL_FUN(	spell_detect_poison	);
DECLARE_SPELL_FUN(	spell_dispel_evil	);
DECLARE_SPELL_FUN(	spell_dispel_magic	);
DECLARE_SPELL_FUN(      spell_dream             );
DECLARE_SPELL_FUN(	spell_earthquake	);
DECLARE_SPELL_FUN(	spell_enchant_weapon	);
DECLARE_SPELL_FUN(	spell_energy_drain	);
DECLARE_SPELL_FUN(	spell_faerie_fire	);
DECLARE_SPELL_FUN(	spell_faerie_fog	);
DECLARE_SPELL_FUN(	spell_farsight		);
DECLARE_SPELL_FUN(	spell_fireball		);
DECLARE_SPELL_FUN(	spell_flamestrike	);
DECLARE_SPELL_FUN(	spell_gate		);
DECLARE_SPELL_FUN(      spell_knock             );
DECLARE_SPELL_FUN(	spell_injure		);
DECLARE_SPELL_FUN(	spell_identify		);
DECLARE_SPELL_FUN(	spell_invis		);
DECLARE_SPELL_FUN(	spell_know_alignment	);
DECLARE_SPELL_FUN(	spell_lightning_bolt	);
DECLARE_SPELL_FUN(	spell_locate_object	);
DECLARE_SPELL_FUN(	spell_magic_missile	);
DECLARE_SPELL_FUN(	spell_mist_walk		);
DECLARE_SPELL_FUN(	spell_pass_door		);
DECLARE_SPELL_FUN(	spell_plant_pass	);
DECLARE_SPELL_FUN(	spell_poison		);
DECLARE_SPELL_FUN(	spell_polymorph		);
DECLARE_SPELL_FUN(	spell_possess		);
DECLARE_SPELL_FUN(	spell_recharge		);
DECLARE_SPELL_FUN(	spell_remove_curse	);
DECLARE_SPELL_FUN(	spell_remove_invis	);
DECLARE_SPELL_FUN(	spell_remove_trap	);
DECLARE_SPELL_FUN(	spell_shocking_grasp	);
DECLARE_SPELL_FUN(	spell_sleep		);
DECLARE_SPELL_FUN(	spell_smaug		);
DECLARE_SPELL_FUN(	spell_solar_flight	);
DECLARE_SPELL_FUN(	spell_summon		);
DECLARE_SPELL_FUN(	spell_teleport		);
DECLARE_SPELL_FUN(	spell_ventriloquate	);
DECLARE_SPELL_FUN(	spell_weaken		);
DECLARE_SPELL_FUN(	spell_word_of_recall	);
DECLARE_SPELL_FUN(	spell_acid_breath	);
DECLARE_SPELL_FUN(	spell_fire_breath	);
DECLARE_SPELL_FUN(	spell_frost_breath	);
DECLARE_SPELL_FUN(	spell_gas_breath	);
DECLARE_SPELL_FUN(	spell_lightning_breath	);
DECLARE_SPELL_FUN(	spell_spiral_blast	);
DECLARE_SPELL_FUN(	spell_scorching_surge	);
DECLARE_SPELL_FUN(	spell_helical_flow	);
DECLARE_SPELL_FUN(      spell_transport      		);
DECLARE_SPELL_FUN(      spell_portal                    );

DECLARE_SPELL_FUN(      spell_ethereal_fist                 );
DECLARE_SPELL_FUN(      spell_spectral_furor                );
DECLARE_SPELL_FUN(      spell_hand_of_chaos                 );
DECLARE_SPELL_FUN(      spell_disruption                    );
DECLARE_SPELL_FUN(      spell_sonic_resonance               );
DECLARE_SPELL_FUN(      spell_mind_wrack                    );
DECLARE_SPELL_FUN(      spell_mind_wrench                   );
DECLARE_SPELL_FUN(      spell_revive                        );
DECLARE_SPELL_FUN(      spell_sulfurous_spray               );
DECLARE_SPELL_FUN(      spell_caustic_fount                 );
DECLARE_SPELL_FUN(      spell_acetum_primus                 );
DECLARE_SPELL_FUN(      spell_galvanic_whip                 );
DECLARE_SPELL_FUN(      spell_magnetic_thrust               );
DECLARE_SPELL_FUN(      spell_quantum_spike                 );
DECLARE_SPELL_FUN(      spell_black_hand                    );
DECLARE_SPELL_FUN(      spell_black_fist                    );
DECLARE_SPELL_FUN(      spell_black_lightning               );
DECLARE_SPELL_FUN(      spell_calm	                    );
DECLARE_SPELL_FUN(      spell_forcepush	                    );
DECLARE_SPELL_FUN(      spell_force_disarm                    );
DECLARE_SPELL_FUN(      spell_steal_life                    );
DECLARE_SPELL_FUN(      spell_midas_touch                   );

DECLARE_SPELL_FUN(      spell_suggest                       );
DECLARE_SPELL_FUN(      spell_cure_addiction                );

DECLARE_DO_FUN( fskill_convert            );
DECLARE_DO_FUN( fskill_awareness	  );
DECLARE_DO_FUN( fskill_fdisguise          );
DECLARE_DO_FUN( fskill_finfo              );
DECLARE_DO_FUN( fskill_fhelp              );
DECLARE_DO_FUN( fskill_finish             );
DECLARE_DO_FUN( fskill_force_lightning    );
DECLARE_DO_FUN( fskill_fshield            );
DECLARE_DO_FUN( fskill_heal               );
DECLARE_DO_FUN( fskill_identify           );
DECLARE_DO_FUN( fskill_instruct           );
DECLARE_DO_FUN( fskill_master             );
DECLARE_DO_FUN( fskill_makelightsaber     );
DECLARE_DO_FUN( fskill_promote            );
DECLARE_DO_FUN( fskill_protect            );
DECLARE_DO_FUN( fskill_refresh            );
DECLARE_DO_FUN( fskill_squeeze            );
DECLARE_DO_FUN( fskill_student            );
DECLARE_DO_FUN( fskill_slash              );
DECLARE_DO_FUN( fskill_whirlwind          );
DECLARE_DO_FUN( fskill_makedualsaber	  );
/*
 * OS-dependent declarations.
 * These are all very standard library functions,
 *   but some systems have incomplete or non-ansi header files.
 */
#if	defined(_AIX)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(apollo)
int	atoi		args( ( const char *string ) );
void *	calloc		args( ( unsigned nelem, size_t size ) );
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(hpux)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(interactive)
#endif

#if	defined(linux)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(MIPS_OS)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(NeXT)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

#if	defined(sequent)
char *	crypt		args( ( const char *key, const char *salt ) );
int	fclose		args( ( FILE *stream ) );
int	fprintf		args( ( FILE *stream, const char *format, ... ) );
int	fread		args( ( void *ptr, int size, int n, FILE *stream ) );
int	fseek		args( ( FILE *stream, long offset, int ptrname ) );
void	perror		args( ( const char *s ) );
int	ungetc		args( ( int c, FILE *stream ) );
#endif

#if	defined(sun)
char *	crypt		args( ( const char *key, const char *salt ) );
int	fclose		args( ( FILE *stream ) );
int	fprintf		args( ( FILE *stream, const char *format, ... ) );
/*
#if 	defined(SYSV)
*/
size_t 	fread		args( ( void *ptr, size_t size, size_t n,
/*				FILE *stream ) );
#else
int	fread		args( ( void *ptr, int size, int n, FILE *stream ) );
#endif
*/
int	fseek		args( ( FILE *stream, long offset, int ptrname ) );
void	perror		args( ( const char *s ) );
int	ungetc		args( ( int c, FILE *stream ) );
#endif

#if	defined(ultrix)
char *	crypt		args( ( const char *key, const char *salt ) );
#endif

/*
 * The crypt(3) function is not available on some operating systems.
 * In particular, the U.S. Government prohibits its export from the
 *   United States to foreign countries.
 * Turn on NOCRYPT to keep passwords in plain text.
 */
#if	defined(NOCRYPT)
#define crypt(s1, s2)	(s1)
#endif


/*
 * Data files used by the server.
 *
 * AREA_LIST contains a list of areas to boot.
 * All files are read in completely at bootup.
 * Most output files (bug, idea, typo, shutdown) are append-only.
 *
 * The NULL_FILE is held open so that we have a stream handle in reserve,
 *   so players can go ahead and telnet to all the other descriptors.
 * Then we close it whenever we need to open a file (e.g. a save file).
 */
#define PLAYER_DIR	"../player/"	/* Player files			*/
#define BACKUP_DIR	"../backup/"    /* Backup Player files		*/
#define GOD_DIR		"../gods/"	/* God Info Dir			*/
#define BOARD_DIR	"../boards/"	/* Board data dir		*/
#define CLAN_DIR	"../clans/"	/* Clan data dir		*/
#define JEDI_DIR	"../jedi/"
#define SENATE_DIR	"../senate/"
#define SHIP_DIR        "../space/"
#define SPACE_DIR       "../space/"    
#define SHIP_PROTOTYPE_DIR   "../ships/"
#define FORCE_DIR	"../force/"
#define FORCE_HELP_DIR	"../force/help/"
#define PLANET_DIR      "../planets/"    
#define GUARD_DIR       "../planets/"    
#define GUILD_DIR       "../guilds/"    /* Guild data dir               */
#define BUILD_DIR       "../building/"  /* Online building save dir     */
#define SYSTEM_DIR	"../system/"	/* Main system files		*/
#define PROG_DIR	"mudprogs/"	/* MUDProg files		*/
#define CORPSE_DIR	"../corpses/"	/* Corpses			*/
#define PROFILE_DIR	"../html/profiles/"	/* Player Profiles */
#define NULL_FILE	"/dev/null"	/* To reserve one stream	*/
#define AREA_LIST	"area.lst"	/* List of areas		*/
#define BAN_LIST        "ban.lst"       /* List of bans                 */
#define CLAN_LIST	"clan.lst"	/* List of clans		*/
#define SENATE_LIST     "senate.lst"
#define JEDI_LIST	"jedi.lst"
#define SHIP_LIST       "ship.lst"
#define PROTOTYPE_LIST  "prototype.lst"
#define PLANET_LIST      "planet.lst"
#define SPACE_LIST      "space.lst"
#define BOUNTY_LIST     "bounty.lst"      
#define disintegration_LIST	"disintegration.lst"
#define SENATE_LIST	"senate.lst"	/* List of senators		*/
#define GUILD_LIST      "guild.lst"     /* List of guilds               */
#define GOD_LIST	"gods.lst"	/* List of gods			*/
#define GUARD_LIST	"guard.lst"

#define BOARD_FILE	"boards.txt"		/* For bulletin boards	 */
#define SHUTDOWN_FILE	"shutdown.txt"		/* For 'shutdown'	 */

#define RIPSCREEN_FILE	SYSTEM_DIR "mudrip.rip"
#define RIPTITLE_FILE	SYSTEM_DIR "mudtitle.rip"
#define ANSITITLE_FILE	SYSTEM_DIR "mudtitle.ans"
#define ASCTITLE_FILE	SYSTEM_DIR "mudtitle.asc"
#define BOOTLOG_FILE	SYSTEM_DIR "boot.txt"	  /* Boot up error file	 */
#define BUG_FILE	SYSTEM_DIR "bugs.txt"	  /* For 'bug' and bug( )*/
#define IDEA_FILE	SYSTEM_DIR "ideas.txt"	  /* For 'idea'		 */
#define CHANGE_FILE	SYSTEM_DIR "changes.txt"  /* Changes file - txt  */
#define CHANGEHTML_FILE	"../html/changes.html" /* Changes file - html */
#define DEBUG_FILE	SYSTEM_DIR "debug.txt"	  /* Catch-all for debug */
#define TYPO_FILE	SYSTEM_DIR "typos.txt"	  /* For 'typo'		 */
#define LOG_FILE	SYSTEM_DIR "log.txt"	  /* For talking in logged rooms */
#define WIZLIST_FILE	SYSTEM_DIR "WIZLIST"	  /* Wizlist		 */
#define WEBWIZLIST_FILE	"../html/WEBWIZLIST"  /* Web Wizlist	 */
#define WHO_FILE	SYSTEM_DIR "../html/WHO"	  /* Who output file	 */
#define WEBWHO_FILE	"../html/WEBWHO"/* Web Who File 	 */
#define REQUEST_PIPE	SYSTEM_DIR "REQUESTS"	  /* Request FIFO	 */
#define SKILL_FILE	SYSTEM_DIR "skills.dat"   /* Skill table	 */
#define HERB_FILE	SYSTEM_DIR "herbs.dat"	  /* Herb table		 */
#define SOCIAL_FILE	SYSTEM_DIR "socials.dat"  /* Socials		 */
#define COMMAND_FILE	SYSTEM_DIR "commands.dat" /* Commands		 */
#define NAMEBAN_FILE	SYSTEM_DIR "nameban.dat"  /* Nameban		 */
#define USAGE_FILE	SYSTEM_DIR "usage.txt"    /* How many people are on 
 						     every half hour - trying to
						     determine best reboot time */
#define TEMP_FILE	SYSTEM_DIR "charsave.tmp" /* More char save protect */						     
#define COPYOVER_FILE	SYSTEM_DIR "copyover.dat" /* for warm reboots	 */
#define EXE_FILE	"../src/swr"		  /* executable path	 */						     
#define SLOG_FILE	"../.slog/slog.txt"	  /* Secret Log		 */

/*
 * Our function prototypes.
 * One big lump ... this is every function in Merc.
 */
#define CD	CHAR_DATA
#define MID	MOB_INDEX_DATA
#define OD	OBJ_DATA
#define OID	OBJ_INDEX_DATA
#define RID	ROOM_INDEX_DATA
#define SF	SPEC_FUN
#define BD	BOARD_DATA
#define CL	CLAN_DATA
#define EDD	EXTRA_DESCR_DATA
#define RD	RESET_DATA
#define ED	EXIT_DATA
#define	ST	SOCIALTYPE
#define	CO	COUNCIL_DATA
#define DE	DEITY_DATA
#define SK	SKILLTYPE
#define SH      SHIP_DATA


/* editor.c cronel new editor */
#define start_editing( ch, data ) \
	start_editing_nolimit( ch, data, MAX_STRING_LENGTH )
void	start_editing_nolimit	args( ( CHAR_DATA *ch, char *data, sh_int max_size ) );
void	stop_editing	args( ( CHAR_DATA *ch ) );
void	edit_buffer	args( ( CHAR_DATA *ch, char *argument ) );
char *	copy_buffer	args( ( CHAR_DATA *ch ) );
void	set_editor_desc	args( ( CHAR_DATA *ch, char *desc ) );
void	editor_desc_printf args( ( CHAR_DATA *ch, char *desc_fmt, ... ) );

/* pfiles.c */
void 	remove_member	args( (char *name, char *shortname) );
void 	add_member	args( (char *name, char *shortname) );

/* act_comm.c */
void	talk_channel	args( ( CHAR_DATA *ch, char *argument, int channel, const char *verb ) );
bool    check_parse_name        args( ( char *name ) );
void    sound_to_room( ROOM_INDEX_DATA *room , char *argument );
bool	circle_follow	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	add_follower	args( ( CHAR_DATA *ch, CHAR_DATA *master ) );
void	stop_follower	args( ( CHAR_DATA *ch ) );
void	die_follower	args( ( CHAR_DATA *ch ) );
bool	is_same_group	args( ( CHAR_DATA *ach, CHAR_DATA *bch ) );
void	send_rip_screen args( ( CHAR_DATA *ch ) );
void	send_rip_title	args( ( CHAR_DATA *ch ) );
void	send_ansi_title args( ( CHAR_DATA *ch ) );
void	send_ascii_title args( ( CHAR_DATA *ch ) );
void	to_channel	args( ( const char *argument, int channel,
				const char *verb, sh_int level ) );
void  	talk_auction    args( ( char *argument ) );
bool    knows_language  args( ( CHAR_DATA *ch, int language,
				CHAR_DATA *cch ) );
bool    can_learn_lang  args( ( CHAR_DATA *ch, int language ) );
int     countlangs      args( ( int languages ) );
char *	obj_short	args( ( OBJ_DATA *obj ) );

/* act_info.c */
bool	can_see_force	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void    show_char_to_char       args( ( CHAR_DATA *list, CHAR_DATA *ch ) );
int	get_door	args( ( char *arg ) );
char *	format_obj_to_char	args( ( OBJ_DATA *obj, CHAR_DATA *ch,
				    bool fShort ) );
void	show_list_to_char	args( ( OBJ_DATA *list, CHAR_DATA *ch,
				    bool fShort, bool fShowNothing ) );
void    show_ships_to_char      args( ( SHIP_DATA *ship, CHAR_DATA *ch ) );

/* act_move.c */
void	clear_vrooms	args( ( void ) );
ED *	find_door	args( ( CHAR_DATA *ch, char *arg, bool quiet ) );
ED *	get_exit	args( ( ROOM_INDEX_DATA *room, sh_int dir ) );
ED *	get_exit_to	args( ( ROOM_INDEX_DATA *room, sh_int dir, int vnum ) );
ED *	get_exit_num	args( ( ROOM_INDEX_DATA *room, sh_int count ) );
ch_ret	move_char	args( ( CHAR_DATA *ch, EXIT_DATA *pexit, int fall ) );
void	teleport	args( ( CHAR_DATA *ch, sh_int room, int flags ) );
sh_int	encumbrance	args( ( CHAR_DATA *ch, sh_int move ) );
bool	will_fall	args( ( CHAR_DATA *ch, int fall ) );
int     wherehome       args( ( CHAR_DATA *ch ) );

/* act_obj.c */

obj_ret	damage_obj	args( ( OBJ_DATA *obj ) );
sh_int	get_obj_resistance args( ( OBJ_DATA *obj ) );
bool    remove_obj      args( ( CHAR_DATA *ch, int iWear, bool fReplace ) );
void    save_clan_storeroom args( ( CHAR_DATA *ch, CLAN_DATA *clan ) );
void    obj_fall  	args( ( OBJ_DATA *obj, bool through ) );

/* act_wiz.c */
void              close_area    args( ( AREA_DATA *pArea ) );
AREA_DATA *	get_area	args( ( char *argument ) );
RID *	find_location	args( ( CHAR_DATA *ch, char *arg ) );
void    echo_to_room    args( ( sh_int AT_COLOR, ROOM_INDEX_DATA *room, char *argument ) );
void	echo_to_all	args( ( sh_int AT_COLOR, char *argument,
				sh_int tar ) );
void   	get_reboot_string args( ( void ) );
struct tm *update_time  args( ( struct tm *old_time ) );
void	free_social	args( ( SOCIALTYPE *social ) );
void	add_social	args( ( SOCIALTYPE *social ) );
void	free_command	args( ( CMDTYPE *command ) );
void	unlink_command	args( ( CMDTYPE *command ) );
void	add_command	args( ( CMDTYPE *command ) );

/* boards.c */
void	load_boards	args( ( void ) );
BD *	get_board	args( ( OBJ_DATA *obj ) );
void	free_note	args( ( NOTE_DATA *pnote ) );

/* build.c */
char *	flag_string	args( ( int bitvector, char * const flagarray[] ) );
int	get_mpflag	args( ( char *flag ) );
int	get_dir		args( ( char *txt  ) );
char *	strip_cr	args( ( char *str  ) );
int     get_vip_flag    args( ( char *flag ) );
int     get_wanted_flag args( ( char *flag ) );

/* clans.c */
CL *	get_clan		args( ( char *name ) );
SENATE2_DATA  * get_senate		args( ( char *name ) );
void	load_clans		args( ( void ) );
void	save_clan		args( ( CLAN_DATA *clan ) );
void	load_jedis		args( ( void ) );
void    load_senates		args( ( void ) );
void	load_senate		args( ( void ) );
void	save_senate		args( ( void ) );
PLANET_DATA *	get_planet	args( ( char *name ) );
void	load_planets		args( ( void ) );
void	save_planet		args( ( PLANET_DATA *planet ) );
long    get_taxes               args( ( PLANET_DATA *planet ) );

/* bounty.c */
BOUNTY_DATA  * get_disintegration   args( ( char *target ) );
void        load_bounties   args( ( void ) );
void        save_bounties   args( ( void ) );
void        save_disintegrations   args( ( void ) );
void        remove_disintegration   args( ( BOUNTY_DATA *bounty ) );
void	    claim_disintegration    args( ( CHAR_DATA *ch , CHAR_DATA *victim ) );
bool        is_disintegration args( ( CHAR_DATA *victim ) );

/* class.c */
int 	    skill_max		args( ( CHAR_DATA *ch, int skill ) );
int	    fskill_max		args( ( CHAR_DATA *ch, int skill ) );
char 	    lightsaber_color	args( ( int color ) );
void	    body_parts		args( ( CHAR_DATA *ch, int iRace ) );
void	    racial_bonus	args( ( CHAR_DATA *ch, int iRace ) );
void	    gain_darkpoint	args( ( CHAR_DATA *ch ) );
void	    gain_darklevel	args( ( CHAR_DATA *ch ) );
bool	    check_req		args( ( CHAR_DATA *ch, int flag ) );
bool	    check_req2		args( ( CHAR_DATA *ch, int flag ) );
void	    level_class		args( ( CHAR_DATA *ch, int Ability ) );

/* force.c */

bool	check_reflect		args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dam ) );
void write_all_forceskills();
void save_forceskill( FORCE_SKILL *fskill );
void write_forceskill_list( );
bool load_forceskill( char *forceskillfile );
void fread_forceskill( FORCE_SKILL *fskill, FILE *fp );
void write_all_forcehelps();
void save_forcehelp( FORCE_HELP *fhelp );
void write_forcehelp_list( );
bool load_forcehelp( char *forcehelpfile );
void fread_forcehelp( FORCE_HELP *fhelp, FILE *fp );
int check_force_skill args( (CHAR_DATA *ch, char *command, char *argument) );
void load_force_skills args( ( void ) );
void load_force_help args( ( void ) );
DO_FUN *get_force_skill_function args( (char *name) );
FORCE_SKILL *get_force_skill(char *argument);
FORCE_HELP *get_force_help(char *fname,char *type);
void force_send_to_room args( (CHAR_DATA *ch, CHAR_DATA *victim, char *msg) );
CHAR_DATA *force_get_victim args( (CHAR_DATA *ch,char *argument,int loc) );
char *force_get_possessive( CHAR_DATA *ch );
char *force_get_objective( CHAR_DATA *ch );
char *force_get_pronoun( CHAR_DATA *ch );
char *force_parse_string( CHAR_DATA *ch, CHAR_DATA *victim, char *msg);
void force_learn_from_failure args( (CHAR_DATA *ch,FORCE_SKILL *fskill) );
void force_learn_from_success args( (CHAR_DATA *ch,FORCE_SKILL *fskill) );
FORCE_SKILL *force_test_skill_use args( (char *skill_name,CHAR_DATA *ch,int skill_type) );
char *force_get_level( CHAR_DATA *ch );
int force_promote_ready(CHAR_DATA *ch);
void draw_force_line(CHAR_DATA *ch,int length);
void draw_force_line_rev(CHAR_DATA *ch, int length);
void update_force args( ( void ) );


/* space.c */
SH        *  get_ship          	    args( ( char *name ) );
void         load_ships        	    args( ( void ) );
void         placeships        	    args( ( void ) );
void         save_ship      	    args( ( SHIP_DATA *ship ) );
void         load_space             args( ( void ) );
void         save_starsystem        args( ( SPACE_DATA *starsystem ) );
SPACE_DATA * starsystem_from_name   args( ( char *name ) );
SPACE_DATA * starsystem_from_room   args( ( ROOM_INDEX_DATA * room ) );
SHIP_DATA  * ship_from_entrance     args( ( int vnum ) );
SHIP_DATA  * ship_from_room         args( ( int vnum ) );
SHIP_DATA  * ship_from_hanger       args( ( int vnum ) );
SHIP_DATA  * ship_from_pilotseat    args( ( int vnum ) );
SHIP_DATA  * ship_from_cockpit      args( ( int vnum ) );
SHIP_DATA  * ship_from_cargohold    args( ( int vnum ) );
SHIP_DATA  * ship_from_turret       args( ( int vnum ) );
SHIP_DATA  * ship_from_engine       args( ( int vnum ) );
SHIP_DATA  * ship_from_pilot        args( ( char *name ) );
SHIP_DATA  * get_ship_here          args( ( char *name , SPACE_DATA *starsystem ) );
void         showstarsystem         args( ( CHAR_DATA *ch , SPACE_DATA *starsystem ) );
void         update_space           args( ( void ) );
void         recharge_ships         args( ( void ) );
void         move_ships             args( ( void ) );
void         update_bus             args( ( void ) );
void         update_traffic         args( ( void ) );
bool         check_pilot            args( ( CHAR_DATA *ch , SHIP_DATA *ship ) );
bool         is_rental              args( ( CHAR_DATA *ch , SHIP_DATA *ship ) );
void         echo_to_ship           args( ( int color , SHIP_DATA *ship , char *argument ) );
void         echo_to_cockpit        args( ( int color , SHIP_DATA *ship , char *argument ) );
void         echo_to_system         args( ( int color , SHIP_DATA *ship , char *argument , SHIP_DATA *ignore ) );
bool         extract_ship           args( ( SHIP_DATA *ship ) );
bool         ship_to_room           args( ( SHIP_DATA *ship , int vnum ) );
bool         ship_to_room2          args( ( SHIP_DATA *ship , ROOM_INDEX_DATA *shipto ) );
long         get_ship_value         args( ( SHIP_DATA *ship ) );
bool         rent_ship              args( ( CHAR_DATA *ch , SHIP_DATA *ship ) );
void         damage_ship            args( ( SHIP_DATA *ship , int min , int max ) );
void         damage_ship_ch         args( ( SHIP_DATA *ship , int min , int max , CHAR_DATA *ch ) );
void         destroy_ship           args( ( SHIP_DATA *ship , CHAR_DATA *ch , char *reason ) );
void         ship_to_starsystem     args( ( SHIP_DATA *ship , SPACE_DATA *starsystem ) );
void         ship_from_starsystem   args( ( SHIP_DATA *ship , SPACE_DATA *starsystem ) );
void         new_missile            args( ( SHIP_DATA *ship , SHIP_DATA *target , CHAR_DATA *ch, int missiletype ) );
void         extract_missile        args( ( MISSILE_DATA *missile ) );
SHIP_DATA * ship_in_room            args( ( ROOM_INDEX_DATA *room, char *name ) ); 

/* morespace.c */
//SHIP_PROTOTYPE *  get_ship_prototype        args( ( char *name ) );
void         load_prototypes        	    args( ( void ) );
//void         save_ship_protoype      	    args( ( SHIP_PROTOTYPE *prototype ) );
//long int     get_prototype_value      	    args( ( SHIP_PROTOTYPE *prototype ) );
void	     create_ship_rooms		    args( ( SHIP_DATA * ship ) );

/* comm.c */
char    *PERS		args( (CHAR_DATA *ch, CHAR_DATA *looker ) );
FELLOW_DATA *  knowsof	args( (CHAR_DATA *ch, CHAR_DATA *victim ) );
void	close_socket	args( ( DESCRIPTOR_DATA *dclose, bool force ) );
void	write_to_buffer	args( ( DESCRIPTOR_DATA *d, const char *txt,
				int length ) );
void	write_to_pager	args( ( DESCRIPTOR_DATA *d, const char *txt,
				int length ) );
void	send_to_char	args( ( const char *txt, CHAR_DATA *ch ) );
void	send_to_char_color	args( ( const char *txt, CHAR_DATA *ch ) );
void	send_to_desc_color	args( ( const char *txt, DESCRIPTOR_DATA *d ) );
void	send_to_char_noand  args( ( const char *txt, CHAR_DATA *ch ) );
void	send_to_pager	args( ( const char *txt, CHAR_DATA *ch ) );
void	send_to_pager_color	args( ( const char *txt, CHAR_DATA *ch ) );
void	set_char_color  args( ( sh_int AType, CHAR_DATA *ch ) );
void	set_pager_color	args( ( sh_int AType, CHAR_DATA *ch ) );
void	ch_printf	args( ( CHAR_DATA *ch, char *fmt, ... ) );
char *	chrmax		args( ( char *src, int length ) );
int     strlen_color    args( (char *argument) );
char *	format_str	args( (char *str, int len) );
void	pager_printf	args( (CHAR_DATA *ch, char *fmt, ...) );
void	log_printf	args( (char *fmt, ...) );
void	copyover_recover	args( (void) );

void	act		args( ( sh_int AType, const char *format, CHAR_DATA *ch,
			    const void *arg1, const void *arg2, int type ) );

/* reset.c */
void wipe_resets( AREA_DATA *pArea, ROOM_INDEX_DATA *pRoom );
RD  *	make_reset	args( ( char letter, int extra, int arg1, int arg2, int arg3 ) );
RD  *	add_reset	args( ( AREA_DATA *tarea, char letter, int extra, int arg1, int arg2, int arg3 ) );
RD  *	place_reset	args( ( AREA_DATA *tarea, char letter, int extra, int arg1, int arg2, int arg3 ) );
void	reset_area	args( ( AREA_DATA * pArea ) );
void 	add_obj_reset   args( ( AREA_DATA *pArea, char cm, OBJ_DATA *obj, int v2, int v3 ) );

/* db.c */
void	show_file	args( ( CHAR_DATA *ch, char *filename ) );
char *	str_dup		args( ( char const *str ) );
char *	centertext	args( ( char *text, int size ) );
void	boot_db		args( ( bool fCopyOver ) );
void	area_update	args( ( void ) );
void	add_char	args( ( CHAR_DATA *ch ) );
CD *	create_mobile	args( ( MOB_INDEX_DATA *pMobIndex ) );
OD *	create_object	args( ( OBJ_INDEX_DATA *pObjIndex, int level ) );
void	clear_char	args( ( CHAR_DATA *ch ) );
void	free_char	args( ( CHAR_DATA *ch ) );
char *	get_extra_descr	args( ( const char *name, EXTRA_DESCR_DATA *ed ) );
MID *	get_mob_index	args( ( sh_int vnum ) );
OID *	get_obj_index	args( ( int vnum ) );
RID *	get_room_index	args( ( int vnum ) );
char	fread_letter	args( ( FILE *fp ) );
int	fread_number	args( ( FILE *fp ) );
char *	fread_string	args( ( FILE *fp ) );
char *	fread_string_nohash args( ( FILE *fp ) );
void	fread_to_eol	args( ( FILE *fp ) );
char *	fread_word	args( ( FILE *fp ) );
char *	fread_line	args( ( FILE *fp ) );
int	number_fuzzy	args( ( int number ) );
int	number_range	args( ( int from, int to ) );
int	number_percent	args( ( void ) );
int	number_door	args( ( void ) );
int	number_bits	args( ( int width ) );
int	number_mm	args( ( void ) );
int	dice		args( ( int number, int size ) );
int	interpolate	args( ( int level, int value_00, int value_32 ) );
void	smash_tilde	args( ( char *str ) );
void	hide_tilde	args( ( char *str ) );
char *	show_tilde	args( ( char *str ) );
bool	str_cmp		args( ( const char *astr, const char *bstr ) );
bool	str_prefix	args( ( const char *astr, const char *bstr ) );
bool	str_infix	args( ( const char *astr, const char *bstr ) );
bool	str_suffix	args( ( const char *astr, const char *bstr ) );
char *	capitalize	args( ( const char *str ) );
char *	strlower	args( ( const char *str ) );
char *	strupper	args( ( const char *str ) );
char *  aoran		args( ( const char *str ) );
void	append_file	args( ( CHAR_DATA *ch, char *file, char *str ) );
void	append_to_file	args( ( char *file, char *str ) );
void	prepend_to_file	args( ( char *file, char *str ) );
void	bug		args( ( const char *str, ... ) );
void	log_string_plus	args( ( const char *str, sh_int log_type, sh_int level ) );
RID *	make_room	args( ( int vnum ) );
RID *	make_ship_room	args( ( SHIP_DATA * ship, int vnum ) );
OID *	make_object	args( ( int vnum, int cvnum, char *name ) );
MID *	make_mobile	args( ( sh_int vnum, sh_int cvnum, char *name ) );
ED  *	make_exit	args( ( ROOM_INDEX_DATA *pRoomIndex, ROOM_INDEX_DATA *to_room, sh_int door ) );
void	add_help	args( ( HELP_DATA *pHelp ) );
void	fix_area_exits	args( ( AREA_DATA *tarea ) );
void	load_area_file	args( ( AREA_DATA *tarea, char *filename ) );
void	randomize_exits	args( ( ROOM_INDEX_DATA *room, sh_int maxdir ) );
void	make_wizlist	args( ( void ) );
void	tail_chain	args( ( void ) );
bool    delete_room     args( ( ROOM_INDEX_DATA *room ) );
bool    delete_obj      args( ( OBJ_INDEX_DATA *obj ) );
bool    delete_mob      args( ( MOB_INDEX_DATA *mob ) );
/* Functions to add to sorting lists. -- Altrag */
/*void	mob_sort	args( ( MOB_INDEX_DATA *pMob ) );
void	obj_sort	args( ( OBJ_INDEX_DATA *pObj ) );
void	room_sort	args( ( ROOM_INDEX_DATA *pRoom ) );*/
void	sort_area	args( ( AREA_DATA *pArea, bool proto ) );

/* build.c */
bool	can_rmodify	args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *room ) );
bool	can_omodify	args( ( CHAR_DATA *ch, OBJ_DATA *obj  ) );
bool	can_mmodify	args( ( CHAR_DATA *ch, CHAR_DATA *mob ) );
bool	can_medit	args( ( CHAR_DATA *ch, MOB_INDEX_DATA *mob ) );
void	free_reset	args( ( AREA_DATA *are, RESET_DATA *res ) );
void	free_area	args( ( AREA_DATA *are ) );
void	assign_area	args( ( CHAR_DATA *ch ) );
EDD *	SetRExtra	args( ( ROOM_INDEX_DATA *room, char *keywords ) );
bool	DelRExtra	args( ( ROOM_INDEX_DATA *room, char *keywords ) );
EDD *	SetOExtra	args( ( OBJ_DATA *obj, char *keywords ) );
bool	DelOExtra	args( ( OBJ_DATA *obj, char *keywords ) );
EDD *	SetOExtraProto	args( ( OBJ_INDEX_DATA *obj, char *keywords ) );
bool	DelOExtraProto	args( ( OBJ_INDEX_DATA *obj, char *keywords ) );
void	fold_area	args( ( AREA_DATA *tarea, char *filename, bool install ) );
int	get_otype	args( ( char *type ) );
int	get_atype	args( ( char *type ) );
int	get_aflag	args( ( char *flag ) );
int	get_pflag	args( ( char *flag ) );
int	get_plflag	args( ( char *flag ) );
int	get_oflag	args( ( char *flag ) );
int	get_wflag	args( ( char *flag ) );

/* fight.c */
void	check_fumble	args( ( CHAR_DATA *ch, OBJ_DATA *wield ) );
bool    check_critical	args( ( CHAR_DATA *ch, int diceroll, bool wield, int armor) );
int	max_fight	args( ( CHAR_DATA *ch ) );
void	violence_update	args( ( void ) );
ch_ret	multi_hit	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dt ) );
sh_int	ris_damage	args( ( CHAR_DATA *ch, sh_int dam, int ris ) );
ch_ret	damage		args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dam,
			    int dt, bool critical ) );
void	update_pos	args( ( CHAR_DATA *victim ) );
void    update_med	args( ( CHAR_DATA *ch ) );
void	set_fighting	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	stop_fighting	args( ( CHAR_DATA *ch, bool fBoth ) );
void	free_fight	args( ( CHAR_DATA *ch ) );
CD *	who_fighting	args( ( CHAR_DATA *ch ) );
void	check_killer	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	check_attacker	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	death_cry	args( ( CHAR_DATA *ch ) );
void	stop_hunting	args( ( CHAR_DATA *ch ) );
void	stop_hating	args( ( CHAR_DATA *ch ) );
void	stop_fearing	args( ( CHAR_DATA *ch ) );
void	start_hunting	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	start_hating	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	start_fearing	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	is_hunting	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	is_hating	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	is_fearing	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	is_safe		args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	is_safe_nm	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	legal_loot	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool    check_illegal_pk args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void    raw_kill        args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );   
bool	in_arena	args( ( CHAR_DATA *ch ) );

/* makeobjs.c */
void	make_corpse	args( ( CHAR_DATA *ch, char *killer ) );
void	make_blood	args( ( CHAR_DATA *ch ) );
void	make_bloodstain args( ( CHAR_DATA *ch ) );
void	make_scraps	args( ( OBJ_DATA *obj ) );
void	make_fire	args( ( ROOM_INDEX_DATA *in_room, sh_int timer) );
OD *	make_trap	args( ( int v0, int v1, int v2, int v3 ) );
OD *	create_money	args( ( int amount ) );

/* misc.c */
void actiondesc args( ( CHAR_DATA *ch, OBJ_DATA *obj, void *vo ) );
void jedi_checks  args( ( CHAR_DATA *ch ) );
void jedi_bonus   args( ( CHAR_DATA *ch ) );
void sith_penalty args( ( CHAR_DATA *ch ) );

/* mud_comm.c */
char *	mprog_type_to_name	args( ( int type ) );

/* mud_prog.c */
#ifdef DUNNO_STRSTR
char *  strstr                  args ( (const char *s1, const char *s2 ) );
#endif

void	mprog_wordlist_check    args ( ( char * arg, CHAR_DATA *mob,
                			CHAR_DATA* actor, OBJ_DATA* object,
					void* vo, int type ) );
void	mprog_percent_check     args ( ( CHAR_DATA *mob, CHAR_DATA* actor,
					OBJ_DATA* object, void* vo,
					int type ) );
void	mprog_act_trigger       args ( ( char* buf, CHAR_DATA* mob,
		                        CHAR_DATA* ch, OBJ_DATA* obj,
					void* vo ) );
void	mprog_bribe_trigger     args ( ( CHAR_DATA* mob, CHAR_DATA* ch,
		                        int amount ) );
void	mprog_entry_trigger     args ( ( CHAR_DATA* mob ) );
void	mprog_give_trigger      args ( ( CHAR_DATA* mob, CHAR_DATA* ch,
                		        OBJ_DATA* obj ) );
void	mprog_greet_trigger     args ( ( CHAR_DATA* mob ) );
void    mprog_fight_trigger     args ( ( CHAR_DATA* mob, CHAR_DATA* ch ) );
void    mprog_hitprcnt_trigger  args ( ( CHAR_DATA* mob, CHAR_DATA* ch ) );
void    mprog_death_trigger     args ( ( CHAR_DATA *killer, CHAR_DATA* mob ) );
void    mprog_random_trigger    args ( ( CHAR_DATA* mob ) );
void    mprog_speech_trigger    args ( ( char* txt, CHAR_DATA* mob ) );
void    mprog_script_trigger    args ( ( CHAR_DATA *mob ) );
void    mprog_hour_trigger      args ( ( CHAR_DATA *mob ) );
void    mprog_time_trigger      args ( ( CHAR_DATA *mob ) );
void    progbug                 args( ( char *str, CHAR_DATA *mob ) );
void	rset_supermob		args( ( ROOM_INDEX_DATA *room) );
void	release_supermob	args( ( ) );
void	mpsleep_update		args( ( ) );

/* player.c */
void	set_title	args( ( CHAR_DATA *ch, char *title ) );

/* skills.c */
bool	check_skill		args( ( CHAR_DATA *ch, char *command, char *argument ) );
void	learn_skill		args( ( CHAR_DATA *ch, int skill ) );
void	learn_force		args( ( CHAR_DATA *ch, int skill ) );
void 	learn_from_success	args( ( CHAR_DATA *ch, int sn ) );
void	learn_from_failure	args( ( CHAR_DATA *ch, int sn ) );
void	disarm			args( ( CHAR_DATA *ch, CHAR_DATA *victim) );
void	trip			args( ( CHAR_DATA *ch, CHAR_DATA *victim) );


/* handler.c */
QUEST_DATA * quest_from_name args( ( CHAR_DATA *ch, char *argument ) );
int 	skill_roll	args( ( CHAR_DATA *ch, int iSkill ) );
int	fskill_roll	args( ( CHAR_DATA *ch, int iSkill ) );
void	remove_bodypart	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int part ) );
int	GET_AC		args( ( CHAR_DATA *ch ) );
void    explode         args( ( OBJ_DATA *obj ) );
int	get_exp		args( ( CHAR_DATA *ch , int ability ) );
int	get_exp_worth	args( ( CHAR_DATA *ch ) );
int	exp_level	args( ( sh_int level ) );
sh_int	get_trust	args( ( CHAR_DATA *ch ) );
sh_int	get_age		args( ( CHAR_DATA *ch ) );
sh_int	get_curr_str	args( ( CHAR_DATA *ch ) );
sh_int	get_curr_int	args( ( CHAR_DATA *ch ) );
sh_int	get_curr_wis	args( ( CHAR_DATA *ch ) );
sh_int	get_curr_dex	args( ( CHAR_DATA *ch ) );
sh_int	get_curr_con	args( ( CHAR_DATA *ch ) );
sh_int	get_curr_cha	args( ( CHAR_DATA *ch ) );
sh_int  get_curr_lck	args( ( CHAR_DATA *ch ) );
sh_int  get_curr_frc	args( ( CHAR_DATA *ch ) );
bool	can_take_proto	args( ( CHAR_DATA *ch ) );
int	can_carry_n	args( ( CHAR_DATA *ch ) );
int	can_carry_w	args( ( CHAR_DATA *ch ) );
bool	is_name		args( ( const char *str, char *namelist ) );
bool	is_name_prefix	args( ( const char *str, char *namelist ) );
bool	nifty_is_name	args( ( char *str, char *namelist ) );
bool	nifty_is_name_prefix args( ( char *str, char *namelist ) );
void	affect_modify	args( ( CHAR_DATA *ch, AFFECT_DATA *paf, bool fAdd ) );
void	affect_to_char	args( ( CHAR_DATA *ch, AFFECT_DATA *paf ) );
void	affect_remove	args( ( CHAR_DATA *ch, AFFECT_DATA *paf ) );
void	affect_strip	args( ( CHAR_DATA *ch, int sn ) );
bool	is_affected	args( ( CHAR_DATA *ch, int sn ) );
void	affect_join	args( ( CHAR_DATA *ch, AFFECT_DATA *paf ) );
void	char_from_room	args( ( CHAR_DATA *ch ) );
void	char_to_room	args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *pRoomIndex ) );
OD *	obj_to_char	args( ( OBJ_DATA *obj, CHAR_DATA *ch ) );
void	obj_from_char	args( ( OBJ_DATA *obj ) );
int	apply_ac	args( ( OBJ_DATA *obj, int iWear ) );
OD *	get_eq_char	args( ( CHAR_DATA *ch, int iWear ) );
void	equip_char	args( ( CHAR_DATA *ch, OBJ_DATA *obj, int iWear ) );
void	unequip_char	args( ( CHAR_DATA *ch, OBJ_DATA *obj ) );
int	count_obj_list	args( ( OBJ_INDEX_DATA *obj, OBJ_DATA *list ) );
int	count_mob_in_room	args( ( MOB_INDEX_DATA *mob, ROOM_INDEX_DATA *list ) );
void	obj_from_room	args( ( OBJ_DATA *obj ) );
OD *	obj_to_room	args( ( OBJ_DATA *obj, ROOM_INDEX_DATA *pRoomIndex ) );
OD *	obj_to_obj	args( ( OBJ_DATA *obj, OBJ_DATA *obj_to ) );
void	obj_from_obj	args( ( OBJ_DATA *obj ) );
void	extract_obj	args( ( OBJ_DATA *obj ) );
void	extract_exit	args( ( ROOM_INDEX_DATA *room, EXIT_DATA *pexit ) );
void	extract_room	args( ( ROOM_INDEX_DATA *room ) );
void	clean_room	args( ( ROOM_INDEX_DATA *room ) );
void	clean_obj	args( ( OBJ_INDEX_DATA *obj ) );
void	clean_mob	args( ( MOB_INDEX_DATA *mob ) );
void	clean_resets	args( ( AREA_DATA *tarea ) );
void	extract_char	args( ( CHAR_DATA *ch, bool fPull ) );
CD *	get_char_room	args( ( CHAR_DATA *ch, char *argument ) );
CD *	get_char_world	args( ( CHAR_DATA *ch, char *argument ) );
CD *	get_char_world_ooc args( ( CHAR_DATA *ch, char *argument ) );
CD *    get_char_from_comfreq  args((CHAR_DATA *ch, char *argument));
OD *	get_obj_type	args( ( OBJ_INDEX_DATA *pObjIndexData ) );
OD *	get_obj_list	args( ( CHAR_DATA *ch, char *argument,
			    OBJ_DATA *list ) );
OD *	get_obj_list_rev args( ( CHAR_DATA *ch, char *argument,
			    OBJ_DATA *list ) );
OD *	get_obj_carry	args( ( CHAR_DATA *ch, char *argument ) );
OD *	get_obj_wear	args( ( CHAR_DATA *ch, char *argument ) );
OD *	get_obj_here	args( ( CHAR_DATA *ch, char *argument ) );
OD *	get_obj_world	args( ( CHAR_DATA *ch, char *argument ) );
int	get_obj_number	args( ( OBJ_DATA *obj ) );
int	get_obj_weight	args( ( OBJ_DATA *obj ) );
bool	room_is_dark	args( ( ROOM_INDEX_DATA *pRoomIndex ) );
bool	room_is_private	args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *pRoomIndex ) );
bool	can_see		args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	can_see_obj	args( ( CHAR_DATA *ch, OBJ_DATA *obj ) );
bool	can_drop_obj	args( ( CHAR_DATA *ch, OBJ_DATA *obj ) );
char *	item_type_name	args( ( OBJ_DATA *obj ) );
char *	affect_loc_name	args( ( int location ) );
char *	affect_bit_name	args( ( int vector ) );
char *	extra_bit_name	args( ( int extra_flags ) );
char *	magic_bit_name	args( ( int magic_flags ) );
ch_ret	check_for_trap	args( ( CHAR_DATA *ch, OBJ_DATA *obj, int flag ) );
ch_ret	check_room_for_traps args( ( CHAR_DATA *ch, int flag ) );
bool	is_trapped	args( ( OBJ_DATA *obj ) );
OD *	get_trap	args( ( OBJ_DATA *obj ) );
ch_ret	spring_trap     args( ( CHAR_DATA *ch, OBJ_DATA *obj ) );
void	name_stamp_stats args( ( CHAR_DATA *ch ) );
void	fix_char	args( ( CHAR_DATA *ch ) );
void	showaffect	args( ( CHAR_DATA *ch, AFFECT_DATA *paf ) );
void	set_cur_obj	args( ( OBJ_DATA *obj ) );
bool	obj_extracted	args( ( OBJ_DATA *obj ) );
void	queue_extracted_obj	args( ( OBJ_DATA *obj ) );
void	clean_obj_queue	args( ( void ) );
void	set_cur_char	args( ( CHAR_DATA *ch ) );
bool	char_died	args( ( CHAR_DATA *ch ) );
void	queue_extracted_char	args( ( CHAR_DATA *ch, bool extract ) );
void	clean_char_queue	args( ( void ) );
void	add_timer	args( ( CHAR_DATA *ch, sh_int type, sh_int count, DO_FUN *fun, int value ) );
TIMER * get_timerptr	args( ( CHAR_DATA *ch, sh_int type ) );
sh_int	get_timer	args( ( CHAR_DATA *ch, sh_int type ) );
void	extract_timer	args( ( CHAR_DATA *ch, TIMER *timer ) );
void	remove_timer	args( ( CHAR_DATA *ch, sh_int type ) );
bool	in_soft_range	args( ( CHAR_DATA *ch, AREA_DATA *tarea ) );
bool	in_hard_range	args( ( CHAR_DATA *ch, AREA_DATA *tarea ) );
bool	chance  	args( ( CHAR_DATA *ch, sh_int percent ) );
bool 	chance_attrib	args( ( CHAR_DATA *ch, sh_int percent, sh_int attrib ) );
OD *	clone_object	args( ( OBJ_DATA *obj ) );
void	split_obj	args( ( OBJ_DATA *obj, int num ) );
void	separate_obj	args( ( OBJ_DATA *obj ) );
bool	empty_obj	args( ( OBJ_DATA *obj, OBJ_DATA *destobj,
				ROOM_INDEX_DATA *destroom ) );
OD *	find_obj	args( ( CHAR_DATA *ch, char *argument,
				bool carryonly ) );
bool	ms_find_obj	args( ( CHAR_DATA *ch ) );
void	worsen_mental_state args( ( CHAR_DATA *ch, int mod ) );
void	better_mental_state args( ( CHAR_DATA *ch, int mod ) );
void	boost_economy	args( ( AREA_DATA *tarea, int gold ) );
void	lower_economy	args( ( AREA_DATA *tarea, int gold ) );
void	economize_mobgold args( ( CHAR_DATA *mob ) );
bool	economy_has	args( ( AREA_DATA *tarea, int gold ) );
void	add_kill	args( ( CHAR_DATA *ch, CHAR_DATA *mob ) );
int	times_killed	args( ( CHAR_DATA *ch, CHAR_DATA *mob ) );


/* interp.c */
bool	check_pos	args( ( CHAR_DATA *ch, sh_int position ) );
void	interpret	args( ( CHAR_DATA *ch, char *argument ) );
bool	is_number	args( ( char *arg ) );
int	number_argument	args( ( char *argument, char *arg ) );
char *	one_argument	args( ( char *argument, char *arg_first ) );
char *	one_argument2	args( ( char *argument, char *arg_first ) );
ST *	find_social	args( ( char *command ) );
CMDTYPE *find_command	args( ( char *command ) );
void	hash_commands	args( ( ) );
void	start_timer	args( ( struct timeval *stime ) );
time_t	end_timer	args( ( struct timeval *stime ) );
void	send_timer	args( ( struct timerset *vtime, CHAR_DATA *ch ) );
void	update_userec	args( ( struct timeval *time_used, struct timerset *userec ) );

/* magic.c */
bool	process_spell_components args( ( CHAR_DATA *ch, int sn ) );
int	ch_slookup	args( ( CHAR_DATA *ch, const char *name ) );
int	find_spell	args( ( CHAR_DATA *ch, const char *name, bool know ) );
int	find_skill	args( ( CHAR_DATA *ch, const char *name, bool know ) );
int	find_weapon	args( ( CHAR_DATA *ch, const char *name, bool know ) );
int	find_tongue	args( ( CHAR_DATA *ch, const char *name, bool know ) );
int	skill_lookup	args( ( const char *name ) );
int	herb_lookup	args( ( const char *name ) );
int	personal_lookup	args( ( CHAR_DATA *ch, const char *name ) );
int	slot_lookup	args( ( int slot ) );
int	bsearch_skill	args( ( const char *name, int first, int top ) );
int	bsearch_skill_exact args( ( const char *name, int first, int top ) );
bool	saves_poison_death	args( ( int level, CHAR_DATA *victim ) );
bool	saves_wand		args( ( int level, CHAR_DATA *victim ) );
bool	saves_para_petri	args( ( int level, CHAR_DATA *victim ) );
bool	saves_breath		args( ( int level, CHAR_DATA *victim ) );
bool	saves_spell_staff	args( ( int level, CHAR_DATA *victim ) );
ch_ret	obj_cast_spell	args( ( int sn, int level, CHAR_DATA *ch, CHAR_DATA *victim, OBJ_DATA *obj ) );
int	dice_parse	args( (CHAR_DATA *ch, int level, char *exp) );
SK *	get_skilltype	args( ( int sn ) );

/* request.c */
void	init_request_pipe	args( ( void ) );
void	check_requests		args( ( void ) );

/* save.c */
/* object saving defines for fread/write_obj. -- Altrag */
#define OS_CARRY	0
#define OS_CORPSE	1
void	save_char_obj	args( ( CHAR_DATA *ch ) );
void	save_clone	args( ( CHAR_DATA *ch ) );
void	save_profile	args( ( CHAR_DATA *ch ) );
bool	load_char_obj	args( ( DESCRIPTOR_DATA *d, char *name, bool preload ) );
void	set_alarm	args( ( long seconds ) );
void	requip_char	args( ( CHAR_DATA *ch ) );
void    fwrite_obj      args( ( CHAR_DATA *ch,  OBJ_DATA  *obj, FILE *fp, 
				int iNest, sh_int os_type ) );
void	fread_obj	args( ( CHAR_DATA *ch,  FILE *fp, sh_int os_type ) );
void	de_equip_char	args( ( CHAR_DATA *ch ) );
void	re_equip_char	args( ( CHAR_DATA *ch ) );
void	save_home	args( ( CHAR_DATA *ch ) );

/* shops.c */

/* special.c */
SF *	spec_lookup	args( ( const char *name ) );
char *	lookup_spec	args( ( SPEC_FUN *special ) );

/* tables.c */
int	get_skill	args( ( char *skilltype ) );
char *	spell_name	args( ( SPELL_FUN *spell ) );
char *	skill_name	args( ( DO_FUN *skill ) );
void	load_skill_table args( ( void ) );
void	save_skill_table args( (int delnum) );
void	sort_skill_table args( ( void ) );
void	load_socials	args( ( void ) );
void	save_socials	args( ( void ) );
void	load_commands	args( ( void ) );
void	save_commands	args( ( void ) );
SPELL_FUN *spell_function args( ( char *name ) );
DO_FUN *skill_function  args( ( char *name ) );
void	load_herb_table	args( ( void ) );
void	save_herb_table	args( ( void ) );

/* track.c */
void	found_prey	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void	hunt_victim	args( ( CHAR_DATA *ch) );

/* update.c */
void	check_force	args( ( CHAR_DATA *ch ) );
void	advance_level	args( ( CHAR_DATA *ch , int ability ) );
void	gain_exp	args( ( CHAR_DATA *ch, int gain ) );
void	gain_exp2	args( ( CHAR_DATA *ch, int gain , int ability) );
void	gain_condition	args( ( CHAR_DATA *ch, int iCond, int value ) );
void	update_handler	args( ( void ) );
void	reboot_check	args( ( time_t reset ) );
#if 0
void    reboot_check    args( ( char *arg ) );
#endif
void    auction_update  args( ( void ) );
void	remove_portal	args( ( OBJ_DATA *portal ) );
int max_level( CHAR_DATA *ch, int ability);

/* hashstr.c */
char *	str_alloc	args( ( char *str ) );
char *	quick_link	args( ( char *str ) );
int	str_free	args( ( char *str ) );
void	show_hash	args( ( int count ) );
char *	hash_stats	args( ( void ) );
char *	check_hash	args( ( char *str ) );
void	hash_dump	args( ( int hash ) );
void	show_high_hash	args( ( int top ) );

/* ships.c */
int  	max_missile	args( ( SHIP_DATA *ship, int iWeapon ) );
void load_ship_prototypes();
int load_prototype( char *prototypefile, int prototype);
bool load_prototype_rooms( FILE *fp, int prototype);
bool fread_prototype_room( FILE *fp, int prototype);
bool load_prototype_header(FILE *fp,int prototype);
void write_all_prototypes();
void write_prototype_list();
void save_prototype( int prototype );
void write_all_prototypes();
void write_prototype_list();
void save_prototype( int prototype );
int	   find_vnum_block		args( ( int num_needed ) );
int        make_prototype_rooms         args( (int ship_type, int vnum,AREA_DATA *tarea,char *Sname) );
int        get_sp_rflag                 args( ( char *flag ) );
SHIP_DATA *make_prototype_ship          args( (int ship_type,int vnum,CHAR_DATA *ch,char *ship_name) );
void	   write_ship_list	        args( ( void ) );
void       resetship                    args( ( SHIP_DATA *ship ) );
char      *parse_prog_string            args( (char *inp,int ship_type,int vnum) );
void       make_rprogs                  args( (int ship_type, int vnum) );
void	   load_ship_prototypes	        args( ( void ) );

/* functions.c */
char    *strrep args( (char *src, char *sch,char *rep) );
char    *strlinwrp args( (char *src, int length) );
char 	*line(int num,char inp);
char	*remand(char *arg);
char	*rembg(char *arg);
char	*htmlcolor(char *arg);
char *format_str(char *src, int len);
int strlen_color (char *argument);
char *chrmax( char *src, int length );


/* newscore.c */
char *  get_race 	args( (CHAR_DATA *ch) );

#undef	SK
#undef	CO
#undef	ST
#undef	CD
#undef	MID
#undef	OD
#undef	OID
#undef	RID
#undef	SF
#undef	BD 
#undef	CL
#undef	EDD
#undef	RD
#undef	ED

/* ships.c */

void load_market_list  args((void));
void save_market_list  args((void));
void add_market_ship  args((SHIP_DATA*ship));
void remove_market_ship  args((BMARKET_DATA*marketship));
void make_random_marketlist  args((void));

/*
 *
 *  New Build Interface Stuff Follows
 *
 */


/*
 *  Data for a menu page
 */
struct	menu_data
{
    char		*sectionNum;
    char		*charChoice;
    int			x;
    int			y;
    char		*outFormat;
    void		*data;
    int			ptrType;
    int			cmdArgs;
    char		*cmdString;
};


DECLARE_DO_FUN( do_redraw_page  );
DECLARE_DO_FUN( do_refresh_page );
DECLARE_DO_FUN( do_pagelen	);
DECLARE_DO_FUN( do_omenu  	);
DECLARE_DO_FUN( do_rmenu  	);
DECLARE_DO_FUN( do_mmenu  	);
DECLARE_DO_FUN( do_clear  	);

extern		MENU_DATA		room_page_a_data[];
extern		MENU_DATA		room_page_b_data[];
extern		MENU_DATA		room_page_c_data[];
extern		MENU_DATA		room_help_page_data[];

extern		MENU_DATA		mob_page_a_data[];
extern		MENU_DATA		mob_page_b_data[];
extern		MENU_DATA		mob_page_c_data[];
extern		MENU_DATA		mob_page_d_data[];
extern		MENU_DATA		mob_page_e_data[];
extern		MENU_DATA		mob_page_f_data[];
extern		MENU_DATA		mob_help_page_data[];

extern		MENU_DATA		obj_page_a_data[];
extern		MENU_DATA		obj_page_b_data[];
extern		MENU_DATA		obj_page_c_data[];
extern		MENU_DATA		obj_page_d_data[];
extern		MENU_DATA		obj_page_e_data[];
extern		MENU_DATA		obj_help_page_data[];

extern		MENU_DATA		control_page_a_data[];
extern		MENU_DATA		control_help_page_data[];

extern	const   char    room_page_a[];
extern	const   char    room_page_b[];
extern	const   char    room_page_c[];
extern	const   char    room_help_page[];

extern	const   char    obj_page_a[];
extern	const   char    obj_page_b[];
extern	const   char    obj_page_c[];
extern	const   char    obj_page_d[];
extern	const   char    obj_page_e[];
extern	const   char    obj_help_page[];

extern	const   char    mob_page_a[];
extern	const   char    mob_page_b[];
extern	const   char    mob_page_c[];
extern	const   char    mob_page_d[];
extern	const   char    mob_page_e[];
extern	const   char    mob_page_f[];
extern	const   char    mob_help_page[];
extern	const   char *  npc_sex[3];
extern	const   char *  ris_strings[];

extern	const   char    control_page_a[];
extern	const   char    control_help_page[];

#define SH_INT 1
#define INT 2
#define CHAR 3
#define STRING 4
#define SPECIAL 5


#define NO_PAGE    0
#define MOB_PAGE_A 1
#define MOB_PAGE_B 2
#define MOB_PAGE_C 3
#define MOB_PAGE_D 4
#define MOB_PAGE_E 5
#define MOB_PAGE_F 17
#define MOB_HELP_PAGE 14
#define ROOM_PAGE_A 6
#define ROOM_PAGE_B 7
#define ROOM_PAGE_C 8
#define ROOM_HELP_PAGE 15
#define OBJ_PAGE_A 9
#define OBJ_PAGE_B 10
#define OBJ_PAGE_C 11
#define OBJ_PAGE_D 12
#define OBJ_PAGE_E 13
#define OBJ_HELP_PAGE 16
#define CONTROL_PAGE_A 18
#define CONTROL_HELP_PAGE 19

#define NO_TYPE   0
#define MOB_TYPE  1
#define OBJ_TYPE  2
#define ROOM_TYPE 3
#define CONTROL_TYPE 4

#define SUB_NORTH DIR_NORTH
#define SUB_EAST  DIR_EAST
#define SUB_SOUTH DIR_SOUTH
#define SUB_WEST  DIR_WEST
#define SUB_UP    DIR_UP
#define SUB_DOWN  DIR_DOWN
#define SUB_NE    DIR_NORTHEAST
#define SUB_NW    DIR_NORTHWEST
#define SUB_SE    DIR_SOUTHEAST
#define SUB_SW    DIR_SOUTHWEST

/*
 * defines for use with this get_affect function
 */

#define RIS_000		BV00
#define RIS_R00		BV01
#define RIS_0I0		BV02
#define RIS_RI0		BV03
#define RIS_00S		BV04
#define RIS_R0S		BV05
#define RIS_0IS		BV06
#define RIS_RIS		BV07

#define GA_AFFECTED	BV09
#define GA_RESISTANT	BV10
#define GA_IMMUNE	BV11
#define GA_SUSCEPTIBLE	BV12
#define GA_RIS          BV30



/*
 *   Map Structures
 */

DECLARE_DO_FUN( do_mapout 	);
DECLARE_DO_FUN( do_lookmap	);

struct  map_data	/* contains per-room data */
{
  int vnum;		/* which map this room belongs to */
  int x;		/* horizontal coordinate */
  int y;		/* vertical coordinate */
  char entry;		/* code that shows up on map */ 
};


struct  map_index_data
{
  MAP_INDEX_DATA  *next;
  int 		  vnum;  		  /* vnum of the map */
  int             map_of_vnums[49][81];   /* room vnums aranged as a map */
};


MAP_INDEX_DATA *get_map_index(int vnum);
void            init_maps();


/*
 * mudprograms stuff
 */
extern	CHAR_DATA *supermob;

void oprog_speech_trigger( char *txt, CHAR_DATA *ch );
void oprog_random_trigger( OBJ_DATA *obj );
void oprog_wear_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
bool oprog_use_trigger( CHAR_DATA *ch, OBJ_DATA *obj, 
                        CHAR_DATA *vict, OBJ_DATA *targ, void *vo );
void oprog_remove_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_sac_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_damage_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_repair_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_drop_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
//void oprog_zap_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
char *oprog_type_to_name( int type );

/*
 * MUD_PROGS START HERE
 * (object stuff)
 */
int rprog_custom_trigger(char *command, char *argument, CHAR_DATA *ch);
int mprog_custom_trigger(char *command, char *argument, CHAR_DATA *ch);
int oprog_custom_trigger(char *command, char *argument, CHAR_DATA *ch);
void oprog_greet_trigger( CHAR_DATA *ch );
void oprog_speech_trigger( char *txt, CHAR_DATA *ch );
void oprog_random_trigger( OBJ_DATA *obj );
void oprog_random_trigger( OBJ_DATA *obj );
void oprog_remove_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_sac_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_get_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_damage_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_repair_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_drop_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_examine_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
//void oprog_zap_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_pull_trigger( CHAR_DATA *ch, OBJ_DATA *obj );
void oprog_push_trigger( CHAR_DATA *ch, OBJ_DATA *obj );


/* mud prog defines */

#define ERROR_PROG        -1
#define IN_FILE_PROG       0
#define ACT_PROG           BV00
#define SPEECH_PROG        BV01
#define RAND_PROG          BV02
#define FIGHT_PROG         BV03
#define RFIGHT_PROG        BV03
#define DEATH_PROG         BV04
#define RDEATH_PROG        BV04
#define HITPRCNT_PROG      BV05
#define ENTRY_PROG         BV06
#define ENTER_PROG         BV06
#define GREET_PROG         BV07
#define RGREET_PROG	   BV07
#define OGREET_PROG        BV07
#define ALL_GREET_PROG	   BV08
#define GIVE_PROG	   BV09
#define BRIBE_PROG	   BV10
#define HOUR_PROG	   BV11
#define TIME_PROG	   BV12
#define WEAR_PROG          BV13  
#define REMOVE_PROG        BV14  
#define SAC_PROG           BV15  
#define LOOK_PROG          BV16  
#define EXA_PROG           BV17  
#define CUSTOM_PROG        BV18
#define GET_PROG 	   BV19  
#define DROP_PROG	   BV20  
#define DAMAGE_PROG	   BV21  
#define REPAIR_PROG	   BV22  
#define RANDIW_PROG	   BV23  
#define SPEECHIW_PROG	   BV24  
#define PULL_PROG	   BV25  
#define PUSH_PROG	   BV26  
#define SLEEP_PROG         BV27  
#define REST_PROG          BV28  
#define LEAVE_PROG         BV29
#define SCRIPT_PROG	   BV30
#define USE_PROG           BV31

void rprog_leave_trigger( CHAR_DATA *ch );
void rprog_enter_trigger( CHAR_DATA *ch );
void rprog_sleep_trigger( CHAR_DATA *ch );
void rprog_rest_trigger( CHAR_DATA *ch );
void rprog_rfight_trigger( CHAR_DATA *ch );
void rprog_death_trigger( CHAR_DATA *killer, CHAR_DATA *ch );
void rprog_speech_trigger( char *txt, CHAR_DATA *ch );
void rprog_random_trigger( CHAR_DATA *ch );
void rprog_time_trigger( CHAR_DATA *ch );
void rprog_hour_trigger( CHAR_DATA *ch );
char *rprog_type_to_name( int type );

#define OPROG_ACT_TRIGGER
#ifdef OPROG_ACT_TRIGGER
void oprog_act_trigger( char *buf, OBJ_DATA *mobj, CHAR_DATA *ch,
			OBJ_DATA *obj, void *vo );
#endif
#define RPROG_ACT_TRIGGER
#ifdef RPROG_ACT_TRIGGER
void rprog_act_trigger( char *buf, ROOM_INDEX_DATA *room, CHAR_DATA *ch,
			OBJ_DATA *obj, void *vo );
#endif


#define send_to_char  send_to_char_color
#define send_to_pager send_to_pager_color

#define GET_BETTED_ON(ch)    ((ch)->betted_on)
#define GET_BET_AMT(ch) ((ch)->bet_amt)
#define GET_PAZAAK_BETTED_ON(ch) ((ch)->pazaak_betted_on)
#define GET_PAZAAK_BET_AMT(ch)   ((ch)->pazaak_bet_amt)
#define IN_PAZAAK(ch)		(IS_SET((ch)->in_room->room_flags2, ROOM_PAZAAK) )
#define IN_ARENA(ch)            (IS_SET((ch)->in_room->room_flags2, ROOM_ARENA))

