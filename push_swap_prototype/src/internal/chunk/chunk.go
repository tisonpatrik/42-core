package chunk

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

type SplitDest struct {
	Min Chunk
	Mid Chunk
	Max Chunk
}


func NewChunk(loc Loc, size int) *Chunk {
	return &Chunk{Loc: loc, Size: size}
}