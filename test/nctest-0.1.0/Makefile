CC      		:= gcc
CFLAGS  		:= -std=c99 -Wall -Wextra -Werror -Wpedantic -Wshadow
# DEBUG_FLAGS 	:= -O0 -g3 -DDEBUG -fno-omit-frame-pointer
RELEASE_FLAGS 	:= -O3 -DNDEBUG

############################################# SOURCE CONFIGS #############################################
INCLUDES 	:= -Iinclude
SRCDIR 		:= src
TESTDIR		:= test
BUILDDIR 	:= build

SRC := $(wildcard $(SRCDIR)/*.c)
TEST_SRC := $(wildcard $(TESTDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o) $(TEST_SRC:$(TESTDIR)/%.c=$(BUILDDIR)/%.o)

TARGET=$(BUILDDIR)/nctest

#########################################################################################################
################################################ RECIPES ################################################
#########################################################################################################

all: run-example-user-tests

run-example-user-tests: CFLAGS += $(RELEASE_FLAGS)
run-example-user-tests: $(TARGET)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all run-example-user-tests clean

#########################################################################################################
################################################# RULES #################################################
#########################################################################################################

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build the static library (without main)
# libnctest.a: nctest.o
# 	ar rcs $@ $^
