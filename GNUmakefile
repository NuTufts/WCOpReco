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

SUBDIRS   = src/data
#Need to include eigen namespace
EIGENSPACE = /usr/include/eigen3
#build/bin build/lib build/python src/algo build/include
INCLUDES += $(addprefix -I, $(SUBDIRS) $(EIGENSPACE))
EXEC      = #dev

all: obj $(EXEC)

%: %.cxx
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@.o
	$(CXX) $(LDFLAGS) -o $@ $@.o $(LDLIBS)
	rm $@.o

obj:
	@echo $(SUBDIRS)
	@for i in $(SUBDIRS); do ( echo "" && echo "Compiling $$i..." && cd $$i && $(MAKE) ) || exit $$?; done
clean:
	rm lib/*.so dev
