package benchmark

import (
	"fmt"
	"push_swap_prototype/internal/generator"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/utils"
	"strings"
)

// RunBenchmark runs the push swap benchmark with the specified number of iterations
func RunBenchmark(iterations int) {
	var results []utils.BenchmarkResult
	
	fmt.Printf("🚀 Starting Push Swap Benchmark with %d iterations\n", iterations)
	fmt.Println(strings.Repeat("=", 60))
	
	// Test with size 100 arrays
	fmt.Printf("📊 Testing arrays of size 100...\n")
	for i := 0; i < iterations; i++ {
		numbers := generator.GenerateRandomNumbers(100)
		ops, finalArray := solver.SolvePushSwap(numbers)
		
		// Validate the result
		isSorted := utils.IsSorted(finalArray)
		operationCount := len(ops)
		
		result := utils.BenchmarkResult{
			Size:          100,
			Operations:    operationCount,
			IsSorted:      isSorted,
			OriginalArray: numbers,
			FinalArray:    finalArray,
			OperationList: ops,
			Failed:        !isSorted,
		}
		
		if !isSorted {
			result.ErrorMessage = "Array not properly sorted"
			fmt.Printf("❌ Iteration %d failed: Array not sorted properly\n", i+1)
			fmt.Printf("   Original: %v\n", numbers)
			fmt.Printf("   Final:    %v\n", finalArray)
		}
		
		results = append(results, result)
		
		if (i+1)%1000 == 0 {
			fmt.Printf("   Completed %d iterations...\n", i+1)
		}
	}
	
	// Test with size 500 arrays
	fmt.Printf("\n📊 Testing arrays of size 500...\n")
	for i := 0; i < iterations; i++ {
		numbers := generator.GenerateRandomNumbers(500)
		ops, finalArray := solver.SolvePushSwap(numbers)
		
		// Validate the result
		isSorted := utils.IsSorted(finalArray)
		operationCount := len(ops)
		
		result := utils.BenchmarkResult{
			Size:          500,
			Operations:    operationCount,
			IsSorted:      isSorted,
			OriginalArray: numbers,
			FinalArray:    finalArray,
			OperationList: ops,
			Failed:        !isSorted,
		}
		
		if !isSorted {
			result.ErrorMessage = "Array not properly sorted"
			fmt.Printf("❌ Iteration %d failed: Array not sorted properly\n", i+1)
			fmt.Printf("   Original: %v\n", numbers)
			fmt.Printf("   Final:    %v\n", finalArray)
		}
		
		results = append(results, result)
		
		if (i+1)%1000 == 0 {
			fmt.Printf("   Completed %d iterations...\n", i+1)
		}
	}
	
	// Calculate and display statistics
	fmt.Println("\n" + strings.Repeat("=", 60))
	fmt.Println("📈 BENCHMARK RESULTS")
	fmt.Println(strings.Repeat("=", 60))
	
	stats := utils.CalculateStats(results)
	displayStats(stats)
	
	// Show detailed operation breakdown for a few sample runs
	fmt.Println("\n🔍 SAMPLE OPERATION BREAKDOWN")
	fmt.Println(strings.Repeat("=", 60))
	
	// Show first successful run of each size
	showSampleRun(results, 100)
	showSampleRun(results, 500)
}

// displayStats displays the benchmark statistics
func displayStats(stats *utils.BenchmarkStats) {
	fmt.Printf("Total Runs: %d\n", stats.TotalRuns)
	fmt.Printf("Successful: %d\n", stats.SuccessfulRuns)
	fmt.Printf("Failed:     %d\n", stats.FailedRuns)
	fmt.Printf("Success Rate: %.2f%%\n", float64(stats.SuccessfulRuns)/float64(stats.TotalRuns)*100)
	
	fmt.Printf("\nOverall Statistics:\n")
	fmt.Printf("  Total Operations: %d\n", stats.TotalOperations)
	fmt.Printf("  Min Operations:   %d\n", stats.MinOperations)
	fmt.Printf("  Max Operations:   %d\n", stats.MaxOperations)
	fmt.Printf("  Avg Operations:   %.2f\n", stats.AvgOperations)
	
	if stats.Size100Stats != nil {
		fmt.Printf("\nSize 100 Statistics:\n")
		displaySizeStats(stats.Size100Stats)
	}
	
	if stats.Size500Stats != nil {
		fmt.Printf("\nSize 500 Statistics:\n")
		displaySizeStats(stats.Size500Stats)
	}
}

// displaySizeStats displays statistics for a specific array size
func displaySizeStats(sizeStats *utils.SizeStats) {
	fmt.Printf("  Total Runs: %d\n", sizeStats.TotalRuns)
	fmt.Printf("  Successful: %d\n", sizeStats.SuccessfulRuns)
	fmt.Printf("  Failed:     %d\n", sizeStats.FailedRuns)
	fmt.Printf("  Success Rate: %.2f%%\n", float64(sizeStats.SuccessfulRuns)/float64(sizeStats.TotalRuns)*100)
	fmt.Printf("  Total Operations: %d\n", sizeStats.TotalOperations)
	fmt.Printf("  Min Operations:   %d\n", sizeStats.MinOperations)
	fmt.Printf("  Max Operations:   %d\n", sizeStats.MaxOperations)
	fmt.Printf("  Avg Operations:   %.2f\n", sizeStats.AvgOperations)
}

// showSampleRun shows a sample successful run for a specific array size
func showSampleRun(results []utils.BenchmarkResult, size int) {
	for _, result := range results {
		if result.Size == size && result.IsSorted {
			fmt.Printf("\nSample run for size %d (successful):\n", size)
			fmt.Printf("  Operations: %d\n", result.Operations)
			
			opStats := utils.CountOperations(result.OperationList)
			fmt.Printf("  Operation breakdown:\n")
			if opStats.Sa > 0 {
				fmt.Printf("    sa:  %d\n", opStats.Sa)
			}
			if opStats.Sb > 0 {
				fmt.Printf("    sb:  %d\n", opStats.Sb)
			}
			if opStats.Ss > 0 {
				fmt.Printf("    ss:  %d\n", opStats.Ss)
			}
			if opStats.Pa > 0 {
				fmt.Printf("    pa:  %d\n", opStats.Pa)
			}
			if opStats.Pb > 0 {
				fmt.Printf("    pb:  %d\n", opStats.Pb)
			}
			if opStats.Ra > 0 {
				fmt.Printf("    ra:  %d\n", opStats.Ra)
			}
			if opStats.Rb > 0 {
				fmt.Printf("    rb:  %d\n", opStats.Rb)
			}
			if opStats.Rr > 0 {
				fmt.Printf("    rr:  %d\n", opStats.Rr)
			}
			if opStats.Rra > 0 {
				fmt.Printf("    rra: %d\n", opStats.Rra)
			}
			if opStats.Rrb > 0 {
				fmt.Printf("    rrb: %d\n", opStats.Rrb)
			}
			if opStats.Rrr > 0 {
				fmt.Printf("    rrr: %d\n", opStats.Rrr)
			}
			
			// Show first few operations
			if len(result.OperationList) > 0 {
				fmt.Printf("  First 10 operations: %v\n", result.OperationList[:min(10, len(result.OperationList))])
			}
			break
		}
	}
}

// min returns the minimum of two integers
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
