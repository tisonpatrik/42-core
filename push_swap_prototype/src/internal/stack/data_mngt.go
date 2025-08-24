package stack

func IsSorted(ps *PushSwapData) bool {
	if ps.A.Size() <= 1 {
		return true
	}

	for i := 1; i < ps.A.Size(); i++ {
		if ps.A.GetValueAtPosition(i) > ps.A.GetValueAtPosition(i+1) {
			return false
		}
	}
	return true
}
