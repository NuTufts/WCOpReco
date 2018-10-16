CXX       = g++

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
ROOTLIBS    = `root-config --libs`

LDLIBS   += $(LDFLAGS) $(ROOTLIBS)

LIBS      = ../
LDLIBS   += -Llib $(addprefix -l, $(LIBS))

HEADERS   = $(wildcard *.h)

EIGENSPACE = /usr/include/eigen3
INCLUDES  += $(addprefix -I,$(EIGENSPACE))
INCLUDES  += -I. -I$(WC_BASEDIR)

SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
BINS = $(SRCS:.cxx=)

all: $(BINS)
%: %.cxx
	@echo "<<compiling binary $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $^ -o $@.o
	@echo "<<link $@ >> "
	$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)
