# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 18:22:03 by ptison            #+#    #+#              #
#    Updated: 2025/10/05 18:18:49 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := bin/push_swap
CHECKER     := bin/checker
BIN_DIR     := bin
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include
CPPFLAGS    := -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

AR          := ar
ARFLAGS     := rcs
RM          := rm -f
MKDIR_P     := mkdir -p
RM_RF       := rm -rf

SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/bin/libft.a

# --------------------------- Sources ----------------------------------------

SRCS        := $(shell find $(SRC_DIR) -iname "*.c")
MAIN_SRCS   := $(shell find $(SRC_DIR)/solver -iname "*.c")
SRCS_BONUS  := $(shell find checker -iname "*.c")

# Checker dependencies - validator and stack modules
CHECKER_DEPS := $(shell find src/validator src/stack -iname "*.c")

OBJS        := $(SRCS:src/%.c=$(BIN_DIR)/%.o)
OBJS_BONUS  := $(SRCS_BONUS:checker/%.c=$(BIN_DIR)/checker_%.o)
OBJS_CHECKER_DEPS := $(CHECKER_DEPS:src/%.c=$(BIN_DIR)/%.o)

DEPS        := $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d) $(OBJS_CHECKER_DEPS:.o=.d)

# --------------------------- Targets ----------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(CHECKER): $(LIBFT) $(OBJS_BONUS) $(OBJS_CHECKER_DEPS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_CHECKER_DEPS) $(LIBFT) -o $@

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

# --------------------------- Compile rules ----------------------------------

bin/%.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/checker_%.o: checker/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -Wno-sign-compare $(CPPFLAGS) -c $< -o $@

bin/%.debug.o: src/%.c | $(BIN_DIR)
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# --------------------------- Convenience ------------------------------------

bonus: $(NAME) $(CHECKER)

OBJS_DEBUG := $(SRCS:src/%.c=$(BIN_DIR)/%.debug.o)

debug: $(LIBFT) $(OBJS_DEBUG) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) $(LIBFT) -o $(NAME)

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 77 25 55 16 52 24 28 83 4 71 85 98 89 99 30 68 92 59 6 17 91 34 86 47 8 3 57 39 65 44 69 23 80 50 60 56 46 27 21 48 54 63 42 20 73 35 97 93 11 10 22 18 87 2 96 15 72 45 29 38 49 67 79 41 94 76 36 19 5 33 12 14 40 88 78 1 84 90 58 32 61 70 43 0 82 95 9 26 75 13 53 31 37 64 62 66 74 81 7 51

# --------------------------- Cleaning ---------------------------------------

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS) $(OBJS_CHECKER_DEPS) $(OBJS_DEBUG) $(DEPS)
	@find $(BIN_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(CHECKER)
	@$(RM_RF) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus valgrind