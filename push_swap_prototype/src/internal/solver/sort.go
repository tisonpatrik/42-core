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


	for stack.GetSize(ps.A) > 3 {
		
		pos := findCheapestElementToMoveOptimized(ps.A, ps.B, stack.GetSize(ps.A))
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

func findCheapestElementToMoveOptimized(stackA, stackB *stack.Stack, len int) position.Position {
	pos := position.Position{}
	pos.StackA = findCheapestElementToMove(stackA, stackB, len)
	currentNode := stack.GetNodeAt(stackA, pos.StackA)

	pos.StackB = moves.FindOptimalInsertionPosition(currentNode, stackA, stackB, len, true)
	return pos
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

// calculateInsertionCost calculates the cost to insert an element from stack A into the correct position in stack B
func calculateInsertionCost(node *stack.Node, stackA, stackB *stack.Stack, len int, props StackBProperties) int {
	nodeContent := node.GetContent()
	
	// Check if element is smaller than min or larger than max in stack B
	// This is the simple case that we can handle directly
	if nodeContent < props.min || nodeContent > props.max {
		posA := stack.GetNodeIndex(node, stackA)
		posB := stack.GetMaxPos(stackB)
		
		pos := position.Position{StackA: posA, StackB: posB}
		return moves.LeastCommonMove(pos, len, props.size, false) + 1
	}
	
	// For complex cases (element goes between existing elements), we need the full calculation
	// But we can optimize by passing the pre-calculated properties
	return calculateComplexElementCost(node, stackA, stackB, len, props)
}

// calculateComplexElementCost handles the complex case where element goes between existing elements
func calculateComplexElementCost(node *stack.Node, stackA, stackB *stack.Stack, len int, props StackBProperties) int {
	posA := stack.GetNodeIndex(node, stackA)
	
	// If stack B is empty, just return position in A + 1 (for push operation)
	if props.size == 0 {
		return posA + 1
	}
	
	// Find the optimal insertion position in stack B
	targetValue := findOptimalInsertionPosition(node, stackB)
	posB := stack.GetNodeIndexByValue(stackB, targetValue)
	
	// Calculate total moves needed: LCM of positions + 1 for push operation
	pos := position.Position{StackA: posA, StackB: posB}
	return moves.LeastCommonMove(pos, len, props.size, false) + 1
}

// findOptimalInsertionPosition finds the best value in stack B to position the new element after
// This is extracted from moves package to avoid dependency and optimize further
func findOptimalInsertionPosition(node *stack.Node, stackB *stack.Stack) int {
	if stack.IsEmpty(stackB) {
		return 0
	}
	
	current := stack.GetTop(stackB)
	if current == nil {
		return 0
	}
	
	// Start with the first element as potential target
	targetValue := current.GetContent()
	newElementValue := node.GetContent()
	
	// Traverse stack B to find the optimal insertion point
	for current != nil {
		currentValue := current.GetContent()
		
		// Check if this position is better for insertion
		// We want to find the largest value that's smaller than our new element
		// OR the smallest value that's larger than our new element
		if isBetterInsertionPosition(currentValue, targetValue, newElementValue) {
			targetValue = currentValue
		}
		
		current = current.GetNext()
	}
	
	return targetValue
}

// isBetterInsertionPosition determines if a new position is better for insertion
func isBetterInsertionPosition(currentValue, targetValue, newElementValue int) bool {
	// Case 1: Current value is larger than target but smaller than new element
	// This means we found a better "upper bound" for insertion
	if currentValue > targetValue && currentValue < newElementValue {
		return true
	}
	
	// Case 2: Current value is smaller than new element but target is larger than new element
	// This means we found a better "lower bound" for insertion
	if currentValue < newElementValue && targetValue > newElementValue {
		return true
	}
	
	return false
}