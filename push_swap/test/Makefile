# Test Makefile for Push Swap Operations
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I../libft/include
LIBFT = ../libft/bin/libft.a

# Directories
BIN_DIR = bin
TEST_SRCS = test_main.c test_swap.c test_push.c test_rotate.c test_reverse_rotate.c test_is_sorted.c test_snapshot_stack.c test_apply_combined.c test_align_min_to_top.c test_indexize_array.c test_separator.c test_find_target_position.c
TEST_OBJS = $(TEST_SRCS:%.c=$(BIN_DIR)/%.o)
TEST_BIN = $(BIN_DIR)/test_main

# Explicitly list all project source files needed for tests
PROJECT_SRCS = ../src/stack/stack.c \
               ../src/stack/ops.c \
               ../src/stack/node.c \
               ../src/stack/tools.c \
               ../src/ops/push.c \
               ../src/ops/swap.c \
               ../src/ops/rotate.c \
               ../src/ops/reverse_rotate.c \
               ../src/ops/sorting_state.c \
               ../src/utils/utils.c \
               ../src/validator/input_parser.c \
               ../src/validator/tokenizer.c \
               ../src/validator/normalization.c \
               ../src/separator/list_arena.c \
               ../src/separator/algo.c \
               ../src/separator/result_builder.c \
               ../src/separator/utils.c \
               ../src/separator/separator.c \
               ../src/selector/utils.c \
               ../src/selector/nearbest.c \
               ../src/selector/lookahead_evaluator.c \
               ../src/selector/candidate_enumerator.c \
               ../src/selector/result_builder.c \
               ../src/selector/selector_arena.c \
               ../src/selector/snapshot_arena.c \
               ../src/solver/apply_combined.c \
               ../src/solver/align_min_to_top.c

PROJECT_OBJS = $(BIN_DIR)/stack.o \
               $(BIN_DIR)/ops.o \
               $(BIN_DIR)/node.o \
               $(BIN_DIR)/tools.o \
               $(BIN_DIR)/push.o \
               $(BIN_DIR)/swap.o \
               $(BIN_DIR)/rotate.o \
               $(BIN_DIR)/reverse_rotate.o \
               $(BIN_DIR)/sorting_state.o \
               $(BIN_DIR)/utils.o \
               $(BIN_DIR)/input_parser.o \
               $(BIN_DIR)/tokenizer.o \
               $(BIN_DIR)/normalization.o \
               $(BIN_DIR)/list_arena.o \
               $(BIN_DIR)/separator_algo.o \
               $(BIN_DIR)/separator_result_builder.o \
               $(BIN_DIR)/separator_utils.o \
               $(BIN_DIR)/separator.o \
               $(BIN_DIR)/selector_utils.o \
               $(BIN_DIR)/nearbest.o \
               $(BIN_DIR)/lookahead_evaluator.o \
               $(BIN_DIR)/candidate_enumerator.o \
               $(BIN_DIR)/selector_result_builder.o \
               $(BIN_DIR)/selector_arena.o \
               $(BIN_DIR)/snapshot_arena.o \
               $(BIN_DIR)/apply_combined.o \
               $(BIN_DIR)/align_min_to_top.o

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

$(BIN_DIR)/tools.o: ../src/stack/tools.c
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

$(BIN_DIR)/input_parser.o: ../src/validator/input_parser.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/tokenizer.o: ../src/validator/tokenizer.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/normalization.o: ../src/validator/normalization.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/list_arena.o: ../src/separator/list_arena.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/separator_algo.o: ../src/separator/algo.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/separator_result_builder.o: ../src/separator/result_builder.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/separator_utils.o: ../src/separator/utils.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/separator.o: ../src/separator/separator.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/selector_utils.o: ../src/selector/utils.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/nearbest.o: ../src/selector/nearbest.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/lookahead_evaluator.o: ../src/selector/lookahead_evaluator.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/candidate_enumerator.o: ../src/selector/candidate_enumerator.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/selector_result_builder.o: ../src/selector/result_builder.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/selector_arena.o: ../src/selector/selector_arena.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/snapshot_arena.o: ../src/selector/snapshot_arena.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/apply_combined.o: ../src/solver/apply_combined.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/align_min_to_top.o: ../src/solver/align_min_to_top.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Build libft if needed
$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -C ../libft bonus

# Clean all binaries and objects
clean:
	@rm -rf $(BIN_DIR)
	@echo "✨ Clean complete!"
