package solver

import (
	"math"
	"push_swap_prototype/internal/executor"
	"push_swap_prototype/internal/finalizer"
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/position"
	"push_swap_prototype/internal/stack"
)


func SolvePushSwap(ps *ops.SortingState) {
	if stack.IsSorted(ps.A) {
		return
	}
	
	sort(ps)
}

func sort(ps *ops.SortingState) {
	ops.PushB(ps)
	ops.PushB(ps)

	for stack.GetSize(ps.A) > 3 {
		pos := findCheapestElementToMoveOptimized(ps.A, ps.B)

		mode := moves.LeastCommonMove(pos, stack.GetSize(ps.A), stack.GetSize(ps.B), true)
		
		if mode == 1 {
			pos.StackA = stack.GetSize(ps.A) - pos.StackA
			if pos.StackB != 0 {
				pos.StackB = stack.GetSize(ps.B) - pos.StackB
			}
		}
		executor.ExecutePs(ps, pos, mode)
		ops.PushB(ps)
	}

	SortThree(ps)
	finalizer.FinalizeSorting(ps)
}

func findCheapestElementToMoveOptimized(stackA, stackB *stack.Stack) position.Position {
	pos := position.Position{}
	len := stack.GetSize(stackA)
	pos.StackA = findCheapestElementToMove(stackA, stackB)
	currentNode := stack.GetNodeAt(stackA, pos.StackA)

	pos.StackB = moves.FindOptimalInsertionPosition(currentNode, stackA, stackB, len, true)
	return pos
}

func findCheapestElementToMove(stackA, stackB *stack.Stack) int {
	// Pre-calculate stack B properties once to avoid repeated calculations
	stackBProps := moves.PrecalculateStackBProperties(stackB)
	
	// Find the element with minimum cost using index-based iteration
	stackSize := stack.GetSize(stackA)
	minCost := math.MaxInt
	cheapestIndex := 0
	
	// Iterate through all indices to find the cheapest element
	for index := range stackSize {
		// Get node at specific index without modifying any variables
		currentNode := stack.GetNodeAt(stackA, index)
		currentCost := moves.CalculateInsertionCost(currentNode, stackA, stackB, stackBProps)
		
		if currentCost < minCost {
			minCost = currentCost
			cheapestIndex = index
		}
	}
	
	return cheapestIndex
}

