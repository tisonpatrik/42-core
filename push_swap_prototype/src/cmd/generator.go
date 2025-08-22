package main

import (
	"math/rand"
)

// GenerateRandomNumbers generates an array of random numbers from 0 to size-1
// Ensures all values are unique (no duplicates)
func GenerateRandomNumbers(size int) []int {
	// Create array with numbers 0 to size-1
	numbers := make([]int, size)
	for i := range size {
		numbers[i] = i
	}
	
	// Fisher-Yates shuffle algorithm for unbiased shuffling
	for i := len(numbers) - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		numbers[i], numbers[j] = numbers[j], numbers[i]
	}
	
	return numbers
}
