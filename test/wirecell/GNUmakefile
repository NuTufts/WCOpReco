CXX       = g++

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`

HEADERS   = $(wildcard *.h)

EIGENSPACE = /usr/include/eigen3
INCLUDES  += $(addprefix -I,$(EIGENSPACE))

SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)

all: $(OBJS)
%.o: %.cxx %.h
#	@echo "<<compiling $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@
