CC := gcc

CFLAGS := -std=c17 -Wall -Wextra -Werror -Wpedantic
CFLAGS += -Wshadow

DEBUG_FLAGS := -O0 -g3 -DDEBUG -fno-omit-frame-pointer

RELEASE_FLAGS := -O3 -DNDEBUG

INCLUDES :=

SRCDIR := src
BUILDDIR := build

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

TARGET=$(BUILDDIR)/mycc

######################################### RECIPES #########################################

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all debug release clean build
