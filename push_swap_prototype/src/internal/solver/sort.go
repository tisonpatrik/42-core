package solver

import (
	"push_swap_prototype/internal/executor"
	"push_swap_prototype/internal/finalizer"
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
	"sort"
)


func SolvePushSwap(ps *ops.SortingState) {
    if stack.IsSorted(ps.A) { return }

    // 1) LIS bootstrap: pushni non-LIS do B (doporučeno)
    pushNonLISIntoB(ps, true) // true = zapni jednoduchý shaping

    // Pokud LIS zatím nechceš, můžeš dočasně použít původní 2×pb:
    // ops.PushB(ps); ops.PushB(ps)

    // 2) Dotlač A na 3 prvky (v LIS scénáři to často už bude skoro hotové)
    for stack.GetSize(ps.A) > 3 {
        pos := moves.CheapestAtoB(ps) // tvoje sjednocená verze s podepsanými costy
        executor.ApplyCombined(ps, pos, true) // pb
    }

    // 3) Minisort tří prvků v A
    SortThree(ps)

    // 4) Návrat B -> A stejnou sjednocenou logikou
    for !stack.IsEmpty(ps.B) {
        pos := moves.CheapestBtoA(ps)
        executor.ApplyCombined(ps, pos, false) // pa
    }

    // 5) Dorovnání A (min na vrch nejkratší cestou)
    finalizer.AlignMinToTop(ps)
}

func pushNonLISIntoB(ps *ops.SortingState, enableBShaping bool) {
    inLIS := moves.ComputeLISNodes(ps.A)
    sizeA := stack.GetSize(ps.A)
    if sizeA <= 3 { return }

    // Projdeme přesně "sizeA" topů (kruh), abychom každý původní prvek viděli jednou.
    for seen := 0; seen < sizeA; seen++ {
        top := stack.GetHead(ps.A) // získej pointer na top uzel (podle tvého API)
        if inLIS[top] {
            ops.RotateA(ps) // ra: LIS prvek přesuneme dozadu a pokračujeme
        } else {
            // Non-LIS → do B
            ops.PushB(ps)   // pb
            if enableBShaping {
                maybeShapeB(ps) // viz níže (volitelně)
            }
        }
    }
}

// Jednoduch� verze: po pb jednou rb, kdy\u017e je hodnota < medi�n B
func maybeShapeB(ps *ops.SortingState) {
    bSize := stack.GetSize(ps.B)
    if bSize < 2 { return }

    valTop := stack.GetHead(ps.B).GetContent() // uprav podle tvého pole s hodnotou
    med    := medianOfStack(ps.B)   // O(k) – rychlá pro k<=size(B)

    if valTop < med {
        ops.RotateB(ps) // rb: menší hodnoty "dole", B zhruba descending
    }
}

// Praktick� median \u2013 vezmi hodnoty do slice a nth_element/partial sort.
// Pro jednoduchost O(k log k) sort sta\u010d�.
func medianOfStack(b *stack.Stack) int {
    k := stack.GetSize(b)
    arr := make([]int, 0, k)
    for n := stack.GetHead(b); n != nil; n = n.GetNext() {
        arr = append(arr, n.GetContent())
    }
    sort.Ints(arr)
    return arr[k/2]
}
