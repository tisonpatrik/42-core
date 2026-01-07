# Project configuration
PROJECT     := philo
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iphilo/include
CPPFLAGS    := -MMD -MP
# -g is crucial for Helgrind/DRD to show line numbers
DEBUG_FLAGS := -g -O0 -DDEBUG

# Build tools
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

# --------------------------- Sources ----------------------------------------

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
DEPS        := $(OBJS:.o=.d) $(OBJS_DEBUG:.o=.d)

# --------------------------- Targets ----------------------------------------
.PHONY: all clean fclean re debug helgrind drd valgrind

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

# --------------------------- Compile rules ----------------------------------

# Standard build
bin/%.o: philo/src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Debug build (Required for useful Helgrind/DRD output)
bin/%.debug.o: philo/src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# --------------------------- Specific Modes ---------------------------------

debug: $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $(NAME)
	@echo "Debug build successful (Ready for Valgrind tools)"

# Runs Helgrind on a test case (Standard 5 philos)
helgrind: debug
	@echo "Running Helgrind..."
	@valgrind --tool=helgrind --history-level=approx ./$(NAME) 5 800 200 200 5

# Runs DRD (Data Race Detector) - lighter alternative to Helgrind
drd: debug
	@echo "Running DRD..."
	@valgrind --tool=drd ./$(NAME) 5 800 200 200 5

# Standard memory leak check
valgrind: debug
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 5

# --------------------------- Cleaning ---------------------------------------

clean:
	@$(RM) $(OBJS) $(OBJS_DEBUG) $(DEPS)
	@find $(BIN_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)
	@$(RM_RF) $(BIN_DIR)

re: fclean all
