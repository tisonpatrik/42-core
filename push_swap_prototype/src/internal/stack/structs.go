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

type SplitDest struct {
	Min Chunk
	Mid Chunk
	Max Chunk
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
