# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Header files
HEADERS = $(SRC_DIR)/models.h

# Default target
all: $(BIN_DIR)/$(NAME)

# Create binary directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the executable (compiles directly from source)
$(BIN_DIR)/$(NAME): $(SRCS) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $@

# Clean everything including executable
clean:
	rm -rf $(BIN_DIR)

# Clean everything including executable
fclean: clean

# Rebuild everything
re: fclean all

# Run the program (you can modify the arguments as needed)
run: $(BIN_DIR)/$(NAME)
	@echo "Running $(NAME)..."
	@echo "Example usage: ./$(BIN_DIR)/$(NAME) 2 1 3 6 5 8"
	@echo "Or use: make test"

# Test with some sample numbers
test: $(BIN_DIR)/$(NAME)
	@echo "Testing with sample numbers: 2 1 3 6 5 8"
	./$(BIN_DIR)/$(NAME) 2 1 3 6 5 8

# Test with more numbers
test_large: $(BIN_DIR)/$(NAME)
	@echo "Testing with 100 random numbers..."
	./$(BIN_DIR)/$(NAME) 64 23 45 12 78 90 34 56 67 89 1 2 3 4 5 6 7 8 9 10

# Phony targets
.PHONY: all clean fclean re run test test_large

# Default target
.DEFAULT_GOAL = all

