package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// moveFromTo moves an element from one location to another and returns 1 if successful
func moveFromTo(ps *stack.PushSwapData, from, to stack.Loc) int {
	fmt.Printf("=== MOVE_FROM_TO ===\n")
	fmt.Printf("Moving from %v to %v\n", from, to)
	fmt.Printf("Stack A size: %d, Stack B size: %d\n", ps.A.Size(), ps.B.Size())
	
	switch from {
	case stack.TOP_A:
		fmt.Printf("Moving from TOP_A\n")
		moveFromTopA(ps, to)
	case stack.TOP_B:
		fmt.Printf("Moving from TOP_B\n")
		moveFromTopB(ps, to)
	case stack.BOTTOM_A:
		fmt.Printf("Moving from BOTTOM_A\n")
		moveFromBottomA(ps, to)
	case stack.BOTTOM_B:
		fmt.Printf("Moving from BOTTOM_B\n")
		moveFromBottomB(ps, to)
	}
	
	fmt.Printf("After move - Stack A size: %d, Stack B size: %d\n", ps.A.Size(), ps.B.Size())
	fmt.Printf("=== MOVE_FROM_TO END ===\n")
	return 1
}

// moveFromTopA moves an element from TOP_A to the specified location
func moveFromTopA(ps *stack.PushSwapData, to stack.Loc) {
	fmt.Printf("  moveFromTopA: TOP_A -> %v\n", to)
	fmt.Printf("  Before: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
	
	switch to {
	case stack.TOP_B:
		stack.Push_b(ps)
		fmt.Printf("  Executed: Push_b\n")
	case stack.BOTTOM_A:
		stack.Rotate_a(ps)
		fmt.Printf("  Executed: Rotate_a\n")
	case stack.BOTTOM_B:
		stack.Push_b(ps)
		stack.Rotate_b(ps)
		fmt.Printf("  Executed: Push_b + Rotate_b\n")
	}
	
	fmt.Printf("  After: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}

// moveFromTopB moves an element from TOP_B to the specified location
func moveFromTopB(ps *stack.PushSwapData, to stack.Loc) {
	fmt.Printf("  moveFromTopB: TOP_B -> %v\n", to)
	fmt.Printf("  Before: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
	
	switch to {
	case stack.TOP_A:
		stack.Push_a(ps)
		fmt.Printf("  Executed: Push_a\n")
	case stack.BOTTOM_B:
		stack.Rotate_b(ps)
		fmt.Printf("  Executed: Rotate_b\n")
	case stack.BOTTOM_A:
		stack.Push_a(ps)
		stack.Rotate_a(ps)
		fmt.Printf("  Executed: Push_a + Rotate_a\n")
	}
	
	fmt.Printf("  After: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}

// moveFromBottomA moves an element from BOTTOM_A to the specified location
func moveFromBottomA(ps *stack.PushSwapData, to stack.Loc) {
	fmt.Printf("  moveFromBottomA: BOTTOM_A -> %v\n", to)
	fmt.Printf("  Before: A[last]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(ps.A.Size()), ps.B.GetValueAtPosition(1))
	
	switch to {
	case stack.TOP_A:
		stack.R_rotate_a(ps)
		fmt.Printf("  Executed: R_rotate_a\n")
	case stack.TOP_B:
		stack.R_rotate_a(ps)
		stack.Push_b(ps)
		fmt.Printf("  Executed: R_rotate_a + Push_b\n")
	case stack.BOTTOM_B:
		stack.R_rotate_a(ps)
		stack.Push_b(ps)
		stack.Rotate_b(ps)
		fmt.Printf("  Executed: R_rotate_a + Push_b + Rotate_b\n")
	}
	
	fmt.Printf("  After: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}

// moveFromBottomB moves an element from BOTTOM_B to the specified location
func moveFromBottomB(ps *stack.PushSwapData, to stack.Loc) {
	fmt.Printf("  moveFromBottomB: BOTTOM_B -> %v\n", to)
	fmt.Printf("  Before: A[0]=%d, B[last]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(ps.B.Size()))
	
	switch to {
	case stack.TOP_B:
		stack.R_rotate_b(ps)
		fmt.Printf("  Executed: R_rotate_b\n")
	case stack.TOP_A:
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
		fmt.Printf("  Executed: R_rotate_b + Push_a\n")
	case stack.BOTTOM_A:
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
		stack.Rotate_a(ps)
		fmt.Printf("  Executed: R_rotate_b + Push_a + Rotate_a\n")
	}
	
	fmt.Printf("  After: A[0]=%d, B[0]=%d\n", ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}
