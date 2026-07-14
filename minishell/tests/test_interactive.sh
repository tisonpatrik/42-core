#!/bin/bash

# Load common functions and variables (utils)
source "$(dirname "$0")/utils.sh"

if ! command -v python3 &> /dev/null; then
    echo -e "${RED}Error: python3 not found. Cannot run interactive history tests.${RESET}"
    ((FAILED_TESTS++))
    end_tests
fi

# Generate temporary python script
cat << 'EOF' > run_interactive_test.py
import os, pty, select, time, sys, re

MINISHELL = sys.argv[1]
PROMPT = "minishell"

GREEN = "\033[0;32m"
RED = "\033[0;31m"
YELLOW = "\033[1;33m"
RESET = "\033[0m"

failed_tests = 0

def strip_ansi(text):
    ansi_escape = re.compile(r'(?:\x1B[@-_]|[\x80-\x9F])[0-?]*[ -/]*[@-~]')
    return ansi_escape.sub('', text)

def run_tests():
    global failed_tests
    pid, fd = pty.fork()

    if pid == 0:
        # Readline needs valid TERM for arrow key handling
        os.environ['TERM'] = 'xterm'
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
            return out.decode('utf-8', 'replace')

        read_output(0.5) # Discard initial prompt

        # --- TEST 1: Ctrl-C on typed command ---
        desc_ctrl_c = "Ctrl-C clears buffer (command must not run)"
        os.write(fd, b'NONEXISTENT_COMMAND_SHOULD_NOT_RUN')
        time.sleep(0.2)
        os.write(fd, b'\x03') # Send Ctrl-C
        time.sleep(0.2)
        os.write(fd, b'\n')   # Send Enter

        out_ctrl = read_output(0.5)
        # If command ran, we will see command not found error
        if "command not found" in out_ctrl or "NONEXISTENT" in strip_ansi(out_ctrl).split('\n')[-2:]:
            print(f"{RED}[KO]{RESET} {desc_ctrl_c}")
            print(f"   {YELLOW}-> Command ran even though it was interrupted with Ctrl-C.{RESET}")
            failed_tests += 1
        else:
            print(f"{GREEN}[OK]{RESET} {desc_ctrl_c}")


        # --- TEST 2: Arrow up (History) ---
        desc_hist = "History via arrow up and command execution"

        # First write command to history
        os.write(fd, b'echo "HISTORY_WORKS_GREAT"\n')
        read_output(0.5) # Read echo result and rest

        # Now press arrow up (\x1b[A) and Enter (\n)
        os.write(fd, b'\x1b[A\n')
        out_hist = read_output(0.5)

        # Expect command to run again and print text
        if "HISTORY_WORKS_GREAT" in out_hist:
            print(f"{GREEN}[OK]{RESET} {desc_hist}")
        else:
            print(f"{RED}[KO]{RESET} {desc_hist}")
            print(f"   {YELLOW}-> After pressing arrow up and Enter, command did not run.{RESET}")
            failed_tests += 1

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

# Run
python3 run_interactive_test.py "$MINISHELL"
if [ $? -ne 0 ]; then
    ((FAILED_TESTS++))
fi

rm -f run_interactive_test.py
end_tests
