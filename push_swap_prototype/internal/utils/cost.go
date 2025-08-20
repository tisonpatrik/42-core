package utils

// ComputeCost calculates the cost of moving an element from position posB in stack B
// to position posA in stack A, and returns the cost and the optimal rotation type
func ComputeCost(posA, sizeA, posB, sizeB int) (int, string) {
	if sizeA == 0 || sizeB == 0 {
		return 0, ""
	}
	
	// Calculate costs for different rotation strategies
	costRR := max(posA, posB)
	costRRR := max(sizeA-posA, sizeB-posB)
	costRaRrb := posA + (sizeB - posB)
	costRraRb := (sizeA - posA) + posB
	
	// Find the minimum cost
	minCost := costRR
	bestType := "rr"
	
	if costRRR < minCost {
		minCost = costRRR
		bestType = "rrr"
	}
	if costRaRrb < minCost {
		minCost = costRaRrb
		bestType = "ra_rrb"
	}
	if costRraRb < minCost {
		minCost = costRraRb
		bestType = "rra_rb"
	}
	
	return minCost, bestType
}

// max returns the maximum of two integers
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
