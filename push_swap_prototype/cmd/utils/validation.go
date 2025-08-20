package utils

// IsSorted checks if an array is sorted in ascending order
func IsSorted(arr []int) bool {
	if len(arr) <= 1 {
		return true
	}
	
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			return false
		}
	}
	return true
}

// ApplyOperations applies a list of operations to two stacks and returns the final state
func ApplyOperations(ops []string, a, b []int) ([]int, []int) {
	stackA := make([]int, len(a))
	stackB := make([]int, len(b))
	copy(stackA, a)
	copy(stackB, b)
	
	for _, op := range ops {
		switch op {
		case "sa":
			if len(stackA) >= 2 {
				stackA[0], stackA[1] = stackA[1], stackA[0]
			}
		case "sb":
			if len(stackB) >= 2 {
				stackB[0], stackB[1] = stackB[1], stackB[0]
			}
		case "ss":
			if len(stackA) >= 2 {
				stackA[0], stackA[1] = stackA[1], stackA[0]
			}
			if len(stackB) >= 2 {
				stackB[0], stackB[1] = stackB[1], stackB[0]
			}
		case "pa":
			if len(stackB) > 0 {
				stackA = append([]int{stackB[0]}, stackA...)
				stackB = stackB[1:]
			}
		case "pb":
			if len(stackA) > 0 {
				stackB = append([]int{stackA[0]}, stackB...)
				stackA = stackA[1:]
			}
		case "ra":
			if len(stackA) >= 2 {
				stackA = append(stackA[1:], stackA[0])
			}
		case "rb":
			if len(stackB) >= 2 {
				stackB = append(stackB[1:], stackB[0])
			}
		case "rr":
			if len(stackA) >= 2 {
				stackA = append(stackA[1:], stackA[0])
			}
			if len(stackB) >= 2 {
				stackB = append(stackB[1:], stackB[0])
			}
		case "rra":
			if len(stackA) >= 2 {
				stackA = append([]int{stackA[len(stackA)-1]}, stackA[:len(stackA)-1]...)
			}
		case "rrb":
			if len(stackB) >= 2 {
				stackB = append([]int{stackB[len(stackB)-1]}, stackB[:len(stackB)-1]...)
			}
		case "rrr":
			if len(stackA) >= 2 {
				stackA = append([]int{stackA[len(stackA)-1]}, stackA[:len(stackA)-1]...)
			}
			if len(stackB) >= 2 {
				stackB = append([]int{stackB[len(stackB)-1]}, stackB[:len(stackB)-1]...)
			}
		}
	}
	
	return stackA, stackB
}
