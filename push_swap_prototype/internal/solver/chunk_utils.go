package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// chunkValue gets the value at a specific position in the chunk (1-based like C)
func chunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {
	fmt.Printf("    chunkValue: chunk loc=%v, size=%d, position=%d\n", chunk.Loc, chunk.Size, n)
	
	loc := chunk.Loc
	stk := locToStack(ps, loc)
	fmt.Printf("      Using stack: %v, stack size: %d\n", chunk.Loc, stk.Size())
	
	var i int
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop() // Default case to ensure i is always initialized
	}
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		for n > 1 {
			i = stk.NextDown(i)
			n--
		}
	case stack.BOTTOM_A, stack.BOTTOM_B:
		for n > 1 {
			i = stk.NextUp(i)
			n--
		}
	}
	
	fmt.Printf("      chunkValue result: %d\n", stk.GetStack()[i])
	return stk.GetStack()[i]
}

// chunkMaxValue finds the maximum value in the given chunk
func chunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	fmt.Printf("    chunkMaxValue: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
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
		i = stk.GetTop() // Default case to ensure i is always initialized
	}
	
	for size > 0 {
		if stk.GetValueAtPosition(i) > maxValue {
			maxValue = stk.GetValueAtPosition(i)
			fmt.Printf("      New max: %d at position %d\n", maxValue, size)
		}
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stk.NextDown(i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stk.NextUp(i)
		}
		size--
	}
	
	fmt.Printf("      chunkMaxValue result: %d\n", maxValue)
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
