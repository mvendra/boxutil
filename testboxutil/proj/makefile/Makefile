.PHONY : all prepfolders clean compile link

APPNAME=testboxutil

BASE=../..
LIB=$(BASE)/lib
BASE_SRC=$(BASE)/src
BASE_OBJ=$(BASE)/build
RUN=$(BASE)/run

SRC=main.cpp

COMPILER=g++

ARCH := $(shell getconf LONG_BIT)
CPPFLAGS=
PLAT=generic

ifeq ($(MODE),)
	MODE=debug
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPPFLAGS += -D LINUX
	PLAT=linux
endif
ifeq ($(UNAME_S),Darwin)
	CPPFLAGS += -D OSX
	PLAT=macosx
endif

ifeq ($(MODE),debug)
INTFLAGS = \
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-D_GLIBCXX_DEBUG \
	-std=c++14
POSTBUILD=
endif

ifeq ($(MODE),release)
INTFLAGS = \
	-O2 \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-std=c++14
POSTBUILD= strip $(FULL_APP_NAME)
endif

ifeq ($(ARCH),64)
	CPPFLAGS += $(INTFLAGS) -m64
else
CPPFLAGS += $(INTFLAGS)
endif

PLAT_ARCH_MODE=$(PLAT)_x$(ARCH)_$(MODE)

LEGACY_TESTFORECHO=$(LIB)/legacy_testforecho/include

INCLUDES=-I$(BASE_SRC) -I../$(BASE_SRC) -I$(LEGACY_TESTFORECHO)
LDFLAGS=-L../$(RUN_FULL) -lboxutil

BASE_OBJ_FULL=$(BASE_OBJ)/$(PLAT_ARCH_MODE)
RUN_FULL=$(RUN)/$(PLAT_ARCH_MODE)
ALL_OBJS=$(foreach src,$(SRC),$(BASE_OBJ_FULL)/$(notdir $(src:.cpp=.o)))
FULL_APP_NAME=$(RUN_FULL)/$(APPNAME)

all: prepfolders compile link

prepfolders:
	@mkdir -p $(BASE_OBJ_FULL)
	@mkdir -p $(RUN_FULL)

compile:
	$(foreach src,$(SRC),$(COMPILER) $(INCLUDES) $(CPPFLAGS) -c $(BASE_SRC)/$(src) -o $(BASE_OBJ_FULL)/$(notdir $(src:.cpp=.o));)

link:
	$(COMPILER) -o $(FULL_APP_NAME) $(ALL_OBJS) $(LDFLAGS)

clean:
	$(foreach objs,$(ALL_OBJS),rm -rf $(objs);)
	rm -rf $(FULL_APP_NAME)
