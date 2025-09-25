# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptison <ptison@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/24 15:07:17 by ptison            #+#    #+#              #
#    Updated: 2025/09/25 10:06:41 by ptison           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME  := bin/client
SERVER_NAME  := bin/server
LATENCY_NAME := bin/latency_test
STRESS_NAME  := bin/stress_test
MAKEFLAGS    += --silent

CC           := cc
CFLAGS       := -Wall -Wextra -Werror -Iinclude -Ilibft/include
LDFLAGS      := -Llibft/bin
LDLIBS       := -lft

RM           := rm -f

CLIENT_SRCS  := src/client.c
SERVER_SRCS  := src/server.c
LATENCY_SRCS := test/latency_test.c
STRESS_SRCS  := test/stress_test.c

CLIENT_OBJS  := $(patsubst src/%.c,bin/%.o,$(CLIENT_SRCS))
SERVER_OBJS  := $(patsubst src/%.c,bin/%.o,$(SERVER_SRCS))
LATENCY_OBJS := $(patsubst test/%.c,bin/%.o,$(LATENCY_SRCS))
STRESS_OBJS  := $(patsubst test/%.c,bin/%.o,$(STRESS_SRCS))
CLIENT_DEPS  := $(CLIENT_OBJS:.o=.d)
SERVER_DEPS  := $(SERVER_OBJS:.o=.d)
LATENCY_DEPS := $(LATENCY_OBJS:.o=.d)
STRESS_DEPS  := $(STRESS_OBJS:.o=.d)

all: $(CLIENT_NAME) $(SERVER_NAME) $(LATENCY_NAME) $(STRESS_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(CLIENT_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(SERVER_NAME): $(SERVER_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(SERVER_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(LATENCY_NAME): $(LATENCY_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(LATENCY_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(STRESS_NAME): $(STRESS_OBJS) | libft/bin/libft.a
	@mkdir -p bin/
	@$(CC) $(STRESS_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bin/%.o: test/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

libft/bin/libft.a:
	@$(MAKE) -C libft

clean:
	@find bin/ -name "*.o" -delete 2>/dev/null || true
	@find bin/ -name "*.d" -delete 2>/dev/null || true
	@find src/ -name "*.o" -delete 2>/dev/null || true
	@find src/ -name "*.d" -delete 2>/dev/null || true
	@find test/ -name "*.o" -delete 2>/dev/null || true
	@find test/ -name "*.d" -delete 2>/dev/null || true

fclean: clean
	@$(RM) -r bin/
	@$(MAKE) -C libft fclean

re: fclean all

-include $(CLIENT_DEPS)
-include $(SERVER_DEPS)
-include $(LATENCY_DEPS)
-include $(STRESS_DEPS)

.PHONY: all clean fclean re