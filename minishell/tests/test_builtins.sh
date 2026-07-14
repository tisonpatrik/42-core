#!/bin/bash
source "$(dirname "$0")/utils.sh"

run_test "echo" "Empty echo"
run_test "echo hello" "Simple echo"
run_test "echo -n hello" "Echo with -n flag"
run_test "echo -n" "Echo only -n flag"
run_test "echo -nnnnn hello" "Echo with combined -n flag"
run_test "echo -n -n -n hello" "Echo with multiple separate -n flags"
run_test "echo -n -nnn -n hello" "Echo with mixed -n flags"
run_test "echo -nhello" "Echo invalid flag -nhello"
run_test "echo -n -m hello" "Echo valid flag followed by invalid"
run_test "echo hello -n" "Echo flag after string (should print -n)"
run_test "echo -n -n -nnnn hello -n" "Complex echo sequence"

run_test "exit" "Basic exit"
run_test "exit 42" "Exit with valid positive code"
run_test "exit -42" "Exit with negative code"
run_test "exit 255" "Exit with 255"
run_test "exit 256" "Exit with 256 (overflows to 0)"
run_test "exit 999" "Exit with 999 (modulo 256)"
run_test "exit +42" "Exit with explicit positive sign"
run_test "exit 042" "Exit with leading zero"
run_test "exit 9223372036854775807" "Exit with LLONG_MAX"
run_test "exit -9223372036854775808" "Exit with LLONG_MIN"

run_test "exit abc" "Exit with non-numeric argument"
run_test "exit 1 2 3" "Exit with too many arguments"
run_test "exit | echo a" "Exit inside a pipeline"

end_tests
