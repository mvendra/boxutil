
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
	$(SOURCE_BASE)/stringmanipexception.cpp \
	$(SOURCE_BASE)/logger.cpp

OBJ=	$(BUILD_BASE)/$(MACHBRAND)/exceptionbase.o \
	$(BUILD_BASE)/$(MACHBRAND)/stringmanip.o \
	$(BUILD_BASE)/$(MACHBRAND)/strveccont.o \
	$(BUILD_BASE)/$(MACHBRAND)/stringvalid.o \
	$(BUILD_BASE)/$(MACHBRAND)/bytearray.o \
	$(BUILD_BASE)/$(MACHBRAND)/stringmanipexception.o \
	$(BUILD_BASE)/$(MACHBRAND)/logger.o

#ARCH := $(shell getconf LONG_BIT)

#ifeq (${CONF},)
	#MODE=debug
#endif

#ifeq ($(ARCH),64)
#CPPFLAGS = $(INTFLAGS) -m64
#else 
#CPPFLAGSS = $(INTFLAGS)
#endif

ifeq (${CONF},Debug_64)
MACHBRAND=linux_debug_64
INTFLAGS = \
	-g \
	-Wall \
	-static \
	-fPIC \
	-pthread
CPPFLAGS = $(INTFLAGS) -m64
POSTBUILD=
#DEFINES= -D _DEBUG -D _LOG 
endif

ifeq (${CONF},Release_64)
MACHBRAND=linux_release_64
INTFLAGS = \
   	-O2 \
	-Wall \
	-static \
	-fPIC \
	-pthread
CPPFLAGS = $(INTFLAGS) -m64
POSTBUILD= strip $(DIST_BASE)/$(MACHBRAND)/$(LIBNAME)
#DEFINES= -D _LOG 
endif

INCLUDES=-I. -I$(SOURCE_BASE)

all: compile

compile:
	g++ $(CPPFLAGS) -c $(SRC)
	mv ./*.o $(BUILD_BASE)/$(MACHBRAND)
	ar -rcs $(BUILD_BASE)/$(MACHBRAND)/$(LIBNAME) $(OBJ)
	mv $(BUILD_BASE)/$(MACHBRAND)/$(LIBNAME) $(DIST_BASE)/$(MACHBRAND)
	$(POSTBUILD)

clean:
	rm -rf $(OBJ)
	rm -rf $(DIST_BASE)/$(MACHBRAND)/$(LIBNAME)
