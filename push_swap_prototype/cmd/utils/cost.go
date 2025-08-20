package utils

// ComputeCost returns cost and rotation type
func ComputeCost(posA, sizeA, posB, sizeB int) (int, string) {
	costs := map[string]int{
		"rr":     Max(posA, posB),
		"rrr":    Max(sizeA-posA, sizeB-posB),
		"ra_rrb": posA + (sizeB - posB),
		"rra_rb": (sizeA - posA) + posB,
	}
	
	minCost := costs["rr"]
	typ := "rr"
	for t, cost := range costs {
		if cost < minCost {
			minCost = cost
			typ = t
		}
	}
	
	return minCost, typ
}
