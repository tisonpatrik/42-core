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
	ToIndex int

	CostA int
	CostB int

	Total   int
}


// Pro úplnost: když chceš jen "cheapest", můžeš použít:
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

// Jemná penalizace: pokud by vložení "val" na pozici toIdx v B rozbilo lokální klesající pořadí,
// vrať 1, jinak 0. Používej jen jako tie-breaker (nikdy nepřičítej velké hodnoty).
func localOrderPenaltyInB(b *stack.Stack, toIdx int, val int) int {
	size := stack.GetSize(b)
	if size < 2 {
		return 0
	}

	// sousedé okolo toIdx (cyklicky)
	prevIdx := (toIdx - 1 + size) % size
	nextIdx := toIdx % size

	prev := stack.GetNodeAt(b, prevIdx).GetContent() // uprav Value podle tvého názvu pole
	next := stack.GetNodeAt(b, nextIdx).GetContent()

	// „správné“ lokální klesání je: prev > val > next
	if prev > val && val > next {
		return 0
	}
	return 1
}

// Comparator pro tie-breakery: menší Total je lepší, pak menší |CostA|, pak menší ToIdx, pak menší FromIdx.
func better(a, b Position) bool {
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

// ---- Enumerátoři kandidátů ----

// Vrátí top-K kandidátů pro A->B seřazených podle (Total + lokální penalizace v B) a tie-breakerů.
func enumerateCandidatesAtoB(a, b *stack.Stack, k int) []Position {
	sizeA, sizeB := stack.GetSize(a), stack.GetSize(b)
	if sizeA == 0 {
		return nil
	}

	cands := make([]Position, 0, sizeA)

	// projdeme uzly A (0 = top)
	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		// Kam v B vložit (tvá existující logika; pozor: posílej sizeB, ne sizeA)
		toIdx := findInsertionIndexInB(b, n.GetContent())

		costA := SignedCost(i, sizeA)     // kandidát dopředu/dozadu v A
		costB := SignedCost(toIdx, sizeB) // target dopředu/dozadu v B

		total := MergedCost(costA, costB)

		// jemná penalizace lokálního pořadí v B (descending) – použij jen jako tie-breaker
		totalWithPenalty := total + localOrderPenaltyInB(b, toIdx, n.GetContent())

		cands = append(cands, Position{
			FromIndex: i, ToIndex: toIdx,
			CostA: costA, CostB: costB,
			Total: totalWithPenalty,
		})
	}

	// seřadit dle našich pravidel (pozor: pracujeme s Total+penalty)
	sort.Slice(cands, func(i, j int) bool { return better(cands[i], cands[j]) })

	if k <= 0 || k >= len(cands) {
		return cands
	}
	return cands[:k]
}

// Vrátí top-K kandidátů pro B->A (žádná B-penalizace; cíl v A je "nejmenší > val", wrap na min).
func enumerateCandidatesBtoA(a, b *stack.Stack, k int) []Position {
	sizeA, sizeB := stack.GetSize(a), stack.GetSize(b)
	if sizeB == 0 {
		return nil
	}

	cands := make([]Position, 0, sizeB)

	i := 0
	for n := stack.GetHead(b); n != nil; n, i = n.GetNext(), i+1 {
		toIdx := findTargetPosInA(a, n.GetContent())

		costA := SignedCost(toIdx, sizeA) // target v A na top
		costB := SignedCost(i,    sizeB)  // kandidát v B na top

		total := MergedCost(costA, costB)

		cands = append(cands, Position{
			FromIndex: i, ToIndex: toIdx,
			CostA: costA, CostB: costB,
			Total: total, // zde bez penalizace
		})
	}

	sort.Slice(cands, func(i, j int) bool { return better(cands[i], cands[j]) })

	if k <= 0 || k >= len(cands) {
		return cands
	}
	return cands[:k]
}

func findTargetPosInA(a *stack.Stack, val int) int {
	if stack.GetSize(a) == 0 {
		return 0
	}
	// 1) najdi prvek s nejmenší hodnotou > val
	bestIdx := -1
	bestVal := 0
	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		if n.GetContent() > val {
			if bestIdx == -1 || n.GetContent() < bestVal {
				bestVal = n.GetContent()
				bestIdx = i
			}
		}
	}
	if bestIdx != -1 {
		return bestIdx
	}

	// 2) není nic většího → target je index minima (wrap)
	minIdx := 0
	minVal := stack.GetHead(a).GetContent()
	i = 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		if n.GetContent() < minVal {
			minVal = n.GetContent()
			minIdx = i
		}
	}
	return minIdx
}


// Najde index v B (0 = top), před který máš vložit hodnotu val, aby B zůstalo v "descending"
// (pokud B udržuješ jako descending). Pokud B je prázdné, vrať 0.
// Povolený rozsah návratu: 0..sizeB (toIdx==sizeB = vložit za poslední => cyklicky před top).
func findInsertionIndexInB(b *stack.Stack, val int) int {
	sizeB := stack.GetSize(b)
	if sizeB == 0 { return 0 }

	minB := stack.GetMin(b)
	maxB := stack.GetMax(b)

	// wrap: mimo rozsah -> vložit „za maximum“
	if val < minB || val > maxB {
		idxMax := stack.GetMaxPos(b)
		return (idxMax + 1) % sizeB
	}

	// hledej první „mezeru“ prev > val > next (cyklicky)
	for j := 0; j < sizeB; j++ {
		prevIdx := (j - 1 + sizeB) % sizeB
		nextIdx := j
		prev := stack.GetNodeAt(b, prevIdx).GetContent()
		next := stack.GetNodeAt(b, nextIdx).GetContent()
		if prev > val && val > next {
			return j
		}
	}
	return 0 // fallback
}

