#!/bin/bash
source "$(dirname "$0")/utils.sh"

# --- ENVIRONMENT VARIABLES & EXPANSION ---
run_test "echo \$USER" "Basic expansion"
run_test "echo \$USER \$PATH" "Multiple variables"
run_test "echo \"Value: \$USER\"" "Double quotes interpolation"
run_test "echo '\$USER'" "Single quotes (no interpolation)"
run_test "echo \$THIS_DOES_NOT_EXIST" "Non-existent variable"
run_test "export USER=evaluator\necho \"\$USER\"" "Set and check USER"
run_test "export EMPTY=\necho a \$EMPTY b \$NONEXISTENT c" "Empty and non-existent variables expansion"

# --- ENV / EXPORT / UNSET ---
run_test "export TEST_VAR=42\nenv | grep TEST_VAR" "Export and check"
run_test "export TEST_VAR=1\nexport TEST_VAR=99\nenv | grep TEST_VAR" "Replace value"
run_test "export TO_DELETE=bye\nunset TO_DELETE\nenv | grep TO_DELETE" "Unset variable"
run_test "export 1VAR=test" "Invalid export identifier (starts with number)"
run_test "export VAR-NAME=test" "Invalid export identifier (contains dash)"

# --- CD & PWD ---
run_test "mkdir -p target\ncd target\n/bin/ls ..\npwd" "Move and check with /bin/ls"
run_test "cd .\npwd\ncd ..\npwd" "CD to dot and dot-dot"
run_test "mkdir -p dir1 dir2\ncd dir1\ncd ../dir2\ncd -\npwd" "CD minus (last dir)"

# --- RELATIVE & ENVIRONMENT PATH ---
run_test "mkdir -p a/b/c\ncd a/b/c\n../../../bin/ls ../../.." "Complex relative path"
run_test "unset PATH\nls" "Unset PATH"
run_test "mkdir -p d1 d2\necho '#!/bin/sh' > d1/cmd\necho 'echo one' >> d1/cmd\necho '#!/bin/sh' > d2/cmd\necho 'echo two' >> d2/cmd\nchmod +x d1/cmd d2/cmd\nexport PATH=\$PWD/d1:\$PWD/d2\ncmd" "Left-to-right PATH check"

# --- REDIRECTIONS ---
run_test "echo content > out.txt\ncat < out.txt" "Simple > and <"
run_test "echo line1 > app.txt\necho line2 >> app.txt\ncat app.txt" "Append >>"
run_test "echo a > f1 > f2 > f3\ncat f1\ncat f2\ncat f3" "Multiple redirections on same command"
run_test "> file_only" "Redirection without command"
run_test "< no_file" "Input redirection from non-existent file"
run_test "cat << EOF\nline1\nline2\nEOF\n" "Basic heredoc"

# --- PIPES ---
run_test "cat file.txt | grep initial" "Simple pipe"
run_test "echo abc | tr a-z A-Z | sed 's/A/X/'" "Multi pipe"
run_test "ls non_existent | grep bla | wc -l" "Failing command at start of pipe"
run_test "echo hi | cat non_existent_file | wc -l" "Failing command in the middle of a pipe"

# --- GO CRAZY (Robustness) ---
run_test "dsbkdsgbksdghsd" "Non-existent command"
run_test "" "Empty command"
LONG_STR="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100"
run_test "echo $LONG_STR" "Long command with many args"

end_tests
