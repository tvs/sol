# SHAPES
OBJS=triangle.o unitsphere.o plane.o instance.o
OUT_OBJS=$(addprefix $(BUILDDIR)/,$(OBJS))
THISDIR=$(shell pwd)

all: build

build: $(OUT_OBJS)

$(BUILDDIR)/%.o: $(THISDIR)/%.cpp
	$(CC) -c $(COPTS) $< -o $@

$(BUILDDIR)/triangle.o: triangle.h triangle.cpp
$(BUILDDIR)/unitsphere.o: unitsphere.h unitsphere.cpp
$(BUILDDIR)/plane.o: plane.h plane.cpp
$(BUILDDIR)/instance.o: instance.h instance.cpp

.PHONY: all build