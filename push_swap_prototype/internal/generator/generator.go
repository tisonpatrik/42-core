package generator

import (
	"math/rand"
	"time"
)

// GenerateRandomNumbers generates an array of random numbers from 0 to size-1
func GenerateRandomNumbers(size int) []int {
	rand.Seed(time.Now().UnixNano())
	
	// Create array with numbers 0 to size-1
	numbers := make([]int, size)
	for i := 0; i < size; i++ {
		numbers[i] = i
	}
	
	// Shuffle the array
	for i := len(numbers) - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		numbers[i], numbers[j] = numbers[j], numbers[i]
	}
	
	return numbers
}
