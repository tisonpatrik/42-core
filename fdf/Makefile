# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 16:33:26 by ptison            #+#    #+#              #
#    Updated: 2025/09/27 16:32:53 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project configuration
PROJECT		:= fdf
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilib/libft/include
DEBUG_FLAGS := -g -O0 -DDEBUG
SANITIZE_FLAGS := -fsanitize=address -fsanitize=undefined

# MLX flags for graphics (Linux) - commented out for now
# MLX_DIR     := /usr/local/lib
# MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_FLAGS   :=

# Build tools
AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

# Directories
SRC_DIR     := src
LIBFT_DIR   := lib/libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a

# Source files organization
MAP_SRCS    := $(shell find ./src/map -iname "*.c")
MAIN_SRCS   := $(shell find ./src -maxdepth 1 -iname "*.c")
ALL_SRCS    := $(MAP_SRCS) $(MAIN_SRCS)
OBJS        := $(ALL_SRCS:src/%.c=bin/%.o)
DEPS        := $(OBJS:.o=.d)

# Default target
all: $(NAME)

# Main executable
$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Create bin directory
$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

# Compile source files
bin/%.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug:
	@echo "Building debug version..."
	@$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" all


# Clean build artifacts
clean:
	@find $(BIN_DIR)/ -name "*.o" -delete 2>/dev/null || true
	@find $(BIN_DIR)/ -name "*.d" -delete 2>/dev/null || true
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	@echo "Full clean..."
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re debug