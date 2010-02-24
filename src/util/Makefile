# UTIL
OBJS=onb.o matrix.o noise.o
OUT_OBJS=$(addprefix $(BUILDDIR)/,$(OBJS))
THISDIR=$(shell pwd)

all: build

build: $(OUT_OBJS)

$(BUILDDIR)/%.o: $(THISDIR)/%.cpp
	$(CC) -c $(COPTS) $< -o $@

$(BUILDDIR)/onb.o: onb.h onb.cpp
$(BUILDDIR)/matrix.o: matrix.h matrix.cpp
$(BUILDDIR)/noise.o: noise.h noise.cpp

.PHONY: all build