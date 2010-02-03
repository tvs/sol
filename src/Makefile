# SRC DIR
SUBLIST=color image shapes util
OBJS=scene.o simpletexture.o main.o 
OUT_OBJS=$(addprefix $(BUILDDIR)/,$(OBJS))
THISDIR=$(shell pwd)

ALL=build

all: $(ALL)

build: $(SUBLIST) $(OUT_OBJS)

$(SUBLIST):
	@$(MAKE) --directory=$@ $(TARGET)

$(BUILDDIR)/%.o: $(THISDIR)/%.cpp
	$(CC) -c $(COPTS) $< -o $@

$(BUILDDIR)/main.o: main.cpp
$(BUILDDIR)/scene.o: scene.h scene.cpp
$(BUILDDIR)/simpletexture.o: simpletexture.h simpletexture.cpp

.PHONY: all build $(SUBLIST)