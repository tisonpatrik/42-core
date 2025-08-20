package main

import (
	"fmt"
	"math/rand"
)

func Solver(numbers []int) {
	fmt.Println(numbers)
}

func RandomNumbersGenerator(size int) []int {
	numbers := make([]int, size)
	used := make(map[int]bool)
	
	for i := range size {
		for {
			num := rand.Intn(size)
			if !used[num] {
				numbers[i] = num
				used[num] = true
				break
			}
		}
	}
	return numbers
}

func BenchmarkSolver(iterations int) {
	
	for range iterations {
		numbers := RandomNumbersGenerator(100)
		Solver(numbers)
	}
	
	for range iterations {
		numbers := RandomNumbersGenerator(500)
		Solver(numbers)
	}
}

func main() {

	BenchmarkSolver(10000)
}
