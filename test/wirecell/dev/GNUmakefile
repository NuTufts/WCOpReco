CXX      =  g++
CFLAGS   =   -g -fPIC
CFLAGS   += `root-config --cflags` -DUSE_OPENCV=1

INCLUDES = -I$(OPENCV_INCDIR)
INCLUDES += -I$(EIGEN_INC_DIR)

LDFLAGS  =  `root-config --ldflags` -lstdc++
LIBS     =  `root-config --libs`
LIBS     += -L$(OPENCV_LIBDIR) -lopencv_core

LIB = ../libWC_test.so
WCLIBDIR = ..

all: $(LIB) main

../libWC_test.so: ../COphit.o  ../ElasticNetModel.o  ../LassoModel.o ../LinearModel.o  ../Opflash.o  ../ToyLightReco.o
	$(CXX) $(LDFLAGS) -shared -o $@ $^ $(LIBS)
#	$(CXX) -shared $(LDFLAGS) -o $@ $^ $(LIBS)
%.o: %.cxx %.h
	@echo "<< compiling $< >>"
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@
main: $(LIB) main.cxx
	$(CXX) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $@.cxx $(LIBS) -L$(WCLIBDIR) -lWC_test
