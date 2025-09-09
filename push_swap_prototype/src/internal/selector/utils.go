package selector

import (
	"math"
	"push_swap_prototype/internal/utils"
	"sort"
)

// SelectorConfig holds configuration parameters for the selector package
type SelectorConfig struct {
	MaxCandidates        int     // Maximum number of candidates to evaluate
	CostThresholdOffset  int     // Offset added to minimum base cost for filtering
	HeuristicWeight      float64 // Weight for heuristic calculations
	SizePenaltyFactor    int     // Factor for size-based penalties
	HeuristicOffset      int     // Offset for heuristic calculations
	HeuristicDivisor     int     // Divisor for heuristic calculations
}

// DefaultSelectorConfig returns the default configuration for the selector
func DefaultSelectorConfig() SelectorConfig {
	return SelectorConfig{
		MaxCandidates:       30,
		CostThresholdOffset: 1,
		HeuristicWeight:     0.5,
		SizePenaltyFactor:   10,
		HeuristicOffset:     1,
		HeuristicDivisor:    2,
	}
}

// WithDefaults returns a config with default values for any zero values
func (sc *SelectorConfig) WithDefaults() SelectorConfig {
	config := *sc
	if config.MaxCandidates == 0 {
		config.MaxCandidates = 30
	}
	if config.CostThresholdOffset == 0 {
		config.CostThresholdOffset = 1
	}
	if config.HeuristicWeight == 0 {
		config.HeuristicWeight = 0.5
	}
	if config.SizePenaltyFactor == 0 {
		config.SizePenaltyFactor = 10
	}
	if config.HeuristicOffset == 0 {
		config.HeuristicOffset = 1
	}
	if config.HeuristicDivisor == 0 {
		config.HeuristicDivisor = 2
	}
	return config
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

