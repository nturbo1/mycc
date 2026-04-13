CC 				:= gcc
CFLAGS 			:= -std=c17 -Wall -Wextra -Werror -Wpedantic -Wshadow
DEBUG_FLAGS 	:= -O0 -g3 -DDEBUG -fno-omit-frame-pointer
RELEASE_FLAGS 	:= -O3 -DNDEBUG

export CC
export CFLAGS
export DEBUG_FLAGS
export RELEASE_FLAGS

############################################# SOURCE CONFIGS #############################################
INCLUDES 	:= -Isrc/include
SRCDIR 		:= src
BUILDDIR 	:= build

SRC 				:= $(wildcard $(SRCDIR)/*.c)
OBJ 				:= $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
OBJ_WITHOUT_MAIN 	:= $(filter-out %/main.o, $(OBJ))
TEST_OBJ 			:= $(OBJ_WITHOUT_MAIN:%.o=../%.o)

TARGET_EXEC := mycc
TARGET		:= $(BUILDDIR)/$(TARGET_EXEC)

#########################################################################################################
################################################ RECIPES ################################################
#########################################################################################################

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

test: $(OBJ_WITHOUT_MAIN)
	@$(MAKE) -C test \
		PROJ_TEST_OBJ="$(TEST_OBJ)" \
		PROJ_TARGET_EXEC="$(TARGET_EXEC)" \
		PROJ_INCLUDES="-I../$(SRCDIR)"

clean:
	rm -rf $(BUILDDIR)
	$(MAKE) -C test clean

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
