#!/bin/bash

source "$(dirname "$0")/utils.sh"

run_test "/bin/echo ok\necho \$?" "Success command followed by echo \$?"
run_test "/bin/nonexistentcmd\necho \$?" "Non-existent command followed by echo \$?"
run_test "/bin/ls /this/dir/does/not/exist\necho \$?" "Failing command followed by echo \$?"
run_test "/bin/ls /fail\nexpr \$? + \$?" "Testing expr \$? + \$? after failure"
run_test "/bin/echo \"funguje to\"\necho \$?" "Success command followed by echo \$?"
run_test "/bin/ls /fail\n   \necho \$?" "Preserve \$? after empty line/spaces"

end_tests
