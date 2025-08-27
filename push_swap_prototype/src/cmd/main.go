package main

import (
	"fmt"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
)

func main() {
	// numbers := GenerateRandomNumbers(100)
	numbers := []int{1, 5, 3, 4, 9, 2, 6, 8, 7, 10}
	fmt.Println(numbers)

	ps := ops.InitData(numbers)
	solver.SolvePushSwap(ps)
	fmt.Printf("Is sorted: %v\n", stack.IsSorted(ps.A))
	stack.PrintStack(ps.A, "A")
	stack.PrintStack(ps.B, "B")
	fmt.Printf("OpList: %d\n", len(ps.OpList))
}
