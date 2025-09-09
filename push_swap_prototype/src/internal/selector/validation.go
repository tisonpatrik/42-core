package selector

import (
	"fmt"
)

// ValidatePosition validates that a position is within valid bounds
func ValidatePosition(pos Position, sizeA, sizeB int) error {
	if pos.FromIndex < 0 || pos.FromIndex >= sizeA {
		return fmt.Errorf("invalid FromIndex %d: must be in range [0, %d)", pos.FromIndex, sizeA)
	}
	if pos.ToIndex < 0 || pos.ToIndex >= sizeB {
		return fmt.Errorf("invalid ToIndex %d: must be in range [0, %d)", pos.ToIndex, sizeB)
	}
	return nil
}

// ValidateCandidates validates that candidates are properly formed
func ValidateCandidates(candidates []Candidate) error {
	for i, candidate := range candidates {
		if candidate.Position.Total < 0 {
			return fmt.Errorf("candidate %d has negative total cost: %d", i, candidate.Position.Total)
		}
		if candidate.Score < 0 {
			return fmt.Errorf("candidate %d has negative score: %d", i, candidate.Score)
		}
	}
	return nil
}

// ValidateConfig validates the selector configuration
func ValidateConfig(config SelectorConfig) error {
	if config.MaxCandidates <= 0 {
		return fmt.Errorf("MaxCandidates must be positive, got %d", config.MaxCandidates)
	}
	if config.CostThresholdOffset < 0 {
		return fmt.Errorf("CostThresholdOffset must be non-negative, got %d", config.CostThresholdOffset)
	}
	if config.SizePenaltyFactor <= 0 {
		return fmt.Errorf("SizePenaltyFactor must be positive, got %d", config.SizePenaltyFactor)
	}
	if config.HeuristicDivisor <= 0 {
		return fmt.Errorf("HeuristicDivisor must be positive, got %d", config.HeuristicDivisor)
	}
	return nil
}

// ValidateStacks validates that stacks are in valid state for operations
func ValidateStacks(a, b []int) error {
	if len(a) == 0 && len(b) == 0 {
		return fmt.Errorf("both stacks cannot be empty")
	}
	return nil
}
