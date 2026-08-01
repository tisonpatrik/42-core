# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omaly <student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 11:24:23 by ptison            #+#    #+#              #
#    Updated: 2026/02/26 12:26:12 by omaly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := bin/libft.a
MAKEFLAGS   += --silent

CC          := cc
PIE_CFLAGS  := -fPIE
CFLAGS      := -Wall -Wextra -Werror -O2 $(PIE_CFLAGS) -Iinclude
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

ALLOC_SRCS	:=	src/allocator/ft_arena.c \
				src/allocator/ft_arena_size.c \
				src/allocator/ft_arena_scratch.c

MEM_SRCS    := 	src/mem/ft_bzero.c \
                src/mem/ft_calloc.c \
                src/mem/ft_free_array.c \
                src/mem/ft_memchr.c \
                src/mem/ft_memcmp.c \
                src/mem/ft_memcpy.c \
                src/mem/ft_memmove.c \
                src/mem/ft_memset.c \
                src/mem/ft_realloc.c

STR_SRCS    :=  src/str/ft_split.c \
				src/str/ft_is_empty.c \
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

STR8_SRCS	:=	src/str8/ft_str8_alloc.c \
				src/str8/ft_str8_compare.c \
				src/str8/ft_str8_create.c \
				src/str8/ft_str8_parse.c \
				src/str8/ft_is_valid_identifier.c

IO_SRCS     :=  src/io/ft_putchar_fd.c \
                src/io/ft_putendl_fd.c \
                src/io/ft_putnbr_fd.c \
                src/io/ft_putstr_fd.c \
                src/io/ft_putnbr_hex.c \
                src/io/ft_putnbr_unsigned.c \
                src/io/ft_putptr.c \
                src/io/ft_get_line/ft_get_line.c \
                src/io/ft_read_file.c

CONV_SRCS   :=  src/conv/ft_atoi.c \
                src/conv/ft_itoa.c \
				src/conv/ft_stroi.c \
				src/conv/ft_atoll.c \
				src/conv/ft_atoll_safe.c \
				src/conv/ft_str8_to_int.c

PRINTF_SRCS :=  src/ft_printf/ft_printf.c

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
				src/math/ft_clamp.c \
				src/math/ft_min_int.c \
				src/math/ft_rgba.c \
				src/math/ft_rgba_blend.c \
				src/math/ft_rgba_fill.c \
				src/math/ft_rgba_view.c \
				src/math/ft_prng_next.c \
				src/math/ft_size.c \
				src/math/ft_step_cycle.c \
                src/math/ft_swap_int.c


SORT_SRCS   :=  src/sort/ft_heap_sort.c

SEARCH_SRCS :=  src/search/ft_lower_bound.c


VEC_SRCS :=  src/vec2/ft_v2d.c \
				src/vec2/ft_v2d_basis.c \
				src/vec2/ft_v2d_geometry.c \
				src/vec2/ft_v2d_normalize.c \
				src/vec2/ft_v2i.c

SRCS        := $(CORE_SRCS) $(MEM_SRCS) $(ALLOC_SRCS) $(STR_SRCS) $(IO_SRCS) $(CONV_SRCS) $(PRINTF_SRCS) $(MATH_SRCS) $(SORT_SRCS) $(SEARCH_SRCS) $(STR8_SRCS) $(VEC_SRCS)

ifdef BONUS
  SRCS      += $(LIST_SRCS)
endif

OBJS        := $(patsubst src/%.c,bin/%.o,$(SRCS))
DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(RM) $(NAME)
	@$(AR) $(ARFLAGS) $@ $^

bin/%.o: src/%.c Makefile
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
