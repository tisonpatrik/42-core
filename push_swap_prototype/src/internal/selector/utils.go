package selector

import "push_swap_prototype/internal/utils"

// SignedCost calculates the signed cost (positive for rotate, negative for reverse rotate) to move an element to a specific index.
func SignedCost(idx, size int) int {
    if idx <= size/2 {
        return idx
    }
    return idx - size
}

// MergedCost calculates the total cost when combining two operations, accounting for common rotations (rr/rrr).
func MergedCost(a, b int) int {
    same := (a >= 0 && b >= 0) || (a < 0 && b < 0)
    if same {
        if utils.Abs(a) > utils.Abs(b) { return utils.Abs(a) }
        return utils.Abs(b)
    }
    return utils.Abs(a) + utils.Abs(b)
}

