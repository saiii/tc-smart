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

LIBS  = -L/home/athip/Dev/boost_1_46_1/BIN/lib -lboost_system
LIBS += -L/home/athip/Dev/sai/makes/gnu -lSai
LIBS += -lvlc
LIBS += -lcrypto++
LIBS += -L/home/athip/Dev/wxWidgets/wxWidgets-2.9.1/BIN/lib -pthread -lwx_gtk2u-2.9
