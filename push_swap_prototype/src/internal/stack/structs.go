package stack

type Loc int

const (
	TOP_A Loc = iota
	BOTTOM_A
	TOP_B
	BOTTOM_B
)

type Chunk struct {
	Loc  Loc  // Changed from 'loc' to 'Loc' to make it public
	Size int  // Changed from 'size' to 'Size' to make it public
}

// Stack represents a circular buffer stack like the C implementation
type Stack struct {
	Stack  []int
	Size   int // capacity of the buffer
	Top    int // index of top element
	Bottom int // index of bottom element
}

type PushSwapData struct {
	A           *Stack
	B           *Stack
	OpList      []Operation
	WritingMode bool
}


type Operation int

const (
	SA Operation = iota
	SB
	SS
	PA
	PB
	RA
	RB
	RR
	RRA
	RRB
	RRR
)
