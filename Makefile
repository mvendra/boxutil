
.PHONY : all clean compile

LIBNAME= libboxutil.a 
LIBLINKFNAME = boxutil

SOURCE_BASE=./src
BUILD_BASE=./build
DIST_BASE=./dist

SRC=	$(SOURCE_BASE)/exceptionbase.cpp \
	$(SOURCE_BASE)/stringmanip.cpp \
	$(SOURCE_BASE)/strveccont.cpp \
	$(SOURCE_BASE)/stringvalid.cpp \
	$(SOURCE_BASE)/bytearray.cpp \
	$(SOURCE_BASE)/stringmanipexception.cpp

OBJ= $(BUILD_BASE)/exceptionbase.o \
     $(BUILD_BASE)/stringmanip.o \
     $(BUILD_BASE)/strveccont.o \
     $(BUILD_BASE)/stringvalid.o \
     $(BUILD_BASE)/bytearray.o \
     $(BUILD_BASE)/stringmanipexception.o

ARCH := $(shell getconf LONG_BIT)

ifeq ($(MODE),)
	MODE=debug
endif

ifeq ($(MODE),debug)
INTFLAGS = \
	-g \
	-Wall \
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
	-static \
	-fPIC \
	-pthread
POSTBUILD= strip $(DIST_BASE)/$(LIBNAME)
#DEFINES= -D _LOG 
endif

ifeq ($(ARCH),64)
CPPFLAGS = $(INTFLAGS) -m64
else 
CPPFLAGSS = $(INTFLAGS)
endif

INCLUDES=-I. -I$(SOURCE_BASE)

all: compile

compile:
	g++ $(CPPFLAGS) -c $(SRC)
	mv ./*.o $(BUILD_BASE)
	ar -rcs $(BUILD_BASE)/$(LIBNAME) $(OBJ)
	mv $(BUILD_BASE)/$(LIBNAME) $(DIST_BASE)
	$(POSTBUILD)

clean:
	rm -rf $(OBJ)
	rm -rf $(DIST_BASE)/$(LIBNAME)
