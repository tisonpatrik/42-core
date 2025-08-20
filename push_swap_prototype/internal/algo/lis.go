package algo

// FindLISIndices finds indices of elements belonging to LIS (Longest Increasing Subsequence)
func FindLISIndices(arr []int) map[int]bool {
	if len(arr) == 0 {
		return make(map[int]bool)
	}
	
	// Use a simpler, more reliable LIS algorithm
	lis := findLISIndices(arr)
	return convertToIndexSet(lis)
}

// findLISIndices finds the indices of the longest increasing subsequence
func findLISIndices(arr []int) []int {
	n := len(arr)
	if n == 0 {
		return []int{}
	}
	
	// dp[i] stores the length of LIS ending at index i
	dp := make([]int, n)
	// prev[i] stores the previous index in the LIS ending at index i
	prev := make([]int, n)
	
	// Initialize
	for i := range dp {
		dp[i] = 1
		prev[i] = -1
	}
	
	maxLen := 1
	maxEnd := 0
	
	// Fill dp array
	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			if arr[i] > arr[j] && dp[j]+1 > dp[i] {
				dp[i] = dp[j] + 1
				prev[i] = j
			}
		}
		if dp[i] > maxLen {
			maxLen = dp[i]
			maxEnd = i
		}
	}
	
	// Reconstruct the LIS
	lis := make([]int, 0)
	for i := maxEnd; i != -1; i = prev[i] {
		lis = append([]int{i}, lis...)
	}
	
	return lis
}

// convertToIndexSet converts a slice of indices to a map for O(1) lookup
func convertToIndexSet(indices []int) map[int]bool {
	result := make(map[int]bool)
	for _, idx := range indices {
		result[idx] = true
	}
	return result
}
