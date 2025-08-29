package moves

// Strategy represents different strategies for moving elements between stacks
type Strategy int

const (
	BothRotate Strategy = iota
	BothReverse
	RotateAReverseB
	ReverseARotateB
)

// lcm calculates the least common move (equivalent to lcm in C)
func LeastCommonMove(pos Position, lenA, lenB int, returnMove bool) int {
	if returnMove {
		return int(findBestStrategy(pos, lenA, lenB))
	}
	return findMinMoves(pos, lenA, lenB)
}

// findBestStrategy finds the best strategy for given positions
func findBestStrategy(pos Position, lenA, lenB int) Strategy {
	// Handle edge case where StackB is 0
	tempPosB := pos.CostB
	if pos.CostB == 0 {
		pos.CostB = pos.CostA
	}
	
	// Calculate move costs for each strategy
	bothRotate := calculateMoveCost(pos.CostA, pos.CostB)
	bothReverse := calculateMoveCost(lenA-pos.CostA, lenB-pos.CostB)
	rotateAReverseB := pos.CostA + (lenB - pos.CostB)
	reverseARotateB := (lenA - pos.CostA) + pos.CostB
	
	// Restore original StackB value
	if tempPosB == 0 {
		pos.CostB = tempPosB
	}
	
	// Find minimum with deterministic tie-breaking
	// Priority order: BothRotate (0) > BothReverse (1) > RotateAReverseB (2) > ReverseARotateB (3)
	minMoves := bothRotate
	bestStrategy := BothRotate
	
	if bothReverse < minMoves {
		minMoves = bothReverse
		bestStrategy = BothReverse
	} else if bothReverse == minMoves {
		// Tie: prefer BothRotate (higher priority)
		// bestStrategy stays BothRotate
	}
	
	if rotateAReverseB < minMoves {
		minMoves = rotateAReverseB
		bestStrategy = RotateAReverseB
	} else if rotateAReverseB == minMoves {
		// Tie: prefer current best strategy (higher priority)
		// bestStrategy stays unchanged
	}
	
	if reverseARotateB < minMoves {
		bestStrategy = ReverseARotateB
	}
	// Note: ReverseARotateB has lowest priority, so no tie-breaking needed
	
	return bestStrategy
}

// findMinMoves finds the minimum number of moves needed
func findMinMoves(pos Position, lenA, lenB int) int {
	// Handle edge case where StackB is 0
	tempPosB := pos.CostB
	if pos.CostB == 0 {
		pos.CostB = pos.CostA
	}
	
	// Calculate move costs for each strategy
	bothRotate := calculateMoveCost(pos.CostA, pos.CostB)
	bothReverse := calculateMoveCost(lenA-pos.CostA, lenB-pos.CostB)
	rotateAReverseB := pos.CostA + (lenB - pos.CostB)
	reverseARotateB := (lenA - pos.CostA) + pos.CostB
	
	// Restore original StackB value
	if tempPosB == 0 {
		pos.CostB = tempPosB
	}
	
	// Find minimum without array operations
	minMoves := bothRotate
	if bothReverse < minMoves {
		minMoves = bothReverse
	}
	if rotateAReverseB < minMoves {
		minMoves = rotateAReverseB
	}
	if reverseARotateB < minMoves {
		minMoves = reverseARotateB
	}
	
	return minMoves
}

// calculateMoveCost calculates the cost (number of moves) for a given strategy
func calculateMoveCost(movesA, movesB int) int {
	if movesA > movesB {
		return movesA
	}
	return movesB
}

