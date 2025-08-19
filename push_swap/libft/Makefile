# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:24:23 by ptison            #+#    #+#              #
#    Updated: 2025/08/19 11:53:09 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libft.a

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude
CPPFLAGS    := -MMD -MP

AR          := ar
ARFLAGS     := rcs
RM          := rm -f

SRC_DIRS    := src/core src/mem src/str src/io src/conv src/conv/ft_strtoi src/ft_printf src/ft_printf/handlers src/utils

ifdef BONUS
  SRC_DIRS  += src/list
endif

SRCS        := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS        := $(SRCS:.c=.o)
DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "Built $@"

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) $(wildcard src/**/*.o)
	@$(RM) $(wildcard src/**/*.d)

fclean: clean
	@$(RM) $(NAME)



re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus

