package selector

import (
	"math"
	"sort"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
	"push_swap_prototype/internal/utils"
)

// PickNearBest selects the best position for moving an element from B to A using near-optimal strategy.
// It considers multiple candidates and uses micro-lookahead to make the best choice.
func PickNearBest(ps *ops.SortingState, maxCandidates int) Position {
	a := snapshot(ps.A)
	b := snapshot(ps.B)

	candidates := enumerateBtoA(a, b) // Total = base
	if len(candidates) == 0 {
		return CheapestAtoB(ps)
	}

	return pickNearBest(a, b, candidates, maxCandidates, false)
}

// filterCandidatesByCostThresholdBtoA filters candidates to keep only those within a cost threshold
// of the minimum base cost, reducing the search space for more efficient processing.
func filterCandidatesByCostThresholdBtoA(candidates []scoredPos) []scoredPos {
	if len(candidates) == 0 {
		return candidates
	}

	// Find the minimum base cost among all candidates
	minBaseCost := math.MaxInt
	for _, candidate := range candidates {
		if candidate.pos.Total < minBaseCost {
			minBaseCost = candidate.pos.Total
		}
	}

	// Keep candidates within threshold (minBase + 1) to maintain good options
	// while filtering out obviously suboptimal ones
	threshold := minBaseCost + DefaultCostThresholdOffset

	filteredCandidates := make([]scoredPos, 0, len(candidates))
	for _, candidate := range candidates {
		if candidate.pos.Total <= threshold {
			filteredCandidates = append(filteredCandidates, candidate)
		}
	}

	return filteredCandidates
}

// selectTopKCandidatesBtoA sorts candidates by score and returns the top K candidates.
// Score includes base cost plus penalty for stable ordering. If maxCandidates is 0 or
// greater than available candidates, returns all candidates.
func selectTopKCandidatesBtoA(candidates []scoredPos, maxCandidates int) []scoredPos {
	if len(candidates) == 0 {
		return candidates
	}

	// Sort by score (base + penalty) with tie-breakers for stable ordering
	sort.Slice(candidates, func(i, j int) bool {
		if candidates[i].score != candidates[j].score {
			return candidates[i].score < candidates[j].score
		}
		// Tie-breakers: prefer lower absolute costs, then by indices
		posI, posJ := candidates[i].pos, candidates[j].pos
		if utils.Abs(posI.CostA) != utils.Abs(posJ.CostA) {
			return utils.Abs(posI.CostA) < utils.Abs(posJ.CostA)
		}
		if posI.ToIndex != posJ.ToIndex {
			return posI.ToIndex < posJ.ToIndex
		}
		return posI.FromIndex < posJ.FromIndex
	})

	// Limit to top K candidates if specified
	if maxCandidates > 0 && maxCandidates < len(candidates) {
		return candidates[:maxCandidates]
	}

	return candidates
}

// evaluateCandidatesWithLookahead performs micro-lookahead evaluation (depth 1) on candidates.
// It simulates each move, calculates a heuristic estimate of remaining work, and selects
// the candidate with the best combined score (actual cost + heuristic estimate).
func evaluateCandidatesWithLookahead(a, b []int, candidates []scoredPos, phaseAtoB bool) Position {
	if len(candidates) == 0 {
		return Position{}
	}

	bestPosition := candidates[0].pos
	bestScore := math.MaxInt

	for _, candidate := range candidates {
		position := candidate.pos

		// Simulate the move and get the actual cost (g)
		newA, _, actualCost := simulateOnce(a, b, position, phaseAtoB)

		// Calculate heuristic estimate of remaining work (h)
		// Using breakpoints/2 as a cheap heuristic for stack disorder
		breakpoints := breakpointsCyclic(newA)
		heuristicEstimate := (breakpoints + 1) / 2

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

func pickNearBest(a, b []int, candidates []scoredPos, maxCandidates int, phaseAtoB bool) Position {
	// 1) Filter candidates by cost threshold
	filteredCandidates := filterCandidatesByCostThresholdBtoA(candidates)

	// 2) Select top-K candidates by score for further evaluation
	filteredCandidates = selectTopKCandidatesBtoA(filteredCandidates, maxCandidates)

	// 3) Evaluate candidates with micro-lookahead and select the best
	return evaluateCandidatesWithLookahead(a, b, filteredCandidates, phaseAtoB)
}

// Enumeration (slice version, fast)
// -------------------------------

type scoredPos struct {
	pos   Position // Total = base
	score int      // base + tiny penalty (for ordering only)
}

func enumerateBtoA(a, b []int) []scoredPos {
	sizeA, sizeB := len(a), len(b)
	if sizeB == 0 {
		return nil
	}
	out := make([]scoredPos, 0, sizeB)

	for i := 0; i < sizeB; i++ {
		val := b[i]
		toIdx := targetPosInA(a, val)

		costA := SignedCost(toIdx, sizeA)
		costB := SignedCost(i, sizeB)

		base := MergedCost(costA, costB)

		out = append(out, scoredPos{
			pos: Position{
				FromIndex: i, ToIndex: toIdx,
				CostA: costA, CostB: costB,
				Total: base,
			},
			score: base, // without penalty
		})
	}
	return out
}

// Simulation depth 1 (without slice rotations)
// -------------------------------------

func simulateOnce(a, b []int, p Position, phaseAtoB bool) ([]int, []int, int) {
	rot := MergedCost(p.CostA, p.CostB) // actual rotations
	if phaseAtoB {
		ia := norm(len(a), p.CostA)
		ib := norm(len(b), p.CostB)
		x := a[ia]
		na := removeAt(a, ia)
		nb := insertAt(b, ib, x)
		return na, nb, rot + 1
	}
	ib := norm(len(b), p.CostB)
	ia := norm(len(a), p.CostA)
	x := b[ib]
	nb := removeAt(b, ib)
	na := insertAt(a, ia, x)
	return na, nb, rot + 1
}

func norm(n, k int) int {
	if n == 0 {
		return 0
	}
	k = ((k % n) + n) % n
	return k
}
func removeAt(s []int, i int) []int {
	out := make([]int, 0, len(s)-1)
	out = append(out, s[:i]...)
	out = append(out, s[i+1:]...)
	return out
}
func insertAt(s []int, i, x int) []int {
	out := make([]int, 0, len(s)+1)
	out = append(out, s[:i]...)
	out = append(out, x)
	out = append(out, s[i:]...)
	return out
}

// Heuristic (cheap)
// ------------------

func breakpointsCyclic(a []int) int {
	n := len(a)
	if n <= 1 {
		return 0
	}
	br := 0
	for i := 0; i < n-1; i++ {
		if a[i] > a[i+1] {
			br++
		}
	}
	if a[n-1] > a[0] {
		br++
	}
	return br
}

// Local helpers (targeting/penalty) over slice
// ---------------------------------------------------

func targetPosInA(a []int, val int) int {
	n := len(a)
	if n == 0 {
		return 0
	}
	bestIdx, bestVal := -1, 0
	for i, x := range a {
		if x > val {
			if bestIdx == -1 || x < bestVal {
				bestVal, bestIdx = x, i
			}
		}
	}
	if bestIdx != -1 {
		return bestIdx
	}
	// index of minimum
	minIdx, minVal := 0, a[0]
	for i, x := range a {
		if x < minVal {
			minVal, minIdx = x, i
		}
	}
	return minIdx
}

// Utility
// -------


func snapshot(s *stack.Stack) []int {
	return SnapshotStack(s)
}
