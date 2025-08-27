package solver

import (
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
	}	else {
		sort(ps)
	}

}

func sort(ps *ops.SortingState) {
	ops.PushB(ps)
	ops.PushB(ps)


	pos := position.Position{}
	for stack.GetSize(ps.A) > 3 {
		
		pos.StackA = findMinIndex(ps.A, ps.B, stack.GetSize(ps.A))
		currentNode := stack.GetNodeAt(ps.A, pos.StackA)

		pos.StackB = moves.ExecuteCalc(currentNode, ps.A, ps.B, stack.GetSize(ps.A), true)

		mode := moves.LeastCommonMove(pos, stack.GetSize(ps.A), stack.GetSize(ps.B), true)
		if mode == 1 {
			pos.StackA = stack.GetSize(ps.A) - pos.StackA
			pos.StackB = stack.GetSize(ps.B) - pos.StackB
		}
		
		executor.ExecutePs(ps, pos, mode)
		ops.PushB(ps)
	}
	
	SortThree(ps)
	
	finalizer.FinalizeSorting(ps)
}


// findMinIndex finds the index of the element that requires the least moves to sort
// Equivalent to find_min_index in C
func findMinIndex(stackA, stackB *stack.Stack, len int) int {
	if stack.IsEmpty(stackA) {
		return -1
	}
	
	// Get first element as starting point
	current := stack.GetTop(stackA)
	min := moves.ExecuteCalc(current, stackA, stackB, len, false)
	currentIndex := 0
	targetIndex := 0
	
	// Iterate through all elements in stack A
	for current != nil {
		if moves.ExecuteCalc(current, stackA, stackB, len, false) < min {
			min = moves.ExecuteCalc(current, stackA, stackB, len, false)
			targetIndex = currentIndex
		}
		current = current.GetNext()
		currentIndex++
	}
	
	return targetIndex
}