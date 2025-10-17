# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 16:33:26 by ptison            #+#    #+#              #
#    Updated: 2025/10/17 22:15:48 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project configuration
PROJECT		:= fdf
BIN_DIR     := bin
NAME        := $(BIN_DIR)/$(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilib/libft/include -I$(MLX42_DIR)/include
DEBUG_FLAGS := -g -O0 -DDEBUG
SANITIZE_FLAGS := -fsanitize=address -fsanitize=undefined

# MLX42 flags for graphics (Linux)
MLX42_DIR   := lib/MLX42
MLX42_LIB   := $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS := -I$(MLX42_DIR)/include -ldl -lglfw -pthread -lm

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
# MAP_SRCS    := $(shell find ./src/map -iname "*.c")  # Commented out - conflicting with app/map_parser.c
APP_SRCS    := $(shell find ./src/app -iname "*.c")
GRID_SRCS   := $(shell find ./src/grid -iname "*.c")
MAP_SRCS := $(shell find ./src/map -iname "*.c")
CAMERA_SRCS := $(shell find ./src/camera -iname "*.c")
RENDER_SRCS := $(shell find ./src/render -iname "*.c")
REFACTORED_SRCS := $(shell find ./src/refactored -iname "*.c")
EXPERIMENTAL_SRCS := $(shell find ./src/experimental -iname "*.c")
MAIN_SRCS   := $(shell find ./src -maxdepth 1 -iname "*.c")
ALL_SRCS    := $(APP_SRCS) $(GRID_SRCS) $(MAP_SRCS) $(CAMERA_SRCS) $(RENDER_SRCS) $(REFACTORED_SRCS) $(EXPERIMENTAL_SRCS) $(MAIN_SRCS)
OBJS        := $(ALL_SRCS:src/%.c=bin/%.o)
DEPS        := $(OBJS:.o=.d)

# Default target
all: $(NAME)

# Main executable
$(NAME): $(LIBFT) $(MLX42_LIB) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

# Create bin directory
$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

# Build MLX42
$(MLX42_LIB):
	@echo "Building MLX42..."
	@cd $(MLX42_DIR) && cmake -B build
	@cd $(MLX42_DIR) && cmake --build build -j4

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
	@$(RM_RF) $(MLX42_DIR)/build

# Full clean
fclean: clean
	@echo "Full clean..."
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re debug