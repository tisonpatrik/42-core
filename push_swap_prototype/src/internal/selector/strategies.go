package selector

// Strategy represents different strategies for moving elements between stacks
type Strategy int

const (
	BothRotate Strategy = iota
	BothReverse
	RotateAReverseB
	ReverseARotateB
)

