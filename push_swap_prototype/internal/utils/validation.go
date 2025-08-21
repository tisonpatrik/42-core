package utils

// IsSorted checks if an array is sorted in ascending order
func IsSorted(arr []int) bool {
	if len(arr) <= 1 {
		return true
	}
	
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			return false
		}
	}
	return true
}

// RandomToRank converts numbers to ranks (1 to n) like the C implementation
func RandomToRank(numbers []int) []int {
	size := len(numbers)
	rank := make([]int, size)
	
	// Exactly like C implementation: count how many numbers are <= current number
	for i := 0; i < size; i++ {
		countSmaller := 0
		for j := 0; j < size; j++ {
			if numbers[j] <= numbers[i] {
				countSmaller++
			}
		}
		rank[i] = countSmaller
	}
	
	return rank
}
