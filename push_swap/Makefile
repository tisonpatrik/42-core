# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 18:22:03 by ptison            #+#    #+#              #
#    Updated: 2025/09/29 18:58:56 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := bin/push_swap
CHECKER     := bin/checker
BIN_DIR     := bin
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include
CPPFLAGS    := -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF		:= rm -rf

SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a

# Validator source files
VALIDATOR_SRCS := src/validator/argument_counter.c \
                  src/validator/input_parser.c \
                  src/validator/normalization.c \
                  src/validator/parser_result.c \
                  src/validator/tokenizer.c \

# Operations source files
OPS_SRCS    := src/ops/push.c \
               src/ops/reverse_rotate.c \
               src/ops/rotate.c \
               src/ops/swap.c \
               src/ops/sorting_state.c \
               src/ops/utils.c

# Separator source files
SEPARATOR_SRCS := src/separator/separator.c \
                  src/separator/separator_arena.c \
                  src/separator/result_builder.c \
                  src/separator/utils.c \
                  src/separator/lis_computation.c

# Selector source files
SELECTOR_SRCS := src/selector/candidate_enumerator.c \
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
                 src/selector/config.c

# Solver source files
SOLVER_SRCS := src/solver/sort.c \
               src/solver/sort_three.c \
               src/solver/apply_combined.c \
               src/solver/align_min_to_top.c

# Optimizer source files
OPTIMIZER_SRCS := src/optimizer/optimizer_core.c \
                  src/optimizer/utils.c \
                  src/optimizer/bubble_operations.c \
                  src/optimizer/bubble_search.c \
                  src/optimizer/bubble_strategy.c \
                  src/optimizer/merge_neighbors.c \
                  src/optimizer/merge_core.c \
                  src/optimizer/merge_logic.c \
                  src/optimizer/cancel_core.c \
                  src/optimizer/cancel_logic.c \
                  src/optimizer/cancel_strategy.c \
                  src/optimizer/properties.c

# Stack source files
STACK_SRCS  := src/stack/stack.c \
               src/stack/ops.c \
               src/stack/node.c \
               src/stack/tools.c

# Main source files
MAIN_SRCS   := src/solver/main.c

# All source files
SRCS        := $(VALIDATOR_SRCS) $(OPS_SRCS) $(SEPARATOR_SRCS) $(SELECTOR_SRCS) \
               $(SOLVER_SRCS) $(OPTIMIZER_SRCS) $(STACK_SRCS) $(MAIN_SRCS)

# Bonus source files (checker)
SRCS_BONUS  := checker/main_bonus.c \
               checker/reader_bonus.c \
               checker/sorting_state_bonus.c \
               checker/resutls_checker_bonus.c \
               checker/push_bonus.c \
               checker/swap_bonus.c \
               checker/rotate_bonus.c \
               checker/reverse_rotate_bonus.c

OBJS        := $(SRCS:src/%.c=bin/%.o)
OBJS_BONUS  := $(SRCS_BONUS:checker/%.c=bin/checker_%.o)

ifdef BONUS
  OBJS      += $(OBJS_BONUS)
endif

DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(CHECKER): $(LIBFT) $(OBJS_BONUS) bin/validator/input_parser.o bin/validator/normalization.o bin/validator/tokenizer.o bin/stack/stack.o bin/stack/tools.o bin/stack/node.o bin/stack/ops.o | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) bin/validator/input_parser.o bin/validator/normalization.o bin/validator/tokenizer.o bin/stack/stack.o bin/stack/tools.o bin/stack/node.o bin/stack/ops.o $(LIBFT) -o $(CHECKER)

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus CHECKER_BUILD=1

bin/%.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/checker_%.o: checker/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -Wno-sign-compare $(CPPFLAGS) -c $< -o $@

bonus: $(NAME) $(CHECKER)

debug:
	@$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" all

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/push_swap 77 25 55 16 52 24 28 83 4 71 85 98 89 99 30 68 92 59 6 17 91 34 86 47 8 3 57 39 65 44 69 23 80 50 60 56 46 27 21 48 54 63 42 20 73 35 97 93 11 10 22 18 87 2 96 15 72 45 29 38 49 67 79 41 94 76 36 19 5 33 12 14 40 88 78 1 84 90 58 32 61 70 43 0 82 95 9 26 75 13 53 31 37 64 62 66 74 81 7 51

clean:
	@find $(BIN_DIR)/ -name "*.o" -delete 2>/dev/null || true
	@find $(BIN_DIR)/ -name "*.d" -delete 2>/dev/null || true
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true
	@find checker/ -name "*.o" -delete 2>/dev/null || true
	@find checker/ -name "*.d" -delete 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus debug valgrind unused-check
