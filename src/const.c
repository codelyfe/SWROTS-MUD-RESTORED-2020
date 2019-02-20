#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include "mud.h"

/* undef these at EOF */
#define AM 95
#define AC 95
#define AT 85
#define AW 85
#define AV 95
#define AD 95
#define AR 90
#define AA 95

/*
 * Race table.
 */
const	struct	race_type	race_table	[MAX_RACE]	=
{
    /*  race name    DEF_AFF    str dex con int wis cha  language */
    {	"Anomid",      0,	-2,  0,  0,  2,  0,  2,  LANG_BASIC },
    { 	"Arkanian",    0,        0, -2,  2,  2,  0, -2,  LANG_ARKANIAN },
    { 	"Bartokk",     0,   	 2,  0,  2, -6,  0, -4,  LANG_BASIC },
    {	"Cerean",      0,	 0, -2,  0,  2,  2,  0,  LANG_CEREAN },
    {	"Chagrian", AFF_AQUA_BREATH,  2, -2,  0,  0,  0,  0,  LANG_CHAGRI },
    {	"Dashade", AFF_FORCE_RESIST, 0,  2,  0,  0, -2, -2,  LANG_DASHADI },
    {	"Defel",       0,       -2,  0,  0,  2,  0,  0,  LANG_DEFEL },
    {	"Drall",       0,	-2, -2,  0,  2,  2,  2,  LANG_DRALLISH },
    {	"Droid", AFF_AQUA_BREATH+AFF_GAS_BREATH, 0, 0, 0, 0, 0, 0, LANG_BINARY },
    {	"Falleen",     0,	 0,  0,  0,  0,  0,  2,  LANG_FALLEEN },
    {	"Ho'Din",      0,	 2, -2,  0,  0,  0,  0,  LANG_HODIN },
    {	"Human",       0,        0,  0,  0,  0,  0,  0,  LANG_BASIC },
    {	"Hutt",AFF_FORCE_RESIST, 2, -4,  2,  2,  2,  2,  LANG_HUTTESE },
    {	"Iktotchi",    0,        0, -2,  2,  0,  0, -2,  LANG_IKTOTCHESE },
    {	"Jawa", AFF_DARKVISION, -4,  2,  0,  0,  0, -2,  LANG_JAWA },
    {	"Kel Dor", AFF_GAS_BREATH, 0, 2, -2, 0, 2, 0, LANG_KELDOR },
    {	"Klatooinian", 0,	 0,  0,  2, -2,  0,  0,  LANG_HUTTESE },
    {	"Miraluka",    0,	 0, -2,  0,  2,  0,  0,  LANG_MIRALUKESE },
    {	"Mon Calamari", AFF_AQUA_BREATH, 0, 0, -2, 2, 0, 0, LANG_MON_CALAMARIAN },
    {	"Muun",	       0,       -2,  0,  0,  4,  0,  0,  LANG_MUUN },
    {	"Noghri",      0,	 0,  2,  0,  0,  2, -4,  LANG_NOGHRI },
    {	"Quarren", AFF_AQUA_BREATH, 0, 0, 2, 0, -2, -2,  LANG_BASIC },
    {	"Rodian",      0,	 0,  2,  0,  0, -2, -2,  LANG_RODESE },
    {	"Ryn",         0,        0,  0,  0,  0,  0,  0,  LANG_RYN }, 
    {	"S'kytri",     0,        2,  0, -2,  0, -2,  0,  LANG_SKYTRIC },
    {	"Sullustan", AFF_DARKVISION, 0, 2, -2, 0, 0, 0,  LANG_SULLUSTESE },
    {	"Togorian",    0,        4, -2,  2, -2, -2,  0,  LANG_TOGORIAN },
    {	"Togruta",     0,	 0,  2, -2,  0,  2,  0,  LANG_TOGRUTI },
    {	"Trandoshan", AFF_DARKVISION, 2, -2, 0, 0, 0, 0, LANG_DOSH },
    {	"Twi'lek",     0,        0,  0,  0,  0, -2,  2,  LANG_LEKKU },
    {	"Ubese",       0,        0,  2, -2,  0,  0,  0,  LANG_UBESE },
    {	"Umbaran", AFF_DARKVISION, 0, 0, -2, 0, 2, 2, LANG_UMBARESE },
    {	"Verpine",     0,        0,  0,  0,  0,  0,  0,  LANG_VERPINE },
    {	"Weequay",     0,        2,  0,  2, -2, -2, -4,  LANG_SRILUURIAN },
    {	"Wookiee",     0,	 4, -2,  0,  0, -2, -2,  LANG_SHYRIIWOOK },
    {	"Woostoid",    0,       -2,  0,  0,  4,  0,  0,  LANG_BASIC },
    {	"Zeltron",     0,        0,  0, -2,  0, -2,  4,  LANG_BASIC }
};

const   struct  droid_type     droid_table     [MAX_DROID]     =
{
    {   "None",                  0,  0,  0,  0,  0,  0 },
    {   "First",	        -2,  0,  0,  2,  0, -2 },
    {   "Second",	        -4,  2,  0,  2,  0,  0 },
    {   "Third",	        -2,  0,  0,  0, -2,  2 },
    {   "Fourth",	         0,  2,  2, -4,  0,  0 },
    {   "Fifth",	         2,  0,  0,  0, -2, -2 }
};

const	struct	stat_type	stat_table	[MAX_STAT] =
{
    {-5}, {-5}, {-4}, {-4}, {-3}, {-3}, {-2}, {-2}, {-1}, {-1},
    { 0}, { 0}, { 1}, { 1}, { 2}, { 2}, { 3}, { 3}, { 4}, { 4},
    { 5}, { 5}, { 6}, { 6}, { 7}, { 7}, { 8}, { 8}, { 9}, { 9},
    {10}, {10}, {11}, {11}, {12}, {12}, {13}, {13}, {14}, {14},
    {15}
};

char *	const	npc_race	[MAX_NPC_RACE] =
{
 "Anomid", "Arkanian", "Bartokk", "Cerean", "Chagrian", "Deshade", "Defel",
 "Drall", "Droid", "Falleen", "Ho'Din", "Human", "Hutt", "Iktotchi", "Jawa",
 "Kel Dor", "Klatooinian", "Miraluka", "Mon Calamari", "Muun", "Noghri",
 "Quarren", "Rodian", "Ryn", "S'kytri", "Sullustan", "Togorian", "Togruta",
 "Trandoshan", "Twi'lek", "Ubese", "Umbaran", "Verpine", "Weequay", "Wookiee",
 "Woostoid", "Zeltron"
};

char *  const	base_name	[BASE_CLASS] =
{
"Fringer", "Noble", "Scoundrel", "Scout", "Soldier", "Tech Specialist",
"Force Adept"
};

char *	const	stance_name	[MAX_STANCE] =
{
"None",
"Echani", "K'tara", "K'thri", "Stava", "Wrruushi", "Form One", "Form Two",
"Form Three", "Form Four", "Form Five", "Form Six", "Form Seven"
};

char *  const	cargo_name	[10] =
{
"None", "Art", "Bacta", "Semi-precious Gems", "Precious Gems", "Common Ore",
"Rare Ore", "Spice", "Slaves", "Weapons"
};

char *	const	planet_name	[] =
{
"coruscant", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10", "p11",
"p12", "p13", "p14", "p15", "p16", "p17", "p18", "p19", "p20", "p21", 
"p22", "p23", "p24", "p25", "p26", "p27", "p28", "p29", "p30"
};

char *	const	ship_size	[MAX_SIZE] =
{
"Fine", "Diminutive", "Tiny", "Small", "Medium", "Large", "Huge",
"Gargantuan", "Colossal"
};

char *	const	bonus_clan	[]	=
{
"None", "Hitroll", "Damroll", "Armor", "Experience" 
};

char *  const	atmo_name	[MAX_ATMO] =
{
"Normal", "Gaseous", "Heat", "Blizzard", "Thin Air", "Oxgenized",
"Toxic", "Windy"
};

const   struct  card_type     card_table     [12]     =
{
 {12}, {13}, {14}, {15}, {-2}, {-8}, {-11}, {-13}, {-14},
 {-15}, {-17}, {0}
};

char *  const	alchemy_name	[10] =
{
 "Claws", "Horns", "Darkvision", "Defense", "Strength", "Dexterity",
 "Constitution", "Intelligence", "Wisdom", "Charisma"
};

char *  const	crystal_name	[16] =
{
"Blue", "Green", "Purple", "Red", "Yellow", "Opila", "Sigil", "Bondar",
"Phond", "Solari", "Damind", "Jenruax", "Upari", "Eralam", "Rubat", "Sapith"
};

char *	const	ability_name	[MAX_ABILITY] =
{
"Fringer", "Noble", "Scoundrel", "Scout", "Soldier", "Tech Specialist",
"Force Adept", "Jedi Consular", "Jedi Guardian", "Bounty Hunter", "Crime Lord", "Dark Side Devotee", "Dark Side Marauder",
"Elite Trooper", "Jedi Ace", "Jedi Investigator", "Jedi Master", "Starship Ace",
"Chief Engineer", "Infiltrator", "Loyal Protector", "Martial Arts Master",
"Outlaw Slicer", "Dark Force Witch", "Sith Acolyte", "Sith Lord", "Sith Warrior",
"Antarian Ranger", "Black Sun Enforcer", "Black Sun Vigo", "Crime Broker",
"Noble House Lord", "Espionage Droid", "Berserker Droid", "Aerobat", "Mystic Agent"
};

char * 	const	nskill_name	[MAX_NSKILL] =
{
"Appraise", "Astrogate", "Balance", "Climb", "Use Computer", "Armor",
"Blasters", "Computers", "Droid", "Device",
"Lightsaber", "Bowcaster", "Heavy Weapon", "Hyperdrive",
"Medpac", "Simple Weapon", "Slugthrower", "Midship",
"Starfighter", "Ship Weapon", "Vibro",
"Demolitions", "Diplomacy", "Disable Device", "Disguise", "Escape Artist",
"Gamble", "Gather Information", "Hide", "Intimidate", "Listen",
"Move Silently", "Pilot", "Repair", "Ride", "Search",
"Sleight Of Hand", "Speak Language", "Spot", "Survival", "Swim", "Treat Injury",
"Tumble"
};

char *  const	fskill_name	[MAX_FSKILL] =
{
"Alchemy", "Affect Mind", "Battlemind", "Drain Energy", "Enhance Ability",
"Enhance Senses", "Farseeing", "Fear", "Force Defense", "Force Grip",
"Force Lightning", "Force Stealth", "Force Strike", "Heal Another", "Heal Self",
"Illusion", "Move Object", "See Force", "Telepathy"
};

char *const part_name	[MAX_PART] =
{
"head", "right arm", "left arm", "right arm", "left arm", "right leg", 
"left leg", "feet", "wings", "right hand", "left hand", "right hand", 
"left hand", "right eye", "left eye"
};

char *const height_name[4] =
{
"average", "short", "tall", "very tall"
};

char *const feat_name[32] =
{
"alertness", "ambidexterity", "athletic", "blind-fighting", "cautious", "dodge",
"fame", "force-sensitive", "frightful presense", "gearhead", "great fortitude",
"headstrong", "improved disarm", "improved trip", "improved two weapon fighting",
"infamy", "influence", "iron will", "lightning reflexes", "low profile", "nimble",
"quickness", "rugged", "sharp-eyed", "skill emphasis", "spacer", "starship dodge",
"starfighter operations", "midship operations", "capital operations", "steady",
"stealthy"
};

char *const feat2_name[32] =
{
"track", "two weapon fighting", "blaster pistols", "blaster rifles", "heavy weapons",
"primitive", "simple", "vibros", "lightsabers", "bowcasters", "light armor", 
"medium armor", "heavy armor", "powered armor", "martial arts", "defensive martial arts",
"improved martial arts", "advanced martial arts"
};

char *const build_name[6] =
{
 "petite", "thin", "lean", "overweight", "muscular", "obese"
};

char *const droid_name[8]=
{
 "modern", "antique", "small", "large", "tiny", "polished",
 "sleek", "huge"
};

const	struct 	exp_type	clan_exp	[31]	=
{
 {0}, {20000}, {40000}, {80000}, {160000}, {250000}, {340000}, {400000},
 {500000}, {700000}, {950000}, {1150000}, {1300000}, {1500000}, {1750000},
 {1900000}, {2250000}, {2600000}, {3000000}, {4000000}, {5000000}, {6000000},
 {7000000}, {8000000}, {9000000}, {10000000}, {11000000}, {12000000},
 {13000000}, {14000000}, {15500000}
};

const	struct	bonus_type	bonus_req	[16]	=
{
 {0}, {3}, {8}, {15}, {24}, {35}, {48}, {63}, {80}, {99}, {120},
 {143}, {168}, {197}, {228}, {261}
};

const   struct  exp_type       exp_table      [31]      =
{
 { 0 }, {1}, {3001}, {6001}, {12001}, {20001}, {30001}, {42001}, {56001},
 {72001}, {90001}, {110001}, {140001}, {172001}, {206001}, {242001}, {280001},
 {320001}, {366001}, {412001}, {460001}, {510001}, {562001}, {616001}, 
 {674001}, {734001}, {796001}, {870001}, {946001}, {1024001}, {1104001}
};

/*
 * Attribute bonus tables.
 */
const	struct	str_app_type	str_app		[26]		=
{
    { -5, -4,   0,  0 },  /* 0  */
    { -5, -4,   3,  1 },  /* 1  */
    { -3, -2,   3,  2 },
    { -3, -1,  10,  3 },  /* 3  */
    { -2, -1,  25,  4 },
    { -2, -1,  55,  5 },  /* 5  */
    { -1,  0,  80,  6 },
    { -1,  0,  90,  8 },
    {  0,  0, 100, 10 },
    {  0,  0, 100, 12 },
    {  0,  0, 115, 14 }, /* 10  */
    {  0,  0, 115, 15 },
    {  0,  0, 140, 16 },
    {  0,  0, 140, 17 }, /* 13  */
    {  0,  1, 170, 18 },
    {  1,  1, 170, 19 }, /* 15  */
    {  1,  2, 195, 20 },
    {  2,  3, 220, 22 },
    {  2,  4, 250, 25 }, /* 18  */
    {  3,  5, 400, 30 },
    {  3,  6, 500, 35 }, /* 20  */
    {  4,  7, 600, 40 },
    {  5,  7, 700, 45 },
    {  6,  8, 800, 50 },
    {  8, 10, 900, 55 },
    { 10, 12, 999, 60 }  /* 25   */
};



const	struct	int_app_type	int_app		[26]		=
{
    {  3 },	/*  0 */
    {  5 },	/*  1 */
    {  7 },
    {  8 },	/*  3 */
    {  9 },
    { 10 },	/*  5 */
    { 11 },
    { 12 },
    { 13 },
    { 15 },
    { 17 },	/* 10 */
    { 19 },
    { 22 },
    { 25 },
    { 28 },
    { 31 },	/* 15 */
    { 34 },
    { 37 },
    { 40 },	/* 18 */
    { 44 },
    { 49 },	/* 20 */
    { 55 },
    { 60 },
    { 70 },
    { 85 },
    { 99 }	/* 25 */
};



const	struct	wis_app_type	wis_app		[26]		=
{
    { 0 },	/*  0 */
    { 0 },	/*  1 */
    { 0 },
    { 0 },	/*  3 */
    { 0 },
    { 1 },	/*  5 */
    { 1 },
    { 1 },
    { 1 },
    { 2 },
    { 2 },	/* 10 */
    { 2 },
    { 2 },
    { 2 },
    { 2 },
    { 3 },	/* 15 */
    { 3 },
    { 4 },
    { 5 },	/* 18 */
    { 5 },
    { 5 },	/* 20 */
    { 6 },
    { 6 },
    { 6 },
    { 6 },
    { 7 }	/* 25 */
};



const	struct	dex_app_type	dex_app		[30]		=
{
    {   60 },   /* 0 */
    {   50 },   /* 1 */
    {   50 },
    {   40 },
    {   30 },
    {   20 },   /* 5 */
    {   10 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    { - 10 },   /* 15 */
    { - 15 },
    { - 20 },
    { - 30 },
    { - 40 },
    { - 50 },   /* 20 */
    { - 60 },
    { - 75 },
    { - 90 },
    { -105 },
    { -120 },   /* 25 */
    { -135 },
    { -150 },
    { -165 },
    { -180 }    /* 29 */
};



const	struct	con_app_type	con_app		[26]		=
{
    { -4, 20 },   /*  0 */
    { -3, 25 },   /*  1 */
    { -2, 30 },
    { -2, 35 },	  /*  3 */
    { -1, 40 },
    { -1, 45 },   /*  5 */
    { -1, 50 },
    {  0, 55 },
    {  0, 60 },
    {  0, 65 },
    {  0, 70 },   /* 10 */
    {  0, 75 },
    {  0, 80 },
    {  0, 85 },
    {  0, 88 },
    {  1, 90 },   /* 15 */
    {  2, 95 },
    {  2, 97 },
    {  3, 99 },   /* 18 */
    {  3, 99 },
    {  4, 99 },   /* 20 */
    {  4, 99 },
    {  5, 99 },
    {  6, 99 },
    {  7, 99 },
    {  8, 99 }    /* 25 */
};


const	struct	cha_app_type	cha_app		[26]		=
{
    { - 60 },   /* 0 */
    { - 50 },   /* 1 */
    { - 50 },
    { - 40 },
    { - 30 },
    { - 20 },   /* 5 */
    { - 10 },
    { -  5 },
    { -  1 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    1 },
    {    5 },   /* 15 */
    {   10 },
    {   20 },
    {   30 },
    {   40 },
    {   50 },   /* 20 */
    {   60 },
    {   70 },
    {   80 },
    {   90 },
    {   99 }    /* 25 */
};

/* Have to fix this up - not exactly sure how it works (Scryn) */
const	struct	lck_app_type	lck_app		[26]		=
{
    {   60 },   /* 0 */
    {   50 },   /* 1 */
    {   50 },
    {   40 },
    {   30 },
    {   20 },   /* 5 */
    {   10 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    { - 10 },   /* 15 */
    { - 15 },
    { - 20 },
    { - 30 },
    { - 40 },
    { - 50 },   /* 20 */
    { - 60 },
    { - 75 },
    { - 90 },
    { -105 },
    { -120 }    /* 25 */
};

const	struct	frc_app_type	frc_app		[26]		=
{
    {    0 },   /* 0 */
    {    0 },   /* 1 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 5 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 15 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 20 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    {    0 }    /* 25 */
};



/*
 * Liquid properties.
 * Used in #OBJECT section of area file.
 */
const	struct	liq_type	liq_table	[LIQ_MAX]	=
{
    { "water",			"clear",	{  0, 1, 10 }	},  /*  0 */
    { "beer",			"amber",	{  3, 2,  5 }	},
    { "wine",			"rose",		{  5, 2,  5 }	},
    { "ale",			"brown",	{  2, 2,  5 }	},
    { "dark ale",		"dark",		{  1, 2,  5 }	},

    { "whiskey",		"golden",	{  6, 1,  4 }	},  /*  5 */
    { "lemonade",		"pink",		{  0, 1,  8 }	},
    { "firebreather",		"boiling",	{ 10, 0,  0 }	},
    { "local specialty",	"everclear",	{  3, 3,  3 }	},
    { "slime mold juice",	"green",	{  0, 4, -8 }	},

    { "milk",			"white",	{  0, 3,  6 }	},  /* 10 */
    { "tea",			"tan",		{  0, 1,  6 }	},
    { "coffee",			"black",	{  0, 1,  6 }	},
    { "blood",			"red",		{  0, 2, -1 }	},
    { "salt water",		"clear",	{  0, 1, -2 }	},

    { "cola",			"cherry",	{  0, 1,  5 }	},  /* 15 */
    { "mead",			"honey color",	{  4, 2,  5 }	},  /* 16 */
    { "grog",			"thick brown",	{  3, 2,  5 }	},  /* 17 */
    { "milkshake",              "creamy",       {  0, 8,  5 }   }   /* 18 */
};

char *	const	attack_table	[12] =
{
    "hit",
    "slice",  "slash", "blast", "blast", "blast", "blast", "stab",
    "pierce", "slice", "slash", "shoot"
};



/*
 * The skill and spell table.
 * Slot numbers must never be changed as they appear in #OBJECTS sections.
 */
#define SLOT(n)	n
#define LI LEVEL_IMMORTAL

#undef AM 
#undef AC 
#undef AT 
#undef AW 
#undef AV 
#undef AD 
#undef AR
#undef AA

#undef LI
