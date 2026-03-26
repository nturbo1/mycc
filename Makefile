CC := gcc

CFLAGS := -std=c17 -Wall -Wextra -Werror -Wpedantic
CFLAGS += -Wshadow
DEBUG_FLAGS := -O0 -g3 -DDEBUG -fno-omit-frame-pointer
RELEASE_FLAGS := -O3 -DNDEBUG

export CC
export CFLAGS
export DEBUG_FLAGS
export RELEASE_FLAGS

############################################# SOURCE CONFIGS #############################################
INCLUDES :=
SRCDIR := src
BUILDDIR := build

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
OBJ_WITHOUT_MAIN := $(filter-out %/main.o, $(OBJ))
OBJ_FOR_TEST := $(OBJ_WITHOUT_MAIN:%.o=../%.o)

TARGET=$(BUILDDIR)/mycc

#########################################################################################################
################################################ RECIPES ################################################
#########################################################################################################

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

test: $(OBJ_WITHOUT_MAIN)
	@$(MAKE) -C test SRC_OBJ="$(OBJ_FOR_TEST)"

clean:
	rm -rf $(BUILDDIR)

.PHONY: all debug release clean build test

#########################################################################################################
################################################# RULES #################################################
#########################################################################################################

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
