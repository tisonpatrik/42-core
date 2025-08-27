package moves

import (
	"push_swap_prototype/internal/position"
	"push_swap_prototype/internal/stack"
)

// executeCalc calculates the number of moves needed to position an element correctly
func ExecuteCalc(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {

	nmoves := 0
	nodeContent := node.GetContent()
	
	// Check if element is smaller than min or larger than max in stack B
	minB := stack.GetMin(stackB)
	maxB := stack.GetMax(stackB) 
	
	if nodeContent < minB || nodeContent > maxB {
		// Element should go to top or bottom of stack B
		posA := stack.GetNodeIndex(node, stackA)  // Fixed: use stackA instead of stackB
		posB := stack.GetMaxPos(stackB)
		if returnPosB == true {
			nmoves = posB
		} else {
			pos := position.Position{StackA: posA, StackB: posB}
			nmoves = LeastCommonMove(pos, len, stack.GetSize(stackB), false) + 1
		}
	} else {
		nmoves = calculateStrategyCost(node, stackA, stackB, len, returnPosB)  // Fixed: pass stackA to calc
	}
	return nmoves
}

// calculateStrategyCost calculates moves for positioning element between existing elements in stack B
// This implements an insertion sort optimization algorithm that finds the best position
// to insert an element from stack A into stack B to maintain sorted order
func calculateStrategyCost(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {
	posA := stack.GetNodeIndex(node, stackA)
	
	// If stack B is empty, just return position in A + 1 (for push operation)
	if stack.IsEmpty(stackB) {
		return posA + 1
	}
	
	// Find the optimal insertion position in stack B
	targetValue := findOptimalInsertionPosition(node, stackB)
	posB := stack.GetNodeIndexByValue(stackB, targetValue)
	
	if returnPosB {
		return posB
	}
	
	// Calculate total moves needed: LCM of positions + 1 for push operation
	pos := position.Position{StackA: posA, StackB: posB}
	return LeastCommonMove(pos, len, stack.GetSize(stackB), false) + 1
}

// findOptimalInsertionPosition finds the best value in stack B to position the new element after
// This implements the core logic of finding where to insert an element to maintain sorted order
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
// This implements the logic for finding the optimal insertion point in a sorted sequence
func isBetterInsertionPosition(currentValue, targetValue, newElementValue int) bool {
	// Case 1: Current value is larger than target but smaller than new element
	// This means we found a better "upper bound" for insertion
	if currentValue > targetValue && currentValue < newElementValue {
		return true
	}
	
	// Case 2: Current value is smaller than new element but target is larger than new element
	// This means we found a better "lower bound" for insertion
	// Equivalent to C: (tmp->content < stack_a->content && target > stack_a->content)
	if currentValue < newElementValue && targetValue > newElementValue {
		return true
	}
	
	return false
}