# SAI
INC = -I. -I/home/athip/Dev/sai.v0.0.x/src -I../..
DEF = -D__stdcall= -D_WIN32 -DDllPrefix= -D_DLL

OBJ = .ClientMsgHandler.o \
      .SaiWrapper.o \
      .ServerMsg.o

libSaiWrapper.so: $(OBJ)
	g++ -fPIC -shared -o $@ $(OBJ)

.%.o: %.cpp
	g++ -o $@ -g $(DEF) $(INC) -c $<

clean:
	@ rm -Rf .*.o
