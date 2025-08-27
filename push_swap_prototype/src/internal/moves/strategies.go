package moves

import (
	"push_swap_prototype/internal/position"
)

// Strategy represents different strategies for moving elements between stacks
type Strategy int

const (
	BothRotate Strategy = iota
	BothReverse
	RotateAReverseB
	ReverseARotateB
)

// lcm calculates the least common move (equivalent to lcm in C)
func LeastCommonMove(pos position.Position, lenA, lenB int, returnMove bool) int {
	if returnMove {
		return int(findBestStrategy(pos, lenA, lenB))
	}
	return findMinMoves(pos, lenA, lenB)
}

// findBestStrategy finds the best strategy for given positions
func findBestStrategy(pos position.Position, lenA, lenB int) Strategy {
	// Handle edge case where StackB is 0
	tempPosB := pos.StackB
	if pos.StackB == 0 {
		pos.StackB = pos.StackA
	}
	
	// Calculate move costs for each strategy
	bothRotate := calculateMoveCost(pos.StackA, pos.StackB)
	bothReverse := calculateMoveCost(lenA-pos.StackA, lenB-pos.StackB)
	rotateAReverseB := pos.StackA + (lenB - pos.StackB)
	reverseARotateB := (lenA - pos.StackA) + pos.StackB
	
	// Restore original StackB value
	if tempPosB == 0 {
		pos.StackB = tempPosB
	}
	
	// Find minimum without array operations
	minMoves := bothRotate
	bestStrategy := BothRotate
	
	if bothReverse < minMoves {
		minMoves = bothReverse
		bestStrategy = BothReverse
	}
	if rotateAReverseB < minMoves {
		minMoves = rotateAReverseB
		bestStrategy = RotateAReverseB
	}
	if reverseARotateB < minMoves {
		bestStrategy = ReverseARotateB
	}
	
	return bestStrategy
}

// findMinMoves finds the minimum number of moves needed
func findMinMoves(pos position.Position, lenA, lenB int) int {
	// Handle edge case where StackB is 0
	tempPosB := pos.StackB
	if pos.StackB == 0 {
		pos.StackB = pos.StackA
	}
	
	// Calculate move costs for each strategy
	bothRotate := calculateMoveCost(pos.StackA, pos.StackB)
	bothReverse := calculateMoveCost(lenA-pos.StackA, lenB-pos.StackB)
	rotateAReverseB := pos.StackA + (lenB - pos.StackB)
	reverseARotateB := (lenA - pos.StackA) + pos.StackB
	
	// Restore original StackB value
	if tempPosB == 0 {
		pos.StackB = tempPosB
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

