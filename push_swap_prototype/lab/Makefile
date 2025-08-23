# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinclude -Ilibs/push_swap/src -Ilibs/cJSON

# Directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
PUSH_SWAP_SRC_DIR = libs/push_swap/src
CJSON_SRC_DIR = libs/cJSON

# Source files with main functions (these will become executables)
MAIN_SRCS = $(SRC_DIR)/main.c

# Utility source files (no main function)
UTIL_SRCS = $(wildcard $(SRC_DIR)/utils/*.c)
TASK_SRCS = $(wildcard $(SRC_DIR)/tasks/*.c)

# Push swap source files needed for the tests
PUSH_SWAP_SRCS = $(PUSH_SWAP_SRC_DIR)/chunk_utils.c $(PUSH_SWAP_SRC_DIR)/stack_utils.c

# cJSON library source files
CJSON_SRCS = $(CJSON_SRC_DIR)/cJSON.c

# Target executables (one for each main source file)
TARGETS = $(BIN_DIR)/main

# Default target
all: $(TARGETS)

# Create directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build main executable
$(BIN_DIR)/main: $(SRC_DIR)/main.c $(UTIL_SRCS) $(TASK_SRCS) $(PUSH_SWAP_SRCS) $(CJSON_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Clean everything including executables
clean:
	rm -rf $(BIN_DIR)

# Clean everything including executables
fclean: clean

# Rebuild everything
re: fclean all

# Run specific executables
run-main: $(BIN_DIR)/main
	./$(BIN_DIR)/main

# Test target - run the test suite
test: $(BIN_DIR)/main
	./$(BIN_DIR)/main

# Phony targets
.PHONY: all clean fclean re run-main test

# Default target
.DEFAULT_GOAL = all
