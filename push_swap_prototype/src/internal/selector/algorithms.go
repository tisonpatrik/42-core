package selector

// BinarySearchInsertionPoint performs binary search to find insertion point for a value
// using a custom comparator function
func BinarySearchInsertionPoint(arr []int, val int, comparator func(int, int) bool) int {
	n := len(arr)
	if n == 0 {
		return 0
	}
	
	left, right := 0, n
	for left < right {
		mid := (left + right) / 2
		if comparator(arr[mid], val) {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return left
}

// FindInsertionIndex finds the insertion index in a sorted descending array (stack B)
// maintaining local order "prev > val > next"
func FindInsertionIndex(sortedArr []int, val int) int {
	if IsEmpty(sortedArr) {
		return 0
	}
	
	// Binary search for insertion point in sorted descending array
	idx := BinarySearchInsertionPoint(sortedArr, val, func(arrVal, targetVal int) bool {
		return arrVal < targetVal
	})
	
	n := len(sortedArr)
	idx = idx % n
	
	// Check circular neighbors for proper local order
	prev := sortedArr[(idx-1+n)%n]
	next := sortedArr[idx%n]
	if prev > val && val > next {
		return idx
	}
	
	// Fallback to linear search if binary search doesn't find exact position
	for j := 0; j < n; j++ {
		prev := sortedArr[(j-1+n)%n]
		next := sortedArr[j]
		if prev > val && val > next {
			return j
		}
	}
	return 0
}

// FindTargetPosition finds the target position in a sorted ascending array (stack A)
// for inserting a value to maintain ascending order
func FindTargetPosition(sortedArr []int, val int) int {
	if IsEmpty(sortedArr) {
		return 0
	}
	
 	// Find the first element > val
	bestIdx, bestVal := -1, 0
	for i, x := range sortedArr {
		if x > val {
			if bestIdx == -1 || x < bestVal {
				bestVal, bestIdx = x, i
			}
		}
	}
	if bestIdx != -1 {
		return bestIdx
	}
	
	// If val >= all elements, return index of minimum
	minIdx, minVal := 0, sortedArr[0]
	for i, x := range sortedArr {
		if x < minVal {
			minVal, minIdx = x, i
		}
	}
	return minIdx
}

// NormalizeIndex normalizes an index to be within bounds [0, n)
func NormalizeIndex(n, k int) int {
	if n == 0 {
		return 0
	}
	k = ((k % n) + n) % n
	return k
}
