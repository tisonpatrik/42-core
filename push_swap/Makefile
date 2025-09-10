
NAME        := bin/push_swap
BIN_DIR     := bin
MAKEFLAGS   += --silent              

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include -Isrc

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
			   src/separator/separator.c \
			   src/separator/lis_interface.c \
			   src/separator/lis_memory_management.c \
			   src/separator/lis_algorithm.c \
			   src/separator/lis_result_builder.c \
			   src/selector/selector_utils.c \
			   src/selector/selector_config.c \
			   src/selector/candidate_manager.c \
			   src/selector/cost_utils.c \
			   src/selector/array_utils.c \
			   src/selector/slice_utils.c \
			   src/selector/nearbest.c \
			   src/selector/move_direction.c \
			   src/selector/lookahead_evaluator.c \
			   src/selector/cost.c \
			   src/selector/cost_calculator.c \
			   src/selector/candidate_enumerator.c \
			   src/selector/algo.c \
			   src/solver/sort.c \
			   src/stack/stack.c \
			   src/stack/ops.c \
			   src/stack/node.c \
			   src/stack/tools.c \
			   src/utils/utils.c \
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

test:
	@$(MAKE) -C test test

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM_RF) $(BIN_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus test
