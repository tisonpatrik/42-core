package main

import (
	"fmt"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

type Result struct {
	OK         bool
	ErrorIndex int
	Error      error
	OpCount    int
}


func Validate(numbers []int, opsList []ops.Operation) Result {
	ps := ops.InitData(numbers) 

	for i, op := range opsList {
		if err := applyChecked(ps, op); err != nil {
			return Result{
				OK:         false,
				ErrorIndex: i,
				Error:      fmt.Errorf("op[%d]=%s: %w", i, ops.OpToString(op), err),
				OpCount:    len(opsList),
			}
		}
	}

	if !stack.IsSorted(ps.A) {
		return Result{
			OK:         false,
			ErrorIndex: len(opsList),
			Error:      fmt.Errorf("final state: stack A is not sorted ascending"),
			OpCount:    len(opsList),
		}
	}
	if !stack.IsEmpty(ps.B) {
		return Result{
			OK:         false,
			ErrorIndex: len(opsList),
			Error:      fmt.Errorf("final state: stack B is not empty"),
			OpCount:    len(opsList),
		}
	}

	return Result{OK: true, ErrorIndex: -1, Error: nil, OpCount: len(opsList)}
}

func applyChecked(ps *ops.SortingState, op ops.Operation) error {
	switch op {
	case ops.SA:
		if stack.GetSize(ps.A) < 2 {
			return fmt.Errorf("SA requires at least 2 elements in A")
		}
		ops.SwapA(ps)
	case ops.SB:
		if stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("SB requires at least 2 elements in B")
		}
		ops.SwapB(ps)
	case ops.SS:
		if stack.GetSize(ps.A) < 2 || stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("SS requires at least 2 in A and 2 in B")
		}
		ops.SwapAB(ps)

	case ops.PA:
		if stack.IsEmpty(ps.B) {
			return fmt.Errorf("PA requires non-empty B")
		}
		ops.PushA(ps)
	case ops.PB:
		if stack.IsEmpty(ps.A) {
			return fmt.Errorf("PB requires non-empty A")
		}
		ops.PushB(ps)

	case ops.RA:
		if stack.GetSize(ps.A) < 2 {
			return fmt.Errorf("RA requires at least 2 elements in A")
		}
		ops.RotateA(ps)
	case ops.RB:
		if stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("RB requires at least 2 elements in B")
		}
		ops.RotateB(ps)
	case ops.RR:
		if stack.GetSize(ps.A) < 2 || stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("RR requires at least 2 in A and 2 in B")
		}
		ops.RotateAB(ps)

	case ops.RRA:
		if stack.GetSize(ps.A) < 2 {
			return fmt.Errorf("RRA requires at least 2 elements in A")
		}
		ops.ReverseRotateA(ps)
	case ops.RRB:
		if stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("RRB requires at least 2 elements in B")
		}
		ops.ReverseRotateB(ps)
	case ops.RRR:
		if stack.GetSize(ps.A) < 2 || stack.GetSize(ps.B) < 2 {
			return fmt.Errorf("RRR requires at least 2 in A and 2 in B")
		}
		ops.ReverseRotateAB(ps)

	default:
		return fmt.Errorf("unknown operation: %d", int(op))
	}
	return nil
}


