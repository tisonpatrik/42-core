#!/bin/bash

# Load common functions and variables (utils)
source "$(dirname "$0")/utils.sh"

# --- TESTS ---

# Standard absolute paths with basic arguments
run_test "/bin/echo hello" "Basic absolute path with one arg"
run_test "/bin/echo hello world test" "Absolute path with multiple args"
run_test "/bin/ls -a" "Command with separated flags"
run_test "/bin/ls" "Command without flags"

# Aggressive whitespace handling (testing the lexer)
run_test "/bin/echo    lots    of    spaces" "Multiple spaces between args"
run_test "/bin/echo \ttabs\t and spaces" "Mixed tabs and spaces"
run_test "    /bin/echo leading spaces" "Leading spaces before command"
run_test "/bin/echo trailing spaces    " "Trailing spaces after command"

# Special characters (unquoted)
run_test "/bin/echo foo,bar" "Comma in arg"
run_test "/bin/echo foo=bar" "Equal sign in arg"
run_test "/bin/echo foo/bar/baz" "Slashes in arg"
run_test "/bin/echo @#%^+-" "Various safe symbols"

# Path resolution tests
run_test "ls" "Relative command (relying on PATH)"
run_test "echo test" "Relative builtin command"

# --- END ---
end_tests
