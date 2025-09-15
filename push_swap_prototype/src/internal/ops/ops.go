package ops


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

func OpToString(op Operation) string {
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
		return "?"
	}
}