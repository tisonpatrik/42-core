NAME        := bin/libft.a
BIN_DIR     := bin
MAKEFLAGS   += --silent

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude

AR          := ar
ARFLAGS     := rcs
RM          := rm -f

# ---- Sources ---------------------------------------------------------------

SRCS        := $(shell find src -iname '*.c' -not -path 'src/list/*')

ifdef BONUS
  SRCS      += $(shell find src/list -iname '*.c')
endif

OBJS        := $(SRCS:src/%.c=$(BIN_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# ---- Rules -----------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS) | $(BIN_DIR)
	@$(AR) $(ARFLAGS) $@ $(OBJS)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: src/%.c | $(BIN_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

-include $(DEPS)

bonus:
	@$(MAKE) BONUS=1 all

# ---- Cleaning --------------------------------------------------------------

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) -r $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re bonus