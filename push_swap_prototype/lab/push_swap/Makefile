# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = $(SRC_DIR)/models.h

# Default target
all: $(BIN_DIR)/$(NAME)

# Create binary directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build the executable
$(BIN_DIR)/$(NAME): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything including executable
fclean: clean
	rm -rf $(BIN_DIR)

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

