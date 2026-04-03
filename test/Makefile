CFLAGS 				?= -std=c17 -Wall -Wextra -Werror -Wpedantic -Wshadow
DEBUG_FLAGS 		?= -O0 -g3 -DDEBUG -fno-omit-frame-pointer
RELEASE_FLAGS 		?= -O3 -DNDEBUG
PROJ_TARGET_EXEC	?= mycc

# Object files that contain tests (expected to be passed by the caller)
PROJ_TEST_OBJ ?=

BUILDDIR 	:= build
TARGET		:= $(BUILDDIR)/$(PROJ_TARGET_EXEC)-tests

# Third-party dependency configs
NCTEST_ROOTDIR := nctest/nctest-0.1.1

PROJ_INCLUDES	?=
INCLUDES 		+= -I$(NCTEST_ROOTDIR)/include $(PROJ_INCLUDES)
SRCDIR 			:= $(NCTEST_ROOTDIR)/src
SRC				:= $(wildcard $(SRCDIR)/*.c)
TEST_SRC		:= $(wildcard *_test.c)
TEST_OBJ		:= $(TEST_SRC:%.c=$(BUILDDIR)/%.o)
OBJ				:= $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: test debug-test clean

test: CFLAGS += $(RELEASE_FLAGS)
debug-test: CFLAGS += $(DEBUG_FLAGS)

test debug-test: $(TARGET)
	@$(TARGET) -v # Remove -v if you want only the final test stats to be outputed

clean:
	rm -rf $(BUILDDIR)

$(TARGET): $(PROJ_TEST_OBJ) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/%_test.o: %_test.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
