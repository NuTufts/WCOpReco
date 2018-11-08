CXX       = g++

LIBNAME = WC_test

CFLAGS    = -g -fPIC -std=c++11
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES  = `root-config --incdir`
SUBDIRS = dev

LDFLAGS   = `root-config --ldflags` -lstdc++
LDLIBS    = `root-config --libs`

HEADERS   = $(wildcard *.h)

INCLUDES  += $(addprefix -I,$(EIGEN_INCDIR))

SRCS := $(wildcard *.cxx)
OBJS := $(SRCS:.cxx=.o)
BINS = $(SRCS:.cxx=)

LIB = lib${LIBNAME}.so

all: $(LIB)

$(LIB): $(OBJS)
#	@echo "<<library rule called>>"
	$(CXX) $(LDFLAGS) -shared -o $@ $(OBJS)

%.o: %.cxx %.h
	@echo "<<compiling $@>>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@
	# @for i in $(SUBDIRS); do ( echo "" && echo "Compiling $$i..." && cd $$i && $(MAKE) ) || exit $$?; done


clean:
	find . -name '*.o' -delete
	find . -name '*.so' -delete
