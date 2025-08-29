package executor

import (
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
)

func ApplyCombined(ps *ops.SortingState, p moves.Position, pushToB bool) {
    a, b := p.CostA, p.CostB

    // společná rotace
    for a > 0 && b > 0 { ops.RotateAB(ps); a--; b-- }     // rr
    for a < 0 && b < 0 { ops.ReverseRotateAB(ps); a++; b++ } // rrr

    // zbytky
    for a > 0 { ops.RotateA(ps); a-- }
    for a < 0 { ops.ReverseRotateA(ps); a++ }
    for b > 0 { ops.RotateB(ps); b-- }
    for b < 0 { ops.ReverseRotateB(ps); b++ }

    // push
    if pushToB { ops.PushB(ps) } else { ops.PushA(ps) }
}

