package executor

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/position"
	"push_swap_prototype/internal/stack"
)

// executePs executes the positioning strategy based on mode (equivalent to execute_ps in C)
func ExecutePs(ps *ops.SortingState, pos position.Position, mode int) {
	switch mode {
	case 0, 1:
		execSmt(ps, pos, mode)
	case 2:
		multiExecute(ps, ops.RA, pos.StackA)
		multiExecute(ps, ops.RRB, stack.GetSize(ps.B)-pos.StackB)
	case 3:
		multiExecute(ps, ops.RRA, stack.GetSize(ps.A)-pos.StackA)
		multiExecute(ps, ops.RB, pos.StackB)
	}
}


// multiExecute executes an operation n times (equivalent to multi_execute in C)
func multiExecute(ps *ops.SortingState, op ops.Operation, n int) {
	for range n {
		switch op {
		case ops.PB:
			ops.PushB(ps)
		case ops.PA:
			ops.PushA(ps)
		case ops.RA:
			ops.RotateA(ps)
		case ops.RB:
			ops.RotateB(ps)
		case ops.RRA:
			ops.ReverseRotateA(ps)
		case ops.RRB:
			ops.ReverseRotateB(ps)
		case ops.RR:
			ops.RotateAB(ps)
		case ops.RRR:
			ops.ReverseRotateAB(ps)
		}
	}
}

// execSmt executes simultaneous moves (equivalent to exec_smt in C)
func execSmt(ps *ops.SortingState, pos position.Position, mode int) {
	switch mode {
	case 0:
		// rr mode
		minMoves := min(pos.StackB, pos.StackA)
		multiExecute(ps, ops.RR, minMoves)

		if max(pos.StackA, pos.StackB) == pos.StackA && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RA, pos.StackA-pos.StackB)
		} else if max(pos.StackA, pos.StackB) == pos.StackB && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RB, pos.StackB-pos.StackA)
		}
	case 1:
		// rrr mode
		minMoves := min(pos.StackB, pos.StackA)
		multiExecute(ps, ops.RRR, minMoves)
		
		if max(pos.StackA, pos.StackB) > pos.StackB && pos.StackA != pos.StackB {
			multiExecute(ps, ops.RRA, pos.StackA-pos.StackB)
		} else if max(pos.StackA, pos.StackB)> pos.StackA && pos.StackA != pos.StackB && pos.StackB != 0 {
			multiExecute(ps, ops.RRB, pos.StackB-pos.StackA)
		}
	}
}

