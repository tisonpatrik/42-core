#!/bin/bash

# Colors
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
RESET="\033[0m"

# Variables
MINISHELL="${MINISHELL:-../bin/minishell}"
OUT_BASH="out_bash.tmp"
OUT_MINI="out_mini.tmp"
ERR_BASH="err_bash.tmp"
ERR_MINI="err_mini.tmp"
VALGRIND_OUT="valgrind.tmp"
TEST_TMP="${TEST_TMP:-/tmp/minishell_test_$$}"

FAILED_TESTS=0

setup_tmp() {
    mkdir -p "$TEST_TMP"
    cd "$TEST_TMP"
}

cleanup() {
    cd /tmp
    rm -rf "$TEST_TMP"
    rm -f "$OUT_BASH" "$OUT_MINI" "$ERR_BASH" "$ERR_MINI" "$VALGRIND_OUT"
}
trap cleanup EXIT

setup_tmp

# Universal test function
run_test() {
    local cmd="$1"
    local desc="$2"

    echo -e "$cmd" | bash > "$OUT_BASH" 2> "$ERR_BASH"
    local ret_bash=$?

    echo -e "$cmd" | "$MINISHELL" > "$OUT_MINI" 2> "$ERR_MINI"
    local ret_mini=$?

    sed -i 's/minishell.*\$//g' "$OUT_MINI" 2>/dev/null
    sed -i '/^exit$/d' "$OUT_MINI" 2>/dev/null
    sed -i '/^exit$/d' "$OUT_BASH" 2>/dev/null

    local fail=0
    if [ $ret_bash -ne $ret_mini ]; then fail=1; fi
    if ! diff -q "$OUT_BASH" "$OUT_MINI" > /dev/null 2>&1; then fail=1; fi

    if [ $fail -eq 0 ]; then
        printf "${GREEN}[OK]${RESET} %s\n" "$desc"
    else
        printf "${RED}[KO]${RESET} %s\n" "$desc"
        echo -e "${YELLOW}Tested command:${RESET}\n$cmd"

        if [ $ret_bash -ne $ret_mini ]; then
            echo -e "${RED}-> Exit code mismatch: Bash = $ret_bash, Minishell = $ret_mini${RESET}"
        fi

        if ! diff -q "$OUT_BASH" "$OUT_MINI" > /dev/null 2>&1; then
            echo -e "${YELLOW}--- Output diff (STDOUT) ---${RESET}"
            diff -u "$OUT_BASH" "$OUT_MINI"
            echo -e "${YELLOW}----------------------------------${RESET}"
        fi
        ((FAILED_TESTS++))
    fi
}

# Run test with Valgrind to detect memory leaks
# Requires a suppressions file for readline to avoid false positives
run_valgrind_test() {
    local cmd="$1"
    local desc="$2"

    echo -e "$cmd" | valgrind --leak-check=full --show-leak-kinds=all \
        --suppressions=readline.supp --error-exitcode=42 \
        "$MINISHELL" > /dev/null 2> "$VALGRIND_OUT"

    local ret_valgrind=$?

    if [ $ret_valgrind -eq 42 ]; then
        printf "${RED}[KO]${RESET} %s (Memory Leak)\n" "$desc"
        echo -e "${YELLOW}Valgrind Output:${RESET}"
        cat "$VALGRIND_OUT"
        ((FAILED_TESTS++))
    else
        printf "${GREEN}[OK]${RESET} %s (No Leaks)\n" "$desc"
    fi
}

# Exit function
end_tests() {
    if [ "$FAILED_TESTS" -ne 0 ]; then
        exit 1
    fi
    exit 0
}
