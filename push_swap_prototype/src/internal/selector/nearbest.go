package selector

import (
	"math"
	"sort"

	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
	"push_swap_prototype/internal/utils"
)

// Public API
// ----------

func PickNearBestAtoB(ps *ops.SortingState, candK int) moves.Position {
	a := snapshot(ps.A)
	b := snapshot(ps.B)

	cands := enumerateAtoB(a, b) // Total = base, Score = base + tiny penalty
	if len(cands) == 0 {
		return moves.CheapestBtoA(ps) // nucený návrat (teoreticky nenastane)
	}
	return pickNearBest(a, b, cands, candK, true)
}

func PickNearBestBtoA(ps *ops.SortingState, candK int) moves.Position {
	a := snapshot(ps.A)
	b := snapshot(ps.B)

	cands := enumerateBtoA(a, b) // Total = base
	if len(cands) == 0 {
		return moves.CheapestAtoB(ps)
	}
	return pickNearBest(a, b, cands, candK, false)
}

// Core
// ----

func pickNearBest(a, b []int, all []scoredPos, candK int, phaseAtoB bool) moves.Position {
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

	// 2) top-K podle Score (Score = base + penalizace) – aby zůstalo stabilní pořadí
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

	// 3) micro lookahead (hloubka 1): vyhodnoť g+h a vyber
	best := filter[0].pos
	bestScore := math.MaxInt

	for _, s := range filter {
		p := s.pos
		na, _, g := simulateOnce(a, b, p, phaseAtoB)
		// levná heuristika: ceil(breakpoints/2)
		h := (breakpointsCyclic(na) + 1) / 2
		score := g + h

		if score < bestScore || (score == bestScore && betterPos(p, best)) {
			best, bestScore = p, score
		}
	}

	return best
}

// Enumerace (slice verze, rychlé)
// -------------------------------

type scoredPos struct {
	pos   moves.Position // Total = base
	score int            // base + tiny penalty (jen pro řazení)
}

func enumerateAtoB(a, b []int) []scoredPos {
	sizeA, sizeB := len(a), len(b)
	if sizeA == 0 {
		return nil
	}
	out := make([]scoredPos, 0, sizeA)

	// předdopočítej min/max/idxMax pro wrap ať to nepočítáme v každé smyčce znovu
	minB, maxB, idxMax := 0, 0, 0
	if sizeB > 0 {
		minB, maxB, idxMax = b[0], b[0], 0
		for i, x := range b {
			if x < minB {
				minB = x
			}
			if x > maxB {
				maxB, idxMax = x, i
			}
		}
	}

	for i := range sizeA {
		val := a[i]
		toIdx := insertionIndexInB(b, minB, maxB, idxMax, val)

		costA := moves.SignedCost(i, sizeA)
		costB := moves.SignedCost(toIdx, sizeB)

		base := moves.MergedCost(costA, costB) // reálné rotace
		pen := localPenaltyInB(b, toIdx, val)  // 0/1

		out = append(out, scoredPos{
			pos: moves.Position{
				FromIndex: i, ToIndex: toIdx,
				CostA: costA, CostB: costB,
				Total: base,
			},
			score: base + pen,
		})
	}
	return out
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

		costA := moves.SignedCost(toIdx, sizeA)
		costB := moves.SignedCost(i, sizeB)

		base := moves.MergedCost(costA, costB)

		out = append(out, scoredPos{
			pos: moves.Position{
				FromIndex: i, ToIndex: toIdx,
				CostA: costA, CostB: costB,
				Total: base,
			},
			score: base, // bez penalizace
		})
	}
	return out
}

// Simulace hloubky 1 (bez rotací slice)
// -------------------------------------

func simulateOnce(a, b []int, p moves.Position, phaseAtoB bool) ([]int, []int, int) {
	rot := moves.MergedCost(p.CostA, p.CostB) // skutečné rotace
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

// Heuristika (levná)
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

// Lokální pomocníci (targeting/penalizace) nad slicem
// ---------------------------------------------------

func insertionIndexInB(b []int, minB, maxB, idxMax int, val int) int {
	n := len(b)
	if n == 0 {
		return 0
	}
	if val < minB || val > maxB {
		return (idxMax + 1) % n // wrap: „za maximum“
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
	// index minima
	minIdx, minVal := 0, a[0]
	for i, x := range a {
		if x < minVal {
			minVal, minIdx = x, i
		}
	}
	return minIdx
}

func localPenaltyInB(b []int, toIdx int, val int) int {
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

// Utility
// -------

func betterPos(a, b moves.Position) bool {
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
