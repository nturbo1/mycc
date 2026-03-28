########################################### TEST SOURCE CONFIGS ##########################################
SRCDIR := ../src #TODO: There should be a better way to this
TEST_INCLUDES := -I$(SRCDIR)
TEST_BUILDDIR := build
TEST_BUILD_UTILDIR := $(TEST_BUILDDIR)/util

TEST_UTIL_SRC := $(wildcard util/*.c)
TEST_SRC := $(wildcard *_test.c)
TEST_UTIL_OBJ := $(TEST_UTIL_SRC:%.c=$(TEST_BUILDDIR)/%.o)
TEST_OBJ := $(TEST_SRC:%.c=$(TEST_BUILDDIR)/%.o)

TEST_TARGET=$(TEST_BUILDDIR)/mycc_test

#########################################################################################################
################################################ RECIPES ################################################
#########################################################################################################

all: test

test: CFLAGS += $(TEST_INCLUDES)
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	rm -rf $(TEST_BUILDDIR)

.PHONY: all test clean

#########################################################################################################
################################################# RULES #################################################
#########################################################################################################

$(TEST_TARGET): $(TEST_OBJ) $(TEST_UTIL_OBJ) $(SRC_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_BUILDDIR)/%.o: %.c | $(TEST_BUILDDIR) $(TEST_BUILD_UTILDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# $(TEST_BUILD_UTILDIR)/%.o: %.c | $(TEST_BUILD_UTILDIR)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_BUILDDIR):
	mkdir -p $(TEST_BUILDDIR)

$(TEST_BUILD_UTILDIR):
	mkdir -p $(TEST_BUILD_UTILDIR)
