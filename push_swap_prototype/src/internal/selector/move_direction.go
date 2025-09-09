package selector

// MoveDirection represents the direction of movement between stacks
type MoveDirection int

const (
	// AtoB represents moving an element from stack A to stack B
	AtoB MoveDirection = iota
	// BtoA represents moving an element from stack B to stack A
	BtoA
)

// MoveSimulator handles simulation of moves between stacks
type MoveSimulator struct{}

// NewMoveSimulator creates a new MoveSimulator
func NewMoveSimulator() *MoveSimulator {
	return &MoveSimulator{}
}

// SimulateMove simulates a single move and returns the resulting stacks and cost
func (ms *MoveSimulator) SimulateMove(a, b []int, pos Position, direction MoveDirection) ([]int, []int, int) {
	rot := MergedCost(pos.CostA, pos.CostB) // actual rotations
	
	if direction == AtoB {
		ia := NormalizeIndex(len(a), pos.CostA)
		ib := NormalizeIndex(len(b), pos.CostB)
		x := a[ia]
		na := RemoveElementAt(a, ia)
		nb := InsertElementAt(b, ib, x)
		return na, nb, rot + 1
	}
	
	// BtoA direction
	ib := NormalizeIndex(len(b), pos.CostB)
	ia := NormalizeIndex(len(a), pos.CostA)
	x := b[ib]
	nb := RemoveElementAt(b, ib)
	na := InsertElementAt(a, ia, x)
	return na, nb, rot + 1
}

