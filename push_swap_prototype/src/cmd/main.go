package main

import (
	"fmt"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
)

func main() {
	numbers := GenerateRandomNumbers(500)

	ps := ops.InitData(numbers)
	solver.SolvePushSwap(ps)
	fmt.Printf("Is sorted: %v\n", stack.IsSorted(ps.A))
	// stack.PrintStack(ps.A, "A")
	// stack.PrintStack(ps.B, "B")
	fmt.Printf("OpList: %d\n", len(ps.OpList))
}
