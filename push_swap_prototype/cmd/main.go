package main

import (
	"os"
	"push_swap_prototype/internal/benchmark"
)

func main() {
	success := benchmark.RunBenchmark(10000)
	
	if !success {
		os.Exit(1)
	}
}
