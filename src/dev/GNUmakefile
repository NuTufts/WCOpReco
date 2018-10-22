CXX       = g++

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
ROOTLIBS  = `root-config --libs`

WCLIBS = `wcopreco-config --libs`
LDLIBS   += $(WCLIBS)
LDLIBS   += $(LDFLAGS) $(ROOTLIBS)

HEADERS   = $(wildcard *.h)
PACKAGE_HEADERS = $(wildcard $(WCOPRECO_INCDIR)/WCOpReco/*.h)
#Need to include eigen namespace
EIGENSPACE = /usr/include/eigen3
#build/bin build/lib build/python src/algo
INCLUDES  += $(addprefix -I,$(EIGENSPACE))
INCLUDES  += -I. -I$(WCOPRECO_INCDIR)

SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
BINS = $(SRCS:.cxx=)

all: $(BINS)


%: %.cxx  # $(PACKAGE_HEADERS) For some Reason this prerequisite doesn't work. Hacked with a touch main.cxx in the toplevel GNUMakefile
#	@echo "<<Package Headers Directory: $(PACKAGE_HEADERS) "
	@echo "<<compiling binary $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $^ -o $@.o
	@echo "<< link $@ >> "
	$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)

includes: $(HEADERS)
	@echo "<< copy headers to include dir >>"

%.h:
	@cp $@ $(WCOPRECO_INCDIR)/

clean:
	@echo "rm $(FINALINCLUDES)"
	rm *.o *.so $(WCOPRECO_LIBDIR)/$(LIB)

