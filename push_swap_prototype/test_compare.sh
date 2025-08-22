#!/bin/bash

# Function to generate random array with numbers from 0 to size-1 without duplicates
generate_random_array() {
    local size=$1
    local array=()
    
    # Create array with numbers 0 to size-1 (0-based indexing for Go)
    for ((i=0; i<size; i++)); do
        array[i]=$i
    done
    
    # Fisher-Yates shuffle for random order
    for ((i=size-1; i>0; i--)); do
        j=$((RANDOM % (i + 1)))
        temp=${array[i]}
        array[i]=${array[j]}
        array[j]=$temp
    done
    
    echo "${array[@]}"
}

# Generate random test array with 10 numbers (0-9)
ARRAY_SIZE=100
TEST_ARRAY=($(generate_random_array $ARRAY_SIZE))

echo "=== COMPARING GO AND C IMPLEMENTATIONS ==="
echo "Generated random array: ${TEST_ARRAY[*]}"
echo "Array size: ${#TEST_ARRAY[@]}"
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "Script directory: $SCRIPT_DIR"

# Build Go version
echo "Building Go version..."
cd "$SCRIPT_DIR"
make build
if [ $? -ne 0 ]; then
    echo "❌ Failed to build Go version"
    exit 1
fi

# Run Go version
echo ""
echo "=== GO VERSION OUTPUT ==="
./bin/push_swap_prototype "${TEST_ARRAY[@]}"
GO_EXIT_CODE=$?

echo ""
echo "=== C VERSION OUTPUT ==="
cd test

# Check if C version exists
if [ ! -f "./push_swap" ]; then
    echo "❌ C version not found. Building..."
    make all
    if [ $? -ne 0 ]; then
        echo "❌ Failed to build C version"
        exit 1
    fi
fi

# Run C version with the same array
./push_swap "${TEST_ARRAY[@]}"
C_EXIT_CODE=$?

echo ""
echo "=== COMPARISON SUMMARY ==="
echo "Go version exit code: $GO_EXIT_CODE"
echo "C version exit code: $C_EXIT_CODE"

if [ $GO_EXIT_CODE -eq 0 ] && [ $C_EXIT_CODE -eq 0 ]; then
    echo "✅ Both versions completed successfully"
else
    echo "❌ One or both versions failed"
    exit 1
fi

echo ""
echo "=== LOGS COMPARISON ==="
echo "Compare the chunk_split logs above to see if both implementations behave identically."
echo "Look for:"
echo "  - Same pivot values"
echo "  - Same chunk assignments (MIN/MID/MAX)"
echo "  - Same final chunk sizes"
