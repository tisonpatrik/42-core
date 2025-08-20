package solver

import (
	"push_swap_prototype/internal/algo"
	"push_swap_prototype/internal/operations"
)

// SolvePushSwap solves the push swap problem using linked list stacks
// Returns the operations and final array
func SolvePushSwap(arr []int) ([]string, []int) {
	ops := make([]string, 0)
	stacks := operations.NewPushSwapStacks()
	stacks.InitializeFromSlice(arr)
	
	// 1) Find LIS and send non-LIS to B
	keep := algo.FindLISIndices(arr)
	
	// Process elements by going through the stack
	for i := 0; i < len(arr); i++ {
		if keep[i] {
			// Keep this element in A, rotate to next position
			stacks.RA()
			ops = append(ops, "ra")
		} else {
			// Send to stack B
			stacks.PB()
			ops = append(ops, "pb")
		}
	}
	
	// 2) Greedy return from B to A
	for !stacks.B.IsEmpty() {
		bestCost := -1
		bestTyp := ""
		bestPosA := -1
		bestPosB := -1
		
		stackASlice := stacks.GetStackASlice()
		stackBSlice := stacks.GetStackBSlice()
		
		for posB, val := range stackBSlice {
			posA := algo.FindTargetPosition(stackASlice, val)
			cost, typ := computeCost(posA, len(stackASlice), posB, len(stackBSlice))
			
			if bestCost == -1 || cost < bestCost {
				bestCost = cost
				bestTyp = typ
				bestPosA = posA
				bestPosB = posB
			}
		}
		
		// Perform best move
		applyRotations(stacks, &ops, bestPosA, bestPosB, bestTyp)
		stacks.PA()
		ops = append(ops, "pa")
	}
	
	// 3) Final rotate - put minimum at top
	finalSlice := stacks.GetStackASlice()
	minPos := findMinPosition(finalSlice)
	
	if minPos <= len(finalSlice)/2 {
		for i := 0; i < minPos; i++ {
			stacks.RA()
			ops = append(ops, "ra")
		}
	} else {
		for i := 0; i < len(finalSlice)-minPos; i++ {
			stacks.RRA()
			ops = append(ops, "rra")
		}
	}
	
	return ops, stacks.GetStackASlice()
}

// computeCost calculates the cost of moving an element
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

// findMinPosition finds the position of the minimum element
func findMinPosition(arr []int) int {
	if len(arr) == 0 {
		return 0
	}
	
	minPos := 0
	minVal := arr[0]
	for i, val := range arr {
		if val < minVal {
			minVal = val
			minPos = i
		}
	}
	return minPos
}

// max returns the maximum of two integers
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
