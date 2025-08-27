package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// Position represents the positions of elements in stacks A and B
type Position struct {
	StackA int // Position in stack A
	StackB int // Position in stack B
}

// PushSwap is the main function that handles different stack sizes (equivalent to push_swap in C)
func SolvePushSwap(ps *ops.SortingState) {

	if stack.IsSorted(ps.A) {
		return
	}	else {
		sort(ps)
	}

}

func sort(ps *ops.SortingState) {
	multiExecute(ps, ops.PB, 2)

	pos := Position{}
	for stack.GetSize(ps.A) > 3 {
		
		pos.StackA = findMinIndex(ps.A, ps.B, stack.GetSize(ps.A))
		currentNode := stack.GetNodeAt(ps.A, pos.StackA)
		if currentNode == nil {
			continue
		}
		pos.StackB = executeCalc(currentNode, ps.A, ps.B, stack.GetSize(ps.A), true)

		mode := lcm(pos, stack.GetSize(ps.A), stack.GetSize(ps.B), true)
		if mode == 1 {
			reversePos(ps, &pos)
		}
		
		executePs(ps, pos, mode)
		
		ops.PushB(ps)
	}
	
	SortThree(ps)
	
	for stack.GetSize(ps.B) > 0 {
		target := findTarget(ps.B, ps.A)
		targetPush(ps, target)
		ops.PushA(ps)
	}
	
	minMaxPush(ps, false)
}

// multiExecute executes an operation n times (equivalent to multi_execute in C)
func multiExecute(ps *ops.SortingState, op ops.Operation, n int) {
	for range n {
		switch op {
		case ops.PB:
			ops.PushB(ps)
		case ops.PA:
			ops.PushA(ps)
		case ops.RA:
			ops.RotateA(ps)
		case ops.RB:
			ops.RotateB(ps)
		case ops.RRA:
			ops.ReverseRotateA(ps)
		case ops.RRB:
			ops.ReverseRotateB(ps)
		case ops.RR:
			ops.RotateA(ps)
			ops.RotateB(ps)
		case ops.RRR:
			ops.ReverseRotateA(ps)
			ops.ReverseRotateB(ps)
		}
	}
}

// execSmt executes simultaneous moves (equivalent to exec_smt in C)
func execSmt(ps *ops.SortingState, pos Position, mode int) {
	switch mode {
	case 0:
		// rr mode
		minMoves := pos.StackA
		if pos.StackB < pos.StackA {
			minMoves = pos.StackB
		}
		multiExecute(ps, ops.RR, minMoves)
		
		if pos.StackA > pos.StackB && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RA, pos.StackA-pos.StackB)
		} else if pos.StackB > pos.StackA && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RB, pos.StackB-pos.StackA)
		}
	case 1:
		// rrr mode
		minMoves := pos.StackA
		if pos.StackB < pos.StackA {
			minMoves = pos.StackB
		}
		multiExecute(ps, ops.RRR, minMoves)
		
		if pos.StackA > pos.StackB && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RRA, pos.StackA-pos.StackB)
		} else if pos.StackB > pos.StackA && pos.StackA != pos.StackB && pos.StackB != 0 {
			multiExecute(ps, ops.RRB, pos.StackB-pos.StackA)
		}
	}
}

// executePs executes the positioning strategy based on mode (equivalent to execute_ps in C)
func executePs(ps *ops.SortingState, pos Position, mode int) {
	switch mode {
	case 0, 1:
		execSmt(ps, pos, mode)
	case 2:
		multiExecute(ps, ops.RA, pos.StackA)
		multiExecute(ps, ops.RRB, stack.GetSize(ps.B)-pos.StackB)
	case 3:
		multiExecute(ps, ops.RRA, stack.GetSize(ps.A)-pos.StackA)
		multiExecute(ps, ops.RB, pos.StackB)
	}
}

// reversePos reverses positions when mode is 1 (equivalent to reverse_pos in C)
func reversePos(ps *ops.SortingState, pos *Position) {
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
// Equivalent to execute_calc in C
func executeCalc(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {

	nmoves := 0
	nodeContent := node.GetContent()
	
	// Check if element is smaller than min or larger than max in stack B
	minB := getMinMaxPos(stackB, false, false) // false = min
	maxB := getMinMaxPos(stackB, true, false)  // true = max
	
	if nodeContent < minB || nodeContent > maxB {
		// Element should go to top or bottom of stack B
		posA := getNodeIndex(node, stackA)  // Fixed: use stackA instead of stackB
		posB := getMinMaxPos(stackB, true, true) // true = max, true = return position
		if returnPosB == true {
			nmoves = posB
		} else {
			nmoves = lcm(Position{StackA: posA, StackB: posB}, len, stack.GetSize(stackB), false) + 1
		}
	} else {
		nmoves = calc(node, stackA, stackB, len, returnPosB)  // Fixed: pass stackA to calc
	}
	return nmoves
}

// calc calculates moves for positioning element between existing elements in stack B
// Equivalent to calc in C
func calc(node *stack.Node, stackA, stackB *stack.Stack, len int, returnPosB bool) int {
	posA := getNodeIndex(node, stackA)
	if stack.IsEmpty(stackB) {
		return posA + 1
	}
	
	// Find target position in stack B - equivalent to C implementation
	tmp := stack.GetTop(stackB)
	if tmp == nil {
		return posA + 1
	}
	
	target := tmp.GetContent()
	for tmp != nil {
		if (tmp.GetContent() > target && tmp.GetContent() < node.GetContent()) ||
			(tmp.GetContent() < node.GetContent() && target > node.GetContent()) {
			target = tmp.GetContent()
		}
		tmp = tmp.GetNext()
	}
	
	posB := getNodeIndexByValue(stackB, target)
	
	if returnPosB {
		return posB
	}
	
	// Return LCM of moves + 1 for push
	return lcm(Position{StackA: posA, StackB: posB}, len, stack.GetSize(stackB), false) + 1
}

// getNodeIndex returns the index of a node in its stack
// Equivalent to node_index in C
func getNodeIndex(node *stack.Node, s *stack.Stack) int {
	if s == nil || node == nil {
		return -1
	}
	
	index := 0
	current := stack.GetTop(s)
	
	for current != nil {
		if current == node {
			return index
		}
		current = current.GetNext()
		index++
	}
	
	return -1
}

// getNodeIndexByValue returns the index of a node with specific value in the stack
// Equivalent to node_index in C
func getNodeIndexByValue(s *stack.Stack, value int) int {
	if s == nil {
		return -1
	}
	
	index := 0
	current := stack.GetTop(s)
	
	for current != nil {
		if current.GetContent() == value {
			return index
		}
		current = current.GetNext()
		index++
	}
	
	return -1
}

// getMinMaxPos returns min/max value or position based on parameters
// Equivalent to min_max_pos in C
func getMinMaxPos(s *stack.Stack, wantMax bool, returnPos bool) int {
	if stack.IsEmpty(s) {
		return 0
	}
	
	current := stack.GetTop(s)
	target := current.GetContent()
	traverseIndex := -1
	targetIndex := 0
	
	for traverseIndex < stack.GetSize(s)-1 {
		traverseIndex++
		if (current.GetContent() > target && wantMax) || (current.GetContent() < target && !wantMax) {
			target = current.GetContent()
			targetIndex = traverseIndex
		}
		current = current.GetNext()
	}
	
	if returnPos {
		return targetIndex
	}
	return target
}

// minLcm finds the minimum value in an array (equivalent to min_lcm in C)
func minLcm(arr []int, len int, returnIndex bool) int {
	min := arr[0]
	targetIndex := 0
	
	for i := 1; i < len; i++ {
		if arr[i] < min && arr[i] >= 0 {
			min = arr[i]
			targetIndex = i
		}
	}
	
	if returnIndex {
		return targetIndex
	}
	return min
}

// lcm calculates the least common move (equivalent to lcm in C)
func lcm(pos Position, lenA, lenB int, returnMove bool) int {
	nlcm := make([]int, 4)
	tempPosB := -1
	result := 0
	if pos.StackB == 0 {
		tempPosB = pos.StackB
		pos.StackB = pos.StackA
	}
	
	nlcm[0] = max(pos.StackA, pos.StackB)
	
	nlcm[1] = max(lenA - pos.StackA, lenB - pos.StackB)
	
	nlcm[2] = pos.StackA + (lenB - pos.StackB)
	nlcm[3] = (lenA - pos.StackA) + pos.StackB
	
	if tempPosB != -1 {
		pos.StackB = tempPosB
	}
	
	if returnMove {
		result = minLcm(nlcm, 4, true)
	} else {
		result = minLcm(nlcm, 4, false)
	}
	return result
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
	   stack.GetTop(stackFrom).GetContent() > getMinMaxPos(stackTo, true, false) {
		return getMinMaxPos(stackTo, false, true)
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
	return getNodeIndexByValue(stackTo, target)
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

// minMaxPush pushes the minimum or maximum element to the top (equivalent to min_max_push in C)
func minMaxPush(ps *ops.SortingState, max bool) {

	pos := getMinMaxPos(ps.A, max, true)
	targetPush(ps, pos)
}