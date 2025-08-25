package main

import (
	"fmt"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
)

func main() {
	numbers := []int{71, 17, 20, 22, 13, 76, 62, 63, 81, 9, 86, 98, 67, 72, 59, 87, 37, 43, 65, 12, 6, 29, 42, 89, 69, 39, 3, 16, 38, 79, 83, 57, 96, 30, 75, 68, 25, 80, 36, 85, 77, 33, 84, 70, 54, 55, 8, 18, 73, 53, 47, 44, 32, 46, 90, 40, 56, 19, 26, 50, 7, 60, 21, 15, 58, 88, 11, 27, 61, 94, 35, 100, 5, 34, 51, 64, 45, 2, 66, 1, 78, 31, 28, 49, 24, 4, 74, 97, 95, 82, 52, 14, 92, 41, 99, 10, 93, 23, 48, 91}
	ps := stack.InitData(numbers, true)

	solver.SolvePushSwap(ps)
	fmt.Printf("Stack A: %v\n", ps.A.Stack)
	fmt.Printf("Stack B: %v\n", ps.B.Stack)
}
