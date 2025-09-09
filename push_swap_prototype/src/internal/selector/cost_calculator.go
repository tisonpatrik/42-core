package selector

import (
	"push_swap_prototype/internal/utils"
)

// CostCalculator handles all cost-related calculations for position evaluation
type CostCalculator struct {
	config SelectorConfig
}

// NewCostCalculator creates a new CostCalculator with the given configuration
func NewCostCalculator(config SelectorConfig) *CostCalculator {
	return &CostCalculator{
		config: config,
	}
}

// CalculatePositionCost calculates the complete cost for moving an element
// from fromIdx to toIdx between stacks of given sizes
func (cc *CostCalculator) CalculatePositionCost(fromIdx, toIdx, sizeA, sizeB int) Position {
	costA := SignedCost(fromIdx, sizeA)
	costB := SignedCost(toIdx, sizeB)
	base := cc.CalculateMergedCost(costA, costB)
	
	return Position{
		FromIndex: fromIdx,
		ToIndex:   toIdx,
		CostA:     costA,
		CostB:     costB,
		Total:     base,
	}
}

// CalculateMergedCost calculates the total cost when combining two operations,
// accounting for common rotations (rr/rrr)
func (cc *CostCalculator) CalculateMergedCost(costA, costB int) int {
	same := (costA >= 0 && costB >= 0) || (costA < 0 && costB < 0)
	if same {
		if utils.Abs(costA) > utils.Abs(costB) {
			return utils.Abs(costA)
		}
		return utils.Abs(costB)
	}
	return utils.Abs(costA) + utils.Abs(costB)
}

// CalculatePenalty calculates penalty for local order violation in stack B
func (cc *CostCalculator) CalculatePenalty(stack []int, toIdx int, val int) int {
	n := len(stack)
	if n < 2 {
		return 0
	}
	
	prev := stack[(toIdx-1+n)%n]
	next := stack[toIdx%n]
	if prev > val && val > next {
		return 0
	}
	return 1
}

// SignedCost calculates the signed cost (positive for rotate, negative for reverse rotate)
// to move an element to a specific index
func SignedCost(idx, size int) int {
	if idx <= size/2 {
		return idx
	}
	return idx - size
}
