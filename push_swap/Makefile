# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:16:00 by ptison            #+#    #+#              #
#    Updated: 2025/09/02 13:30:18 by patrik           ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME        := bin/push_swap   
BIN_DIR     := bin              

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft -Isrc

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p          
RM_RF		:= rm -rf

SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

# Main source files
SRCS        := src/validator/input_parser.c \
			   src/validator/normalization.c \
			   src/validator/tokenizer.c \
			   src/ops/push.c \
			   src/ops/reverse_rotate.c \
			   src/ops/rotate.c \
			   src/ops/swap.c \
			   src/ops/sorting_state.c \
			   src/stack/stack.c \
			   src/stack/ops.c \
			   src/stack/node.c \
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
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/ops/%.o: src/ops/%.c | $(BIN_DIR)
	@$(MKDIR_P) bin/ops
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/stack/%.o: src/stack/%.c | $(BIN_DIR)
	@$(MKDIR_P) bin/stack
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/validator/%.o: src/validator/%.c | $(BIN_DIR)
	@$(MKDIR_P) bin/validator
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/utils/%.o: src/utils/%.c | $(BIN_DIR)
	@$(MKDIR_P) bin/utils
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
