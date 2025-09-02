# Test Makefile for Push Swap Operations
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I../libft/include
LIBFT = ../libft/libft.a

# Directories
BIN_DIR = bin
TEST_SRCS = $(wildcard *.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BIN_DIR)/%.o)
TEST_BIN = $(BIN_DIR)/test_operations

# Explicitly list all project source files needed for tests
PROJECT_SRCS = ../src/stack/stack.c \
               ../src/stack/ops.c \
               ../src/stack/node.c \
               ../src/ops/push.c \
               ../src/ops/swap.c \
               ../src/ops/rotate.c \
               ../src/ops/reverse_rotate.c \
               ../src/ops/sorting_state.c \
               ../src/utils/utils.c

PROJECT_OBJS = $(addprefix $(BIN_DIR)/,$(notdir $(PROJECT_SRCS:.c=.o)))

.PHONY: all clean test

# Main test target - builds, runs, and cleans
test: $(BIN_DIR) $(TEST_BIN)
	@echo "🧪 Running tests..."
	@./$(TEST_BIN)
	@echo "🧹 Cleaning up..."
	@$(MAKE) clean

# Create bin directory
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Build test binary
$(TEST_BIN): $(TEST_OBJS) $(PROJECT_OBJS) $(LIBFT)
	@echo "🔨 Building test binary..."
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(PROJECT_OBJS) $(LIBFT) -o $(TEST_BIN)

# Pattern rule for test source files
$(BIN_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Explicit rules for project source files
$(BIN_DIR)/stack.o: ../src/stack/stack.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/ops.o: ../src/stack/ops.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/node.o: ../src/stack/node.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/push.o: ../src/ops/push.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/swap.o: ../src/ops/swap.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/rotate.o: ../src/ops/rotate.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/reverse_rotate.o: ../src/ops/reverse_rotate.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/sorting_state.o: ../src/ops/sorting_state.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/utils.o: ../src/utils/utils.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Build libft if needed
$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -C ../libft bonus

# Clean all binaries and objects
clean:
	@rm -rf $(BIN_DIR)
	@echo "✨ Clean complete!"
