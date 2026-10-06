NAME        := zombie
BIN_DIR     := bin

CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98
DEPFLAGS    := -MMD -MP

RM          := rm -f
RM_RF       := rm -rf
MKDIR_P     := mkdir -p

SRCS        := main.cpp \
               Zombie.cpp \
               newZombie.cpp \
               randomChump.cpp
OBJS        := $(SRCS:%.cpp=$(BIN_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf 'Successfully built: %s\n' "$(NAME)"


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

.PHONY: all clean fclean re
