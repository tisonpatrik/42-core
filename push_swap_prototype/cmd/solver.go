package main

import (
	"push_swap_prototype/cmd/algo"
	"push_swap_prototype/cmd/utils"
)

func Solver(arr []int) ([]string, []int) {
	ops := make([]string, 0)
	a := make([]int, len(arr))
	copy(a, arr)
	b := make([]int, 0)
	
	// 1) Find LIS and send non-LIS to B
	keep := algo.LISIndices(a)
	i := 0
	for i < len(a) {
		if keep[i] {
			ops = append(ops, "ra")
			a = append(a[1:], a[0])
			i++
		} else {
			ops = append(ops, "pb")
			b = append([]int{a[0]}, b...)
			a = a[1:]
		}
	}
	
	// 2) Greedy return
	for len(b) > 0 {
		bestCost := -1
		bestTyp := ""
		bestPosA := -1
		bestPosB := -1
		
		for posB, val := range b {
			posA := algo.TargetPos(a, val)
			cost, typ := utils.ComputeCost(posA, len(a), posB, len(b))
			
			if bestCost == -1 || cost < bestCost {
				bestCost = cost
				bestTyp = typ
				bestPosA = posA
				bestPosB = posB
			}
		}
		
		// perform best move
		a, b = utils.ApplyRotations(&ops, a, b, bestPosA, bestPosB, bestTyp)
		ops = append(ops, "pa")
		a = append([]int{b[0]}, a...)
		b = b[1:]
	}
	
	// 3) Final rotate - put minimum at top
	minPos := 0
	minVal := a[0]
	for i, val := range a {
		if val < minVal {
			minVal = val
			minPos = i
		}
	}
	
	if minPos <= len(a)/2 {
		for i := 0; i < minPos; i++ {
			ops = append(ops, "ra")
			a = append(a[1:], a[0])
		}
	} else {
		for i := 0; i < len(a)-minPos; i++ {
			ops = append(ops, "rra")
			a = append([]int{a[len(a)-1]}, a[:len(a)-1]...)
		}
	}
	
	return ops, a
}