package moves

func SignedCost(idx, size int) int {
    if idx <= size/2 {
        return idx
    }
    return idx - size
}

func MergedCost(a, b int) int {
    same := (a >= 0 && b >= 0) || (a < 0 && b < 0)
    if same {
        if abs(a) > abs(b) { return abs(a) }
        return abs(b)
    }
    return abs(a) + abs(b)
}

func abs(x int) int { if x < 0 { return -x }; return x }
