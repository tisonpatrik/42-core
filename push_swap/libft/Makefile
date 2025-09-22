# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:24:23 by ptison            #+#    #+#              #
#    Updated: 2025/09/20 11:15:21 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := bin/libft.a
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude
CPPFLAGS    := -MMD -MP

AR          := ar
ARFLAGS     := rcs
RM          := rm -f

CORE_SRCS   := 	src/core/ft_isalnum.c \
                src/core/ft_isalpha.c \
                src/core/ft_isascii.c \
                src/core/ft_isdigit.c \
                src/core/ft_isprint.c \
                src/core/ft_isspace.c \
                src/core/ft_tolower.c \
                src/core/ft_toupper.c

MEM_SRCS    :=  src/mem/ft_arena.c \
                src/mem/ft_bzero.c \
                src/mem/ft_calloc.c \
                src/mem/ft_free_array.c \
                src/mem/ft_memchr.c \
                src/mem/ft_memcmp.c \
                src/mem/ft_memcpy.c \
                src/mem/ft_memmove.c \
                src/mem/ft_memset.c

STR_SRCS    :=  src/str/ft_split.c \
                src/str/ft_strchr.c \
                src/str/ft_strdup.c \
                src/str/ft_striteri.c \
                src/str/ft_strjoin.c \
                src/str/ft_strlcat.c \
                src/str/ft_strlcpy.c \
                src/str/ft_strlen.c \
                src/str/ft_strmapi.c \
                src/str/ft_strncmp.c \
                src/str/ft_strnstr.c \
                src/str/ft_strrchr.c \
                src/str/ft_strtrim.c \
                src/str/ft_substr.c

IO_SRCS     :=  src/io/ft_putchar_fd.c \
                src/io/ft_putendl_fd.c \
                src/io/ft_putnbr_fd.c \
                src/io/ft_putstr_fd.c

CONV_SRCS   :=  src/conv/ft_atoi.c \
                src/conv/ft_itoa.c \
				src/conv/ft_strtoi/utils.c \
				src/conv/ft_strtoi/ft_strtoi.c

UTILS_SRCS  :=  src/utils/ft_parse_sign.c \
                src/utils/ft_skip_whitespace.c

PRINTF_SRCS :=  src/ft_printf/dispatcher.c \
                src/ft_printf/ft_printf.c \
                src/ft_printf/parser.c \
                src/ft_printf/utils.c \
                src/ft_printf/handlers/char_handler.c \
                src/ft_printf/handlers/decimal_handler.c \
                src/ft_printf/handlers/hex_handler.c \
                src/ft_printf/handlers/percent_handler.c \
                src/ft_printf/handlers/pointer_handler.c \
                src/ft_printf/handlers/string_handler.c \
                src/ft_printf/handlers/unsigned_handler.c

LIST_SRCS   :=  src/list/ft_lstadd_back_bonus.c \
                src/list/ft_lstadd_front_bonus.c \
                src/list/ft_lstclear_bonus.c \
                src/list/ft_lstdelone_bonus.c \
                src/list/ft_lstiter_bonus.c \
                src/list/ft_lstlast_bonus.c \
                src/list/ft_lstmap_bonus.c \
                src/list/ft_lstnew_bonus.c \
                src/list/ft_lstsize_bonus.c

MATH_SRCS   :=  src/math/ft_abs.c \
                src/math/ft_swap_int.c


SORT_SRCS   :=  src/sort/ft_heap_sort.c

SEARCH_SRCS :=  src/search/ft_lower_bound.c

SRCS        := $(CORE_SRCS) $(MEM_SRCS) $(STR_SRCS) $(IO_SRCS) $(CONV_SRCS) $(UTILS_SRCS) $(PRINTF_SRCS) $(MATH_SRCS) $(SORT_SRCS) $(SEARCH_SRCS)

ifdef BONUS
  SRCS      += $(LIST_SRCS)
endif

OBJS        := $(patsubst src/%.c,bin/%.o,$(SRCS))
DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus:
	@$(MAKE) BONUS=1 all

clean:
	@$(RM) -r bin/
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus

