#!/bin/bash
source "$(dirname "$0")/utils.sh"

run_test 'echo "hello world"' "Simple double quotes with spaces"
run_test 'echo "cat lol.c | cat > lol.c"' "Command from assignment in double quotes"
run_test 'echo "   spaces   at   edges   "' "Double quotes with multiple spaces"
run_test 'echo "hello" "world"' "Multiple double quoted strings"
run_test 'echo "hello""world"' "Adjacent double quoted strings"
run_test 'echo "one"two"three"' "Mixed unquoted and double quoted strings"
run_test 'echo "*"' "Asterisk in double quotes (should not expand)"
run_test 'echo "> < >> |"' "Redirection and pipe characters in double quotes"
run_test 'echo ""' "Empty double quotes"

echo -e "\n=== TESTING: SIMPLE QUOTES ==="

run_test "echo 'hello world'" "Simple single quotes with spaces"
run_test "echo ''" "Empty single quotes"
run_test "echo ' '" "Single quotes with a single space"
run_test "echo '  spaces  '" "Single quotes with multiple spaces"
run_test "echo '$USER'" "Env variable in single quotes (must NOT expand)"
run_test "echo '$PATH'" "Another env variable in single quotes"
run_test "echo 'cat lol.c | cat > lol.c'" "Pipes and redirections in single quotes"
run_test "echo 'hello' 'world'" "Multiple single quoted strings"
run_test "echo 'hello''world'" "Adjacent single quoted strings"
run_test "echo 'one'two'three'" "Mixed unquoted and single quoted strings"
run_test "echo '*'" "Asterisk in single quotes"

echo -e "\n=== TESTING: MIXED QUOTES & CONCATENATION ==="

run_test 'echo "hello '\''world'\''"' "Single quotes inside double quotes"
run_test "echo 'hello \"world\"'" "Double quotes inside single quotes"
run_test 'echo "$USER"Desktop' "Concatenate expansion with unquoted string"
run_test 'echo '\''$USER'\''"$USER"' "Concatenate single quotes with expanded double quotes"

end_tests
