package main

import (
	"math/rand"
)

func GenerateRandomNumbers(size int) []int {
	numbers := make([]int, size)
	for i := range size {
		numbers[i] = i
	}

	for i := len(numbers) - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		numbers[i], numbers[j] = numbers[j], numbers[i]
	}

	return numbers
}
