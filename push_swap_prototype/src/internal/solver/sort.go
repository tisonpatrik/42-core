package solver

import (
	"push_swap_prototype/internal/executor"
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/position"
	"push_swap_prototype/internal/stack"
)

// Position represents the positions of elements in stacks A and B

// PushSwap is the main function that handles different stack sizes (equivalent to push_swap in C)
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

		pos.StackB = executeCalc(currentNode, ps.A, ps.B, stack.GetSize(ps.A), true)

		mode := moves.LeastCommonMove(pos, stack.GetSize(ps.A), stack.GetSize(ps.B), true)
		if mode == 1 {
			reversePos(ps, &pos)
		}
		
		executor.ExecutePs(ps, pos, mode)
		
		ops.PushB(ps)
	}
	
	SortThree(ps)
	
	for stack.GetSize(ps.B) > 0 {
		target := findTarget(ps.B, ps.A)
		targetPush(ps, target)
		ops.PushA(ps)
	}
	
	
	minPos := stack.GetMinPos(ps.A)
	targetPush(ps, minPos)
}

// reversePos reverses positions when mode is 1 (equivalent to reverse_pos in C)
func reversePos(ps *ops.SortingState, pos *position.Position) {
	// This function is called when mode == 1, which means we need to reverse the positions
	// In the C code, this function modifies the pos array to reverse the positions
	pos.StackA = stack.GetSize(ps.A) - pos.StackA
	pos.StackB = stack.GetSize(ps.B) - pos.StackB
}

// findMinIndex finds the index of the element that requires the least moves to sort
// Equivalent to find_min_index in C
func findMinIndex(stackA, stackB *stack.Stack, len int) int {
	if stack.IsEmpty(stackA) {
		return -1
	}
	
	// Get first element as starting point
	current := stack.GetTop(stackA)
	min := executeCalc(current, stackA, stackB, len, false)
	currentIndex := 0
	targetIndex := 0
	
	// Iterate through all elements in stack A
	for current != nil {
		if executeCalc(current, stackA, stackB, len, false) < min {
			min = executeCalc(current, stackA, stackB, len, false)
			targetIndex = currentIndex
		}
		current = current.GetNext()
		currentIndex++
	}
	
	return targetIndex
}

// executeCalc calculates the number of moves needed to position an element correctly
func executeCalc(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {

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
			nmoves = moves.LeastCommonMove(pos, len, stack.GetSize(stackB), false) + 1
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
	return moves.LeastCommonMove(pos, len, stack.GetSize(stackB), false) + 1
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
	if currentValue < newElementValue && targetValue > newElementValue {
		return true
	}
	
	return false
}





// findTarget finds the best position to insert a value in stack_to (equivalent to find_target in C)
func findTarget(stackFrom, stackTo *stack.Stack) int {
	if stack.IsEmpty(stackTo) {
		return 0
	}
	
	// tmp = last_first_node(stack_to, false);
	tmp := stack.GetTop(stackTo)
	if tmp == nil {
		return 0
	}
	
	// target = tmp->content;
	target := tmp.GetContent()
	
	// if (stack_from->content > min_max_pos(stack_to, true, false))
	//     return (min_max_pos(stack_to, false, true));
	if stack.GetTop(stackFrom) != nil && 
	   stack.GetTop(stackFrom).GetContent() > stack.GetMax(stackTo) {
		return stack.GetMinPos(stackTo)
	}
	

	for tmp != nil {
		if stack.GetTop(stackFrom) != nil {
			fromContent := stack.GetTop(stackFrom).GetContent()
			if (tmp.GetContent() < target && tmp.GetContent() > fromContent) ||
			   (tmp.GetContent() > fromContent && target < fromContent) {
				target = tmp.GetContent()
			}
		}
		tmp = tmp.GetNext()
	}
	
	// return (node_index(stack_to, target));
	return stack.GetNodeIndexByValue(stackTo, target)
}

// targetPush moves the element at position pos to the top of the stack (equivalent to target_push in C)
func targetPush(ps *ops.SortingState, pos int) {
	if ps.A == nil {
		return
	}
	
	// stack = last_first_node(stack, false);
	// len = stack_len(stack);
	len := stack.GetSize(ps.A)
	
	if pos <= len/2 {
		for pos > 0 {
			ops.RotateA(ps)
			pos--
		}
	} else {
		reversePos := len - pos
		for reversePos > 0 {
			ops.ReverseRotateA(ps)
			reversePos--
		}
	}
}

