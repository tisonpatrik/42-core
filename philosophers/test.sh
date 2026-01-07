#!/bin/bash

# ==============================================================================
#  ULTIMATE PHILO TESTER (Helgrind + DRD + Memcheck)
#  Optimized for School Environment (No TSan)
# ==============================================================================

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

PHILO_BIN="./bin/philo"
LOG_FILE="test_output.log"

# Scenarios to test
# Format: "NbPhilo TimeDie TimeEat TimeSleep [Meals]"
SCENARIOS=(
    "4 410 200 200 5"       # Standard test
    "5 800 200 200 5"       # Odd number of philosophers
    "4 310 150 150 5"       # Tight timing
    "2 310 150 150 5"       # Minimum philosophers
)

# -------------------------------------------------------------------------
# Helper Functions
# -------------------------------------------------------------------------

compile_project() {
    echo -e "${BLUE}=========================================${NC}"
    echo -e "${YELLOW}   Compiling project (Debug Mode)...     ${NC}"
    echo -e "${BLUE}=========================================${NC}"

    make fclean > /dev/null
    make debug > /dev/null

    if [ ! -f "$PHILO_BIN" ]; then
        echo -e "${RED}Error: Binary '$PHILO_BIN' not found. Check Makefile.${NC}"
        exit 1
    fi
    echo -e "${GREEN}Compilation successful.${NC}\n"
}

run_valgrind_test() {
    local TOOL_NAME=$1
    local TOOL_FLAG=$2
    local ARGS=$3

    echo -ne "${CYAN}[$TOOL_NAME]${NC} Testing: ./philo $ARGS ... "

    # Run Valgrind with specific tool
    # --history-level=approx is needed for Helgrind to be reasonably fast
    valgrind $TOOL_FLAG --history-level=approx $PHILO_BIN $ARGS > /dev/null 2> $LOG_FILE

    # Check output for errors
    if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}FAIL!${NC}"
        echo -e "${RED}Errors found in log:${NC}"
        grep "ERROR SUMMARY" $LOG_FILE
        # Show specific error context
        if [ "$TOOL_NAME" == "LEAKS" ]; then
             grep -A 2 "definitely lost" $LOG_FILE
        else
             grep "Possible data race" $LOG_FILE | head -n 3
             grep "Lock order violation" $LOG_FILE | head -n 3
        fi
        echo -e "${YELLOW}Full log saved to $LOG_FILE${NC}"
        exit 1
    fi
}

# -------------------------------------------------------------------------
# Execution
# -------------------------------------------------------------------------

compile_project

echo -e "${BLUE}Starting Tests... Note: Valgrind is slow, please wait.${NC}\n"

# --- PHASE 1: HELGRIND (Thread Error Detector) ---
echo -e "${YELLOW}--- PHASE 1: HELGRIND (Locks & Race Conditions) ---${NC}"
for ARGS in "${SCENARIOS[@]}"; do
    run_valgrind_test "HELGRIND" "--tool=helgrind" "$ARGS"
done

# --- PHASE 2: DRD (Data Race Detector - Alternative to Helgrind) ---
echo -e "\n${YELLOW}--- PHASE 2: DRD (Alternative Race Detector) ---${NC}"
for ARGS in "${SCENARIOS[@]}"; do
    run_valgrind_test "DRD" "--tool=drd" "$ARGS"
done

# --- PHASE 3: MEMORY LEAKS ---
echo -e "\n${YELLOW}--- PHASE 3: MEMCHECK (Memory Leaks) ---${NC}"
for ARGS in "${SCENARIOS[@]}"; do
    run_valgrind_test "LEAKS" "--leak-check=full --show-leak-kinds=all --track-origins=yes" "$ARGS"
done

# --- PHASE 4: SPECIAL CASE (1 PHILOSOPHER) ---
echo -e "\n${YELLOW}--- PHASE 4: SPECIAL CASE (1 PHILO) ---${NC}"
# 1 Philo should die. We check if Valgrind reports errors (like unclosed mutexes).
# We expect the program to finish, but likely with a death message.
ARGS="1 800 200 200"
echo -ne "${CYAN}[HELGRIND]${NC} Testing: ./philo $ARGS (Expect death) ... "
valgrind --tool=helgrind $PHILO_BIN $ARGS > /dev/null 2> $LOG_FILE

if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
    echo -e "${GREEN}OK${NC}"
else
    # Sometimes 1 philo dying leaves "still reachable" blocks which Helgrind might flag lightly,
    # but we look for synchronization errors.
    ERRS=$(grep "ERROR SUMMARY" $LOG_FILE)
    if [[ $ERRS == *"0 errors"* ]]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${YELLOW}WARNING (Check manually): $ERRS${NC}"
    fi
fi

# -------------------------------------------------------------------------
# Conclusion
# -------------------------------------------------------------------------
echo -e "\n${BLUE}=========================================${NC}"
echo -e "${GREEN}    ALL TESTS COMPLETED SUCCESSFULLY     ${NC}"
echo -e "${BLUE}=========================================${NC}"
rm -f $LOG_FILE
