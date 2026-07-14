#!/bin/bash

# ==========================================
# CONFIGURATION AND COLORS
# ==========================================
GREEN="\033[0;32m"
RED="\033[0;31m"
CYAN="\033[1;36m"
YELLOW="\033[1;33m"
RESET="\033[0m"

# Summary variables
TOTAL_SCRIPTS=0
PASSED_SCRIPTS=0
FAILED_SCRIPTS=0

# ==========================================
# ENVIRONMENT PREP AND BUILD
# ==========================================
echo -e "${CYAN}=== Minishell Setup ===${RESET}"
echo -e "${YELLOW}Compiling project with 'make re'...${RESET}"
make re > /dev/null 2>&1

if [ ! -f "./bin/minishell" ]; then
    echo -e "${RED}Error: Minishell binary not found at './bin/minishell'.${RESET}"
    exit 1
fi
MINISHELL_ABS=$(readlink -f "./bin/minishell")
echo -e "${GREEN}Binary ready: $MINISHELL_ABS${RESET}\n"

# Export binary path for test scripts
export MINISHELL="$MINISHELL_ABS"

# ==========================================
# RUN TEST SCRIPTS
# ==========================================
echo -e "${CYAN}=== Running test scripts from 'tests/' ===${RESET}\n"

# Iterate over all .sh files in tests/ directory
for test_script in tests/*.sh; do
    # Check if any files exist
    if [ ! -e "$test_script" ]; then
        echo -e "${YELLOW}No .sh scripts found in 'tests/' directory.${RESET}"
        break
    fi

    ((TOTAL_SCRIPTS++))
    echo -e "${CYAN}>>> Running: $(basename "$test_script") <<<${RESET}"

    # Run specific test script
    bash "$test_script"
    EXIT_CODE=$?

    if [ $EXIT_CODE -eq 0 ]; then
        ((PASSED_SCRIPTS++))
        echo -e "${GREEN}>>> $(basename "$test_script") PASSED <<<${RESET}\n"
    else
        ((FAILED_SCRIPTS++))
        echo -e "${RED}>>> $(basename "$test_script") FAILED <<<${RESET}\n"
    fi
done

# ==========================================
# SUMMARY
# ==========================================
echo -e "${CYAN}============================================${RESET}"
echo -e "${CYAN}             TEST RESULTS             ${RESET}"
echo -e "${CYAN}============================================${RESET}"

echo -e "Total test suites    : $TOTAL_SCRIPTS"
echo -e "Passed               : ${GREEN}$PASSED_SCRIPTS${RESET}"

if [ "$FAILED_SCRIPTS" -eq 0 ] && [ "$TOTAL_SCRIPTS" -gt 0 ]; then
    echo -e "Failed               : ${GREEN}0${RESET}"
    echo -e "\n${GREEN}ALL TEST SUITES PASSED!${RESET}"
    exit 0
else
    echo -e "Failed               : ${RED}$FAILED_SCRIPTS${RESET}"
    echo -e "\n${RED}Some test suites failed. Check outputs above.${RESET}"
    exit 1
fi
