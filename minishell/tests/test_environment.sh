#!/bin/bash

# Environment edge case tests
source "$(dirname "$0")/utils.sh"

# Note: Some tests require special invocation (env -i)
# These are marked and should be run separately if needed

run_test "Env export" "Export variable" "export TEST_VAR=hello\necho \$TEST_VAR"
run_test "Env unset" "Unset variable" "export TO_DELETE=bye\nunset TO_DELETE\nenv | grep TO_DELETE"
run_test "Env overwrite" "Overwrite existing var" "export HOME=/new/home\necho \$HOME"

run_test "Empty export" "Export with empty value" "export EMPTY=\necho \"VAL:'\$EMPTY'\""
run_test "Export special chars" "Export with special chars" "export SPECIAL='a b c'\necho \$SPECIAL"

run_test "Multiple exports" "Multiple exports" "export A=1 B=2 C=3\nenv | grep -E '^[ABC]='"

run_test "Unset PATH" "Unset PATH (should fail gracefully)" "unset PATH\nls"
run_test "Unset HOME" "Unset HOME" "unset HOME\ncd ~"

run_test "Env with equals" "Variable with = in value" "export VAR=hello=world\necho \$VAR"

run_test "Export existing" "Export already exported var" "export USER=test\nexport USER\nenv | grep USER"

run_test "Unset readonly" "Try to unset readonly (should fail)" "unset HOME"

end_tests
