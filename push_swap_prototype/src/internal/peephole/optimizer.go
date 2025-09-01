package optimizer

import "push_swap_prototype/internal/ops"

// OptimizeOps: multiple rounds of safe local rewrites.
// Passes:
//  1) bubbleAcrossOtherStack (window ≤ maxBubble) – extracts candidates for merge
//  2) mergeNeighbors – (ra rb)->rr, (rra rrb)->rrr, (sa sb)->ss + absorption rr/rrr
//  3) cancelInversePairs – adjacent inverses (ra rra), (pb pa), (ss ss), ...
//  4) cancelAcrossOtherStackA/B – (ra ... rra) / (rb ... rrb) across other stack
// OptimizeOps applies multiple rounds of safe local optimizations to the operation sequence.
// It performs bubble operations, neighbor merging, inverse pair cancellation, and cross-stack optimizations.
func OptimizeOps(seq []ops.Operation) []ops.Operation {
	if len(seq) < 2 {
		return seq
	}
	out := seq
	const maxBubble = 4

	changed := true
	for changed {
		changed = false

		var c bool
		out, c = bubbleAcrossOtherStack(out, maxBubble)
		changed = changed || c

		out, c = mergeNeighbors(out)
		changed = changed || c

		out, c = cancelInversePairs(out)
		changed = changed || c

		out, c = cancelAcrossOtherStackA(out)
		changed = changed || c

		out, c = cancelAcrossOtherStackB(out)
		changed = changed || c
	}
	return out
}

// ---------- bubble (short window, commutation across other stack) ----------
//
// Goal: move through B-only (resp. A-only) operations so that
// adjacency suitable for merge is created: (ra rb)->rr, (rra rrb)->rrr (and vice versa).
//
// We do NOT cross barriers: pa/pb, rr/rrr, ss.

func bubbleAcrossOtherStack(src []ops.Operation, maxGap int) ([]ops.Operation, bool) {
	n := len(src)
	if n < 3 {
		return src, false
	}
	out := make([]ops.Operation, n)
	copy(out, src)
	changed := false

	// helper function: attempt to bubble op at index j through [i+1..j-1]
	bubble := func(i, j int, isA bool) bool {
		// allow only "other stack only" in gap and no barriers
		for k := i + 1; k < j; k++ {
			if isBarrier(out[k]) {
				return false
			}
			// when bubbling A-op, gap must be B-only
			if isA && (touchesA(out[k]) || !touchesB(out[k]) && !isPureB(out[k])) {
				return false
			}
			// when bubbling B-op, gap must be A-only
			if !isA && (touchesB(out[k]) || !touchesA(out[k]) && !isPureA(out[k])) {
				return false
			}
		}
		// perform series of adjacent swaps (commutation)
		for k := j; k > i+1; k-- {
			out[k], out[k-1] = out[k-1], out[k]
		}
		return true
	}

	// go through sequence and look for pairs to merge within maxGap range
	for i := 0; i < len(out)-1; i++ {
		a := out[i]

		// A-op + look for suitable B-op in window to create rr/rrr
		if a == ops.RA || a == ops.RRA {
			want := ops.RB
			if a == ops.RRA {
				want = ops.RRB
			}
			for j := i + 1; j < len(out) && j-i-1 <= maxGap; j++ {
				if out[j] == want {
					if bubble(i, j, true) { // bubble B-op through B-only block
						changed = true
						// move one step further, merge will handle next pass
					}
					break
				}
				if isBarrier(out[j]) || touchesA(out[j]) {
					break // hit barrier or A-op → not this way
				}
			}
			continue
		}

		// B-op + look for suitable A-op in window
		if a == ops.RB || a == ops.RRB {
			want := ops.RA
			if a == ops.RRB {
				want = ops.RRA
			}
			for j := i + 1; j < len(out) && j-i-1 <= maxGap; j++ {
				if out[j] == want {
					if bubble(i, j, false) { // bubble A-op through A-only block
						changed = true
					}
					break
				}
				if isBarrier(out[j]) || touchesB(out[j]) {
					break
				}
			}
			continue
		}
	}

	return out, changed
}

// purely A-only?
func isPureA(op ops.Operation) bool {
	return op == ops.SA || op == ops.RA || op == ops.RRA
}

// purely B-only?
func isPureB(op ops.Operation) bool {
	return op == ops.SB || op == ops.RB || op == ops.RRB
}

// ---------- mergeNeighbors (unchanged) ----------

func mergeNeighbors(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 2 { return src, false }
	dst := make([]ops.Operation, 0, len(src))
	changed := false
	i := 0
	for i < len(src) {
		if i+1 < len(src) {
			a, b := src[i], src[i+1]

			// (ra rb) -> rr  and vice versa
			if (a == ops.RA && b == ops.RB) || (a == ops.RB && b == ops.RA) {
				dst = append(dst, ops.RR); i += 2; changed = true; continue
			}
			// (rra rrb) -> rrr  and vice versa
			if (a == ops.RRA && b == ops.RRB) || (a == ops.RRB && b == ops.RRA) {
				dst = append(dst, ops.RRR); i += 2; changed = true; continue
			}
			// (sa sb) -> ss  and vice versa
			if (a == ops.SA && b == ops.SB) || (a == ops.SB && b == ops.SA) {
				dst = append(dst, ops.SS); i += 2; changed = true; continue
			}

			// Absorption: rr + rra -> rb ; rr + rrb -> ra
			if a == ops.RR && b == ops.RRA { dst = append(dst, ops.RB); i += 2; changed = true; continue }
			if a == ops.RR && b == ops.RRB { dst = append(dst, ops.RA); i += 2; changed = true; continue }
			// vice versa
			if a == ops.RRA && b == ops.RR { dst = append(dst, ops.RRB); i += 2; changed = true; continue }
			if a == ops.RRB && b == ops.RR { dst = append(dst, ops.RRA); i += 2; changed = true; continue }

			// Absorption: rrr + ra -> rrb ; rrr + rb -> rra
			if a == ops.RRR && b == ops.RA { dst = append(dst, ops.RRB); i += 2; changed = true; continue }
			if a == ops.RRR && b == ops.RB { dst = append(dst, ops.RRA); i += 2; changed = true; continue }
			// vice versa
			if a == ops.RA && b == ops.RRR { dst = append(dst, ops.RB); i += 2; changed = true; continue }
			if a == ops.RB && b == ops.RRR { dst = append(dst, ops.RA); i += 2; changed = true; continue }
		}
		dst = append(dst, src[i])
		i++
	}
	return dst, changed
}

// ---------- canceling adjacent inverses (unchanged) ----------

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
	case ops.SA:  return b == ops.SA // sa;sa -> ∅
	case ops.SB:  return b == ops.SB // sb;sb -> ∅
	case ops.SS:  return b == ops.SS // ss;ss -> ∅
	case ops.PA:  return b == ops.PB
	case ops.PB:  return b == ops.PA
	}
	return false
}

// ---------- canceling inverses across other stack (unchanged logic) ----------

func cancelAcrossOtherStackA(src []ops.Operation) ([]ops.Operation, bool) {
	if len(src) < 3 { return src, false }
	dst := make([]ops.Operation, 0, len(src))
	changed := false

	for i := 0; i < len(src); i++ {
		op := src[i]
		if op == ops.RA || op == ops.RRA {
			inv := ops.RRA
			if op == ops.RRA { inv = ops.RA }

			j := i + 1
			for j < len(src) {
				if isBarrier(src[j]) || touchesA(src[j]) { break }
				if src[j] == inv {
					// only B-only between them -> cancel both, keep B-only
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

// ---------- operation properties ----------

func touchesA(op ops.Operation) bool {
	switch op {
	case ops.SA, ops.RA, ops.RRA:
		return true
	}
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
