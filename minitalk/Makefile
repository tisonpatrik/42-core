# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/24 15:07:17 by ptison            #+#    #+#              #
#    Updated: 2025/09/24 15:12:44 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME  := bin/client
SERVER_NAME  := bin/server
MAKEFLAGS    += --silent

CC           := cc
CFLAGS       := -Wall -Wextra -Werror -Iinclude -Ilibft/include
LDFLAGS      := -Llibft/bin
LDLIBS       := -lft

RM           := rm -f

CLIENT_SRCS  := src/client.c
SERVER_SRCS  := src/server.c

CLIENT_OBJS  := $(patsubst src/%.c,bin/%.o,$(CLIENT_SRCS))
SERVER_OBJS  := $(patsubst src/%.c,bin/%.o,$(SERVER_SRCS))
CLIENT_DEPS  := $(CLIENT_OBJS:.o=.d)
SERVER_DEPS  := $(SERVER_OBJS:.o=.d)

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(CLIENT_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(SERVER_NAME): $(SERVER_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(SERVER_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

libft/bin/libft.a:
	@$(MAKE) -C libft

clean:
	@find bin/ -name "*.o" -delete 2>/dev/null || true
	@find bin/ -name "*.d" -delete 2>/dev/null || true
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true

fclean: clean
	@$(RM) -r bin/
	@$(MAKE) -C libft fclean

re: fclean all

-include $(CLIENT_DEPS)
-include $(SERVER_DEPS)

.PHONY: all clean fclean re