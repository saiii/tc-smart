##=============================================================================
## Copyright (C) 2011 Athip Rooprayochsilp <athipr@gmail.com>
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##              
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##=============================================================================

CC   = gcc
OPTS = -g -Wall -O3
DEF  =
include .Include.mk
include .Libs.mk

TCSMART_SRC = navEvents.c \
              disabledEvents.c \
              events.c \
              viewEvents.c \
              utils.c \
              main.c \
              navstack.c \
              config.c 

TCSMART_FM = bin/TcSmartFm \
             bin/stacktest

TCSMART_OBJ1= $(TCSMART_SRC:.c=.o)
TCSMART_OBJ = $(addprefix .Obj/, $(TCSMART_OBJ1))
TCSMART_DEP = $(TCSMART_OBJ:.o=.d)
TCSMART_ASM = $(TCSMART_OBJ:.o=.asm)

TEST = .Obj/stacktest.o \
       .Obj/navstack.o

all: $(TCSMART_FM)

bin/TcSmartFm: $(TCSMART_OBJ) 
	$(CC) -o $@ $(OPTS) $(TCSMART_OBJ) $(LIBS)

bin/stacktest: $(TEST)
	$(CC) -o $@ $(OPTS) $(TEST) $(LIBS)

.Obj/%.o: src/%.c 
	$(CC) -o $@ $(OPTS) $(DEF) $(INC) -c $<

.Obj/%.d: src/%.c
	@ set -e; rm -f $@; \
                $(CC) -M $(OPTS) $(DEF) $(INC) -c $< > $@.d; \
                sed 's,\($*\)\.o[ :]*,src/\1.o $@: ,g' < $@.d > $@; \
                rm -f $@.d

clean:
	@ rm -f .Obj/*.o .Obj/*.d bin/*

include $(TCSMART_DEP)

