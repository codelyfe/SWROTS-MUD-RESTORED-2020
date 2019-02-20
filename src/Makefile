CC      = gcc
PROF    = 
NOCRYPT =
#Uncomment the next line if you want request support
#DBUGFLG = -DREQUESTS
C_FLAGS = -g3 -Wall $(PROF) $(NOCRYPT) $(DBUGFLG)
L_FLAGS = $(PROF)

O_FILES = act_comm.o act_info.o act_move.o act_obj.o act_wiz.o boards.o \
	  build.o clans.o comm.o comments.o const.o db.o fight.o \
	  handler.o hashstr.o id.o interp.o magic.o makeobjs.o \
	  misc.o mud_comm.o mud_prog.o player.o requests.o \
	  reset.o save.o shops.o skills.o special.o tables.o track.o update.o \
	  space.o bounty.o swskills.o functions.o slicers.o marriage.o hunter.o \
	  planets.o pfiles.o newarena.o tech.o \
	  editor.o ships.o force.o finfo.o fskills.o 11.o class.o new_fskills.o \
          council.o 

C_FILES = act_comm.c act_info.c act_move.c act_obj.c act_wiz.c boards.c \
	  build.c clans.c comm.c comments.c const.c db.c fight.c \
	  handler.c hashstr.c id.c interp.c magic.c makeobjs.c \
	  misc.c mud_comm.c mud_prog.c player.c requests.c \
	  reset.c save.c shops.c skills.c special.c tables.c track.c update.c \
	  space.c bounty.c swskills.c functions.c slicers.c marriage.c hunter.c \
          planets.c pfiles.c newarena.c tech.c \
          editor.c ships.c force.o finfo.c fskills.c 11.c class.c new_fskills.c \
          council.c

H_FILES = mud.h bet.h

all:
#	co $(H_FILES)
	make swr
#	rm -f $(H_FILES)

swr: $(O_FILES)
	rm -f swr
	$(CC) $(L_FLAGS) -o swr $(O_FILES) -lm -lcrypt
	chmod g+w swr
	chmod g+w $(O_FILES)

.c.o: mud.h
	$(CC) -c $(C_FLAGS) $<

clean:
	rm -f $(O_FILES)

new:
	make clean
	make
