package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
)

func main() {
	size, _ := strconv.Atoi(os.Args[1])
	numbers := GenerateRandomNumbers(size)
	
	for i, num := range numbers {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(num)
	}
	fmt.Println()
}

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
