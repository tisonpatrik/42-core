package solver

import (
	"push_swap_prototype/internal/stack"
)

func ChunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {
	loc := chunk.Loc
	stk := locToStack(ps, loc)

	// Check if stack is empty or uninitialized
	if stk == nil || stk.CurrentSize() == 0 {
		return 0
	}

	var i int
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()	
	}
	
	// Validate index bounds
	if i < 0 || i >= len(stk.GetStack()) {
		return 0
	}
	
	// Match C implementation exactly: advance by n-1 positions
	if loc == stack.TOP_A || loc == stack.TOP_B {
		for n--; n > 0; n-- {
			i = stk.NextDown(i)
		}
	} else if loc == stack.BOTTOM_A || loc == stack.BOTTOM_B {
		for n--; n > 0; n-- {
			i = stk.NextUp(i)
		}
	}
	
	// Validate the final index
	if i < 0 || i >= len(stk.GetStack()) {
		return 0
	}
	
	// Get the value at the calculated index
	result := stk.GetStack()[i]
	return result
}

func ChunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {

	var stk *stack.Stack
	var size int
	var maxValue int
	var i int

	stk = locToStack(ps, chunk.Loc)
	size = chunk.Size
	maxValue = 0
	
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()
	}
	
	// Fix: Match C implementation exactly - process exactly chunk_size elements
	// C: while (size--) - decrements first, then checks
	for ; size > 0; size-- {
		if stk.GetStack()[i] > maxValue {
			maxValue = stk.GetStack()[i]
		}
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stk.NextDown(i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stk.NextUp(i)
		}
	}
	return maxValue
}

// locToStack returns the appropriate stack based on the location
func locToStack(ps *stack.PushSwapData, loc stack.Loc) *stack.Stack {
	if loc == stack.TOP_A || loc == stack.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}
