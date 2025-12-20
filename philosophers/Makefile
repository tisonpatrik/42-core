# Project configuration
PROJECT     := philo
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iphilo/include
CPPFLAGS    := -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG
TSAN_FLAGS  := -fsanitize=thread -g

# Build tools
AR          := ar
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

# --------------------------- Sources ----------------------------------------

# Source files - defined clearly to avoid path errors
SRCS_MAIN   := philo/src/main.c
SRCS_PHILO  := philo/src/philosophy/philosophers.c \
               philo/src/philosophy/arena.c \
               philo/src/philosophy/states.c \
               philo/src/philosophy/resources.c \
               philo/src/philosophy/mind.c \
               philo/src/philosophy/stomach.c
SRCS_SIM    := philo/src/simulation/arena.c \
               philo/src/simulation/forks.c \
               philo/src/simulation/reaper.c \
               philo/src/simulation/simulator.c \
               philo/src/simulation/time.c
SRCS_VALID  := philo/src/validation/validator.c \
               philo/src/validation/converter.c

ALL_SRCS    := $(SRCS_MAIN) $(SRCS_PHILO) $(SRCS_SIM) $(SRCS_VALID)

# Object definitions
OBJS        := $(patsubst philo/src/%.c,bin/%.o,$(ALL_SRCS))
OBJS_DEBUG  := $(patsubst philo/src/%.c,bin/%.debug.o,$(ALL_SRCS))
OBJS_TSAN   := $(patsubst philo/src/%.c,bin/%.tsan.o,$(ALL_SRCS))
DEPS        := $(OBJS:.o=.d) $(OBJS_DEBUG:.o=.d) $(OBJS_TSAN:.o=.d)

# --------------------------- Targets ----------------------------------------
.PHONY: all clean fclean re debug tsan valgrind

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

# --------------------------- Compile rules ----------------------------------

# Standard build
bin/%.o: philo/src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Debug build
bin/%.debug.o: philo/src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CPPFLAGS) -c $< -o $@

# TSan build (ThreadSanitizer)
bin/%.tsan.o: philo/src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(TSAN_FLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# --------------------------- Specific Modes ---------------------------------

debug: $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $(NAME)

tsan: $(OBJS_TSAN)
	@$(CC) $(CFLAGS) $(TSAN_FLAGS) $(OBJS_TSAN) -o $(NAME)
	@echo "TSan build successful (Don't use Valgrind with this build!)"

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 5

# --------------------------- Cleaning ---------------------------------------

clean:
	@$(RM) $(OBJS) $(OBJS_DEBUG) $(OBJS_TSAN) $(DEPS)
	@find $(BIN_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)
	@$(RM_RF) $(BIN_DIR)

re: fclean all
