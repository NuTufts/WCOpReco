CXX       = g++

CFLAGS    = -g -fPIC
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`
INCLUDES += `larcv-config --includes`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`
LDLIBS   += `larcv-config --libs`

LIBS      =
LDLIBS   += -Llib $(addprefix -l, $(LIBS))

SUBDIRS   = .
#build/bin build/lib build/python src/algo
INCLUDES += $(addprefix -I, $(SUBDIRS))
SRCS := $(wildcard *.cxx)
BINS := $(SRCS:%.cxx=%)
EXEC      = #dev

all: ${BINS} $(EXEC)


%: %.cxx
	$(CXX)  $(INCLUDES) -c $< -o $@.o
	#$(CFLAGS)
	#$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)
