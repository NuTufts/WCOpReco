CXX       = g++

LIBNAME = WCOpReco_app

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`

LIBS      = ../../build/lib
LDLIBS   += -Llib $(addprefix -l, $(LIBS))

HEADERS   = $(wildcard *.h)
#Need to include eigen namespace
EIGENSPACE = /usr/include/eigen3
#build/bin build/lib build/python src/algo
INCLUDES  += $(addprefix -I,$(EIGENSPACE))
INCLUDES  += -I. -I$(WCOPRECO_INCDIR)/WCOpReco
FINALINCLUDES= $(addpredix $(WCOPRECO_INCDIR),$(HEADERS))
SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
LIB = lib${LIBNAME}.so

all: $(LIB) $(WCOPRECO_LIBDIR)/$(LIB) includes

$(LIB): $(OBJS)
#	@echo "<<library rule called>>"
	$(CXX) $(LDFLAGS) -shared -o $@ $(OBJS)

$(WCOPRECO_LIBDIR)/$(LIB): $(OBJS)
	@echo "<< copy lib to lib folder >>"
	@cp $(LIB) $@

%.o: %.cxx %.h
#	@echo "<<compiling $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

includes:
	@echo "<< copy headers to include dir: $(WCOPRECO_INCDIR) >>"
	@cp *.h $(WCOPRECO_INCDIR)/WCOpReco/

clean:
	@echo "rm $(FINALINCLUDES)"
	rm *.o *.so $(WCOPRECO_LIBDIR)/$(LIB)
