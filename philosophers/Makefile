# Project configuration
PROJECT		:= philo
BIN_DIR     := bin
BIN_NAME    := $(BIN_DIR)/$(PROJECT)
NAME        := $(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iphilo/include -Iphilo/libft/include
CPPFLAGS    := -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

# Build tools
AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

# Directories
SRC_DIR     := philo/src
LIBFT_DIR   := philo/libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a


# --------------------------- Sources ----------------------------------------

# Source files organization
ALL_SRCS    := philo/src/main.c \
               philo/src/simulator.c \
               philo/src/simulator_arena.c \
               philo/src/validator.c
OBJS        := $(ALL_SRCS:philo/src/%.c=bin/%.o)
DEPS        := $(OBJS:.o=.d)

# --------------------------- Targets ----------------------------------------
.PHONY: all
all: $(NAME)

$(NAME): $(BIN_NAME)
	@cp $(BIN_NAME) $(NAME)

$(BIN_NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(MKDIR_P) $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

# --------------------------- Compile rules ----------------------------------

bin/%.o: philo/src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/%.debug.o: philo/src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# --------------------------- Convenience ------------------------------------
.PHONY: debug
OBJS_DEBUG := $(ALL_SRCS:philo/src/%.c=$(BIN_DIR)/%.debug.o)

debug: $(LIBFT) $(OBJS_DEBUG) | $(BIN_DIR)
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) $(LIBFT) -o $(BIN_NAME)
	@cp $(BIN_NAME) $(NAME)

.PHONY: valgrind
valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

# --------------------------- Cleaning ---------------------------------------

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(OBJS_DEBUG) $(DEPS)
	@find $(BIN_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean


.PHONY: fclean
fclean: clean
	@test -f $(NAME) && $(RM) $(NAME) || true
	@$(RM) $(BIN_NAME)
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: re
re: fclean all
