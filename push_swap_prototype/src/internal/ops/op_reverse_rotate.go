package ops

import "push_swap_prototype/internal/stack"

func reverseRotate(stk *stack.Stack) bool {
    return stack.ReverseRotate(stk)
}

func ReverseRotateA(ps *SortingState) {
    if reverseRotate(ps.A) {
        SaveOp(ps, RRA)
    }
}

func ReverseRotateB(ps *SortingState) {
    if reverseRotate(ps.B) {
        SaveOp(ps, RRB)
    }
}

func ReverseRotateAB(ps *SortingState) {
    ra := reverseRotate(ps.A)
    rb := reverseRotate(ps.B)
    if ra && rb {
        SaveOp(ps, RRR)
    } 
}
