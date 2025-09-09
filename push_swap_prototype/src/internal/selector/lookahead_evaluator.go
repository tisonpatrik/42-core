package selector

import (
	"math"
)

// LookaheadEvaluator handles micro-lookahead evaluation of candidates
type LookaheadEvaluator struct {
	config   SelectorConfig
	simulator *MoveSimulator
}

// NewLookaheadEvaluator creates a new LookaheadEvaluator with the given configuration
func NewLookaheadEvaluator(config SelectorConfig) *LookaheadEvaluator {
	return &LookaheadEvaluator{
		config:    config,
		simulator: NewMoveSimulator(),
	}
}

// EvaluateWithLookahead performs micro-lookahead evaluation (depth 1) on candidates
func (le *LookaheadEvaluator) EvaluateWithLookahead(a, b []int, candidates []Candidate, direction MoveDirection) Position {
	if len(candidates) == 0 {
		return Position{}
	}

	bestPosition := candidates[0].Position
	bestScore := math.MaxInt

	for _, candidate := range candidates {
		position := candidate.Position

		// Simulate the move and get the actual cost (g)
		newA, _, actualCost := le.simulateMove(a, b, position, direction)

		// Calculate heuristic estimate of remaining work (h)
		heuristicEstimate := le.calculateHeuristic(newA)

		// Combined score = actual cost + heuristic estimate
		totalScore := actualCost + heuristicEstimate

		// Select better position (lower score, or same score with better position)
		if totalScore < bestScore || (totalScore == bestScore && BetterPosition(position, bestPosition)) {
			bestPosition = position
			bestScore = totalScore
		}
	}

	return bestPosition
}

// simulateMove simulates a single move and returns the resulting stacks and cost
func (le *LookaheadEvaluator) simulateMove(a, b []int, pos Position, direction MoveDirection) ([]int, []int, int) {
	return le.simulator.SimulateMove(a, b, pos, direction)
}

// calculateHeuristic calculates a heuristic estimate of remaining work
func (le *LookaheadEvaluator) calculateHeuristic(stack []int) int {
	// Using breakpoints and size penalty as a cheap heuristic for stack disorder
	breakpoints := CalculateBreakpoints(stack)
	sizePenalty := len(stack) / le.config.SizePenaltyFactor
	return (breakpoints + sizePenalty + le.config.HeuristicOffset) / le.config.HeuristicDivisor
}
