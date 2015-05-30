
.PHONY : all clean compile testapp 

LIBNAME= libboxutil.a 
LIBLINKFNAME = boxutil
TESTAPPNAME= testboxutil

SRC= ./src/bytearray.cpp ./src/exceptionbase.cpp ./src/logger.cpp ./src/stringmanip.cpp ./src/stringmanipexception.cpp ./src/stringvalid.cpp ./src/strveccont.cpp ./src/sysutil.cpp
OBJ= bytearray.o exceptionbase.o logger.o stringmanip.o stringmanipexception.o stringvalid.o strveccont.o sysutil.o

ARCH := $(shell getconf LONG_BIT)

ifeq ($(MODE),)
	MODE=debug
endif

ifeq ($(MODE),debug)
INTFLAGS = \
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-static \
	-fPIC \
	-pthread
POSTBUILD=
#DEFINES= -D _DEBUG -D _LOG 
endif

ifeq ($(MODE),release)
INTFLAGS = \
   	-O2 \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-static \
	-fPIC \
	-pthread
POSTBUILD= strip $(LIBNAME)
#DEFINES= -D _LOG 
endif

ifeq ($(ARCH),64)
CPPFLAGS = $(INTFLAGS) -m64
else 
CPPFLAGSS = $(INTFLAGS)
endif

INCLUDES=-I./src/

all: compile testapp

compile:
	g++ -c $(SRC) $(CPPFLAGS)
	ar -rcs $(LIBNAME) $(OBJ)
	$(POSTBUILD)

testapp:
	make -C ./testboxutil

clean:
	rm -rf $(LIBNAME)
	rm -rf $(OBJ)

