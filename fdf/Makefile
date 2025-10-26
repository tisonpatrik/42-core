# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 16:33:26 by ptison            #+#    #+#              #
#    Updated: 2025/10/26 11:01:09 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project configuration
PROJECT		:= fdf
BIN_DIR     := bin
NAME        := $(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -MMD -MP -Iinclude -Ilib/libft/include -I$(MLX42_DIR)/include
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
APP_SRCS    := src/app/app..c \
               src/app/hook.c

GRID_SRCS   := src/grid/file_analyzer.c \
               src/grid/grid_arena.c \
               src/grid/grid.c \
               src/grid/parser.c \
               src/grid/row_parser.c \
               src/grid/token_parser.c \
               src/grid/util.c

CAMERA_SRCS := src/camera/camera.c

RENDER_SRCS := src/render/bresenham.c \
               src/render/draw.c \
               src/render/project.c \
               src/render/render_arena.c \
               src/render/render.c

UTILS_SRCS  := src/utils/utils.c

MAIN_SRCS   := src/main.c

ALL_SRCS    := $(APP_SRCS) $(GRID_SRCS) $(CAMERA_SRCS) $(RENDER_SRCS) $(UTILS_SRCS) $(MAIN_SRCS)
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

# Include dependency files
-include $(DEPS)

# Debug build
debug:
	@echo "Building debug version..."
	@$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" all


# Clean build artifacts
clean:
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM_RF) $(MLX42_DIR)/build

# Full clean
fclean: clean
	@echo "Full clean..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re debug