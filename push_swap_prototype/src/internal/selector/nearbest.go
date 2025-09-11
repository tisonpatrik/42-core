package selector

import (
	"push_swap_prototype/internal/ops"
)

// SelectBestBtoAMove selects the best position for moving an element from B to A using near-optimal strategy.
// It considers multiple candidates and uses micro-lookahead to make the best choice.
func SelectBestBtoAMove(ps *ops.SortingState, maxCandidates int) Position {
	config := DefaultSelectorConfig()
	
	// Snapshot stacks for efficient processing
	a := SnapshotStack(ps.A)
	b := SnapshotStack(ps.B)

	// Enumerate candidates from B to A
	enumerator := NewCandidateEnumerator(config)
	candidates := enumerator.EnumerateBtoA(a, b)
	if len(candidates) == 0 {
		return SelectBestAtoBMove(ps)
	}

	// Filter and select best candidate using lookahead
	return selectBestCandidateWithLookahead(a, b, candidates, maxCandidates, config, BtoA)
}


// selectBestCandidateWithLookahead filters candidates and selects the best one using micro-lookahead
func selectBestCandidateWithLookahead(a, b []int, candidates []Candidate, maxCandidates int, config SelectorConfig, direction MoveDirection) Position {
	// 1) Filter candidates by cost threshold
	filteredCandidates := FilterCandidatesByThreshold(candidates, config.CostThresholdOffset)

	// 2) Select top-K candidates by score for further evaluation
	filteredCandidates = SelectTopKCandidates(filteredCandidates, maxCandidates)

	// 3) Evaluate candidates with micro-lookahead and select the best
	evaluator := NewLookaheadEvaluator(config)
	return evaluator.EvaluateWithLookahead(a, b, filteredCandidates, direction)
}

