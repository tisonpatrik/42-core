# Project configuration
NAME        := replace
BIN_DIR     := bin

# Compiler settings
CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98
DEPFLAGS    := -MMD -MP

# Build tools
RM          := rm -f
RM_RF       := rm -rf
MKDIR_P     := mkdir -p

# --------------------------- Sources ----------------------------------------

SRCS        := main.cpp \
               replaceFile.cpp \
               replaceText.cpp
OBJS        := $(SRCS:%.cpp=$(BIN_DIR)/%.o)
TEST_OBJS   := $(BIN_DIR)/tests.o $(BIN_DIR)/replaceFile.o \
               $(BIN_DIR)/replaceText.o
DEPS        := $(sort $(OBJS:.o=.d) $(TEST_OBJS:.o=.d))

# --------------------------- Targets ----------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf 'Successfully built: %s\n' "$(NAME)"

test: $(NAME) $(BIN_DIR)/tests
	@$(MKDIR_P) "$(BIN_DIR)/test-fixtures/blocked.txt.replace"
	@$(BIN_DIR)/tests "$(BIN_DIR)/test-fixtures"
	@if ./$(NAME) >/dev/null 2>&1; then \
		printf 'Invalid argument count test failed.\n'; exit 1; \
	fi
	@printf '[PASS] invalid argument count\n'

$(BIN_DIR)/tests: $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TEST_OBJS) $(LDLIBS) -o $@

# --------------------------- Compile rules ----------------------------------

$(BIN_DIR)/%.o: %.cpp Makefile
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# --------------------------- Cleaning ---------------------------------------

clean:
	@$(RM_RF) $(BIN_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all test clean fclean re
