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
	if stack.IsSorted(ps.A) { return }

	separator.PushNonLISIntoB(ps, true)

	candK := 30

	// Open log file once and keep it open
	logFile := openLogFile()
	defer logFile.Close()

	iterationCount := 0
	for stack.GetSize(ps.A) > 3 {
		logInput(logFile, ps.A, ps.B, candK, iterationCount)
		pos := selector.PickNearBest(ps, candK)
		logOutput(logFile, pos, iterationCount)
		ApplyCombined(ps, pos, true)
		iterationCount++
	}

	SortThree(ps)

	for !stack.IsEmpty(ps.B) {
		pos := selector.PickNearBest(ps, candK)
		ApplyCombined(ps, pos, false) // pa
	}

	AlignMinToTop(ps)

	optimizer.OptimizeOps(ps.OpList)
}

func openLogFile() *os.File {
	file, err := os.OpenFile("PickNearBest1.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		fmt.Printf("Error opening log file: %v\n", err)
		return nil
	}
	return file
}

func logInput(logFile *os.File, a, b *stack.Stack, candK int, iteration int) {
	if logFile == nil {
		return
	}
	numbersA := stack.ToArray(a)
	numbersB := stack.ToArray(b)
	fmt.Fprintf(logFile, "\nIteration %d input: A=%v B=%v candK=%d\n", iteration, numbersA, numbersB, candK)
}

func logOutput(logFile *os.File, result selector.Position, iteration int) {
	if logFile == nil {
		return
	}
	fmt.Fprintf(logFile, "Iteration %d output: Position=%+v\n", iteration, result)
}


