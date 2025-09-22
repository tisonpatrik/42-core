package selector

import (
	"push_swap_prototype/internal/ops"
)

// SelectBestAtoBMove finds the position with the lowest cost for moving an element from stack A to stack B.
// It evaluates all possible positions and returns the one with minimal rotation cost.
func SelectBestAtoBMove(ps *ops.SortingState) Position {
	enumerator := NewCandidateEnumerator(DefaultSelectorConfig())
	candidates := enumerator.EnumerateAtoB(ps.A, ps.B)
	return SelectBestCandidate(candidates)
}

// CheapestAtoB is kept for backward compatibility - delegates to SelectBestAtoBMove
func CheapestAtoB(ps *ops.SortingState) Position {
	return SelectBestAtoBMove(ps)
}
