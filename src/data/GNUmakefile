CXX       = g++ 

LIBNAME = WCOpReco_data

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`

LIBS      = ../../build/lib
LDLIBS   += -Llib $(addprefix -l, $(LIBS))

HEADERS   = ../../build/include/WCOpReco
#Need to include eigen namespace
EIGENSPACE = /usr/include/eigen3
#build/bin build/lib build/python src/algo
INCLUDES  = $(addprefix -I, $(HEADERS) $(EIGENSPACE))
SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
LIB = lib${LIBNAME}.so

all: $(LIB) $(WCOPRECO_LIBDIR)/$(LIB)
	@echo "<<wheres my $(WCOPRECO_LIBDIR)/$(LIB) >>"

$(LIB): $(OBJS)
	@echo "<<library rule called>>"
	$(CXX) $(LDFLAGS) -shared -o $@ $(OBJS)

$(WCOPRECO_LIBDIR)/$(LIB): $(OBJS)

%.o: %.cxx %.h
	@echo "<<compiling $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

