NAME        := push_swap
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -Ilibft
SRC_DIR     := src
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS        := $(filter-out %_bonus.c, $(wildcard $(SRC_DIR)/*.c))
OBJS        := $(SRCS:.c=.o)

SRCS_BONUS  := $(wildcard $(SRC_DIR)/*_bonus.c)
OBJS_BONUS  := $(SRCS_BONUS:.c=.o)

ifdef BONUS
SRCS        += $(SRCS_BONUS)
OBJS        := $(SRCS:.c=.o)
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

