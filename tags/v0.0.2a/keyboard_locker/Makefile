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

export: locker_client
	@ sudo cp -f locker_client /usr/bin/
	@ sudo tar cvfP locker_client.tar /usr/lib/libboost_system.so.1.46.1 /usr/lib/libboost_regex.so.1.46.1 /usr/lib/libSai.so /usr/lib/libxerces-c-3.1.so /usr/lib/libcrypto++.so.8 /usr/bin/locker_client 
	@ sudo rm -f locker_client.tar.bz2
	@ sudo bzip2 -z --best locker_client.tar
	@ sudo chmod 666 locker_client.tar.bz2

clean:
	@ rm -Rf .*.o
	@ rm -Rf locker_client
