package solver

import (
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/separator"
	"push_swap_prototype/internal/stack"
)



func SolvePushSwap(ps *ops.SortingState) {
    if stack.IsSorted(ps.A) { return }

    // 1) LIS bootstrap: pushni non-LIS do B (doporučeno)
    separator.PushNonLISIntoB(ps, true) // true = zapni jednoduchý shaping

    // Pokud LIS zatím nechceš, můžeš dočasně použít původní 2×pb:
    // ops.PushB(ps); ops.PushB(ps)

    // 2) Dotlač A na 3 prvky (v LIS scénáři to často už bude skoro hotové)
    for stack.GetSize(ps.A) > 3 {
        pos := moves.CheapestAtoB(ps) // tvoje sjednocená verze s podepsanými costy
        ApplyCombined(ps, pos, true) // pb
    }

    // 3) Minisort tří prvků v A
    SortThree(ps)

    // 4) Návrat B -> A stejnou sjednocenou logikou
    for !stack.IsEmpty(ps.B) {
        pos := moves.CheapestBtoA(ps)
        ApplyCombined(ps, pos, false) // pa
    }

    // 5) Dorovnání A (min na vrch nejkratší cestou)
    AlignMinToTop(ps)
}

