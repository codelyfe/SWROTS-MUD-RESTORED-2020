# Star Wars: Return of the Sith

Text MUD based on SMAUG and the SWFotE (Star Wars: Fall of the Empire) codebase.
Restored 2020 by Randal. Updated November 16, 2026.

This codebase is a RotS distribution of SWFotE. The original project lived at
http://swfote.sourceforge.net. SMAUG 1.0 was written in 1994-1997 by Derek
Snider and the SMAUG team. The force skill system was written in 2001 by
Richard Berrill (Bambua), with later changes by Tawnos. In-game help
(`help`, `wizhelp`, `hlist`, `changes`) is more detailed than this file.

A premade level 36 administrator is named `User`. The password is `password`.
Change the name and password before anyone else can connect.

## Build

From `src`, with gcc:

```
make swr
```

The Makefile passes `-fcommon`. This code defines the same globals in more
than one file, which current gcc rejects unless that flag is set.

Clean objects and rebuild:

```
make clean
make swr
```

`startup` is a csh script. On Ubuntu install it with `sudo apt-get install csh`.
From `src`:

```
./startup
```

Or, so the process survives a logout:

```
nohup ./startup 1111 &
```

## Port

The port is 1111, set in `src/startup`. The game also opens `port+1`,
`port+10`, and `port+20`.

## Layout

- `area` — world files. Boot list is `area/area.lst`.
- `planets` — planet files. Boot list is `planets/planet.lst`.
- `space` — star systems and ships. Boot list is `space/space.lst`.
- `ships` — ship prototypes.
- `system` — skills, commands, socials, sysdata.
- `force` — force skill list and help.
- `clans` — clan files.
- `player` — player files. Idle purge is 30 days for players and 5 days for newbies (`Newbie_purge` and `Regular_purge` in `system/sysdata.dat`).
- `doc` — original SMAUG notes. Online help is more current.
- `src` — C source. Space combat is in `space.c`, `ships.c`, and `11.c`. Force code is in `force.c`, `finfo.c`, `fskills.c`, and `new_fskills.c`.

## Planets

Worlds load in the star system they belong to in the films. Imperial worlds
are held by the clan `The Sith Empire`, because this build has no separate
Galactic Empire clan. Alliance worlds use `The Republic`. Hutt and independent
worlds are Neutral.

| World | System |
|---|---|
| Coruscant, Corellia, Kashyyyk, Endor, Bakura, Byss, Bilbringi, Honoghr | their own systems |
| Tatooine | Tatoo (Tatoo I and Tatoo II) |
| Nal Hutta, Nar Shaddaa | Y'Toub |
| Mon Calamari | Calamari |
| Yavin IV | Yavin |
| Ord Mantell | Bright Jewel |
| Bespin | Bespin |
| Korriban | Horuset |
| Ossus | Adegan |
| XN1224-a, HP9015-l | AB90152 asteroid belt |

`ossus.are` and `guild.are` are not on the boot list. Their room numbers
collide with Tatooine and the Sith academy, and loading them would replace
those rooms. Ossus is in the Adegan system but has no landing area until
that file is renumbered. Thorne is not a film world, so it has its own
system. Alassa is not a Star Wars planet and is not booted.

## Force

Force does not use the old "feel" skill. A player's force block looks like:

```
Force           ## 0 #### ####
ForceControl    ##
ForceSense      ##
ForceAlter      ##
ForceChance     0 or 1
ForceId         0 or 1
ForceAlign      -100 to 100
ForceConverted  0 or 1
ForceType       0, 1, or 2
ForceLvlStatus  0, 1, 2, or 3
ForceSkill      ## ###
```

`ForceType` is 1 for Jedi and 2 for Sith. `ForceLvlStatus` is 1 apprentice,
2 knight or lord, 3 master. Skill numbers follow `force/forceskills.lst`.
Learned percent is 0 through 100. Opposite alignment (Jedi at -100, Sith at
100) causes pain and skill loss.

## Ships

Primaries and secondaries are `primaryType`, `secondaryType`, and their
counts, not a single laser stat. Hit checks use speed, maneuver, and ship
size. Barrel roll evades beams. Juke evades warheads.

A black-market yard is a room with the `blackmarket` flag. The list is
rebuilt on boot from clan ships. Simulators need `setship <ship> flags
simulator` and `setship <ship> simvnum <room>`. Without the return room,
destroying the simulator can crash the game.

If `shipvnum.are` is corrupt, replace it with `shipvnum.are.CLEAN` and
remove bought ships from the space directory.

## Older fixes

Players can save without being a graduate. Search `CODELYFE` in
`src/act_comm.c` and `src/save.c`. The starting area was also made easier.
A repeated-assignment bug in the old sources is described at
https://stackoverflow.com/questions/54794046/solved-error-lvalue-required-as-left-operand-of-assignment-swrots

Hard-ban, for a client that reconnects through a normal ban, is in `src/comm.c`.

## November 16, 2026

- The game links on current gcc (`-fcommon`) and boots to "SWRotS ready on port 1111".
- Boot no longer hangs on `corpses/ERASE_ME.txt`. A file with no newline used to spin forever inside `bug()`.
- Skill lookup includes the first skill. Missing combat skills, spells, and languages were added to `system/skills.dat`. `spell_smaug` and `do_backstab` load again.
- Resets that pointed at missing mobiles or objects were removed. Exits into missing rooms were removed, including room 669 down and room 9034 northwest.
- Ship and prototype loaders accept `Torpedos`, `primaryType`, `primaryCount`, `Simulator`, and the other weapon fields those files already contained.
- Every planet file on `planet.lst` loads. Coruscant, Yavin IV, Nar Shaddaa, Bespin, Byss, Honoghr, and Bilbringi load their ground areas. Systems were renamed to the film names: Tatoo, Bakura, Yavin, Bright Jewel, Horuset, and Adegan.
- Film ships added to `ships/prototype.lst`: TIE Interceptor, TIE Advanced, B-wing, Firespray-31, GR-75, Nebulon-B, and MC80. Lambda was already present as the T-4a.
- `look` can draw a small room map. `map` shows it once. `automap` turns it on or off. In-game help: `help map`.
- `build.bat`, `start.bat`, and `stop.bat` in the repo root build, start, and stop the server through WSL. The game listens on port 1111. The log is `log/server.log`.
- All forty new worlds now have longer rooms, a deeper wing past the landing site, and people on the ground. Naboo, Kamino, Hoth, and Dagobah were done first. The rest, from Geonosis and Mustafar through Fondor, Florrum, and Kalee, follow the same pattern: a local, a worker, and someone who will sell you a thing from that world.
- Uncharted space is 8,000 seeded systems. From a launched ship, `survey` jumps to a new one. `explore` lands you on a small surface with wildlife and records the world. `guide` lists the worlds you have walked. `warp <planet>` returns you only to a world already in that guide. Charts are saved in `space/charts`. Each character's guide is `space/guides/<name>.guide`. In-game help: `help survey`.
- Five prestige classes were added, each with a max level of 10: Medic, Mandalorian, Inquisitor, Royal Guard, and Gunner. `level` lists them. `help medic`, `help mandalorian`, `help inquisitor`, `help royal guard`, and `help gunner` list the requirements.
- Trainable skills added to `skills`: Command, Bargain, Gunnery, and Beast Handling. Gunner levels also raise Gunnery. Joke commands anyone can use: `weed`, `cig`, `coffee`, `fart`, and `hiccup`. `smoke` still needs a lit pipe.
- Infamy tracks player theft and player killing. At 15 an equal bounty hunter travels by ship, then on foot, and warns you as it gets close. Killing it drops the contract for a while. At 35 a public trial jails you; the sentence only ticks while you are online, then you are returned to the room you left. Immortals can force it with `sendhunter <player>`. `infamy` shows your score.
- `alias` saves up to eight names for longer commands, and they are written on the character. `alias n north` makes `n` walk north. `alias greet say Hello there.` saves a whole line. `alias n` removes that one. The saved name has to match exactly, so a short alias does not steal a longer command the way `survey` used to steal `s`. In-game help: `help alias`.
- Clients that accept MSDP (telnet option 69) get health, max health, movement, max movement, the room name, and the room vnum with each prompt, so a client can draw bars and a map beside the text. The game offers it when you connect.
- A player can buy the room they are standing in with `buyhouse` for 25,000 credits. One house per character. It starts locked. `house unlock` and `house lock` open and close it. `house guest <name>` and `house unguest <name>` name who may enter while it is locked. The owner, a named guest, and immortals can always enter. Houses are saved in `system/houses.dat`. This is separate from clan storerooms. In-game help: `help house`.
- Builder quests are in `system/quests.dat`. Each quest has an id, a name, a giver mobile, a credit prize, and up to six stages. A stage is either visit a room (`R`) or kill a mobile (`M`). Standing with the giver, `qaccept` starts it, `qstat` shows the current stage, and `qfinish` pays the prize when every stage is done. Progress is saved on the character. The old `quest` command is still the quest talk channel. One sample is already loaded: an Academy errand from the receptionist on Honoghr. In-game help: `help qaccept`.
