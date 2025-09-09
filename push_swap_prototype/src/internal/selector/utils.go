package selector

import (
	"push_swap_prototype/internal/stack"
	"push_swap_prototype/internal/utils"
)

// Constants for cost calculations and thresholds
const (
	// DefaultCostThresholdOffset is the offset added to minimum base cost for filtering candidates
	DefaultCostThresholdOffset = 1
	// DefaultCostThreshold is the threshold for filtering candidates in AtoB operations
	DefaultCostThreshold = 2
	// DefaultMaxCandidates is the default maximum number of candidates to evaluate
	DefaultMaxCandidates = 30
)

// SignedCost calculates the signed cost (positive for rotate, negative for reverse rotate) to move an element to a specific index.
func SignedCost(idx, size int) int {
    if idx <= size/2 {
        return idx
    }
    return idx - size
}

// MergedCost calculates the total cost when combining two operations, accounting for common rotations (rr/rrr).
func MergedCost(a, b int) int {
    same := (a >= 0 && b >= 0) || (a < 0 && b < 0)
    if same {
        if utils.Abs(a) > utils.Abs(b) { return utils.Abs(a) }
        return utils.Abs(b)
    }
    return utils.Abs(a) + utils.Abs(b)
}

// BetterPosition compares two positions and returns true if the first position is better than the second.
// This consolidates the duplicate better/betterPos functions.
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

// SnapshotStack converts a stack to a slice representation for efficient processing.
// This consolidates the duplicate snapshot/snapshotValues functions.
func SnapshotStack(s *stack.Stack) []int {
	out := make([]int, 0, stack.GetSize(s))
	for n := stack.GetHead(s); n != nil; n = n.GetNext() {
		out = append(out, n.GetContent())
	}
	return out
}

