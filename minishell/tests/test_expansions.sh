#!/bin/bash

# Load common functions and variables (utils)
source "$(dirname "$0")/utils.sh"

# --- ENVIRONMENT VARIABLES & EXPANSION ---
run_test "Variables" "Basic expansion" "echo \$USER"
run_test "Variables" "Multiple variables" "echo \$USER \$PATH"
run_test "Variables" "Double quotes interpolation" "echo \"Value: \$USER\""
run_test "Variables" "Single quotes (no interpolation)" "echo '\$USER'"
run_test "Variables" "Non-existent variable" "echo \$THIS_DOES_NOT_EXIST"
run_test "Variables" "Set and check USER" "export USER=evaluator\necho \"\$USER\""

# --- ENV / EXPORT / UNSET ---
run_test "Env/Export" "Export and check" "export TEST_VAR=42\nenv | grep TEST_VAR"
run_test "Env/Export" "Replace value" "export TEST_VAR=1\nexport TEST_VAR=99\nenv | grep TEST_VAR"
run_test "Unset" "Unset variable" "export TO_DELETE=bye\nunset TO_DELETE\nenv | grep TO_DELETE"

# --- CD & PWD ---
run_test "CD" "Move and check with /bin/ls" "mkdir -p target\ncd target\n/bin/ls ..\npwd"
run_test "CD" "CD to dot and dot-dot" "cd .\npwd\ncd ..\npwd"
run_test "CD" "CD minus (last dir)" "mkdir -p dir1 dir2\ncd dir1\ncd ../dir2\ncd -\npwd"

# --- RELATIVE & ENVIRONMENT PATH ---
run_test "Path" "Complex relative path" "mkdir -p a/b/c\ncd a/b/c\n../../../bin/ls ../../.."
run_test "Path" "Unset PATH" "unset PATH\nls"
run_test "Path" "Left-to-right PATH check" "mkdir -p d1 d2\necho '#!/bin/sh' > d1/cmd\necho 'echo one' >> d1/cmd\necho '#!/bin/sh' > d2/cmd\necho 'echo two' >> d2/cmd\nchmod +x d1/cmd d2/cmd\nexport PATH=\$PWD/d1:\$PWD/d2\ncmd"

# --- REDIRECTIONS ---
run_test "Redir" "Simple > and <" "echo content > out.txt\ncat < out.txt"
run_test "Redir" "Append >>" "echo line1 > app.txt\necho line2 >> app.txt\ncat app.txt"
run_test "Redir" "Multiple of same redir" "echo a > f1 > f2\ncat f1\ncat f2"

# --- PIPES ---
run_test "Pipes" "Simple pipe" "cat file.txt | grep initial"
run_test "Pipes" "Multi pipe" "echo abc | tr a-z A-Z | sed 's/A/X/'"
run_test "Pipes" "Failing command in pipe" "ls non_existent | grep bla | wc -l"

# --- GO CRAZY (Robustness) ---
run_test "Robustness" "Non-existent command" "dsbkdsgbksdghsd"
run_test "Robustness" "Empty command" ""
LONG_STR="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100"
run_test "Robustness" "Long command with many args" "echo $LONG_STR"

end_tests
