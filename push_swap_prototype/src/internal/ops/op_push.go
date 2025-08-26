package ops

import (
	"push_swap_prototype/internal/stack"
)



func push(src *stack.Stack, dest *stack.Stack) {
	if stack.IsFull(dest) {
		return
	}
	
	// Get the value from the top of source stack
	value := stack.GetValue(src, 0) // Get top element (position 0)
	if value == stack.NullValue() {
		return // Source stack is empty
	}
	
	// Push the value to destination stack
	stack.Push(dest, value)
	
	// Remove the value from source stack by updating top pointer
	// and clearing the value at the old top position
	oldTop := stack.GetTop(src)
	stack.SetValueAt(src, oldTop, stack.NullValue())
	
	// Update source stack top pointer
	if stack.GettSize(src) == 1 {
		// If this was the last element, mark stack as empty
		stack.SetTop(src, -1)
		stack.SetBottom(src, -1)
	} else {
		// Move top down
		stack.SetTop(src, stack.Next(src, oldTop))
	}
}

func PushA(ps *SortingState) {
	// Enhanced logging and validation
	LogOperation("PushA", ps)
	
	// Validate stack state before operation
	result := ValidateStackState(ps, "before PushA")
	if !result.IsValid {
		LogError("Stack validation failed before PushA:")
		for _, err := range result.Errors {
			LogError("  - %s", err)
		}
		// Continue with operation but log the issue
	}
	
	// Perform the push operation
	push(ps.B, ps.A)
	
	// Validate stack state after operation
	result = ValidateStackState(ps, "after PushA")
	if !result.IsValid {
		LogError("Stack validation failed after PushA:")
		for _, err := range result.Errors {
			LogError("  - %s", err)
		}
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		LogWarning("  - %s", warning)
	}
	
	// Save operation if in writing mode
	if ps.WritingMode {
		SaveOp(ps, PA)
	}
	
	LogOperationResult("PushA", ps)
}

func PushB(ps *SortingState) {
	// Enhanced logging and validation
	LogOperation("PushB", ps)

	// Validate stack state before operatioPushSwapDatan
	result := ValidateStackState(ps, "before PushB")
	if !result.IsValid {
		LogError("Stack validation failed before PushB:")
		for _, err := range result.Errors {
			LogError("  - %s", err)
		}
		// Continue with operation but log the issue
	}
	
	// Perform the push operation
	push(ps.A, ps.B)
	
	// Validate stack state after operation
	result = ValidateStackState(ps, "after PushB")
	if !result.IsValid {
		LogError("Stack validation failed after PushB:")
		for _, err := range result.Errors {
			LogError("  - %s", err)
		}
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		LogWarning("  - %s", warning)
	}
	
	// Save operation if in writing mode
	if ps.WritingMode {
		SaveOp(ps, PB)
	}
	
	LogOperationResult("PushB", ps)
}