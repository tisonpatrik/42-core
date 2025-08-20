package main

import "math/rand"


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