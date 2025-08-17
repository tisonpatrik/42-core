# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:16:00 by ptison            #+#    #+#              #
#    Updated: 2025/08/17 13:59:11 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := bin/push_swap   
BIN_DIR     := bin              

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft -Isrc
CPPFLAGS    := -MMD -MP

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p          

SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS_BASE   := $(wildcard $(SRC_DIR)/*.c) \
               $(wildcard $(SRC_DIR)/*/*.c)

SRCS        := $(filter-out %_bonus.c,$(SRCS_BASE))
SRCS_BONUS  := $(filter %_bonus.c,$(SRCS_BASE))

OBJS        := $(SRCS:.c=.o)
OBJS_BONUS  := $(SRCS_BONUS:.c=.o)

ifdef BONUS
  OBJS      += $(OBJS_BONUS)
endif

DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Built executable: $(NAME)"

$(BIN_DIR):    
	$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@rmdir $(BIN_DIR) 2>/dev/null || true  

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus
