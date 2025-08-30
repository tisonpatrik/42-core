package optimizer

import "push_swap_prototype/internal/ops"

// OptimizeOps provede n\u011bkolik kol bezpe\u010dn�ch lok�ln�ch p\u0159epis\u016f,
// dokud se sekvence nezkr�t�. Pravidla:
//  - mergeNeighbors:  (ra rb)->rr, (rra rrb)->rrr, (sa sb)->ss
//                     + absorpce: rr+rra->rb, rr+rrb->ra, rrr+ra->rrb, rrr+rb->rra
//                     + symetrick� varianty s opa\u010dn�m po\u0159ad�m
//  - cancelInversePairs: sousedn� inverze (ra rra), (pb pa), (ss ss), ...
//  - cancelAcrossOtherStack: (ra ... rra) ru\u0161�, pokud mezi nimi jsou jen B-only operace;
//                            obdobn\u011b (rb ... rrb) p\u0159es A-only operace.
// Bari�ry: pa/pb, rr/rrr, ss (a obecn\u011b cokoliv, co \u201etouchuje oba stacky\u201c).
func OptimizeOps(seq []ops.Operation) []ops.Operation {
	if len(seq) < 2 {
		return seq
	}
	out := seq
	changed := true
	for changed {
		changed = false

		var c bool
		out, c = mergeNeighbors(out)
		changed = changed || c

		out, c = cancelInversePairs(out)
		changed = changed || c

		// ru\u0161en� inverz� s mezerou \u201ep\u0159es druh� stack\u201c
		out, c = cancelAcrossOtherStackA(out) // (ra ... rra) p\u0159es B-only
		changed = changed || c
		out, c = cancelAcrossOtherStackB(out) // (rb ... rrb) p\u0159es A-only
		changed = changed || c
	}
	return out
}

// --- helpers o povaze operac� ---

func touchesA(op ops.Operation) bool {
	switch op {
	case ops.SA, ops.RA, ops.RRA:
		return true
	}
	// SS/RR/RRR/PA/PB zasahuj� oba \u2013 to \u0159e\u0161�me jako \u201ebarrier\u201c
	return false
}

func touchesB(op ops.Operation) bool {
	switch op {
	case ops.SB, ops.RB, ops.RRB:
		return true
	}
	return false
}

func isBarrier(op ops.Operation) bool {
	switch op {
	case ops.SS, ops.RR, ops.RRR, ops.PA, ops.PB:
		return true
	}
	return false
}

// --- 1) Merge & absorpce soused\u016f ---

func mergeNeighbors(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 2 {
		return src, false
	}
	dst := make([]ops.Operation, 0, len(src))
	changed := false
	i := 0
	for i < len(src) {
		if i+1 < len(src) {
			a, b := src[i], src[i+1]

			// (ra rb) -> rr  a opa\u010dn\u011b
			if (a == ops.RA && b == ops.RB) || (a == ops.RB && b == ops.RA) {
				dst = append(dst, ops.RR); i += 2; changed = true; continue
			}
			// (rra rrb) -> rrr  a opa\u010dn\u011b
			if (a == ops.RRA && b == ops.RRB) || (a == ops.RRB && b == ops.RRA) {
				dst = append(dst, ops.RRR); i += 2; changed = true; continue
			}
			// (sa sb) -> ss  a opa\u010dn\u011b
			if (a == ops.SA && b == ops.SB) || (a == ops.SB && b == ops.SA) {
				dst = append(dst, ops.SS); i += 2; changed = true; continue
			}

			// Absorpce: rr + rra -> rb ; rr + rrb -> ra
			if a == ops.RR && b == ops.RRA { dst = append(dst, ops.RB); i += 2; changed = true; continue }
			if a == ops.RR && b == ops.RRB { dst = append(dst, ops.RA); i += 2; changed = true; continue }
			// opa\u010dn� sm\u011br: rra + rr -> rrb ; rrb + rr -> rra
			if a == ops.RRA && b == ops.RR { dst = append(dst, ops.RRB); i += 2; changed = true; continue }
			if a == ops.RRB && b == ops.RR { dst = append(dst, ops.RRA); i += 2; changed = true; continue }

			// Absorpce: rrr + ra -> rrb ; rrr + rb -> rra
			if a == ops.RRR && b == ops.RA { dst = append(dst, ops.RRB); i += 2; changed = true; continue }
			if a == ops.RRR && b == ops.RB { dst = append(dst, ops.RRA); i += 2; changed = true; continue }
			// opa\u010dn� sm\u011br: ra + rrr -> rb ; rb + rrr -> ra
			if a == ops.RA && b == ops.RRR { dst = append(dst, ops.RB); i += 2; changed = true; continue }
			if a == ops.RB && b == ops.RRR { dst = append(dst, ops.RA); i += 2; changed = true; continue }
		}
		dst = append(dst, src[i])
		i++
	}
	return dst, changed
}

// --- 2) P\u0159�m� ru\u0161en� sousedn�ch inverz� ---

func cancelInversePairs(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 2 { return src, false }
	dst := make([]ops.Operation, 0, len(src))
	changed := false
	i := 0
	for i < len(src) {
		if i+1 < len(src) && isInverse(src[i], src[i+1]) {
			i += 2
			changed = true
			continue
		}
		dst = append(dst, src[i])
		i++
	}
	return dst, changed
}

func isInverse(a, b ops.Operation) bool {
	switch a {
	case ops.RA:  return b == ops.RRA
	case ops.RRA: return b == ops.RA
	case ops.RB:  return b == ops.RRB
	case ops.RRB: return b == ops.RB
	case ops.RR:  return b == ops.RRR
	case ops.RRR: return b == ops.RR
	case ops.SA:  return b == ops.SA // sa;sa -> \u2205
	case ops.SB:  return b == ops.SB // sb;sb -> \u2205
	case ops.SS:  return b == ops.SS // ss;ss -> \u2205
	case ops.PA:  return b == ops.PB
	case ops.PB:  return b == ops.PA
	}
	return false
}

// --- 3) Ru\u0161en� inverz� \u201ep\u0159es druh� stack\u201c ---

// (ra ... rra) se zru\u0161�, pokud mezi nimi je jen B-only sekvence (\u017e�dn� bari�ry a \u017e�dn� A-only).
func cancelAcrossOtherStackA(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 3 { return src, false }
	dst := make([]ops.Operation, 0, len(src))
	changed := false

	for i := 0; i < len(src); i++ {
		op := src[i]
		if op == ops.RA || op == ops.RRA {
			inv := ops.RRA
			if op == ops.RRA { inv = ops.RA }

			// prohled�me dop\u0159edu: povol�me jen B-only; bari�ra/ A-only ru\u0161� mo\u017enost
			j := i + 1
			for j < len(src) {
				if isBarrier(src[j]) || touchesA(src[j]) { break }
				if src[j] == inv {
					// m�me (ra ... rra) p\u0159es B-only -> zru\u0161 oba, B-only nech
					dst = append(dst, src[i+1:j]...) // vlo\u017e B-only mezery
					i = j // posu\u0148 se p\u0159es zru\u0161en� p�r
					changed = true
					goto next
				}
				j++
			}
		}
		dst = append(dst, op)
	next:
	}
	return dst, changed
}

// (rb ... rrb) se zru\u0161�, pokud mezi nimi je jen A-only sekvence.
func cancelAcrossOtherStackB(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 3 { return src, false }
	dst := make([]ops.Operation, 0, len(src))
	changed := false

	for i := 0; i < len(src); i++ {
		op := src[i]
		if op == ops.RB || op == ops.RRB {
			inv := ops.RRB
			if op == ops.RRB { inv = ops.RB }

			j := i + 1
			for j < len(src) {
				if isBarrier(src[j]) || touchesB(src[j]) { break }
				if src[j] == inv {
					// (rb ... rrb) p\u0159es A-only -> zru\u0161 oba
					dst = append(dst, src[i+1:j]...)
					i = j
					changed = true
					goto next
				}
				j++
			}
		}
		dst = append(dst, op)
	next:
	}
	return dst, changed
}
