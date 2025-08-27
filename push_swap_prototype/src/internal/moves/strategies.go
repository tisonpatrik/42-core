package moves

import (
	"push_swap_prototype/internal/position"
)

// MoveStrategy represents different strategies for moving elements between stacks
type MoveStrategy struct {
	StrategyType string
	Moves        int
}

// MoveStrategies holds all possible move strategies for comparison
type MoveStrategies struct {
	BothRotate     MoveStrategy // Both stacks rotate in same direction
	BothReverse    MoveStrategy // Both stacks reverse rotate in same direction
	RotateAReverseB MoveStrategy // Rotate A, reverse rotate B
	ReverseARotateB MoveStrategy // Reverse rotate A, rotate B
}

// lcm calculates the least common move (equivalent to lcm in C)
func LeastCommonMove(pos position.Position, lenA, lenB int, returnMove bool) int {
	strategies := calculateMoveStrategies(pos, lenA, lenB)
	
	if returnMove {
		// Return strategy index based on type
		switch findBestStrategy(strategies, true).(string) {
		case "both_rotate":
			return 0
		case "both_reverse":
			return 1
		case "rotate_a_reverse_b":
			return 2
		case "reverse_a_rotate_b":
			return 3
		default:
			return 0
		}
	}
	
	// Return minimum number of moves
	return findBestStrategy(strategies, false).(int)
}

// calculateMoveStrategies calculates all possible move strategies for given positions
func calculateMoveStrategies(pos position.Position, lenA, lenB int) MoveStrategies {
	// Handle edge case where StackB is 0
	tempPosB := pos.StackB
	if pos.StackB == 0 {
		pos.StackB = pos.StackA
	}
	
	strategies := MoveStrategies{
		BothRotate: MoveStrategy{
			StrategyType: "both_rotate",
			Moves:        max(pos.StackA, pos.StackB),
		},
		BothReverse: MoveStrategy{
			StrategyType: "both_reverse",
			Moves:        max(lenA-pos.StackA, lenB-pos.StackB),
		},
		RotateAReverseB: MoveStrategy{
			StrategyType: "rotate_a_reverse_b",
			Moves:        pos.StackA + (lenB - pos.StackB),
		},
		ReverseARotateB: MoveStrategy{
			StrategyType: "reverse_a_rotate_b",
			Moves:        (lenA - pos.StackA) + pos.StackB,
		},
	}
	
	// Restore original StackB value
	if tempPosB == 0 {
		pos.StackB = tempPosB
	}
	
	return strategies
}


// findBestStrategy finds the strategy with the minimum number of moves
func findBestStrategy(strategies MoveStrategies,returnStrategyType bool) any {
	bestStrategy := strategies.BothRotate
	minMoves := strategies.BothRotate.Moves
	
	if strategies.BothReverse.Moves < minMoves {
		bestStrategy = strategies.BothReverse
		minMoves = strategies.BothReverse.Moves
	}
	if strategies.RotateAReverseB.Moves < minMoves {
		bestStrategy = strategies.RotateAReverseB
		minMoves = strategies.RotateAReverseB.Moves
	}
	if strategies.ReverseARotateB.Moves < minMoves {
		bestStrategy = strategies.ReverseARotateB
		minMoves = strategies.ReverseARotateB.Moves
	}
	
	if returnStrategyType {
		return bestStrategy.StrategyType
	}
	return minMoves
}

