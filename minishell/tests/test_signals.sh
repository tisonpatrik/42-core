#!/bin/bash

# Load common functions and variables (utils)
source "$(dirname "$0")/utils.sh"

if ! command -v python3 &> /dev/null; then
    echo -e "${RED}Error: python3 not found. Cannot run PTY signal tests.${RESET}"
    ((FAILED_TESTS++))
    end_tests
fi

# Generate temporary python script for signal testing
cat << 'EOF' > run_pty_test.py
import os, pty, select, time, sys, re

MINISHELL = sys.argv[1]
PROMPT = "minishell"

GREEN = "\033[0;32m"
RED = "\033[0;31m"
YELLOW = "\033[1;33m"
CYAN = "\033[1;36m"
RESET = "\033[0m"

failed_tests = 0

def strip_ansi(text):
    ansi_escape = re.compile(r'(?:\x1B[@-_]|[\x80-\x9F])[0-?]*[ -/]*[@-~]')
    return ansi_escape.sub('', text)

def run_tests():
    global failed_tests
    pid, fd = pty.fork()

    if pid == 0:
        os.execv(MINISHELL, [MINISHELL])
    else:
        def read_output(delay=0.5):
            time.sleep(delay)
            out = b""
            while select.select([fd], [], [], 0.1)[0]:
                try:
                    data = os.read(fd, 1024)
                    if not data: break
                    out += data
                except OSError:
                    break
            return strip_ansi(out.decode('utf-8', 'replace'))

        def assert_test(desc, send_bytes, expect_in=[], not_expect_in=[], max_prompts=None, delay=0.5):
            global failed_tests
            if send_bytes:
                os.write(fd, send_bytes)

            actual = read_output(delay)
            passed = True
            error_msg = []

            for exp in expect_in:
                if exp not in actual:
                    passed = False
                    error_msg.append(f"Missing expected text: '{exp}'")

            for n_exp in not_expect_in:
                if n_exp in actual:
                    passed = False
                    error_msg.append(f"Found forbidden text: '{n_exp}'")

            if max_prompts is not None:
                prompt_count = actual.count(PROMPT)
                if prompt_count > max_prompts:
                    passed = False
                    error_msg.append(f"Too many prompts! Expected max: {max_prompts}, found: {prompt_count}")

            if passed:
                print(f"{GREEN}[OK]{RESET} {desc}")
            else:
                print(f"{RED}[KO]{RESET} {desc}")
                for err in error_msg:
                    print(f"   {RED}-> {err}{RESET}")
                safe_actual = actual.replace('\r', '\\r').replace('\n', '\\n\n      ')
                print(f"   {YELLOW}ACTUAL OUTPUT:{RESET}\n      {safe_actual}")
                failed_tests += 1
            return passed

        read_output(0.5) # Discard initial prompt on startup

        assert_test("Ctrl-\\ (SIGQUIT) on empty prompt", b'\x1c',
                    expect_in=[], not_expect_in=["Quit"], max_prompts=0)

        assert_test("Ctrl-C (SIGINT) on empty prompt", b'\x03',
                    expect_in=["^C", PROMPT], not_expect_in=[], max_prompts=1)

        os.write(fd, b'echo typed_text')
        read_output(0.5) # Let it output the text

        assert_test("Ctrl-D (EOF) with typed text", b'\x04',
                    expect_in=[], not_expect_in=["exit"], max_prompts=0)

        assert_test("Ctrl-\\ (SIGQUIT) with typed text", b'\x1c',
                    expect_in=[], not_expect_in=["Quit"], max_prompts=0)

        assert_test("Ctrl-C (SIGINT) with typed text", b'\x03',
                    expect_in=["^C", PROMPT], not_expect_in=["typed_text"], max_prompts=1)

        # Blocking commands (cat)
        os.write(fd, b'cat\n')
        read_output(0.5)
        assert_test("Ctrl-C on running 'cat'", b'\x03',
                    expect_in=["^C", PROMPT], not_expect_in=[], max_prompts=1)

        os.write(fd, b'cat\n')
        read_output(0.5)
        assert_test("Ctrl-\\ on running 'cat' (SIGQUIT)", b'\x1c',
                    expect_in=["Quit", PROMPT], not_expect_in=[], max_prompts=1)

        os.write(fd, b'cat\n')
        read_output(0.5)
        assert_test("Ctrl-D on running 'cat' (EOF)", b'\x04',
                    expect_in=[PROMPT], not_expect_in=["^D", "Quit"], max_prompts=1)

        # Cleanup and exit
        try:
            os.write(fd, b'\x04\nexit\n')
            time.sleep(0.2)
            os.kill(pid, 9)
            os.waitpid(pid, 0)
        except Exception:
            pass
        os.close(fd)

run_tests()
sys.exit(1 if failed_tests > 0 else 0)
EOF

# Run generated script with minishell path
python3 run_pty_test.py "$MINISHELL"
if [ $? -ne 0 ]; then
    ((FAILED_TESTS++))
fi

rm -f run_pty_test.py

# Evaluation (if failed_tests > 0, returns exit 1)
end_tests
