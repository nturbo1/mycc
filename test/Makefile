########################################### TEST SOURCE CONFIGS ##########################################
SRCDIR := ../src #TODO: There should be a better way to this
TEST_INCLUDES := -I$(SRCDIR)
TEST_BUILDDIR := build

TEST_SRC := $(wildcard *_test.c)
TEST_OBJ := $(TEST_SRC:%.c=$(TEST_BUILDDIR)/%.o)

TEST_TARGET=$(TEST_BUILDDIR)/mycc_test

#########################################################################################################
################################################ RECIPES ################################################
#########################################################################################################

all: test

debug-test: CFLAGS += $(DEBUG_FLAGS)
debug-test: CFLAGS += $(TEST_INCLUDES)
debug-test: $(TEST_TARGET)
	@./$(TEST_TARGET)

test: CFLAGS += $(RELEASE_FLAGS)
test: CFLAGS += $(TEST_INCLUDES)
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean-test:
	rm -rf $(TEST_BUILDDIR)

.PHONY: all debug-test test clean-test

#########################################################################################################
################################################# RULES #################################################
#########################################################################################################

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(SRC_OBJ) -o $@

$(TEST_BUILDDIR)/%.o: %.c | $(TEST_BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_BUILDDIR):
	mkdir -p $(TEST_BUILDDIR)
