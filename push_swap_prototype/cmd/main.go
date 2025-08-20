package main

import (
	"os"
	"push_swap_prototype/internal/benchmark"
)

func main() {
	success := benchmark.RunBenchmark(1)
	
	if !success {
		os.Exit(1)
	}
}
