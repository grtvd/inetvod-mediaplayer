TARGET = ps2

# Which compiler
CC = g++

# libs and includes
#LIBS = -lglut -lGL -lGLU -lX11 -lm -L/usr/X11R6/lib
LIBS = /usr/doc/PlayStation2/mesa/src-glu/libGLU.la /usr/doc/PlayStation2/mesa/src/libGL.la -lm
#INCLUDE = -I /usr/X11R6/include -I /usr/X11R6/include/GL 
INCLUDE = -I /usr/doc/PlayStation2/mesa/include/ -I ../PS2Pad -I ../JoyPadLib -I ./Main -I ./Core -I ./Data -I ./Controls -I ./Request -I ./Welcome -I ./Setup -I ./NowPlaying -I ./Search
LIBTOOL = /bin/sh /usr/doc/PlayStation2/mesa/libtool
LINK = $(LIBTOOL) --mode=link c++

.SUFFIXES: .c .cpp .s .vsm .dsm .o

# COMMON_OBJS = ../common/screen.o ../common/camera.o ../common/mat44.o ../common/mat33.o ../common/quaternion.o ../common/vec4.o ../common/vec3.o ../common/dmawrap.o
COMMON_OBJS = 

OBJS = ./Main/Main.o \
	./Core/MainApp.o \
	./Core/TType.o \
	./Core/TString.o \
	./Core/TException.o \
	./Core/Rect.o \
	./Core/Font.o \
	./Core/Draw.o \
	./Core/TStrUtils.o \
	./Core/NameValuePair.o \
	./Core/Control.o \
	./Core/ContainerControl.o \
	./Core/Screen.o \
	./Core/ButtonControl.o \
	./Core/EditControl.o \
	./Core/LabelControl.o \
	./Core/SelectControl.o \
	./Core/ListControl.o \
	./Core/TextControl.o \
	./Core/MessageScreen.o \
	./Core/WaitScreen.o \
	./Core/TTick.o \
	./Data/Session.o \
	./Data/Provider.o \
	./Data/RentedShow.o \
	./Data/Category.o \
	./Data/Rating.o \
	./Data/ShowSearch.o \
	./Data/ShowDetail.o \
	./Data/ShowCost.o \
	./Data/ShowProvider.o \
	./Request/DataRequestor.o \
	./Request/MemberSignonRqst.o \
	./Welcome/StartScreen.o \
	../JoyPadLib/joypadlib.o \
	../PS2Pad/PS2Pad.o \
	$(COMMON_OBJS)

#	./Controls/TextListControl.o \
#	./Controls/ShowListControl.o \
#	./Welcome/WelcomeScreen.o \
#	./NowPlaying/NowPlayingScreen.o \
#	./Search/ProviderSearchControl.o \
#	./Search/CategorySearchControl.o \
#	./Search/SearchScreen.o \
#	./Setup/SetupScreen.o \
#	./Setup/AskSignedUpControl.o \
#	./Setup/SerialNoPinControl.o \

# Options for development
CFLAGS = -g -Wall -fno-common -ffast-math $(INCLUDE)
#CFLAGS = -g -Wall -Werror -fno-common -ffast-math $(INCLUDE)

# Options for release
# CFLAGS = -o2 -Wall -ansi -Werror -fno-common -ffast-math $(INCLUDE)

$(TARGET): $(OBJS)
	$(LINK) -o $@ $(OBJS) $(LIBS)
#	$(CC) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CC) -c $< $(CFLAGS) -o $@

.c.o:
	$(CC) -c $< $(CFLAGS) -o $@

.vsm.o:
	ee-dvp-as -o $*.vo_ $*.vsm
	objcopy -Obinary $*.vo_ $*.bin_
	./bin2as $* $*.bin_ > $*.a_
	as -mcpu=r5900 -KPIC -mips2 -o $*.o $*.a_
	rm $*.vo_ $*.bin_ $*.a_

*.vsm: bin2as
bin2as:  bin2as.cpp
	cc -o bin2as bin2as.cpp

depend:
	g++ $(CFLAGS) -MM *.cpp > .depend
#	g++ $(CFLAGS) -MM ../common/*.cpp | sed s/^.*:/..\\/common\\/\&/>> .depend

clean:
	rm -f $(TARGET) bin2as
	rm -f $(OBJS)
	rm -f Makefile.bak
	rm -f .depend

-include .depend
