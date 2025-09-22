package selector

// Position represents a move position with cost information
type Position struct {
	FromIndex int // Index in source stack
	ToIndex   int // Index in target stack
	CostA     int // Cost for stack A operations
	CostB     int // Cost for stack B operations
	Total     int // Total merged cost
}
