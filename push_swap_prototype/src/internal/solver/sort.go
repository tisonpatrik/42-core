package solver

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/ops"
	optimizer "push_swap_prototype/internal/peephole"
	"push_swap_prototype/internal/selector"
	"push_swap_prototype/internal/separator"
	"push_swap_prototype/internal/stack"
)


func SolvePushSwap(ps *ops.SortingState) {
	fmt.Printf("[DEBUG] SolvePushSwap: Starting to solve push_swap\n")
	
	if stack.IsSorted(ps.A) { 
		fmt.Printf("[DEBUG] SolvePushSwap: Stack A is already sorted, returning\n")
		return 
	}

	fmt.Printf("[DEBUG] SolvePushSwap: Pushing non-LIS elements into B\n")
	separator.PushNonLISIntoB(ps, true)

	candK := 30
	fmt.Printf("[DEBUG] SolvePushSwap: Starting main loop with candK=%d\n", candK)

	for stack.GetSize(ps.A) > 3 {
		fmt.Printf("[DEBUG] SolvePushSwap: Stack A size = %d, calling PickNearBest\n", stack.GetSize(ps.A))
		pos := selector.PickNearBest(ps, candK)
		fmt.Printf("[DEBUG] SolvePushSwap: Got position from PickNearBest: %+v\n", pos)
		ApplyCombined(ps, pos, true)
	}

	fmt.Printf("[DEBUG] SolvePushSwap: Sorting remaining 3 elements\n")
	SortThree(ps)

	fmt.Printf("[DEBUG] SolvePushSwap: Moving elements back from B to A\n")
	for !stack.IsEmpty(ps.B) {
		fmt.Printf("[DEBUG] SolvePushSwap: Stack B size = %d, calling PickNearBest\n", stack.GetSize(ps.B))
		pos := selector.PickNearBest(ps, candK)
		fmt.Printf("[DEBUG] SolvePushSwap: Got position from PickNearBest: %+v\n", pos)
		ApplyCombined(ps, pos, false) // pa
	}

	fmt.Printf("[DEBUG] SolvePushSwap: Aligning minimum to top\n")
	AlignMinToTop(ps)

	fmt.Printf("[DEBUG] SolvePushSwap: Optimizing operations\n")
	optimizer.OptimizeOps(ps.OpList)
	fmt.Printf("[DEBUG] SolvePushSwap: Finished solving\n")
}

func OpenLogFile() *os.File {
	file, err := os.OpenFile("PickNearBest1.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		fmt.Printf("Error opening log file: %v\n", err)
		return nil
	}
	return file
}

func LogInput(logFile *os.File, a, b *stack.Stack, candK int, iteration int) {
	if logFile == nil {
		return
	}
	numbersA := stack.ToArray(a)
	numbersB := stack.ToArray(b)
	fmt.Fprintf(logFile, "\nIteration %d input: A=%v B=%v candK=%d\n", iteration, numbersA, numbersB, candK)
}

func LogOutput(logFile *os.File, result selector.Position, iteration int) {
	if logFile == nil {
		return
	}
	fmt.Fprintf(logFile, "Iteration %d output: Position=%+v\n", iteration, result)
}


