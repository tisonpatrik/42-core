#!/usr/bin/env python3
"""
Test script to find cases where push_swap fails to sort within the given operation limit.
Takes 2 arguments:
1. Number of numbers on input
2. Maximum number of operations allowed

Prints all cases that failed.
"""

import itertools
import random
import subprocess
import sys


def generate_random_sequence(n):
    """Generate a random sequence of n unique numbers."""
    numbers = list(range(1, n + 1))
    random.shuffle(numbers)
    return numbers


def run_push_swap(numbers):
    """Run push_swap with given numbers and return the output."""
    try:
        # Convert numbers to strings
        args = [str(num) for num in numbers]

        # Run push_swap
        result = subprocess.run(
            ["./bin/push_swap"] + args, capture_output=True, text=True, timeout=30
        )

        if result.returncode != 0:
            return None, f"Exit code: {result.returncode}, stderr: {result.stderr}"

        return result.stdout.strip(), None
    except subprocess.TimeoutExpired:
        return None, "Timeout"
    except Exception as e:
        return None, f"Error: {str(e)}"


def count_operations(operations_output):
    """Count the number of operations in the output."""
    if not operations_output:
        return 0
    return len(operations_output.split("\n"))


def test_sequence(numbers, max_ops):
    """Test a sequence and return True if it passes, False if it fails."""
    operations_output, error = run_push_swap(numbers)

    if error:
        return False, f"Execution error: {error}"

    op_count = count_operations(operations_output)

    if op_count > max_ops:
        return False, f"Too many operations: {op_count} > {max_ops}"

    return True, f"Success: {op_count} operations"


def main():
    if len(sys.argv) != 3:
        print("Usage: python3 test_failures.py <number_count> <max_operations>")
        print("Example: python3 test_failures.py 5 12")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
        max_ops = int(sys.argv[2])
    except ValueError:
        print("Error: Both arguments must be integers")
        sys.exit(1)

    if n < 1 or max_ops < 0:
        print("Error: number_count must be >= 1, max_operations must be >= 0")
        sys.exit(1)

    print(f"Testing with {n} numbers, max {max_ops} operations")
    print("=" * 50)

    failed_cases = []
    total_tested = 0

    # Test all permutations for small n, random samples for larger n
    if n <= 8:
        print(f"Testing all {n}! permutations...")
        sequences = list(itertools.permutations(range(1, n + 1)))
    else:
        print(f"Testing random samples (n={n} is too large for all permutations)...")
        sequences = []
        for _ in range(min(1000, n * 100)):  # Reasonable number of samples
            sequences.append(tuple(generate_random_sequence(n)))

    for i, sequence in enumerate(sequences):
        total_tested += 1
        success, message = test_sequence(list(sequence), max_ops)

        if not success:
            failed_cases.append((list(sequence), message))
            print(f"FAIL #{len(failed_cases)}: {sequence} - {message}")

        # Progress indicator
        if total_tested % 100 == 0:
            print(f"Tested {total_tested}/{len(sequences)} sequences...")

    print("\n" + "=" * 50)
    print("SUMMARY:")
    print(f"Total tested: {total_tested}")
    print(f"Failed cases: {len(failed_cases)}")
    print(
        f"Success rate: {((total_tested - len(failed_cases)) / total_tested * 100):.1f}%"
    )

    if failed_cases:
        print("\nALL FAILED CASES:")
        for i, (sequence, reason) in enumerate(failed_cases, 1):
            print(f"{i:3d}. {sequence} - {reason}")
    else:
        print("\nAll test cases passed! 🎉")


if __name__ == "__main__":
    main()
