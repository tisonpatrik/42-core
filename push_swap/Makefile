
NAME        := bin/push_swap
BIN_DIR     := bin
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include -Isrc
DEBUG_FLAGS := -g -O0 -DDEBUG

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF		:= rm -rf

SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a

# Main source files
SRCS        := src/validator/input_parser.c \
			   src/validator/normalization.c \
			   src/validator/tokenizer.c \
			   src/ops/push.c \
			   src/ops/reverse_rotate.c \
			   src/ops/rotate.c \
			   src/ops/swap.c \
			   src/ops/sorting_state.c \
			   src/ops/utils.c \
			   src/separator/separator.c \
			   src/separator/list_arena.c \
			   src/separator/algo.c \
			   src/separator/result_builder.c \
			   src/separator/utils.c \
			   src/separator/lis_computation.c \
			   src/selector/candidate_enumerator.c \
			   src/selector/candidate_comparator.c \
			   src/selector/candidates_builder.c \
			   src/selector/snapshot_arena.c \
			   src/selector/lookahead_evaluator.c \
			   src/selector/sorting_heuristic.c \
			   src/selector/nearbest.c \
			   src/selector/result_builder.c \
			   src/selector/selector_arena.c \
			   src/selector/utils.c \
			   src/selector/target_position.c \
			   src/simulation_config/config.c \
			   src/solver/sort.c \
			   src/solver/sort_three.c \
			   src/solver/apply_combined.c \
			   src/solver/align_min_to_top.c \
			   src/optimizer/optimizer.c \
			   src/optimizer/optimizer_arena.c \
			   src/optimizer/operation_builder.c \
			   src/optimizer/optimizer_utils.c \
			   src/optimizer/bubble_operations.c \
			   src/optimizer/merge_neighbors.c \
			   src/optimizer/cancel_operations.c \
			   src/optimizer/operation_properties.c \
			   src/stack/stack.c \
			   src/stack/ops.c \
			   src/stack/node.c \
			   src/stack/tools.c \
			   src/main.c

# Bonus source files (if any)
SRCS_BONUS  :=

OBJS        := $(SRCS:src/%.c=bin/%.o)
OBJS_BONUS  := $(SRCS_BONUS:src/%.c=bin/%.o)

ifdef BONUS
  OBJS      += $(OBJS_BONUS)
endif

DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

bin/%.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	@$(MAKE) BONUS=1 all

debug:
	@$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" all

test:
	@$(MAKE) -C test test

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/push_swap 77 25 55 16 52 24 28 83 4 71 85 98 89 99 30 68 92 59 6 17 91 34 86 47 8 3 57 39 65 44 69 23 80 50 60 56 46 27 21 48 54 63 42 20 73 35 97 93 11 10 22 18 87 2 96 15 72 45 29 38 49 67 79 41 94 76 36 19 5 33 12 14 40 88 78 1 84 90 58 32 61 70 43 0 82 95 9 26 75 13 53 31 37 64 62 66 74 81 7 51

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM_RF) $(BIN_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus debug test valgrind
