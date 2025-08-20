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
