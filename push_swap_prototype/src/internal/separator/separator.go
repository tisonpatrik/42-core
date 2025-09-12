package separator

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// PushNonLISIntoB pushes all elements that are not part of the Longest Increasing Subsequence to stack B.
// When enableBShaping is true, it also applies simple shaping to maintain B's order.
func PushNonLISIntoB(ps *ops.SortingState, enableBShaping bool) {
	inLIS := ComputeLISNodes(ps.A)
	sizeA := stack.GetSize(ps.A)
	if sizeA <= 3 { return }

	// continuously maintain min/max B (fast approximation "median rule")
	minB, maxB := 0, 0
	hasBRange := false

	for range sizeA {
		top := stack.GetHead(ps.A)
		if inLIS[top] {
			ops.RotateA(ps)
			continue
		}
		// pb
		ops.PushB(ps)

		if enableBShaping {
			// O(1) shaping via min/max
			val := stack.GetHead(ps.B).GetContent()
			if !hasBRange {
				minB, maxB, hasBRange = val, val, true
			} else {
				if val < minB { minB = val }
				if val > maxB { maxB = val }
			}
			mid := (minB + maxB) / 2
			if val < mid {
				ops.RotateB(ps) // rb
			}
		}
	}
	// ops.LogState(ps)
}