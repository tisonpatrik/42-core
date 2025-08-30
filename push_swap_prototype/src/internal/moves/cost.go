package moves

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
	Total     int // čistý base cost = MergedCost(CostA, CostB)
}

// ----------------- PUBLIC API -----------------

func CheapestAtoB(ps *ops.SortingState) Position {
	best := Position{Total: math.MaxInt}
	for _, p := range enumerateCandidatesAtoB(ps.A, ps.B, 0) { // 0 => všichni
		if better(p, best) {
			best = p
		}
	}
	return best
}

func CheapestBtoA(ps *ops.SortingState) Position {
	best := Position{Total: math.MaxInt}
	for _, p := range enumerateCandidatesBtoA(ps.A, ps.B, 0) {
		if better(p, best) {
			best = p
		}
	}
	return best
}

// ----------------- ENUMERÁTORY -----------------

// enumerateCandidatesAtoB: vrátí top-K kandidátů podle skóre (base + jemná penalizace),
// ale do Position.Total ukládá **jen base** (MergedCost).
func enumerateCandidatesAtoB(a, b *stack.Stack, k int) []Position {
	sizeA := stack.GetSize(a)
	if sizeA == 0 {
		return nil
	}

	// 1) Jednou si načti B do slice (rychlejší penalizace/targeting sousedů)
	bvals := snapshotValues(b)

	type scored struct {
		pos   Position
		score int // base + penalty
	}
	ss := make([]scored, 0, sizeA)

	// 2) Projdeme A shora dolů
	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		val := n.GetContent()
		toIdx := insertionIndexInBVals(bvals, val) // targeting nad slice

		costA := SignedCost(i, sizeA)
		costB := SignedCost(toIdx, len(bvals))

		base := MergedCost(costA, costB)                    // reálné rotace
		pen  := localOrderPenaltyInBV(bvals, toIdx, val)    // 0/1 jemný tie-break

		ss = append(ss, scored{
			pos: Position{
				FromIndex: i,
				ToIndex:   toIdx,
				CostA:     costA,
				CostB:     costB,
				Total:     base, // <<< důležité: ukládáme čistý base
			},
			score: base + pen, // pořadí kandidátů
		})
	}

	// 3) Seřazení dle score + tie-breakery
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

	// 4) (volitelný, ale doporučený) gating: nech jen base ≤ minBase+2
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

// enumerateCandidatesBtoA: B-penalizaci nepoužívá; `Total` = base.
func enumerateCandidatesBtoA(a, b *stack.Stack, k int) []Position {
	sizeA, sizeB := stack.GetSize(a), stack.GetSize(b)
	if sizeB == 0 {
		return nil
	}

	cands := make([]Position, 0, sizeB)
	i := 0
	for n := stack.GetHead(b); n != nil; n, i = n.GetNext(), i+1 {
		toIdx := findTargetPosInA(a, n.GetContent())
		costA := SignedCost(toIdx, sizeA)
		costB := SignedCost(i, sizeB)
		base  := MergedCost(costA, costB)
		cands = append(cands, Position{
			FromIndex: i, ToIndex: toIdx,
			CostA: costA, CostB: costB,
			Total: base,
		})
	}

	sort.Slice(cands, func(i, j int) bool { return better(cands[i], cands[j]) })
	if k > 0 && k < len(cands) {
		return cands[:k]
	}
	return cands
}

// ----------------- HELPERY (B snapshot/penalizace) -----------------

// rychlé čtení hodnot B do slice (top..bottom)
func snapshotValues(s *stack.Stack) []int {
	out := make([]int, 0, stack.GetSize(s))
	for n := stack.GetHead(s); n != nil; n = n.GetNext() {
		out = append(out, n.GetContent())
	}
	return out
}

// insertionIndexInBVals: index v B (nad slice), kam vložit val, chceme lokální "prev > val > next"
func insertionIndexInBVals(b []int, val int) int {
	n := len(b)
	if n == 0 {
		return 0
	}
	// wrap: mimo rozsah => za maximum
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

// jemná penalizace nad slice (0/1)
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

// ----------------- OSTATNÍ (beze změny) -----------------

func findTargetPosInA(a *stack.Stack, val int) int {
	if stack.GetSize(a) == 0 { return 0 }
	bestIdx, bestVal := -1, 0
	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		if x := n.GetContent(); x > val {
			if bestIdx == -1 || x < bestVal {
				bestVal, bestIdx = x, i
			}
		}
	}
	if bestIdx != -1 { return bestIdx }
	// wrap na minimum
	minIdx := 0
	minVal := stack.GetHead(a).GetContent()
	i = 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		if x := n.GetContent(); x < minVal {
			minVal, minIdx = x, i
		}
	}
	return minIdx
}

func better(a, b Position) bool {
	if a.Total != b.Total { return a.Total < b.Total }
	if utils.Abs(a.CostA) != utils.Abs(b.CostA) {
		return utils.Abs(a.CostA) < utils.Abs(b.CostA)
	}
	if a.ToIndex != b.ToIndex { return a.ToIndex < b.ToIndex }
	return a.FromIndex < b.FromIndex
}
