#!/bin/bash

# Memory and file descriptor leak tests
source "$(dirname "$0")/utils.sh"

VALGRIND_AVAILABLE=0
if command -v valgrind &> /dev/null; then
    VALGRIND_AVAILABLE=1
fi

LEAKS_AVAILABLE=0
if command -v leaks &> /dev/null; then
    LEAKS_AVAILABLE=1
fi

# Function to run command and check for leaks
run_leak_test() {
    local desc="$1"
    local cmd="$2"
    
    echo "Testing: $desc"
    echo "Command: $cmd"
    
    if [ $VALGRIND_AVAILABLE -eq 1 ]; then
        valgrind --leak-check=full --error-exitcode=42 bash -c "echo '$cmd' | $MINISHELL" 2>&1 | grep -E "(definitely lost|indirectly lost|ERROR SUMMARY)"
    else
        echo "  [SKIP] valgrind not available"
    fi
    
    if [ $LEAKS_AVAILABLE -eq 1 ]; then
        leaks -atExit -- $MINISHELL -c "$cmd" 2>&1 | grep -E "(leaks|Process)"
    else
        echo "  [SKIP] leaks (macOS) not available"
    fi
    
    echo ""
}

# Test file descriptors after pipes
run_test "FD after pipe" "File descriptors after pipe chain" "echo test | cat | wc -l"

# Multiple sequential pipes
run_test "Sequential pipes" "Multiple sequential pipes" "echo a | cat | cat | cat | cat"

# Redirections and cleanup
run_test "FD after redirect" "File descriptors after redirect" "echo hello > test_out.txt\ncat test_out.txt"

# Subshell handling
run_test "Subshell" "Subshell with variable" "(export X=1; echo \$X)"

# Here documents
run_test "Heredoc FD" "File descriptor after heredoc" "<< EOF cat\ntest line\nEOF"

# Multiple redirections
run_test "Multi redirect FD" "FD after multiple redirects" "echo one > f1 > f2 > f3\ncat f3"

# Exit and check
run_test "Exit cleanup" "Exit and verify no fds leaked" "exit 0"

# Complex command with errors
run_test "Error FD" "FD after syntax error" "echo \"unclosed"

# If valgrind is available, run specific leak tests
if [ $VALGRIND_AVAILABLE -eq 1 ]; then
    echo "=== Running valgrind memory leak checks ==="
    
    # Simple command
    echo "Testing: echo hello"
    valgrind --leak-check=full --error-exitcode=42 bash -c "echo hello | $MINISHELL" 2>&1 | tail -5
    
    # Exit command
    echo "Testing: exit 0"
    valgrind --leak-check=full --error-exitcode=42 bash -c "exit 0 | $MINISHELL" 2>&1 | tail -5
fi

echo ""
echo "Note: For full leak testing, run manually with:"
echo "  valgrind --leak-check=full --show-leak-kinds=all ./bin/minishell"
echo "  leaks -atExit -- ./bin/minishell"

end_tests
