# SHAPES
OBJS=triangle.o unitsphere.o plane.o instance.o beztrianglemesh.o bezierpatch.o teapot.o
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
$(BUILDDIR)/beztrianglemesh.o: beztrianglemesh.h beztrianglemesh.cpp
$(BUILDDIR)/bezierpatch.o: bezierpatch.h bezierpatch.cpp
$(BUILDDIR)/teapot.o: teapot.h teapot.cpp

.PHONY: all build