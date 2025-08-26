package stack



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
