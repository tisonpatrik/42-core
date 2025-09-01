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
func PickNearBest(ps *ops.SortingState, candK int) Position {
	a := snapshot(ps.A)
	b := snapshot(ps.B)

	cands := enumerateBtoA(a, b) // Total = base
	if len(cands) == 0 {
		return CheapestAtoB(ps)
	}
	return pickNearBest(a, b, cands, candK, false)
}


func pickNearBest(a, b []int, all []scoredPos, candK int, phaseAtoB bool) Position {
	// 1) minBase + gating (≤ minBase+1)
	minBase := math.MaxInt
	for _, s := range all {
		if s.pos.Total < minBase {
			minBase = s.pos.Total
		}
	}
	threshold := minBase + 1

	filter := make([]scoredPos, 0, len(all))
	for _, s := range all {
		if s.pos.Total <= threshold {
			filter = append(filter, s)
		}
	}

	// 2) top-K by Score (Score = base + penalty) – to maintain stable ordering
	sort.Slice(filter, func(i, j int) bool {
		if filter[i].score != filter[j].score {
			return filter[i].score < filter[j].score
		}
		pi, pj := filter[i].pos, filter[j].pos
		if utils.Abs(pi.CostA) != utils.Abs(pj.CostA) {
			return utils.Abs(pi.CostA) < utils.Abs(pj.CostA)
		}
		if pi.ToIndex != pj.ToIndex {
			return pi.ToIndex < pj.ToIndex
		}
		return pi.FromIndex < pj.FromIndex
	})
	if candK > 0 && candK < len(filter) {
		filter = filter[:candK]
	}

	// 3) micro lookahead (depth 1): evaluate g+h and select
	best := filter[0].pos
	bestScore := math.MaxInt

	for _, s := range filter {
		p := s.pos
		na, _, g := simulateOnce(a, b, p, phaseAtoB)
		// cheap heuristic: ceil(breakpoints/2)
		h := (breakpointsCyclic(na) + 1) / 2
		score := g + h

		if score < bestScore || (score == bestScore && betterPos(p, best)) {
			best, bestScore = p, score
		}
	}

	return best
}

// Enumeration (slice version, fast)
// -------------------------------

type scoredPos struct {
	pos   Position // Total = base
	score int            // base + tiny penalty (for ordering only)
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

func betterPos(a, b Position) bool {
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

func snapshot(s *stack.Stack) []int {
	out := make([]int, 0, stack.GetSize(s))
	for n := stack.GetHead(s); n != nil; n = n.GetNext() {
		out = append(out, n.GetContent())
	}
	return out
}
