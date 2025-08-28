package main

import (
	"fmt"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
)

func main() {
	numbers := GenerateRandomNumbers(500)
	// numbers := []int{1, 5, 3, 4, 9, 2, 6, 8, 7, 10}
	// numbers := []int{77, 25, 55, 16, 52, 24, 28, 83, 4, 71, 85, 98, 89, 99, 30, 68, 92, 59, 6, 17, 91, 34, 86, 47, 8, 3, 57, 39, 65, 44, 69, 23, 80, 50, 60, 56, 46, 27, 21, 48, 54, 63, 42, 20, 73, 35, 97, 93, 11, 10, 22, 18, 87, 2, 96, 15, 72, 45, 29, 38, 49, 67, 79, 41, 94, 76, 36, 19, 5, 33, 12, 14, 40, 88, 78, 1, 84, 90, 58, 32, 61, 70, 43, 0, 82, 95, 9, 26, 75, 13, 53, 31, 37, 64, 62, 66, 74, 81, 7, 51}
	// fmt.Println(numbers)

	ps := ops.InitData(numbers)
	solver.SolvePushSwap(ps)
	fmt.Printf("Is sorted: %v\n", stack.IsSorted(ps.A))
	// stack.PrintStack(ps.A, "A")
	// stack.PrintStack(ps.B, "B")
	fmt.Printf("OpList: %d\n", len(ps.OpList))
}
