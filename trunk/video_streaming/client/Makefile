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

TCSMART_SRC = Main.cpp \
              OneInstance.cpp \
              Daemonizer.cpp \
              Command.cpp

TCSMART_VDOCLIENT = tc_smart_vdo_client tc_smart_vdo_client_killer

TCSMART_OBJ1= $(TCSMART_SRC:.cpp=.o)
TCSMART_OBJ = $(addprefix ., $(TCSMART_OBJ1))
TCSMART_DEP = $(TCSMART_OBJ:.o=.d)
TCSMART_ASM = $(TCSMART_OBJ:.o=.asm)

all: $(TCSMART_VDOCLIENT)

tc_smart_vdo_client: $(TCSMART_OBJ) 
	$(CC) -o $@ $(OPTS) $(TCSMART_OBJ) $(LIBS)

tc_smart_vdo_client_killer: .Killer.o
	$(CC) -o $@ $(OPTS) $< $(LIBS)

.%.o: %.cpp
	$(CC) -o $@ $(OPTS) $(DEF) $(INC) -c $<

.%.d: %.cpp
	@ set -e; rm -f $@; \
                $(CC) -M $(OPTS) $(DEF) $(INC) -c $< > $@.d; \
                sed 's,\($*\)\.o[ :]*,src/\1.o $@: ,g' < $@.d > $@; \
                rm -f $@.d

export: tc_smart_vdo_client
	@ sudo cp -f tc_smart_vdo_client /usr/bin/
	@ sudo cp -f tc_smart_vdo_client_killer /usr/bin/
	@ sudo tar cvfP tc_smart_client.tar /usr/lib/libboost_system.so.1.46.1 /usr/lib/libboost_regex.so.1.46.1 /usr/lib/libSai.so /usr/lib/libxerces-c-3.1.so /usr/lib/libvlc.so.5 /usr/lib/libcrypto++.so.8 /usr/lib/libvlccore.so.4 /usr/bin/tc_smart_vdo_client /usr/bin/tc_smart_vdo_client_killer
	@ sudo rm -f tc_smart_client.tar.bz2
	@ sudo bzip2 -z --best tc_smart_client.tar
	@ sudo chmod 666 tc_smart_client.tar.bz2

clean:
	@ rm -f .*.o .*.d tc_smart_vdo_client tc_smart_vdo_client_killer

include $(TCSMART_DEP)

