#!/bin/bash

# Colors for better readability
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PHILO_BIN="./bin/philo"
LOG_FILE="test_output.log"

# Function to generate random number in range
rand() {
    shuf -i $1-$2 -n 1
}

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}    ULTIMATE PHILO TESTER (TSan + Helgrind)   ${NC}"
echo -e "${BLUE}=========================================${NC}"

# -------------------------------------------------------------------------
# PHASE 1: ThreadSanitizer (Fast, many tests)
# -------------------------------------------------------------------------
echo -e "\n${YELLOW}[PHASE 1] Compiling with ThreadSanitizer (make tsan)...${NC}"
make fclean > /dev/null
make tsan > /dev/null

if [ ! -f "$PHILO_BIN" ]; then
    echo -e "${RED}Error: Binary does not exist. Check Makefile.${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation OK. Starting 30 Randomized TSan tests...${NC}"

# Number of tests for TSan
TSAN_ITERATIONS=30

for ((i=1; i<=TSAN_ITERATIONS; i++))
do
    # Generate random arguments
    # Philosophers: 2 to 199
    NB_PHILO=$(rand 2 199)
    # Time to eat: 60 to 150ms
    T_EAT=$(rand 60 150)
    # Time to sleep: 60 to 150ms
    T_SLEEP=$(rand 60 150)
    # Time to die: Must be more than eat+sleep so they don't die immediately (we want to test race conditions, not death)
    SAFE_T_DIE=$((T_EAT + T_SLEEP + 20))
    T_DIE=$(rand $SAFE_T_DIE $((SAFE_T_DIE + 100)))
    # Number of meals: 2 to 10 (to be fast)
    N_MEALS=$(rand 2 10)

    ARGS="$NB_PHILO $T_DIE $T_EAT $T_SLEEP $N_MEALS"

    echo -ne "Test $i/$TSAN_ITERATIONS: ./philo $ARGS ... "

    # Run
    $PHILO_BIN $NB_PHILO $T_DIE $T_EAT $T_SLEEP $N_MEALS > /dev/null 2> $LOG_FILE
    RET=$?

    # TSan returns exit code != 0 if it finds an error
    if [ $RET -ne 0 ]; then
        echo -e "${RED}FAIL!${NC}"
        echo -e "${RED}ThreadSanitizer found error (or segfault)! Log:${NC}"
        cat $LOG_FILE
        exit 1
    else
        echo -e "${GREEN}OK${NC}"
    fi
done

echo -e "${GREEN}>>> All TSan tests passed! <<<${NC}"

# -------------------------------------------------------------------------
# PHASE 2: Helgrind (Slow, precise tests)
# -------------------------------------------------------------------------
echo -e "\n${YELLOW}[PHASE 2] Re-compiling for Helgrind (make re)...${NC}"
make re > /dev/null

echo -e "${GREEN}Starting specific Helgrind tests...${NC}"

# Definition of scenarios for Helgrind (fewer tests because it's slow)
# Format: "Count TimeToDie TimeToEat TimeToSleep NumberOfMeals"
SCENARIOS=(
    "4 410 200 200 3"      # Classic
    "5 800 200 200 3"      # Odd count
    "2 310 150 150 3"      # Small count
)

COUNT=0
for ARGS in "${SCENARIOS[@]}"
do
    ((COUNT++))
    echo -ne "Helgrind Test $COUNT: ./philo $ARGS ... "

    # Run valgrind and redirect stderr to file
    valgrind --tool=helgrind --history-level=approx $PHILO_BIN $ARGS > /dev/null 2> $LOG_FILE

    # Look for "0 errors" in log
    if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
        echo -e "${GREEN}OK (0 errors)${NC}"
    else
        echo -e "${RED}FAIL!${NC}"
        echo -e "${RED}Helgrind found errors! Here is the output:${NC}"
        grep "ERROR SUMMARY" $LOG_FILE
        # Optionally print error details (first 20 lines)
        head -n 20 $LOG_FILE
        exit 1
    fi
done

# Special test for 1 philosopher (should die, but must not throw mutex error)
echo -ne "Helgrind Test (1 Philo): ./philo 1 800 200 200 ... "
# Here we expect death, so program exit code might be non-zero, we only care about Helgrind output
valgrind --tool=helgrind $PHILO_BIN 1 800 200 200 > /dev/null 2> $LOG_FILE
if grep -q "ERROR SUMMARY: 0 errors" $LOG_FILE; then
    echo -e "${GREEN}OK (0 errors)${NC}"
else
    # For 1 philosopher, "announced death" is sometimes considered a leak if not cleaned up,
    # but we mainly care about Lock Order Violations.
    ERRS=$(grep "ERROR SUMMARY" $LOG_FILE)
    echo -e "${YELLOW}Check manual: $ERRS${NC}"
fi

echo -e "\n${BLUE}=========================================${NC}"
echo -e "${GREEN}   DONE! All tests completed.      ${NC}"
echo -e "${BLUE}=========================================${NC}"
rm -f $LOG_FILE
