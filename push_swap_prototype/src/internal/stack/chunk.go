package stack

type Loc int

const (
	TOP_A Loc = iota
	BOTTOM_A
	TOP_B
	BOTTOM_B
)

type Chunk struct {
	Loc  Loc
	Size int
}