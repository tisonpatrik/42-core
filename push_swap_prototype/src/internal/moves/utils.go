package moves

import "push_swap_prototype/internal/utils"

func SignedCost(idx, size int) int {
    if idx <= size/2 {
        return idx
    }
    return idx - size
}

func MergedCost(a, b int) int {
    same := (a >= 0 && b >= 0) || (a < 0 && b < 0)
    if same {
        if utils.Abs(a) > utils.Abs(b) { return utils.Abs(a) }
        return utils.Abs(b)
    }
    return utils.Abs(a) + utils.Abs(b)
}

