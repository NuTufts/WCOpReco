
SUBDIRS = src
#Don't make test subdir - will overwrite things!

all: obj


obj:
	@for i in $(SUBDIRS); do ( echo "" && echo "Compiling $$i..." && cd $$i && $(MAKE) ) || exit $$?; done

clean:
	find . -name '*.o' -delete
	find . -name '*.so' -delete

