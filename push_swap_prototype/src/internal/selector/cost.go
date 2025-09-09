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
		if better(p, best) {
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

	// 1) Load B into slice once (faster penalty/targeting neighbors)
	bvals := snapshotValues(b)

	type scored struct {
		pos   Position
		score int // base + penalty
	}
	ss := make([]scored, 0, sizeA)

	// 2) Go through A from top to bottom
	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		val := n.GetContent()
		toIdx := insertionIndexInBVals(bvals, val) // targeting over slice

		costA := SignedCost(i, sizeA)
		costB := SignedCost(toIdx, len(bvals))

		base := MergedCost(costA, costB)                    // actual rotations
		pen  := localOrderPenaltyInBV(bvals, toIdx, val)    // 0/1 fine tie-break

		ss = append(ss, scored{
			pos: Position{
				FromIndex: i,
				ToIndex:   toIdx,
				CostA:     costA,
				CostB:     costB,
				Total:     base, // <<< important: storing pure base
			},
			score: base + pen, // candidate ordering
		})
	}

	// 3) Sorting by score + tie-breakers
	sort.Slice(ss, func(i, j int) bool {
		if ss[i].score != ss[j].score {
			return ss[i].score < ss[j].score
		}
		ai, aj := ss[i].pos, ss[j].pos
		if utils.Abs(ai.CostA) != utils.Abs(aj.CostA) {
			return utils.Abs(ai.CostA) < utils.Abs(aj.CostA)
		}
		if ai.ToIndex != aj.ToIndex {
			return ai.ToIndex < aj.ToIndex
		}
		return ai.FromIndex < aj.FromIndex
	})

	// 4) (optional, but recommended) gating: keep only base ≤ minBase+2
	minBase := math.MaxInt
	for _, s := range ss {
		if s.pos.Total < minBase {
			minBase = s.pos.Total
		}
	}
	filtered := make([]Position, 0, len(ss))
	threshold := minBase + 2
	for _, s := range ss {
		if s.pos.Total <= threshold {
			filtered = append(filtered, s.pos)
		}
	}

	if k > 0 && k < len(filtered) {
		return filtered[:k]
	}
	return filtered
}



// fast reading of B values into slice (top..bottom)
func snapshotValues(s *stack.Stack) []int {
	out := make([]int, 0, stack.GetSize(s))
	for n := stack.GetHead(s); n != nil; n = n.GetNext() {
		out = append(out, n.GetContent())
	}
	return out
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


func better(a, b Position) bool {
	if a.Total != b.Total { return a.Total < b.Total }
	if utils.Abs(a.CostA) != utils.Abs(b.CostA) {
		return utils.Abs(a.CostA) < utils.Abs(b.CostA)
	}
	if a.ToIndex != b.ToIndex { return a.ToIndex < b.ToIndex }
	return a.FromIndex < b.FromIndex
}
