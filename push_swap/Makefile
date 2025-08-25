# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:16:00 by ptison            #+#    #+#              #
#    Updated: 2025/08/19 12:01:58 by patrik           ###   ########.fr        #
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
SRCS        := src/input_parser.c \
			   src/normalization.c \
			   src/push.c \
			   src/push_swap.c \
               src/reverse_rotate.c \
               src/rotate.c \
               src/swap.c \
			   src/tokenizer.c \
			   src/utils.c

# Bonus source files (if any)
SRCS_BONUS  :=

OBJS        := $(SRCS:.c=.o)
OBJS_BONUS  := $(SRCS_BONUS:.c=.o)

ifdef BONUS
  OBJS      += $(OBJS_BONUS)
endif

DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Built executable: $(NAME)"

$(BIN_DIR):    
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	@$(MAKE) BONUS=1 all

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM_RF) $(BIN_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus
