# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:24:23 by ptison            #+#    #+#              #
#    Updated: 2025/08/17 13:18:46 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libft.a
BIN_DIR     := bin

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude
CPPFLAGS    := -MMD -MP

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR       := mkdir -p

SRC_DIRS    := src/core src/mem src/str src/io src/conv src/ft_printf src/ft_printf/handlers

ifdef BONUS
  SRC_DIRS  += src/list
endif

SRCS        := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS        := $(SRCS:.c=.o)
DEPS        := $(OBJS:.o=.d)

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

$(BIN_DIR)/$(NAME): $(OBJS) | $(BIN_DIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built $@"

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(BIN_DIR)/$(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus

