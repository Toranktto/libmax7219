DIRS=	libmax7219 examples

.PHONY: all

all:
	for m in $(DIRS); do \
		$(MAKE) -C $$m all; \
	done

all:
	for m in $(DIRS); do \
		$(MAKE) -C $$m clean; \
	done

cleandir:
	for m in $(DIRS); do \
		$(MAKE) -C $$m cleandir; \
	done
