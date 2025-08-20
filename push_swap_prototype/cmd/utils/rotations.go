package utils

// ApplyRotations performs specific rotations based on chosen type
func ApplyRotations(ops *[]string, a, b []int, posA, posB int, typ string) ([]int, []int) {
	sizeA, sizeB := len(a), len(b)
	
	switch typ {
	case "rr":
		for posA > 0 && posB > 0 {
			*ops = append(*ops, "rr")
			a = append(a[1:], a[0])
			b = append(b[1:], b[0])
			posA--
			posB--
		}
		for posA > 0 {
			*ops = append(*ops, "ra")
			a = append(a[1:], a[0])
			posA--
		}
		for posB > 0 {
			*ops = append(*ops, "rb")
			b = append(b[1:], b[0])
			posB--
		}
		
	case "rrr":
		for posA < sizeA && posB < sizeB && (sizeA-posA) > 0 && (sizeB-posB) > 0 {
			*ops = append(*ops, "rrr")
			a = append([]int{a[len(a)-1]}, a[:len(a)-1]...)
			b = append([]int{b[len(b)-1]}, b[:len(b)-1]...)
			posA = (posA + 1) % sizeA
			posB = (posB + 1) % sizeB
			if posA == 0 && posB == 0 {
				break
			}
		}
		for posA < sizeA && posA != 0 {
			*ops = append(*ops, "rra")
			a = append([]int{a[len(a)-1]}, a[:len(a)-1]...)
			posA = (posA + 1) % sizeA
		}
		for posB < sizeB && posB != 0 {
			*ops = append(*ops, "rrb")
			b = append([]int{b[len(b)-1]}, b[:len(b)-1]...)
			posB = (posB + 1) % sizeB
		}
		
	case "ra_rrb":
		for posA > 0 {
			*ops = append(*ops, "ra")
			a = append(a[1:], a[0])
			posA--
		}
		for posB < sizeB && posB != 0 {
			*ops = append(*ops, "rrb")
			b = append([]int{b[len(b)-1]}, b[:len(b)-1]...)
			posB = (posB + 1) % sizeB
		}
		
	default: // rra_rb
		for posA < sizeA && posA != 0 {
			*ops = append(*ops, "rra")
			a = append([]int{a[len(a)-1]}, a[:len(a)-1]...)
			posA = (posA + 1) % sizeA
		}
		for posB > 0 {
			*ops = append(*ops, "rb")
			b = append(b[1:], b[0])
			posB--
		}
	}
	
	return a, b
}
