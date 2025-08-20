package utils

// OperationStats tracks statistics for different operation types
type OperationStats struct {
	Sa   int
	Sb   int
	Ss   int
	Pa   int
	Pb   int
	Ra   int
	Rb   int
	Rr   int
	Rra  int
	Rrb  int
	Rrr  int
}

// GetTotalOperations returns the total number of operations
func (s *OperationStats) GetTotalOperations() int {
	return s.Sa + s.Sb + s.Ss + s.Pa + s.Pb + s.Ra + s.Rb + s.Rr + s.Rra + s.Rrb + s.Rrr
}

// CountOperations counts the occurrences of each operation type
func CountOperations(ops []string) *OperationStats {
	stats := &OperationStats{}
	
	for _, op := range ops {
		switch op {
		case "sa":
			stats.Sa++
		case "sb":
			stats.Sb++
		case "ss":
			stats.Ss++
		case "pa":
			stats.Pa++
		case "pb":
			stats.Pb++
		case "ra":
			stats.Ra++
		case "rb":
			stats.Rb++
		case "rra":
			stats.Rra++
		case "rrb":
			stats.Rrb++
		case "rr":
			stats.Rr++
		case "rrr":
			stats.Rrr++
		}
	}
	
	return stats
}

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

// BenchmarkStats aggregates statistics across multiple benchmark runs
type BenchmarkStats struct {
	TotalRuns      int
	SuccessfulRuns int
	FailedRuns     int
	TotalOperations int
	MinOperations   int
	MaxOperations   int
	AvgOperations   float64
	Size100Stats    *SizeStats
	Size500Stats    *SizeStats
}

// SizeStats tracks statistics for a specific array size
type SizeStats struct {
	Size           int
	TotalRuns      int
	SuccessfulRuns int
	FailedRuns     int
	TotalOperations int
	MinOperations   int
	MaxOperations   int
	AvgOperations   float64
}

// CalculateStats calculates comprehensive statistics from benchmark results
func CalculateStats(results []BenchmarkResult) *BenchmarkStats {
	if len(results) == 0 {
		return &BenchmarkStats{}
	}
	
	stats := &BenchmarkStats{
		TotalRuns: len(results),
		MinOperations: results[0].Operations,
		MaxOperations: results[0].Operations,
	}
	
	// Separate results by size
	var size100Results, size500Results []BenchmarkResult
	
	for _, result := range results {
		stats.TotalOperations += result.Operations
		
		if result.IsSorted {
			stats.SuccessfulRuns++
		} else {
			stats.FailedRuns++
		}
		
		if result.Operations < stats.MinOperations {
			stats.MinOperations = result.Operations
		}
		if result.Operations > stats.MaxOperations {
			stats.MaxOperations = result.Operations
		}
		
		// Separate by size
		if result.Size == 100 {
			size100Results = append(size100Results, result)
		} else if result.Size == 500 {
			size500Results = append(size500Results, result)
		}
	}
	
	stats.AvgOperations = float64(stats.TotalOperations) / float64(stats.TotalRuns)
	
	// Calculate size-specific stats
	stats.Size100Stats = calculateSizeStats(size100Results)
	stats.Size500Stats = calculateSizeStats(size500Results)
	
	return stats
}

// calculateSizeStats calculates statistics for a specific array size
func calculateSizeStats(results []BenchmarkResult) *SizeStats {
	if len(results) == 0 {
		return &SizeStats{}
	}
	
	stats := &SizeStats{
		Size: results[0].Size,
		TotalRuns: len(results),
		MinOperations: results[0].Operations,
		MaxOperations: results[0].Operations,
	}
	
	for _, result := range results {
		stats.TotalOperations += result.Operations
		
		if result.IsSorted {
			stats.SuccessfulRuns++
		} else {
			stats.FailedRuns++
		}
		
		if result.Operations < stats.MinOperations {
			stats.MinOperations = result.Operations
		}
		if result.Operations > stats.MaxOperations {
			stats.MaxOperations = result.Operations
		}
	}
	
	stats.AvgOperations = float64(stats.TotalOperations) / float64(stats.TotalRuns)
	return stats
}
