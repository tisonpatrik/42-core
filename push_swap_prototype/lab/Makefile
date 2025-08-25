# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrik <patrik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 14:02:06 by ugerkens          #+#    #+#              #
#    Updated: 2025/08/24 19:06:36 by patrik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -Iinclude -Isrc -O3
RM					=	rm -rf
CHECKER				=	bin/checker
PUSH_SWAP			=	bin/push_swap
TEST_RUNNER			=	bin/test_runner
NAME				=	$(PUSH_SWAP) $(CHECKER)

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/include

FT_PRINTF			=	ft_printf.a
FT_PRINTF_DIR		=	lib/ft_printf
FT_PRINTF_FILE		=	$(FT_PRINTF_DIR)/$(FT_PRINTF)
CFLAGS				+=	-I $(FT_PRINTF_DIR)/include

MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH				=	src:src/stack:src/push_swap:src/checker_bonus:include
STACK_INC			=	stack.h
PUSH_SWAP_INC		=	$(STACK_INC) push_swap.h debug_logging.h
CHECKER_INC			=	$(STACK_INC) checker_bonus.h debug_logging.h

# Rules
build:				$(PUSH_SWAP) $(TEST_RUNNER)

all:				build test

bonus:				$(CHECKER)

test_runner:		$(TEST_RUNNER)

test:				$(TEST_RUNNER)
	@echo "=== Running test with 100 random numbers ==="
	@./bin/test_runner

bin:
					mkdir -p bin

LIB					=	$(LIBFT_FILE) $(FT_PRINTF_FILE)

# Use wildcards to find all .c files and compile them to .o in bin
PUSH_SWAP_OBJ		=	$(wildcard src/*.c src/stack/*.c src/push_swap/*.c src/logging/*.c)
PUSH_SWAP_OBJ		:=	$(notdir $(PUSH_SWAP_OBJ:%.c=%.o))
PUSH_SWAP_OBJ		:=	$(addprefix bin/,$(PUSH_SWAP_OBJ))

CHECKER_OBJ			=	$(wildcard src/stack/*.c src/checker_bonus/*.c src/logging/*.c)
CHECKER_OBJ			:=	$(notdir $(CHECKER_OBJ:%.c=%.o))
CHECKER_OBJ			:=	$(addprefix bin/,$(CHECKER_OBJ))

TEST_RUNNER_OBJ		=	tools/test_runner.c
TEST_RUNNER_OBJ		:=	$(notdir $(TEST_RUNNER_OBJ:%.c=%.o))
TEST_RUNNER_OBJ		:=	$(addprefix bin/,$(TEST_RUNNER_OBJ))

# Generic rule for all .o files
bin/%.o:	src/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

bin/%.o:	src/stack/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

bin/%.o:	src/push_swap/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

bin/%.o:	src/checker_bonus/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

bin/%.o:	src/logging/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

bin/%.o:	tools/%.c
			@mkdir -p bin
			$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)
$(FT_PRINTF_FILE):
					$(MAKE_LIB) $(FT_PRINTF_DIR)

$(PUSH_SWAP):		bin $(LIB) $(PUSH_SWAP_OBJ)
					$(CC) $(CFLAGS) $(PUSH_SWAP_OBJ) $(LIB) -o $@

$(CHECKER):			bin $(LIB) $(CHECKER_OBJ)
					$(CC) $(CFLAGS) $(CHECKER_OBJ) $(LIB) -o $@

$(TEST_RUNNER):		bin $(TEST_RUNNER_OBJ)
					$(CC) $(CFLAGS) $(TEST_RUNNER_OBJ) -o $@

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean
					$(MAKE_LIB) $(FT_PRINTF_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean
					$(MAKE_LIB) $(FT_PRINTF_DIR) fclean

clean:				lib_clean
					$(RM) bin

fclean:				clean lib_fclean
					$(RM) $(NAME)
					$(RM) bin

re:					fclean all

.SILENT:

.PHONY:				all build test bonus test_runner lib_clean lib_fclean clean fclean re bin
