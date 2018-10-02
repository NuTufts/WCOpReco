
SUBDIRS = data dev deconv

all: obj


obj:
	@for i in $(SUBDIRS); do ( echo "" && echo "Compiling $$i..." && cd $$i && $(MAKE) ) || exit $$?; done

clean:
