package algo

// TargetPos finds position in A where val should go (first position greater than val)
func TargetPos(a []int, val int) int {
	if len(a) == 0 {
		return 0
	}
	
	bigger := make([]int, 0)
	for i, x := range a {
		if x > val {
			bigger = append(bigger, i)
		}
	}
	
	if len(bigger) == 0 {
		// If no bigger values, insert at the end (after the largest value)
		// This maintains the sorted order
		return len(a)
	}
	
	// find minimum of bigger positions
	minBigger := bigger[0]
	for _, pos := range bigger {
		if pos < minBigger {
			minBigger = pos
		}
	}
	return minBigger
}
