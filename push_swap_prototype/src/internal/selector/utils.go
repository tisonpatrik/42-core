package selector

import (
	"math"
	"push_swap_prototype/internal/utils"
	"sort"
)

// SelectorConfig holds configuration parameters for the selector package
type SelectorConfig struct {
	MaxCandidates        int // Maximum number of candidates to evaluate
	CostThresholdOffset  int // Offset added to minimum base cost for filtering
	SizePenaltyFactor    int // Factor for size-based penalties
	HeuristicOffset      int // Offset for heuristic calculations
	HeuristicDivisor     int // Divisor for heuristic calculations
}

// DefaultSelectorConfig returns the default configuration for the selector
func DefaultSelectorConfig() SelectorConfig {
	return SelectorConfig{
		MaxCandidates:       30,
		CostThresholdOffset: 1,
		SizePenaltyFactor:   10,
		HeuristicOffset:     1,
		HeuristicDivisor:    2,
	}
}



// Candidate represents a position with its calculated score for evaluation
type Candidate struct {
	Position Position // The position details (costs, indices)
	Score    int      // Combined score (base cost + penalty)
}

// NewCandidate creates a new Candidate with the given position and score
func NewCandidate(pos Position, score int) Candidate {
	return Candidate{
		Position: pos,
		Score:    score,
	}
}

// FilterCandidatesByThreshold filters candidates to keep only those within the cost threshold
func FilterCandidatesByThreshold(candidates []Candidate, thresholdOffset int) []Candidate {
	if len(candidates) == 0 {
		return candidates
	}

	// Find minimum base cost
	minBaseCost := math.MaxInt
	for _, candidate := range candidates {
		if candidate.Position.Total < minBaseCost {
			minBaseCost = candidate.Position.Total
		}
	}

	// Filter by threshold
	threshold := minBaseCost + thresholdOffset
	filtered := make([]Candidate, 0, len(candidates))
	for _, candidate := range candidates {
		if candidate.Position.Total <= threshold {
			filtered = append(filtered, candidate)
		}
	}

	return filtered
}

// SelectTopKCandidates sorts candidates by score and returns the top K candidates
func SelectTopKCandidates(candidates []Candidate, maxK int) []Candidate {
	if len(candidates) == 0 {
		return candidates
	}

	// Sort by score with tie-breakers
	sort.Slice(candidates, func(i, j int) bool {
		if candidates[i].Score != candidates[j].Score {
			return candidates[i].Score < candidates[j].Score
		}
		// Use BetterPosition for tie-breakers
		return BetterPosition(candidates[i].Position, candidates[j].Position)
	})

	// Limit to top K candidates if specified
	if maxK > 0 && maxK < len(candidates) {
		return candidates[:maxK]
	}
	return candidates
}
// BetterPosition compares two positions and returns true if the first position is better than the second
func BetterPosition(a, b Position) bool {
	if a.Total != b.Total {
		return a.Total < b.Total
	}
	if utils.Abs(a.CostA) != utils.Abs(b.CostA) {
		return utils.Abs(a.CostA) < utils.Abs(b.CostA)
	}
	if a.ToIndex != b.ToIndex {
		return a.ToIndex < b.ToIndex
	}
	return a.FromIndex < b.FromIndex
}

// SelectBestCandidate selects the best candidate from a list of candidates
func SelectBestCandidate(candidates []Candidate) Position {
	if len(candidates) == 0 {
		return Position{Total: math.MaxInt}
	}
	
	best := candidates[0].Position
	for _, candidate := range candidates {
		if BetterPosition(candidate.Position, best) {
			best = candidate.Position
		}
	}
	return best
}

// MergedCost calculates the total cost when combining two operations,
// accounting for common rotations (rr/rrr)
func MergedCost(a, b int) int {
	same := (a >= 0 && b >= 0) || (a < 0 && b < 0)
	if same {
		if utils.Abs(a) > utils.Abs(b) {
			return utils.Abs(a)
		}
		return utils.Abs(b)
	}
	return utils.Abs(a) + utils.Abs(b)
}

// SignedCost calculates the signed cost (positive for rotate, negative for reverse rotate)
// to move an element to a specific index
func SignedCost(idx, size int) int {
	if idx <= size/2 {
		return idx
	}
	return idx - size
}

// IsEmpty returns true if the slice is empty
func IsEmpty(s []int) bool {
	return len(s) == 0
}

// IsEmptyOrSingle returns true if the slice has 0 or 1 elements
func IsEmptyOrSingle(s []int) bool {
	return len(s) <= 1
}

