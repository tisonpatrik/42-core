package solver

import (
	"push_swap_prototype/internal/stack"
)

func chunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {

	
	loc := chunk.Loc
	stk := locToStack(ps, loc)

	
	var i int
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()	
	}
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		for n > 0 {
			n--
			i = stk.NextDown(i)
		}
	case stack.BOTTOM_A, stack.BOTTOM_B:
		for n > 0 {
			n--
			i = stk.NextUp(i)
		}
	}
	
	result := stk.GetStack()[i]

	return result
}

func chunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {

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
	
	for size > 0 {
		size--
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
