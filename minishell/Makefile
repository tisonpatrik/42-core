# ============================================================================ #
#                                 CONFIG                                       #
# ============================================================================ #

PROJECT     := minishell
BIN_DIR     := bin
OBJ_DIR     := $(BIN_DIR)/obj
NAME        := $(BIN_DIR)/$(PROJECT)

# Compiler & Flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft/include
CPPFLAGS    := -MMD -MP
LDFLAGS     := -Llibft/bin -lft -lreadline
# Debugging Flags
DEBUG_FLAGS := -g3 -O0 -DDEBUG -fsanitize=address

# Tools
RM          := rm -f
RM_RF       := rm -rf
MKDIR_P     := mkdir -p

# ============================================================================ #
#                                SOURCES                                       #
# ============================================================================ #

SRCS_STATE		:=	src/main.c \
					src/state/env_access.c \
					src/state/env_modify_0.c \
					src/state/env_modify_1.c \
					src/state/signals.c \
					src/state/shell_state.c

SRCS_LEXER		:=	src/lexer/lexer.c \
					src/lexer/token.c \
					src/lexer/scanner.c

SRCS_PARSER		:=	src/parser/parser.c \
					src/parser/parse_cmd.c \
					src/parser/parse_job.c \
					src/parser/parse_redir.c \
					src/parser/context.c \
					src/parser/ast_node.c

SRCS_EXPANDER	:=	src/expander/expander.c \
					src/expander/core_helpers.c \
					src/expander/core.c \
					src/expander/expander_helpers.c \
					src/expander/vars.c \
					src/expander/builder.c

SRCS_EXEC		:=	src/execution/executor.c \
					src/execution/redirections.c \
					src/execution/cmd.c \
					src/execution/child.c \
					src/execution/pipe.c \
					src/execution/utils.c

SRCS_HEREDOC	:=	src/heredoc/heredoc.c \
					src/heredoc/read.c \
					src/heredoc/expand.c \
					src/heredoc/expand_helpers.c \
					src/heredoc/utils.c

SRCS_SHELL		:=	src/shell/arena.c \
					src/shell/input.c \
					src/shell/loop.c

SRCS_BUILTINS	:=	src/builtins/builtins.c \
					src/builtins/echo.c \
					src/builtins/cd.c \
					src/builtins/pwd.c \
					src/builtins/export.c \
					src/builtins/export_helpers.c \
					src/builtins/unset.c \
					src/builtins/env.c \
					src/builtins/exit.c

SRCS_ERROR		:=	src/errors/error.c

SRCS		:= $(SRCS_STATE) $(SRCS_LEXER) $(SRCS_PARSER) $(SRCS_EXPANDER) $(SRCS_EXEC) $(SRCS_HEREDOC) $(SRCS_BUILTINS) $(SRCS_SHELL) $(SRCS_ERROR)

# ============================================================================ #
#                                OBJECTS                                       #
# ============================================================================ #

OBJS		:=	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_DEBUG	:=	$(patsubst src/%.c,$(OBJ_DIR)/%.debug.o,$(SRCS))
DEPS		:=	$(OBJS:.o=.d) $(OBJS_DEBUG:.o=.d)
LIBFT		:=	libft/bin/libft.a

# ============================================================================ #
#                                TARGETS                                       #
# ============================================================================ #

.PHONY: all clean fclean re debug valgrind run

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(LIBFT):
	@make -C libft --no-print-directory

# ============================================================================ #
#                             COMPILATION RULES                                #
# ============================================================================ #

$(OBJ_DIR)/%.o: src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.debug.o: src/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# ============================================================================ #
#                               DEBUG MODES                                    #
# ============================================================================ #

debug: $(LIBFT) $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) $(LDFLAGS) -o $(NAME)

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

# ============================================================================ #
#                                CLEANUP                                       #
# ============================================================================ #

clean:
	@$(RM_RF) $(OBJ_DIR)
	@make -C libft clean --no-print-directory

fclean: clean
	@$(RM_RF) $(BIN_DIR)
	@make -C libft fclean --no-print-directory

re: fclean all
