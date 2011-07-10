INC   = -I. 
INC  += -I/home/athip/Dev/sai/src -I/home/athip/Dev/tc-smart/video_streaming
INC  += -I/home/athip/Dev/boost_1_46_1/BIN/include
LIBS  = -L/home/athip/Dev/boost_1_46_1/BIN/lib -lboost_system -lboost_regex
LIBS += -L/home/athip/Dev/sai/makes/gnu -lSai
LIBS += -L/home/athip/Dev/xerces-c-3.1.1-x86-linux-gcc-3.4/lib -lxerces-c
LIBS += -lcrypto++

OBJ =  .Main.o \
       .Cmd.o \
       .Daemonizer.o

locker_client: $(OBJ)
	g++ -o $@ -g $(OBJ) $(LIBS)

.%.o: %.cpp
	g++ -o $@ $(INC) $(DEF) -g -c $<
