OBJS=image.o
OUT_OBJS=$(addprefix $(BUILDDIR)/,$(OBJS))
THISDIR=$(shell pwd)

all: build

build: $(OUT_OBJS)

$(BUILDDIR)/%.o: $(THISDIR)/%.cpp
	$(CC) -c $(COPTS) $< -o $@

$(BUILDDIR)/%.o: $(THISDIR)/%.h
	$(CC) -c $(COPTS) $< -o $@

$(BUILDDIR)/image.o: image.h image.cpp

.PHONY: all build