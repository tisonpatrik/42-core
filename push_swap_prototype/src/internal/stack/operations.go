package stack

// PushSwapData represents the two stacks used in push swap (like C t_ps)
type PushSwapData struct {
	A           *Stack
	B           *Stack
	OpList      []Operation
	WritingMode bool
}

// NewPushSwapData creates new push swap data structure
func NewPushSwapData() *PushSwapData {
	return &PushSwapData{
		A:           New(),
		B:           New(),
		OpList:      []Operation{},
		WritingMode: true,
	}
}

// NewPushSwapDataWithCapacity creates new push swap data structure with specific capacity (like C init_data)
func NewPushSwapDataWithCapacity(capacity int) *PushSwapData {
	// Like C init_data: both stacks get the same capacity
	a := New()
	a.InitWithCapacity(capacity)
	b := New()
	b.InitWithCapacity(capacity)

	return &PushSwapData{
		A:           a,
		B:           b,
		OpList:      []Operation{},
		WritingMode: true,
	}
}

// saveOp saves an operation to the operation list (like C save_op)
func saveOp(data *PushSwapData, op Operation) {
	if data == nil || !data.WritingMode {
		return
	}
	data.OpList = append(data.OpList, op)
}

// GetOperations returns the list of operations performed
func (ps *PushSwapData) GetOperations() []Operation {
	if ps.OpList == nil {
		return []Operation{}
	}
	return ps.OpList
}

// InitializeFromSlice initializes stack A with values from a slice (like C fill_stack)
func InitializeFromSlice(data *PushSwapData, values []int) {
	if data == nil {
		return
	}
	// We do not need ranking, bcs we are generating already ranked values.

	// Initialize stack A with proper capacity if not already done
	if data.A.size == 0 {
		data.A.InitWithCapacity(len(values))
	}

	// Fill stack A with ranked values (like C fill_stack)
	copy(data.A.stack, values)
	
	// Set pointers like C fill_stack: first element is at top, last element is at bottom
	data.A.top = 0
	data.A.bottom = len(values) - 1
}


// Operation represents a push swap operation (like C t_op)
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

// String returns the string representation of an operation (like C op_to_string)
func (op Operation) String() string {
	switch op {
	case SA:
		return "sa"
	case SB:
		return "sb"
	case SS:
		return "ss"
	case PA:
		return "pa"
	case PB:
		return "pb"
	case RA:
		return "ra"
	case RB:
		return "rb"
	case RR:
		return "rr"
	case RRA:
		return "rra"
	case RRB:
		return "rrb"
	case RRR:
		return "rrr"
	default:
		return "unknown"
	}
}

// Loc represents the location of a chunk in the stacks (like C t_loc)
type Loc int

const (
	TOP_A Loc = iota
	BOTTOM_A
	TOP_B
	BOTTOM_B
)

// Chunk represents a chunk of elements to be sorted (like C t_chunk)
type Chunk struct {
	Loc  Loc
	Size int
}

// SplitDest represents the destination for splitting a chunk (like C t_split_dest)
type SplitDest struct {
	Min Chunk
	Mid Chunk
	Max Chunk
}
