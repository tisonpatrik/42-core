# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 16:33:26 by ptison            #+#    #+#              #
#    Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT		:= fdf
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilib/libft/include
DEBUG_FLAGS := -g -O0 -DDEBUG

# MLX flags for graphics (Linux) - commented out for now
# MLX_DIR     := /usr/local/lib
# MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_FLAGS   :=

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

SRC_DIR     := src
LIBFT_DIR   := lib/libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a

# All source files
SRCS	    := $(shell find ./src -iname "*.c")
OBJS        := $(SRCS:src/%.c=bin/%.o)
DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

bin/%.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

debug:
	@$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" all

test: $(NAME)
	@./$(NAME) maps/42.fdf

clean:
	@find $(BIN_DIR)/ -name "*.o" -delete 2>/dev/null || true
	@find $(BIN_DIR)/ -name "*.d" -delete 2>/dev/null || true
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# -include $(DEPS)

.PHONY: all clean fclean re debug test