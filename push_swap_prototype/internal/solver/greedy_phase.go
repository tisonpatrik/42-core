package solver

import (
	"push_swap_prototype/internal/algo"
	"push_swap_prototype/internal/operations"
)

// ProcessGreedyPhase moves elements from stack B back to stack A using greedy strategy
// Returns the operations performed during this phase
func ProcessGreedyPhase(stacks *operations.PushSwapStacks) []string {
	ops := make([]string, 0)
	
	// Greedy return from B to A
	for !stacks.B.IsEmpty() {
		bestMove := findBestMove(stacks)
		
		// Perform best move
		applyRotations(stacks, &ops, bestMove.posA, bestMove.posB, bestMove.typ)
		stacks.PA()
		ops = append(ops, "pa")
	}
	
	return ops
}

// Move represents a move with its cost and parameters
type Move struct {
	posA, posB int
	typ        string
	cost       int
}

// findBestMove finds the best move to perform from stack B to stack A
func findBestMove(stacks *operations.PushSwapStacks) Move {
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
	
	return Move{
		posA: bestPosA,
		posB: bestPosB,
		typ:  bestTyp,
		cost: bestCost,
	}
}
