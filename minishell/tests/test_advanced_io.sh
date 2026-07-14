#!/bin/bash

# Advanced I/O tests - multiple redirections and pipes combined
source "$(dirname "$0")/utils.sh"

# Multiple output redirections (left-to-right)
run_test "Multi redirect out" "Multiple output redirects" "echo test > file1 > file2 > file3"
run_test "Multi redirect append" "Multiple append redirects" "echo line1 >> a.txt >> b.txt >> c.txt"

# Pipe with failing command
run_test "Pipe fail" "Pipe with non-existent file" "cat neexistujici_soubor | wc -l"
run_test "Pipe grep fail" "Pipe with failing grep" "echo hello | grep nonexistent"

# Input from non-existent file
run_test "Input no file" "Input redirect from non-existent file" "< no_file"

# Output without command
run_test "Output only" "Output redirect without command" "> file_only"

# Here document with pipes
run_test "Heredoc pipe" "Heredoc combined with pipe" "<< EOF cat | grep test\nline1\nline2\ntest line\nEOF"

# Complex pipeline
run_test "Complex pipe" "Complex pipeline" "echo a | tr a-z A-Z | wc -l"
run_test "Multi pipe fail" "Multiple pipes with failure" "cat non_existent | grep x | wc -l"

# Mixed I/O
run_test "Mixed IO" "Input and output together" "cat < input.txt > output.txt"
run_test "Pipe and redirect" "Pipe with redirect" "echo test | grep t > out.txt"

# Stdin in pipe
run_test "Stdin in pipe" "Stdin in middle of pipe" "cat < file.txt | wc -l"

end_tests
