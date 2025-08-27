package moves

import (
	"push_swap_prototype/internal/position"
	"push_swap_prototype/internal/stack"
)

// FindOptimalInsertionPosition finds the optimal position in stack B to insert an element from stack A
// This is the core of our greedy insertion sort algorithm
func FindOptimalInsertionPosition(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {

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

