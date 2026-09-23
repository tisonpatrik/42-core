# Project configuration
NAME        := phonebook
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
               Contact.cpp \
               PhoneBook.cpp
OBJS        := $(SRCS:%.cpp=$(BIN_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# --------------------------- Targets ----------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf 'Successfully built: %s\n' "$(NAME)"

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

.PHONY: all clean fclean re
