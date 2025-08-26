package stack

import (
	"fmt"
	"time"
)

type ValidationResult struct {
	IsValid bool
	Errors  []string
	Warnings []string
	Duration time.Duration
}

func ValidateStackState(ps *SortingState, context string) *ValidationResult {
	start := time.Now()
	result := &ValidationResult{
		IsValid: true,
		Errors:  make([]string, 0),
		Warnings: make([]string, 0),
	}

	// Basic nil checks
	if ps == nil {
		result.IsValid = false
		result.Errors = append(result.Errors, "PushSwapData is nil")
		result.Duration = time.Since(start)
		return result
	}

	if ps.A == nil {
		result.IsValid = false
		result.Errors = append(result.Errors, "Stack A is nil")
		result.Duration = time.Since(start)
		return result
	}

	if ps.B == nil {
		result.IsValid = false
		result.Errors = append(result.Errors, "Stack B is nil")
		result.Duration = time.Since(start)
		return result
	}

	// Validate Stack A
	if err := validateStack(ps.A, "Stack A", result); err != nil {
		result.IsValid = false
		result.Errors = append(result.Errors, err.Error())
	}

	// Validate Stack B
	if err := validateStack(ps.B, "Stack B", result); err != nil {
		result.IsValid = false
		result.Errors = append(result.Errors, err.Error())
	}

	// Validate chunk consistency if available
	if ps.A != nil && ps.B != nil {
		if err := validateChunkConsistency(ps, result); err != nil {
			result.Warnings = append(result.Warnings, err.Error())
		}
	}

	result.Duration = time.Since(start)
	return result
}

// validateStack validates individual stack integrity
func validateStack(stk *Stack, stackName string, result *ValidationResult) error {
	// Check index bounds
	if stk.Top < 0 || stk.Top >= GettSize(stk) {
		result.Errors = append(result.Errors, 
			fmt.Sprintf("%s: invalid top index %d (size: %d)", stackName, stk.Top, GettSize(stk)))
	}

	if stk.Bottom < 0 || stk.Bottom >= GettSize(stk) {
		result.Errors = append(result.Errors, 
			fmt.Sprintf("%s: invalid bottom index %d (size: %d)", stackName, stk.Bottom, GettSize(stk)))
	}

	// Check current size logic
	currentSize := GettSize(stk)
	if currentSize < 0 {
		result.Errors = append(result.Errors, 
			fmt.Sprintf("%s: invalid current size %d", stackName, currentSize))
	}

	if currentSize > GettSize(stk) {
		result.Errors = append(result.Errors, 
			fmt.Sprintf("%s: current size %d exceeds max size %d", stackName, currentSize, GettSize(stk)))
	}

	// Validate circular buffer logic
	if err := validateCircularBuffer(stk, stackName, result); err != nil {
		result.Errors = append(result.Errors, err.Error())
	}

	// Check for data consistency
	if err := validateStackValues(stk, stackName, result); err != nil {
		result.Warnings = append(result.Warnings, err.Error())
	}

	return nil
}

// validateCircularBuffer validates circular buffer integrity
func validateCircularBuffer(stk *Stack, stackName string, result *ValidationResult) error {
	if stk.Top > stk.Bottom {
		// Top is greater than bottom - check wraparound logic
		if stk.Top >= GettSize(stk) || stk.Bottom < 0 {
			result.Errors = append(result.Errors, 
				fmt.Sprintf("%s: invalid wraparound indices: top=%d, bottom=%d", 
					stackName, stk.Top, stk.Bottom))
		}
	} else {
		// Top is less than bottom - normal order
		if stk.Top < 0 || stk.Bottom >= GettSize(stk) {
			result.Errors = append(result.Errors, 
				fmt.Sprintf("%s: invalid normal indices: top=%d, bottom=%d", 
					stackName, stk.Top, stk.Bottom))
		}
	}

	return nil
}

// validateStackValues validates that stack values are consistent
func validateStackValues(stk *Stack, stackName string, result *ValidationResult) error {
	currentSize := GettSize(stk)
	
	// Check if stack is empty but has non-zero indices
	if currentSize == 0 {
		if stk.Top != stk.Bottom || stk.Stack[stk.Top] != 0 {
			result.Warnings = append(result.Warnings, 
				fmt.Sprintf("%s: stack appears empty but has non-zero values", stackName))
		}
		return nil
	}

	// Check for potential data corruption
	nonZeroCount := 0
	for i := 0; i < GettSize(stk); i++ {
		if stk.Stack[i] != 0 {
			nonZeroCount++
		}
	}

	if nonZeroCount != currentSize {
		result.Warnings = append(result.Warnings, 
			fmt.Sprintf("%s: value count mismatch: expected %d, found %d", 
				stackName, currentSize, nonZeroCount))
	}

	return nil
}

// validateChunkConsistency validates chunk-related consistency
func validateChunkConsistency(ps *SortingState, result *ValidationResult) error {
	// This is a placeholder for future chunk validation logic
	// For now, we'll just check basic stack relationship
	if GettSize(ps.A) != GettSize(ps.B) {
		result.Warnings = append(result.Warnings, 
			fmt.Sprintf("Stack size mismatch: A=%d, B=%d", GettSize(ps.A), GettSize(ps.B)))
	}

	return nil
}

// LogStackState logs the current stack state for debugging
func LogStackState(ps *SortingState, context string) {
	if ps == nil {
		fmt.Printf("=== %s: PushSwapData is nil ===\n", context)
		return
	}

	fmt.Printf("=== %s ===\n", context)
	
	if ps.A != nil {
		fmt.Printf("Stack A: top=%d, bottom=%d, size=%d, current_size=%d\n", 
			ps.A.Top, ps.A.Bottom, GettSize(ps.A), GettSize(ps.A))
		fmt.Printf("Stack A top 5 values: [%d %d %d %d %d]\n",
			Value(ps.A, 1), Value(ps.A, 2), Value(ps.A, 3), Value(ps.A, 4), Value(ps.A, 5))
	} else {
		fmt.Printf("Stack A: nil\n")
	}

	if ps.B != nil {
		fmt.Printf("Stack B: top=%d, bottom=%d, size=%d, current_size=%d\n", 
			ps.B.Top, ps.B.Bottom, GettSize(ps.B), GettSize(ps.B))
		fmt.Printf("Stack B top 5 values: [%d %d %d %d %d]\n",
			Value(ps.B, 1), Value(ps.B, 2), Value(ps.B, 3), Value(ps.B, 4), Value(ps.B, 5))
	} else {
		fmt.Printf("Stack B: nil\n")
	}
}

// LogOperation logs the start of an operation
func LogOperation(operation string, ps *SortingState) {
	fmt.Printf("=== %s START ===\n", operation)
	LogStackState(ps, fmt.Sprintf("Before %s", operation))
}

// LogOperationResult logs the result of an operation
func LogOperationResult(operation string, ps *SortingState) {
	LogStackState(ps, fmt.Sprintf("After %s", operation))
	fmt.Printf("=== %s END ===\n", operation)
}

// LogError logs an error with context
func LogError(format string, args ...interface{}) {
	fmt.Printf("❌ ERROR: %s\n", fmt.Sprintf(format, args...))
}

// LogWarning logs a warning with context
func LogWarning(format string, args ...interface{}) {
	fmt.Printf("⚠️  WARNING: %s\n", fmt.Sprintf(format, args...))
}

// LogInfo logs informational message
func LogInfo(format string, args ...interface{}) {
	fmt.Printf("ℹ️  INFO: %s\n", fmt.Sprintf(format, args...))
}
