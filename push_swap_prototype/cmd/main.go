package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/benchmark"
	"push_swap_prototype/internal/operations"
)

func main() {
	// Simple test of stack operations
	testStackOperations()
	
	// Run the benchmark
	success := benchmark.RunBenchmark(1)
	
	if !success {
		os.Exit(1)
	}
}

func testStackOperations() {
	fmt.Println("Testing basic stack operations...")
	
	ps := operations.NewPushSwapData()
	
	// Test with a simple array
	numbers := []int{3, 1, 2}
	operations.InitializeFromSlice(ps, numbers)
	
	fmt.Printf("Initial stack A: %v\n", ps.A.ToSlice())
	fmt.Printf("Stack A size: %d\n", ps.A.Size())
	
	// Test swap
	operations.Swap_a(ps)
	fmt.Printf("After SA: %v\n", ps.A.ToSlice())
	
	// Test rotate
	operations.Rotate_a(ps)
	fmt.Printf("After RA: %v\n", ps.A.ToSlice())
	
	// Test reverse rotate
	operations.R_rotate_a(ps)
	fmt.Printf("After RRA: %v\n", ps.A.ToSlice())
	
	// Test push to B
	operations.Push_b(ps)
	fmt.Printf("After PB - A: %v, B: %v\n", ps.A.ToSlice(), ps.B.ToSlice())
	
	// Test push back to A
	operations.Push_a(ps)
	fmt.Printf("After PA - A: %v, B: %v\n", ps.A.ToSlice(), ps.B.ToSlice())
	
	fmt.Printf("Operations performed: %v\n", ps.GetOperations())
}
