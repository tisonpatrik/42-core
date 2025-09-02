# Test Makefile for Push Swap Operations
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I../libft/include
LIBFT = ../libft/libft.a

# Directories
BIN_DIR = bin
TEST_SRCS = $(wildcard *.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BIN_DIR)/%.o)
TEST_BIN = $(BIN_DIR)/test_operations

# Automatically find all project source files
PROJECT_SRCS = $(wildcard ../src/**/*.c)
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

# Pattern rule for all source files
$(BIN_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Pattern rules for project source files (flattened)
$(BIN_DIR)/%.o: ../src/stack/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: ../src/ops/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Build libft if needed
$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -C ../libft bonus

# Clean all binaries and objects
clean:
	@rm -rf $(BIN_DIR)
	@echo "✨ Clean complete!"
