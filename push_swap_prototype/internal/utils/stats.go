package utils

// BenchmarkResult represents the result of a single benchmark run
type BenchmarkResult struct {
	Size           int
	Operations     int
	IsSorted       bool
	OriginalArray  []int
	FinalArray     []int
	OperationList  []string
	Failed         bool
	ErrorMessage   string
}

// BenchmarkStats represents aggregated benchmark statistics
type BenchmarkStats struct {
	TotalRuns        int
	SuccessfulRuns   int
	FailedRuns       int
	TotalOperations  int
	MinOperations    int
	MaxOperations    int
	AvgOperations    float64
	Size100Stats     *SizeStats
	Size500Stats     *SizeStats
}

// SizeStats represents statistics for a specific array size
type SizeStats struct {
	TotalRuns        int
	SuccessfulRuns   int
	FailedRuns       int
	TotalOperations  int
	MinOperations    int
	MaxOperations    int
	AvgOperations    float64
}

// OperationCounts represents the count of each operation type
type OperationCounts struct {
	Sa  int
	Sb  int
	Ss  int
	Pa  int
	Pb  int
	Ra  int
	Rb  int
	Rr  int
	Rra int
	Rrb int
	Rrr int
}

// CalculateStats calculates statistics from benchmark results
func CalculateStats(results []BenchmarkResult) *BenchmarkStats {
	stats := &BenchmarkStats{}
	
	for _, result := range results {
		stats.TotalRuns++
		stats.TotalOperations += result.Operations
		
		if result.IsSorted {
			stats.SuccessfulRuns++
		} else {
			stats.FailedRuns++
		}
		
		if stats.MinOperations == 0 || result.Operations < stats.MinOperations {
			stats.MinOperations = result.Operations
		}
		if result.Operations > stats.MaxOperations {
			stats.MaxOperations = result.Operations
		}
	}
	
	if stats.TotalRuns > 0 {
		stats.AvgOperations = float64(stats.TotalOperations) / float64(stats.TotalRuns)
	}
	
	// Calculate size-specific stats
	stats.Size100Stats = calculateSizeStats(results, 100)
	stats.Size500Stats = calculateSizeStats(results, 500)
	
	return stats
}

// calculateSizeStats calculates statistics for a specific array size
func calculateSizeStats(results []BenchmarkResult, size int) *SizeStats {
	stats := &SizeStats{}
	
	for _, result := range results {
		if result.Size == size {
			stats.TotalRuns++
			stats.TotalOperations += result.Operations
			
			if result.IsSorted {
				stats.SuccessfulRuns++
			} else {
				stats.FailedRuns++
			}
			
			if stats.MinOperations == 0 || result.Operations < stats.MinOperations {
				stats.MinOperations = result.Operations
			}
			if result.Operations > stats.MaxOperations {
				stats.MaxOperations = result.Operations
			}
		}
	}
	
	if stats.TotalRuns > 0 {
		stats.AvgOperations = float64(stats.TotalOperations) / float64(stats.TotalRuns)
	}
	
	return stats
}

// CountOperations counts the occurrences of each operation type
func CountOperations(ops []string) OperationCounts {
	counts := OperationCounts{}
	
	for _, op := range ops {
		switch op {
		case "sa":
			counts.Sa++
		case "sb":
			counts.Sb++
		case "ss":
			counts.Ss++
		case "pa":
			counts.Pa++
		case "pb":
			counts.Pb++
		case "ra":
			counts.Ra++
		case "rb":
			counts.Rb++
		case "rr":
			counts.Rr++
		case "rra":
			counts.Rra++
		case "rrb":
			counts.Rrb++
		case "rrr":
			counts.Rrr++
		}
	}
	
	return counts
}
