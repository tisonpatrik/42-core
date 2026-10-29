NAME        := fixed
BIN_DIR     := bin

CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98
DEPFLAGS    := -MMD -MP

RM          := rm -f
RM_RF       := rm -rf
MKDIR_P     := mkdir -p


SRCS        := main.cpp \
               Fixed.cpp
OBJS        := $(SRCS:%.cpp=$(BIN_DIR)/%.o)
TEST_OBJS   := $(BIN_DIR)/tests.o $(BIN_DIR)/Fixed.o
DEPS        := $(sort $(OBJS:.o=.d) $(TEST_OBJS:.o=.d))


all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf 'Successfully built: %s\n' "$(NAME)"

test: $(NAME) $(BIN_DIR)/tests
	@$(BIN_DIR)/tests
	@./$(NAME) > "$(BIN_DIR)/output.txt"
	@diff -u fixtures/expected.txt "$(BIN_DIR)/output.txt"
	@printf 'Example output matches.\n'

$(BIN_DIR)/tests: $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TEST_OBJS) $(LDLIBS) -o $@


$(BIN_DIR)/%.o: %.cpp Makefile
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@


clean:
	@$(RM_RF) $(BIN_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all test clean fclean re
