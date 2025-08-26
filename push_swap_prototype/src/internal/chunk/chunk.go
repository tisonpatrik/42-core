package chunk

type Loc int

const (
	TOP_A Loc = iota
	BOTTOM_A
	TOP_B
	BOTTOM_B
)

type Chunk struct {
	loc  Loc
	size int
}

type SplitDest struct {
	Min Chunk
	Mid Chunk
	Max Chunk
}


func NewChunk(loc Loc, size int) *Chunk {
	return &Chunk{loc: loc, size: size}
}

func GetSize(c *Chunk) int {
	return c.size
}

func GetLoc(c *Chunk) Loc {
	return c.loc
}

func SetSize(c *Chunk, size int) {
	c.size = size
}

func SetLoc(c *Chunk, loc Loc) {
	c.loc = loc
}