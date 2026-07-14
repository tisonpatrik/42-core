#!/bin/bash

# Syntax error tests - verify parser detects errors without crashing
source "$(dirname "$0")/utils.sh"

# Pipe without command
run_test "Pipe without command" "Pipe without left command" "echo test | cat"

# Double pipe
run_test "Double pipe" "Double pipe syntax error" "cat | | wc"

# Redirection errors
run_test "Redirection error" "Output then input error" "echo > <"
run_test "Double redirect" "Double output redirect error" ">> > file"
run_test "Redirect without target" "Redirect with no target" "echo >"

# Unclosed quotes (shell should not crash)
run_test "Unclosed double" "Unclosed double quote" "echo \"unclosed"
run_test "Unclosed single" "Unclosed single quote" "echo 'unclosed"
run_test "Unclosed mixed" "Unclosed mixed quotes" "echo \"hello'"

# Missing command
run_test "Just pipe" "Just pipe symbol" "|"
run_test "Multiple pipes" "Multiple pipes with no command" "||"
run_test "Just redirect" "Just redirect symbol" "> file"

# Invalid sequences
run_test "Invalid sequence" "Invalid command sequence" ";;"
run_test "Semicolon pipe" "Semicolon followed by pipe" ";|"

end_tests
