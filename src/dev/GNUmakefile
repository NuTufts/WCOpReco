CXX       = g++ 

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`

WCLIBS  = $($($(notdir $(wildcard $(WCOPRECO_LIBDIR)/*.so),lib=)),.so=)
#WCLIBS  = $(WCLIBS: lib=)
#WCLIBS := $(WCLIBS: .so=)
LDLIBS   += -L$(WCOPRECO_LIBDIR) $(addprefix -l, $(WCLIBS))

HEADERS   = $(wildcard *.h)
#Need to include eigen namespace
EIGENSPACE = /usr/include/eigen3
#build/bin build/lib build/python src/algo
INCLUDES  += $(addprefix -I,$(EIGENSPACE))
INCLUDES  += -I. -I$(WCOPRECO_INCDIR)

SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
BINS = $(SRCS:.cxx=)

all: $(BINS)


%: %.cxx
	@echo "<<compiling binary $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $^ -o $@.o 
	$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)

includes: $(HEADERS)
	@echo "<< copy headers to include dir >>"

%.h:
	@cp $@ $(WCOPRECO_INCDIR)/

clean:
	@echo "rm $(FINALINCLUDES)"
	rm *.o *.so $(WCOPRECO_LIBDIR)/$(LIB)
