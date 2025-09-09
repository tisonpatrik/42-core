package selector

import (
	"push_swap_prototype/internal/stack"
)

// CandidateEnumerator handles enumeration of candidate positions for moves
type CandidateEnumerator struct {
	costCalc *CostCalculator
	config   SelectorConfig
}

// NewCandidateEnumerator creates a new CandidateEnumerator with the given configuration
func NewCandidateEnumerator(config SelectorConfig) *CandidateEnumerator {
	return &CandidateEnumerator{
		costCalc: NewCostCalculator(config),
		config:   config,
	}
}

// EnumerateAtoB enumerates all possible positions for moving elements from stack A to stack B
func (ce *CandidateEnumerator) EnumerateAtoB(a, b *stack.Stack) []Candidate {
	sizeA := stack.GetSize(a)
	if sizeA == 0 {
		return nil
	}

	// Build candidates from stack A
	candidates := ce.buildCandidatesFromStackA(a, b)

	// Filter candidates by cost threshold
	filtered := FilterCandidatesByThreshold(candidates, ce.config.CostThresholdOffset)

	// Return top K candidates (0 means all)
	return SelectTopKCandidates(filtered, 0)
}

// EnumerateBtoA enumerates all possible positions for moving elements from stack B to stack A
func (ce *CandidateEnumerator) EnumerateBtoA(a, b []int) []Candidate {
	sizeA, sizeB := len(a), len(b)
	if sizeB == 0 {
		return nil
	}
	
	candidates := make([]Candidate, 0, sizeB)

	for i := 0; i < sizeB; i++ {
		val := b[i]
		toIdx := FindTargetPosition(a, val)

		// For BtoA moves: fromIdx=i (in stack B), toIdx=toIdx (in stack A)
		// CostA is calculated from toIdx and sizeA, CostB from fromIdx and sizeB
		costA := SignedCost(toIdx, sizeA)
		costB := SignedCost(i, sizeB)
		base := ce.costCalc.CalculateMergedCost(costA, costB)

		position := Position{
			FromIndex: i,     // index in stack B
			ToIndex:   toIdx, // index in stack A
			CostA:     costA,
			CostB:     costB,
			Total:     base,
		}

		candidates = append(candidates, NewCandidate(position, base))
	}
	return candidates
}

// buildCandidatesFromStackA builds candidate positions by evaluating each element in stack A
func (ce *CandidateEnumerator) buildCandidatesFromStackA(a, b *stack.Stack) []Candidate {
	sizeA := stack.GetSize(a)
	bvals := SnapshotStack(b)
	candidates := make([]Candidate, 0, sizeA)

	i := 0
	for n := stack.GetHead(a); n != nil; n, i = n.GetNext(), i+1 {
		val := n.GetContent()
		toIdx := FindInsertionIndex(bvals, val)

		position := ce.costCalc.CalculatePositionCost(i, toIdx, sizeA, len(bvals))
		base := position.Total
		penalty := ce.costCalc.CalculatePenalty(bvals, toIdx, val)

		candidates = append(candidates, NewCandidate(position, base+penalty))
	}

	return candidates
}
