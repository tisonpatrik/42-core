package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/selector"
)

// ApplyCombined applies a combined rotation and push operation based on the given position.
// It performs common rotations (rr/rrr) first, then remaining rotations, and finally the push operation.
func ApplyCombined(ps *ops.SortingState, p selector.Position, pushToB bool) {
    a, b := p.CostA, p.CostB

    // common rotation
    for a > 0 && b > 0 { ops.RotateAB(ps); a--; b-- }  
    for a < 0 && b < 0 { ops.ReverseRotateAB(ps); a++; b++ }

    // remaining rotations
    for a > 0 { ops.RotateA(ps); a-- }
    for a < 0 { ops.ReverseRotateA(ps); a++ }
    for b > 0 { ops.RotateB(ps); b-- }
    for b < 0 { ops.ReverseRotateB(ps); b++ }

    // push operation
    if pushToB { ops.PushB(ps) } else { ops.PushA(ps) }
}

