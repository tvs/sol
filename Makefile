export TOP := $(shell pwd)
export SRCDIR := $(TOP)/src
export BUILDDIR := $(TOP)/bin

export CC=g++
export COPTS=-g -Wall -I$(SRCDIR)

OJBECTFILES=$(filter %.o, $(BUILDDIR))

ALL=build link

.PHONY: all

all: $(ALL)

build:
	@$(MAKE) --directory=$(SRCDIR) TARGET=build

link:
	$(CC) $(COPTS) $(BUILDDIR)/*.o -o sol

clean:
	@rm -rf $(BUILDDIR)/*.o

clobber: clean
	@rm -rf sol