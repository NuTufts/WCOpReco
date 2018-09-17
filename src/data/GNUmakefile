CXX       = g++

CFLAGS    = -g -fPIC
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`
#INCLUDES += `larcv-config --includes`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`
#LDLIBS   += `larcv-config --libs`

LIBS      = ../../build/lib
LDLIBS   += -Llib $(addprefix -l, $(LIBS))

HEADERS   = ../../build/include/WCOpReco
#build/bin build/lib build/python src/algo
INCLUDES  = $(addprefix -I, $(HEADERS))
SRCS := $(wildcard *.cxx)
BINS := $(SRCS:%.cxx=%)
EXEC      = #dev

all: ${BINS} $(EXEC)


%: %.cxx
	$(CXX)  $(INCLUDES) -c $< -o $@.o
	#$(CFLAGS)
	#$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)
