# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 20:04:42 by ptison            #+#    #+#              #
#    Updated: 2025/11/04 20:24:01 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project configuration
PROJECT		:= philo
BIN_DIR     := bin
NAME        := $(PROJECT)
MAKEFLAGS   += --silent

# Compiler settings
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include
CPPFLAGS    := -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

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
MAIN_SRCS   := src/main.c

ALL_SRCS    := $
OBJS        := $(ALL_SRCS:src/%.c=bin/%.o)
DEPS        := $(OBJS:.o=.d)

# Default target
all: $(NAME)


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

