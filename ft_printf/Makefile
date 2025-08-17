#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 10:38:00 by patrik            #+#    #+#              #
#    Updated: 2025/06/15 13:12:30 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libftprintf.a

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft -Isrc
CPPFLAGS    := -MMD -MP

AR          := ar
ARFLAGS     := rcs
RM          := rm -f

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

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "Archive created: $(NAME)"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all



.PHONY: all clean fclean re
