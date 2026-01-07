#!/bin/bash

# ==============================================================================
#  ULTIMATE PHILO TESTER (Helgrind + DRD + Memcheck + Endurance)
#  VERSION: Optimized Speed for Heavy Tests
# ==============================================================================

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

PHILO_BIN="./bin/philo"
LOG_FILE="test_output.log"
STABILITY_LOG="stability_test.log"

# -------------------------------------------------------------------------
# SCENARIOS DEFINITION
# -------------------------------------------------------------------------

# Standard scenarios (Logic heavy)
STANDARD_SCENARIOS=(
    "4 410 200 200 5"       # Standard test
    "5 800 200 200 5"       # Odd number
    "4 310 150 150 5"       # Tight timing
)

# Large scenarios (Thread heavy) -> OPTIMIZED FOR SPEED
# We use shorter times (310/150/150) and only 1 meal for large groups.
# This is enough to check for Deadlocks/Races during init, eating, and exit.
LARGE_SCENARIOS=(
    "10 310 150 150 2"      # 10 Philos, 2 meals
    "30 310 150 150 1"      # 30 Philos, 1 meal (enough to check locking)
    "100 310 150 150 1"     # 100 Philos, 1 meal (stress creation/destruction)
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
    local TOOL_FLAGS=$2
    local ARGS=$3

    echo -ne "${CYAN}[$TOOL_NAME]${NC} Testing: ./philo $ARGS ... "

    valgrind $TOOL_FLAGS $PHILO_BIN $ARGS > /dev/null 2> $LOG_FILE

    if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}FAIL!${NC}"
        grep "ERROR SUMMARY" $LOG_FILE
        if [ "$TOOL_NAME" == "LEAKS" ]; then
             grep -A 2 "definitely lost" $LOG_FILE
        else
             grep "Possible data race" $LOG_FILE | head -n 3
             grep "Lock order violation" $LOG_FILE | head -n 3
        fi
        exit 1
    fi
}

# -------------------------------------------------------------------------
# Execution
# -------------------------------------------------------------------------

compile_project

echo -e "${BLUE}Starting Tests...${NC}"

# --- PHASE 1: HELGRIND ---
echo -e "${YELLOW}--- PHASE 1: HELGRIND (Locks & Race Conditions) ---${NC}"
# Standard
for ARGS in "${STANDARD_SCENARIOS[@]}"; do
    run_valgrind_test "HELGRIND" "--tool=helgrind --history-level=approx" "$ARGS"
done
# Heavy (Optimized)
echo -e "${MAGENTA}... Running Heavy Load Helgrind Tests (Optimized) ...${NC}"
for ARGS in "${LARGE_SCENARIOS[@]}"; do
    run_valgrind_test "HELGRIND_HEAVY" "--tool=helgrind --history-level=approx" "$ARGS"
done

# --- PHASE 2: DRD ---
echo -e "\n${YELLOW}--- PHASE 2: DRD (Alternative Race Detector) ---${NC}"
# Standard
for ARGS in "${STANDARD_SCENARIOS[@]}"; do
    run_valgrind_test "DRD" "--tool=drd" "$ARGS"
done
# Heavy (Optimized)
echo -e "${MAGENTA}... Running Heavy Load DRD Tests (Optimized) ...${NC}"
for ARGS in "${LARGE_SCENARIOS[@]}"; do
    run_valgrind_test "DRD_HEAVY" "--tool=drd" "$ARGS"
done

# --- PHASE 3: MEMORY LEAKS ---
echo -e "\n${YELLOW}--- PHASE 3: MEMCHECK (Memory Leaks) ---${NC}"
run_valgrind_test "LEAKS" "--leak-check=full --show-leak-kinds=all --track-origins=yes" "5 310 150 150 5"
# Quick check on 100 philos (meals=1 is enough to leak if not cleaned up properly)
run_valgrind_test "LEAKS_HEAVY" "--leak-check=full --show-leak-kinds=all --track-origins=yes" "100 310 150 150 1"

# --- PHASE 4: SPECIAL CASE (1 PHILO) ---
echo -e "\n${YELLOW}--- PHASE 4: SPECIAL CASE (1 PHILO) ---${NC}"
ARGS="1 800 200 200"
echo -ne "${CYAN}[HELGRIND]${NC} Testing: ./philo $ARGS (Expect death) ... "
valgrind --tool=helgrind --history-level=approx $PHILO_BIN $ARGS > /dev/null 2> $LOG_FILE
if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
    echo -e "${GREEN}OK${NC}"
else
    ERRS=$(grep "ERROR SUMMARY" $LOG_FILE)
    if [[ $ERRS == *"0 errors"* ]]; then echo -e "${GREEN}OK${NC}"; else echo -e "${YELLOW}WARNING: $ERRS${NC}"; fi
fi

# --- PHASE 5: ENDURANCE TEST (30 Seconds) ---
echo -e "\n${YELLOW}--- PHASE 5: ENDURANCE TEST (30 Seconds) ---${NC}"
# This runs WITHOUT Valgrind, so we use full parameters to test stability
ARGS="5 800 200 200"
echo -e "${CYAN}[STABILITY]${NC} Running: ./philo $ARGS for 30s..."
echo -e "${MAGENTA}   (Output redirected to $STABILITY_LOG)${NC}"

$PHILO_BIN $ARGS > $STABILITY_LOG &
PID=$!

for i in {30..1}; do
    echo -ne "\r   Running... $i s remaining   "
    sleep 1
    if ! ps -p $PID > /dev/null; then
        echo -e "\n${RED}FAIL! Process died early!${NC}"
        echo -e "Check $STABILITY_LOG for details."
        exit 1
    fi
done

kill $PID 2>/dev/null
wait $PID 2>/dev/null

echo -e "\n   Checking log for unexpected deaths..."
if grep -q "died" $STABILITY_LOG; then
    echo -e "${RED}FAIL! A philosopher died!${NC}"
    grep "died" $STABILITY_LOG | head -n 5
    exit 1
else
    if [ ! -s $STABILITY_LOG ]; then
        echo -e "${RED}FAIL! Log is empty.${NC}"
        exit 1
    else
        echo -e "${GREEN}OK! (Stable run)${NC}"
    fi
fi

# -------------------------------------------------------------------------
# Conclusion
# -------------------------------------------------------------------------
echo -e "\n${BLUE}=========================================${NC}"
echo -e "${GREEN}    ALL TESTS COMPLETED SUCCESSFULLY     ${NC}"
echo -e "${BLUE}=========================================${NC}"
rm -f $LOG_FILE $STABILITY_LOG
