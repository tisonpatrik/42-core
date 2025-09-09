package selector

import (
	"math"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
	"push_swap_prototype/internal/utils"
	"sort"
)

type Position struct {
	FromIndex int
	ToIndex   int
	CostA     int
	CostB     int
	Total     int // pure base cost = MergedCost(CostA, CostB)
}


// CheapestAtoB finds the position with the lowest cost for moving an element from stack A to stack B.
// It evaluates all possible positions and returns the one with minimal rotation cost.
func CheapestAtoB(ps *ops.SortingState) Position {
	best := Position{Total: math.MaxInt}
	for _, p := range enumerateCandidatesAtoB(ps.A, ps.B, 0) { // 0 => all
		if BetterPosition(p, best) {
			best = p
		}
	}
	return best
}


// enumerateCandidatesAtoB: returns top-K candidates by score (base + fine penalty),
// but stores **only base** (MergedCost) in Position.Total.
func enumerateCandidatesAtoB(a, b *stack.Stack, k int) []Position {
	sizeA := stack.GetSize(a)
	if sizeA == 0 {
		return nil
	}

	// Build candidates from stack A
	candidates := buildCandidatesFromStackA(a, b)
	
	// Sort candidates by score with tie-breakers
	sortCandidatesByScore(candidates)
	
	// Filter candidates by cost threshold
	filtered := filterCandidatesByCostThresholdAtoB(candidates)
	
	// Return top K candidates
	return selectTopKCandidatesAtoB(filtered, k)
}

// scoredCandidate represents a position with its calculated score
type scoredCandidate struct {
	pos   Position
	score int // base + penalty
}

// buildCandidatesFromStackA builds candidate positions by evaluating each element in stack A
func buildCandidatesFromStackA(a, b *stack.Stack) []scoredCandidate {
	sizeA := stack.GetSize(a)
	bvals := SnapshotStack(b)
	candidates := make([]scoredCandidate, 0, sizeA)

	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		val := n.GetContent()
		toIdx := insertionIndexInBVals(bvals, val)

		costA := SignedCost(i, sizeA)
		costB := SignedCost(toIdx, len(bvals))

		base := MergedCost(costA, costB)
		penalty := localOrderPenaltyInBV(bvals, toIdx, val)

		candidates = append(candidates, scoredCandidate{
			pos: Position{
				FromIndex: i,
				ToIndex:   toIdx,
				CostA:     costA,
				CostB:     costB,
				Total:     base, // storing pure base cost
			},
			score: base + penalty, // candidate ordering
		})
	}

	return candidates
}

// sortCandidatesByScore sorts candidates by score with tie-breakers
func sortCandidatesByScore(candidates []scoredCandidate) {
	sort.Slice(candidates, func(i, j int) bool {
		if candidates[i].score != candidates[j].score {
			return candidates[i].score < candidates[j].score
		}
		ai, aj := candidates[i].pos, candidates[j].pos
		if utils.Abs(ai.CostA) != utils.Abs(aj.CostA) {
			return utils.Abs(ai.CostA) < utils.Abs(aj.CostA)
		}
		if ai.ToIndex != aj.ToIndex {
			return ai.ToIndex < aj.ToIndex
		}
		return ai.FromIndex < aj.FromIndex
	})
}

// filterCandidatesByCostThresholdAtoB filters candidates to keep only those within cost threshold for AtoB operations
func filterCandidatesByCostThresholdAtoB(candidates []scoredCandidate) []Position {
	if len(candidates) == 0 {
		return nil
	}

	// Find minimum base cost
	minBase := math.MaxInt
	for _, candidate := range candidates {
		if candidate.pos.Total < minBase {
			minBase = candidate.pos.Total
		}
	}

	// Filter by threshold
	threshold := minBase + DefaultCostThreshold
	filtered := make([]Position, 0, len(candidates))
	for _, candidate := range candidates {
		if candidate.pos.Total <= threshold {
			filtered = append(filtered, candidate.pos)
		}
	}

	return filtered
}

// selectTopKCandidatesAtoB returns the top K candidates from the filtered list for AtoB operations
func selectTopKCandidatesAtoB(filtered []Position, k int) []Position {
	if k > 0 && k < len(filtered) {
		return filtered[:k]
	}
	return filtered
}




// insertionIndexInBVals: index in B (over slice), where to insert val, we want local "prev > val > next"
func insertionIndexInBVals(b []int, val int) int {
	n := len(b)
	if n == 0 {
		return 0
	}
	// wrap: out of range => after maximum
	minB, maxB, idxMax := b[0], b[0], 0
	for i, x := range b {
		if x < minB { minB = x }
		if x > maxB { maxB = x; idxMax = i }
	}
	if val < minB || val > maxB {
		return (idxMax + 1) % n
	}
	for j := 0; j < n; j++ {
		prev := b[(j-1+n)%n]
		next := b[j]
		if prev > val && val > next {
			return j
		}
	}
	return 0
}

// fine penalty over slice (0/1)
func localOrderPenaltyInBV(b []int, toIdx int, val int) int {
	n := len(b)
	if n < 2 {
		return 0
	}
	prev := b[(toIdx-1+n)%n]
	next := b[toIdx%n]
	if prev > val && val > next {
		return 0
	}
	return 1
}



