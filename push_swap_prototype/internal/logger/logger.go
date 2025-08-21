package logger

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
)

var (
	debugLogger *log.Logger
	logFile     *os.File
)

// Init initializes the logger with a log file
func Init(logDir string) error {
	// Create logs directory if it doesn't exist
	if err := os.MkdirAll(logDir, 0755); err != nil {
		return fmt.Errorf("failed to create log directory: %w", err)
	}
	
	// Create log file with fixed name
	logPath := filepath.Join(logDir, "push_swap_sorting.log")
	
	// Open log file (truncate if exists)
	var err error
	logFile, err = os.OpenFile(logPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		return fmt.Errorf("failed to create log file: %w", err)
	}
	
	// Create logger with no datetime prefix
	debugLogger = log.New(logFile, "", 0)
	
	fmt.Printf("Debug logging initialized: %s\n", logPath)
	return nil
}


// Close closes the log file
func Close() {
	if logFile != nil {
		logFile.Close()
	}
}

// LogOperation logs a push_swap operation
func LogOperation(op string, stackA, stackB []int) {
	if debugLogger != nil {
		debugLogger.Printf("OP %s: A[%v] B[%v]", op, stackA, stackB)
	}
}

// LogChunkState logs chunk sorting state
func LogChunkState(action string, loc string, size int, maxValue, pivot1, pivot2 int) {
	if debugLogger != nil {
		debugLogger.Printf("CHUNK %s: loc=%s size=%d max=%d pivot1=%d pivot2=%d", 
			action, loc, size, maxValue, pivot1, pivot2)
	}
}

// LogSplitResult logs chunk split results
func LogSplitResult(maxSize, maxLoc, midSize, midLoc, minSize, minLoc int) {
	if debugLogger != nil {
		debugLogger.Printf("SPLIT: Max(size=%d, loc=%d) Mid(size=%d, loc=%d) Min(size=%d, loc=%d)",
			maxSize, maxLoc, midSize, midLoc, minSize, minLoc)
	}
}

// LogSortingStep logs a sorting step with current state
func LogSortingStep(step string, stackA, stackB []int, details string) {
	if debugLogger != nil {
		if details != "" {
			debugLogger.Printf("SORT %s: A[%v] B[%v] %s", step, stackA, stackB, details)
		} else {
			debugLogger.Printf("SORT %s: A[%v] B[%v]", step, stackA, stackB)
		}
	}
}

// LogInitialState logs the initial state before sorting
func LogInitialState(numbers []int) {
	if debugLogger != nil {
		debugLogger.Printf("INIT: Input numbers: %v", numbers)
	}
}

// LogFinalState logs the final sorted state
func LogFinalState(stackA, stackB []int, operationCount int) {
	if debugLogger != nil {
		debugLogger.Printf("FINAL: A[%v] B[%v] Operations: %d", stackA, stackB, operationCount)
	}
}

// LogEasySort logs easy sort optimization steps
func LogEasySort(chunkSize int, value int, consecutive bool) {
	if debugLogger != nil {
		status := "not_consecutive"
		if consecutive {
			status = "consecutive"
		}
		debugLogger.Printf("EASY_SORT: chunk_size=%d value=%d status=%s", chunkSize, value, status)
	}
}

// LogThreeSort logs three-element sorting steps
func LogThreeSort(values []int, operation string) {
	if debugLogger != nil {
		debugLogger.Printf("THREE_SORT: values=[%v] operation=%s", values, operation)
	}
}

// LogFiveSort logs five-element sorting steps
func LogFiveSort(values []int, operation string) {
	if debugLogger != nil {
		debugLogger.Printf("FIVE_SORT: values=[%v] operation=%s", values, operation)
	}
}
