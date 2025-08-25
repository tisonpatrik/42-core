package stack

func IsSorted(ps *PushSwapData) bool {
	i := ps.A.Top
	rank := 1

	for rank <= ps.A.Size {
		if ps.A.Stack[i] != rank {
			return false
		}
		rank++
		i = NextDown(ps.A, i)
	}
	return true
}

