package algo

import (
	"sort"
)

// LISIndices finds indices of elements belonging to LIS (Longest Increasing Subsequence)
func LISIndices(arr []int) map[int]bool {
	n := len(arr)
	parent := make([]int, n)
	for i := range parent {
		parent[i] = -1
	}
	
	tails := make([]int, 0)
	tailsVal := make([]int, 0)
	
	for i, x := range arr {
		j := sort.SearchInts(tailsVal, x)
		if j == len(tailsVal) {
			tailsVal = append(tailsVal, x)
			tails = append(tails, i)
		} else {
			tailsVal[j] = x
			tails[j] = i
		}
		if j > 0 {
			parent[i] = tails[j-1]
		}
	}
	
	// reconstruct LIS
	lis := make([]int, 0)
	k := tails[len(tails)-1]
	for k != -1 {
		lis = append(lis, k)
		k = parent[k]
	}
	
	// reverse and convert to set
	result := make(map[int]bool)
	for i := len(lis) - 1; i >= 0; i-- {
		result[lis[i]] = true
	}
	return result
}
