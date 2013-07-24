export TOP := $(shell pwd)
export SRCDIR := $(TOP)/src
export BUILDDIR := $(TOP)/bin
export IMAGEDIR := $(TOP)/images
export DOCDIR := $(TOP)/doc

export CC=g++
export COPTS=-g -Wall -I$(SRCDIR)

PGNAME=sol

OJBECTFILES=$(filter %.o, $(BUILDDIR))

ALL=build link

.PHONY: all

all: $(ALL)

build:
	@$(MAKE) --directory=$(SRCDIR) TARGET=build

link:
	$(CC) $(COPTS) $(BUILDDIR)/*.o -o $(PGNAME)

clean:
	@rm -rf $(BUILDDIR)/*.o

clobber: clean
	@rm -rf sol

tar: clobber
	@tar --exclude='.*' -czvf sol.tar.gz Makefile src/ images/ doc/

run: 
	@./$(PGNAME) > /tmp/file.$$.ppm; xv /tmp/file.$$.ppm