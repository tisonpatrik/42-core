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

// sort implements the main greedy insertion sort algorithm for push_swap
// Algorithm: Greedy Insertion Sort with Cost Optimization
// 1. Push first two elements to stack B to start building sorted sequence
// 2. For each remaining element in stack A:
//    a) Find the cheapest element to move (least moves required)
//    b) Find optimal insertion position in stack B
//    c) Execute moves using least common move strategy
//    d) Push element to stack B
// 3. Sort remaining 3 elements in stack A
// 4. Finalize by moving all elements back to stack A in correct order
func sort(ps *ops.SortingState) {
	// Start with 2 elements in stack B to establish initial sorted sequence
	ops.PushB(ps)
	ops.PushB(ps)

	pos := position.Position{}
	
	// Main sorting loop: move elements from A to B one by one
	for stack.GetSize(ps.A) > 3 {
		// Step 1: Find the element that costs least to move
		pos.StackA = findCheapestElementToMove(ps.A, ps.B, stack.GetSize(ps.A))
		currentNode := stack.GetNodeAt(ps.A, pos.StackA)

		// Step 2: Find optimal insertion position in stack B
		pos.StackB = moves.FindOptimalInsertionPosition(currentNode, ps.A, ps.B, stack.GetSize(ps.A), true)

		// Step 3: Determine best move strategy (rotate vs reverse)
		mode := moves.LeastCommonMove(pos, stack.GetSize(ps.A), stack.GetSize(ps.B), true)
		if mode == 1 {
			// Adjust positions for reverse strategy
			pos.StackA = stack.GetSize(ps.A) - pos.StackA
			pos.StackB = stack.GetSize(ps.B) - pos.StackB
		}
		
		// Step 4: Execute the moves and push element to B
		executor.ExecutePs(ps, pos, mode)
		ops.PushB(ps)
	}
	
	// Sort remaining 3 elements in stack A using specialized algorithm
	SortThree(ps)
	
	// Move all elements back to stack A in correct sorted order
	finalizer.FinalizeSorting(ps)
}


// findCheapestElementToMove finds the element in stack A that requires the least moves
// to be inserted into the correct position in stack B
// This implements a greedy algorithm: always move the cheapest element first
func findCheapestElementToMove(stackA, stackB *stack.Stack, len int) int {
	if stack.IsEmpty(stackA) {
		return -1
	}
	
	// Pre-calculate stack B properties once to avoid repeated calculations
	stackBProps := precalculateStackBProperties(stackB)
	
	// Find the element with minimum cost
	current := stack.GetTop(stackA)
	minCost := calculateInsertionCost(current, stackA, stackB, len, stackBProps)
	cheapestIndex := 0
	currentIndex := 0
	
	// Iterate through all elements in stack A to find the cheapest one
	for current != nil {
		currentCost := calculateInsertionCost(current, stackA, stackB, len, stackBProps)
		if currentCost < minCost {
			minCost = currentCost
			cheapestIndex = currentIndex
		}
		current = current.GetNext()
		currentIndex++
	}
	
	return cheapestIndex
}

// StackBProperties holds pre-calculated properties of stack B
type StackBProperties struct {
	size int
	min  int
	max  int
}

// precalculateStackBProperties calculates and caches stack B properties
func precalculateStackBProperties(stackB *stack.Stack) StackBProperties {
	return StackBProperties{
		size: stack.GetSize(stackB),
		min:  stack.GetMin(stackB),
		max:  stack.GetMax(stackB),
	}
}

// calculateInsertionCost calculates the total cost to insert an element from stack A into stack B
// This is the core cost function for our greedy algorithm
func calculateInsertionCost(node *stack.Node, stackA, stackB *stack.Stack, len int, props StackBProperties) int {
	// Get positions for the element
	posA := stack.GetNodeIndex(node, stackA)
	
	// Find optimal insertion position in stack B using the moves package
	posB := moves.FindOptimalInsertionPosition(node, stackA, stackB, len, true)
	
	// Calculate total moves: position moves + 1 for push operation
	pos := position.Position{StackA: posA, StackB: posB}
	return moves.LeastCommonMove(pos, len, props.size, false) + 1
}





