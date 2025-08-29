package finalizer

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// FinalizeSorting completes the sorting process by returning all elements from stack B to A
// and ensuring the minimum element is at the top of stack A
func FinalizeSorting(ps *ops.SortingState) {
	// Return all elements from stack B to stack A in optimal order
	for stack.GetSize(ps.B) > 0 {
		target := findTarget(ps.B, ps.A)
		targetPush(ps, target)
		ops.PushA(ps)
	}
	
	// Move minimum element to the top of stack A to complete sorting
	minPos := stack.GetMinPos(ps.A)
	targetPush(ps, minPos)
}

// findTarget finds the best position to insert a value in stack_to (equivalent to find_target in C)
func findTarget(stackFrom, stackTo *stack.Stack) int {
	if stack.IsEmpty(stackTo) {
		return 0
	}
	
	// tmp = last_first_node(stack_to, false);
	tmp := stack.GetHead(stackTo)
	if tmp == nil {
		return 0
	}
	
	// target = tmp->content;
	target := tmp.GetContent()
	
	// if (stack_from->content > min_max_pos(stack_to, true, false))
	//     return (min_max_pos(stack_to, false, true));
	if stack.GetHead(stackFrom) != nil && 
	   stack.GetHead(stackFrom).GetContent() > stack.GetMax(stackTo) {
		return stack.GetMinPos(stackTo)
	}
	

	for tmp != nil {
		if stack.GetHead(stackFrom) != nil {
			fromContent := stack.GetHead(stackFrom).GetContent()
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
// NOTE: This replicates the C bug where pos-- is evaluated first, causing one less operation
func targetPush(ps *ops.SortingState, pos int) {
	if ps.A == nil {
		return
	}
	
	// stack = last_first_node(stack, false);
	// len = stack_len(stack);
	len := stack.GetSize(ps.A)
	if pos <= len/2 {
		// Replicate C bug: while (pos--) - pos is decremented first, then checked
		// This means we do one less operation than expected
		for pos > 0 {
			pos--
			ops.RotateA(ps)
		}
	} else {
		reversePos := len - pos
		// Replicate C bug: while (reversePos--) - reversePos is decremented first, then checked
		// This means we do one less operation than expected
		for reversePos > 0 {
			reversePos--
			ops.ReverseRotateA(ps)
		}
	}
}
