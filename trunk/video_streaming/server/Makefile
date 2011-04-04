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

CC   = g++
OPTS = -g -Wall -O3 
DEF  = 

include .Include.mk
include .Libs.mk

TCSMART_SRC = Main.cpp

TCSMART_VDOCLIENT = tc_smart_vdo_server

TCSMART_OBJ1= $(TCSMART_SRC:.cpp=.o)
TCSMART_OBJ = $(addprefix ., $(TCSMART_OBJ1))
TCSMART_DEP = $(TCSMART_OBJ:.o=.d)
TCSMART_ASM = $(TCSMART_OBJ:.o=.asm)

all: $(TCSMART_VDOCLIENT)

tc_smart_vdo_server: $(TCSMART_OBJ) 
	$(CC) -o $@ $(OPTS) $(TCSMART_OBJ) $(LIBS)

.%.o: %.cpp
	$(CC) -o $@ $(OPTS) $(DEF) $(INC) -c $<

.%.d: %.cpp
	@ set -e; rm -f $@; \
                $(CC) -M $(OPTS) $(DEF) $(INC) -c $< > $@.d; \
                sed 's,\($*\)\.o[ :]*,src/\1.o $@: ,g' < $@.d > $@; \
                rm -f $@.d

clean:
	@ rm -f .*.o .*.d tc_smart_vdo_server

include $(TCSMART_DEP)

