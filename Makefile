PREFIX ?= /usr/local

CXX ?= g++
CXXFLAGS = -Wall -Wextra -Werror -fPIC -std=c++11
CPPFLAGS = -I. -Isrc -Iinclude
LDFLAGS = -L.

ifeq ($(ARCHIVECC_DEBUG),1)
ARCHIVECC_CXXFLAGS += -g -O0
else
ARCHIVECC_CXXFLAGS += -O2
endif

DEPS = libarchive

SRC = $(wildcard src/*.cc)


CXXFLAGS += $(shell pkg-config --cflags $(DEPS))
LIBS = -Wl,--as-needed $(shell pkg-config --libs $(DEPS))

OBJ = $(SRC:%.cc=%.o)
TARGET = libarchivecc.so

ALL_OBJ = $(OBJ)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) -shared $(LIBS)

install: all
	install -d $(PREFIX)/lib
	install -m 755 $(TARGET) $(PREFIX)/lib/
	install -d $(PREFIX)/include/archivecc
	install -m 644 include/archivecc/*.h $(PREFIX)/include/archivecc

clean:
	rm -f $(TARGET) $(ALL_OBJ)

.PHONY: all clean
