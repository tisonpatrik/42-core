package solver

import "push_swap_prototype/internal/operations"

// computeCost calculates the cost of moving an element from position posB in stack B
// to position posA in stack A, and returns the cost and the optimal rotation type
func computeCost(posA, sizeA, posB, sizeB int) (int, string) {
	if sizeA == 0 || sizeB == 0 {
		return 0, ""
	}
	
	costRR := max(posA, posB)
	costRRR := max(sizeA-posA, sizeB-posB)
	costRaRrb := posA + (sizeB - posB)
	costRraRb := (sizeA - posA) + posB
	
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

// applyRotations performs rotations based on the chosen type
func applyRotations(stacks *operations.PushSwapStacks, ops *[]string, posA, posB int, typ string) {
	sizeA, sizeB := stacks.A.Size(), stacks.B.Size()
	
	switch typ {
	case "rr":
		for posA > 0 && posB > 0 {
			stacks.RR()
			*ops = append(*ops, "rr")
			posA--
			posB--
		}
		for posA > 0 {
			stacks.RA()
			*ops = append(*ops, "ra")
			posA--
		}
		for posB > 0 {
			stacks.RB()
			*ops = append(*ops, "rb")
			posB--
		}
		
	case "rrr":
		for posA < sizeA && posB < sizeB && (sizeA-posA) > 0 && (sizeB-posB) > 0 {
			stacks.RRR()
			*ops = append(*ops, "rrr")
			posA = (posA + 1) % sizeA
			posB = (posB + 1) % sizeB
			if posA == 0 && posB == 0 {
				break
			}
		}
		for posA < sizeA && posA != 0 {
			stacks.RRA()
			*ops = append(*ops, "rra")
			posA = (posA + 1) % sizeA
		}
		for posB < sizeB && posB != 0 {
			stacks.RRB()
			*ops = append(*ops, "rrb")
			posB = (posB + 1) % sizeB
		}
		
	case "ra_rrb":
		for posA > 0 {
			stacks.RA()
			*ops = append(*ops, "ra")
			posA--
		}
		for posB < sizeB && posB != 0 {
			stacks.RRB()
			*ops = append(*ops, "rrb")
			posB = (posB + 1) % sizeB
		}
		
	default: // rra_rb
		for posA < sizeA && posA != 0 {
			stacks.RRA()
			*ops = append(*ops, "rra")
			posA = (posA + 1) % sizeA
		}
		for posB > 0 {
			stacks.RB()
			*ops = append(*ops, "rb")
			posB--
		}
	}
}

// max returns the maximum of two integers
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
