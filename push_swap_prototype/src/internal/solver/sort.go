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

	iterationCount := 0
	for stack.GetSize(ps.A) > 3 {
		if iterationCount == 0 {
			logInput(ps.A, ps.B, candK)
		}
		pos := selector.PickNearBest(ps, candK)
		if iterationCount == 0 {
			logOutput(pos)
		}
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

func logInput(a, b *stack.Stack, candK int) {
	numbersA := stack.ToArray(a)
	numbersB := stack.ToArray(b)
	file, err := os.OpenFile("PickNearBest1.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		fmt.Printf("Error opening file: %v\n", err)
		return
	}
	defer file.Close()
	
	fmt.Fprintf(file, "input: A=%v B=%v candK=%d\n", numbersA, numbersB, candK)
}

func logOutput(result selector.Position) {
	file, err := os.OpenFile("PickNearBest1.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Printf("Error opening file: %v\n", err)
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "output: Position=%+v\n", result)
}


