package stack

// SwapTop swaps the top two elements of a stack
func SwapTop(stack []int) []int {
	if len(stack) < 2 {
		return stack
	}
	stack[0], stack[1] = stack[1], stack[0]
	return stack
}

// PushToTop pushes an element to the top of a stack
func PushToTop(stack []int, val int) []int {
	return append([]int{val}, stack...)
}

// PopFromTop removes and returns the top element of a stack
func PopFromTop(stack []int) ([]int, int) {
	if len(stack) == 0 {
		return stack, 0
	}
	return stack[1:], stack[0]
}

// RotateUp rotates the stack up (first element goes to bottom)
func RotateUp(stack []int) []int {
	if len(stack) < 2 {
		return stack
	}
	return append(stack[1:], stack[0])
}

// RotateDown rotates the stack down (last element goes to top)
func RotateDown(stack []int) []int {
	if len(stack) < 2 {
		return stack
	}
	return append([]int{stack[len(stack)-1]}, stack[:len(stack)-1]...)
}
