# Project configuration
PROJECT		:= philo
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iphilo/include
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


# --------------------------- Sources ----------------------------------------

# Source files organization
ALL_SRCS    := philo/src/main.c \
				philo/src/simulator.c \
                philo/src/arena.c \
                philo/src/output.c \
                philo/src/validator.c \
                philo/src/atoi.c \
                philo/src/philosophers.c \
                philo/src/reaper.c \
                philo/src/time.c
OBJS        := $(patsubst philo/src/%.c,bin/%.o,$(ALL_SRCS))
DEPS        := $(OBJS:.o=.d)

# --------------------------- Targets ----------------------------------------
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) | $(BIN_DIR)
	@$(MKDIR_P) $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

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
OBJS_DEBUG := $(patsubst philo/src/%.c,bin/%.debug.o,$(ALL_SRCS))

debug: $(OBJS_DEBUG) | $(BIN_DIR)
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $(NAME)

.PHONY: valgrind
valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

# --------------------------- Cleaning ---------------------------------------

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(OBJS_DEBUG) $(DEPS)
	@find $(BIN_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete 2>/dev/null || true


.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)
	@$(RM_RF) $(BIN_DIR)

.PHONY: re
re: fclean all
