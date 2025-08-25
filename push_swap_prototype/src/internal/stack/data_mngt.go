package stack

func IsSorted(ps *PushSwapData) bool {
	if ps.A.Size() <= 1 {
		return true
	}

	for i := 1; i < ps.A.Size(); i++ {
		if ps.A.GetValue(i) > ps.A.GetValue(i+1) {
			return false
		}
	}
	return true
}
