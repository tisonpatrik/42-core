package main

import (
	"flag"
	"fmt"
	"os"
	"push_swap_prototype/internal/logger"
	"push_swap_prototype/internal/solver"
	"strconv"
)

func main() {
	// Parse command line flags
	var logLevel = flag.String("log", "info", "Log level: none, error, warn, info, debug, trace")
	flag.Parse()

	// Set the log level based on command line argument
	switch *logLevel {
	case "none":
		logger.SetLogLevel(logger.LOG_NONE)
	case "error":
		logger.SetLogLevel(logger.LOG_ERROR)
	case "warn":
		logger.SetLogLevel(logger.LOG_WARN)
	case "info":
		logger.SetLogLevel(logger.LOG_INFO)
	case "debug":
		logger.SetLogLevel(logger.LOG_DEBUG)
	case "trace":
		logger.SetLogLevel(logger.LOG_TRACE)
	default:
		fmt.Printf("Invalid log level: %s. Using 'info' instead.\n", *logLevel)
		logger.SetLogLevel(logger.LOG_INFO)
	}

	// Initialize logger
	if err := logger.Init("logs"); err != nil {
		fmt.Printf("Failed to initialize logger: %v\n", err)
		os.Exit(1)
	}
	defer logger.Close()

	// Get remaining arguments (numbers to sort)
	args := flag.Args()
	if len(args) < 1 {
		fmt.Printf("Usage: %s [-log=level] <numbers...>\n", os.Args[0])
		fmt.Printf("Example: %s -log=info 3 1 4 1 5\n", os.Args[0])
		fmt.Printf("Example: %s -log=none 3 1 4 1 5\n", os.Args[0])
		os.Exit(1)
	}

	// Parse command line arguments to integers
	var numbers []int
	for i := 0; i < len(args); i++ {
		num, err := strconv.Atoi(args[i])
		if err != nil {
			fmt.Printf("Error: '%s' is not a valid integer\n", args[i])
			os.Exit(1)
		}
		numbers = append(numbers, num)
	}

	fmt.Printf("=== MAIN START ===\n")
	fmt.Printf("Log level: %s\n", *logLevel)
	fmt.Printf("Testing with array: %v\n", numbers)
	fmt.Printf("Array size: %d\n", len(numbers))
	fmt.Printf("=== MAIN END ===\n")

	// Solve the push swap problem
	fmt.Printf("=== SOLVING START ===\n")
	ops, result := solver.SolvePushSwap(numbers)
	fmt.Printf("=== SOLVING END ===\n")
	
	fmt.Printf("=== RESULTS ===\n")
	fmt.Printf("Operations count: %d\n", len(ops))
	fmt.Printf("Result: %v\n", result)
	
	// Check if it's sorted
	isSorted := true
	for i := 1; i < len(result); i++ {
		if result[i] < result[i-1] {
			isSorted = false
			fmt.Printf("❌ Not sorted at position %d: %d > %d\n", i, result[i-1], result[i])
			break
		}
	}
	if isSorted {
		fmt.Printf("✅ Array is sorted!\n")
	} else {
		fmt.Printf("❌ Array is NOT sorted!\n")
		os.Exit(1)
	}
	fmt.Printf("=== RESULTS END ===\n")
}
