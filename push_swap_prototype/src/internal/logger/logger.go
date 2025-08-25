package logger

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
	"runtime"
	"sync"
	"time"

	"push_swap_prototype/internal/stack"
)

// Logger represents a thread-safe file logger
type Logger struct {
	file     *os.File
	logger   *log.Logger
	mutex    sync.Mutex
	filename string
}

// Global logger instance
var debugLogger *Logger
var once sync.Once

// getLogger returns the singleton logger instance
func getLogger() *Logger {
	once.Do(func() {
		debugLogger = &Logger{}
		debugLogger.init()
	})
	return debugLogger
}

// init initializes the logger with best practices
func (l *Logger) init() {
	l.mutex.Lock()
	defer l.mutex.Unlock()
	
	// Create logs directory if it doesn't exist
	logsDir := "logs"
	if err := os.MkdirAll(logsDir, 0755); err != nil {
		fmt.Printf("Warning: Could not create logs directory: %v\n", err)
		return
	}
	
	// Create filename with timestamp like C version
	timestamp := time.Now().Format("2006-01-02_15-04-05")
	l.filename = filepath.Join(logsDir, fmt.Sprintf("push_swap_%s.log", timestamp))
	
	// Open file with proper permissions and flags
	var err error
	l.file, err = os.OpenFile(l.filename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Printf("Warning: Could not open debug log file: %v\n", err)
		return
	}
	
	// Create logger with no prefix (we add timestamp manually)
	l.logger = log.New(l.file, "", 0)
	
	// Log initialization
	l.logger.Printf("[%s] Logger initialized: %s\n", 
		time.Now().Format("2006-01-02 15:04:05"), l.filename)
}

// write writes a message to the log file with proper error handling
func (l *Logger) write(message string) {
	l.mutex.Lock()
	defer l.mutex.Unlock()
	
	if l.logger == nil {
		return
	}
	
	// Ensure file is still valid
	if l.file == nil {
		return
	}
	
	// Write with error handling
	if err := l.logger.Output(0, message); err != nil {
		fmt.Printf("Warning: Failed to write to log file: %v\n", err)
	}
	
	// Flush to ensure data is written to disk
	if err := l.file.Sync(); err != nil {
		fmt.Printf("Warning: Failed to sync log file: %v\n", err)
	}
}

// close properly closes the logger
func (l *Logger) close() {
	l.mutex.Lock()
	defer l.mutex.Unlock()
	
	if l.file != nil {
		// Log shutdown message
		if l.logger != nil {
			l.logger.Printf("[%s] Logger shutting down\n", 
				time.Now().Format("2006-01-02 15:04:05"))
		}
		
		// Close file
		if err := l.file.Close(); err != nil {
			fmt.Printf("Warning: Failed to close log file: %v\n", err)
		}
		
		l.file = nil
		l.logger = nil
	}
}

// DebugLog writes to file only like C version - EXACTLY matching C format
func DebugLog(format string, args ...interface{}) {
	logger := getLogger()
	
	// Format the message
	message := fmt.Sprintf(format, args...)
	
	// Add timestamp EXACTLY like C: [2025-08-25 15:04:05]
	timestamp := time.Now().Format("[2006-01-02 15:04:05]")
	fullMessage := fmt.Sprintf("%s %s\n", timestamp, message)
	
	// Write to file only (like C version) - NO stdout output
	logger.write(fullMessage)
}

// CloseDebugLogger closes the debug file when done
func CloseDebugLogger() {
	if debugLogger != nil {
		debugLogger.close()
	}
}

// getCallerFunctionName gets the name of the calling function
func getCallerFunctionName() string {
	pc, _, _, ok := runtime.Caller(2) // Skip 2 frames to get the actual caller
	if !ok {
		return "UNKNOWN"
	}
	
	fn := runtime.FuncForPC(pc)
	if fn == nil {
		return "UNKNOWN"
	}
	
	return filepath.Base(fn.Name())
}

// DebugLogFunctionEntry logs function entry with stack state - EXACTLY like C
func DebugLogFunctionEntry(functionName string, ps *stack.PushSwapData) {
	DebugLog("ENTRY: %s()", functionName)
	if ps != nil {
		DebugLogStackState(ps, "function entry")
	}
}

// DebugLogFunctionExit logs function exit with stack state - EXACTLY like C
func DebugLogFunctionExit(functionName string, ps *stack.PushSwapData) {
	DebugLog("EXIT: %s()", functionName)
	if ps != nil {
		DebugLogStackState(ps, "function exit")
	}
}

// DebugLogOperation logs operation execution with stack state - EXACTLY like C
func DebugLogOperation(opName string, ps *stack.PushSwapData) {
	DebugLog("OPERATION: %s", opName)
	if ps != nil {
		DebugLogStackState(ps, "after operation")
	}
}

// DebugLogStackState logs complete stack state - EXACTLY like C
func DebugLogStackState(ps *stack.PushSwapData, context string) {
	if ps == nil {
		return
	}
	
	DebugLog("STACK STATE (%s):", context)
	DebugLog("  Stack A: size=%d, top=%d, bottom=%d", 
		ps.A.CurrentSize(), ps.A.GetTop(), ps.A.GetBottom())
	DebugLog("  Stack B: size=%d, top=%d, bottom=%d", 
		ps.B.CurrentSize(), ps.B.GetTop(), ps.B.GetBottom())
	
	// Log ALL elements of each stack (no truncation) - EXACTLY like C
	if ps.A.CurrentSize() > 0 {
		var aElements string
		i := ps.A.GetTop()
		for j := 0; j < ps.A.CurrentSize(); j++ {
			aElements += fmt.Sprintf("%d ", ps.A.GetStack()[i])
			i = ps.A.NextDown(i)
		}
		DebugLog("  Stack A elements: [%s]", aElements)
	}
	
	if ps.B.CurrentSize() > 0 {
		var bElements string
		i := ps.B.GetTop()
		for j := 0; j < ps.B.CurrentSize(); j++ {
			bElements += fmt.Sprintf("%d ", ps.B.GetStack()[i])
			i = ps.B.NextDown(i)
		}
		DebugLog("  Stack B elements: [%s]", bElements)
	}
}

// DebugLogChunkState logs chunk state - EXACTLY like C
func DebugLogChunkState(chunk *stack.Chunk, context string) {
	if chunk == nil {
		return
	}
	DebugLog("CHUNK STATE (%s):", context)
	DebugLog("  Location: %d, Size: %d", chunk.Loc, chunk.Size)
}

// DebugLogVariableChange logs variable change with line number - EXACTLY like C
func DebugLogVariableChange(funcName string, lineNum int, ps *stack.PushSwapData, varName string, varValue string) {
	DebugLog("LINE %d in %s(): %s = %s", lineNum, funcName, varName, varValue)
	
	// Also log current stack state when variables change - EXACTLY like C
	if ps != nil {
		DebugLogStackState(ps, "variable change")
	}
}

// DebugLogLineState logs complete line state - EXACTLY like C
func DebugLogLineState(funcName string, lineNum int, ps *stack.PushSwapData, context string) {
	DebugLog("=== LINE %d in %s() === %s", lineNum, funcName, context)
	
	if ps != nil {
		DebugLogAllVariables(funcName, lineNum, ps, context)
	}
}

// DebugLogBeforeOperation logs before operation execution - EXACTLY like C
func DebugLogBeforeOperation(funcName string, lineNum int, ps *stack.PushSwapData, opName string) {
	DebugLog("BEFORE %s at LINE %d in %s()", opName, lineNum, funcName)
	
	if ps != nil {
		DebugLogStackState(ps, "before operation")
	}
}

// DebugLogAfterOperation logs after operation execution - EXACTLY like C
func DebugLogAfterOperation(funcName string, lineNum int, ps *stack.PushSwapData, opName string) {
	DebugLog("AFTER %s at LINE %d in %s()", opName, lineNum, funcName)
	
	if ps != nil {
		DebugLogStackState(ps, "after operation")
	}
}

// DebugLogAllVariables logs all variables in current scope - EXACTLY like C
func DebugLogAllVariables(funcName string, lineNum int, ps *stack.PushSwapData, context string) {
	if ps == nil {
		return
	}
	
	DebugLog("ALL VARIABLES at LINE %d in %s() - %s:", lineNum, funcName, context)
	
	// Log stack A details
	DebugLog("  Stack A: size=%d, top=%d, bottom=%d", 
		ps.A.CurrentSize(), ps.A.GetTop(), ps.A.GetBottom())
	
	// Log stack B details  
	DebugLog("  Stack B: size=%d, top=%d, bottom=%d", 
		ps.B.CurrentSize(), ps.B.GetTop(), ps.B.GetBottom())
	
	// Log operation list info
	if ps.OpList != nil {
		opCount := len(ps.OpList)
		DebugLog("  Operations in list: %d", opCount)
	}
	
	// Log writing mode
	DebugLog("  Writing mode: %t", ps.WritingMode)
	
	// Log ALL elements of each stack for complete visibility - EXACTLY like C
	if ps.A.CurrentSize() > 0 {
		var aElements string
		i := ps.A.GetTop()
		for j := 0; j < ps.A.CurrentSize(); j++ {
			aElements += fmt.Sprintf("%d ", ps.A.GetStack()[i])
			i = ps.A.NextDown(i)
		}
		DebugLog("  Stack A ALL elements: [%s]", aElements)
	}
	
	if ps.B.CurrentSize() > 0 {
		var bElements string
		i := ps.B.GetTop()
		for j := 0; j < ps.B.CurrentSize(); j++ {
			bElements += fmt.Sprintf("%d ", ps.B.GetStack()[i])
			i = ps.B.NextDown(i)
		}
		DebugLog("  Stack B ALL elements: [%s]", bElements)
	}
}

// Convenience macros for easy function logging - EXACTLY like C
func DebugFuncEntry(ps *stack.PushSwapData) {
	functionName := getCallerFunctionName()
	DebugLogFunctionEntry(functionName, ps)
}

func DebugFuncExit(ps *stack.PushSwapData) {
	functionName := getCallerFunctionName()
	DebugLogFunctionExit(functionName, ps)
}

func DebugOp(op string, ps *stack.PushSwapData) {
	DebugLogOperation(op, ps)
}

// Convenience functions for line-by-line logging - EXACTLY like C
func DebugLine(ps *stack.PushSwapData, lineNum int) {
	functionName := getCallerFunctionName()
	DebugLogLineState(functionName, lineNum, ps, "line execution")
}

func DebugVar(ps *stack.PushSwapData, varName string, varValue string) {
	functionName := getCallerFunctionName()
	DebugLogVariableChange(functionName, 0, ps, varName, varValue)
}

func DebugStackChange(ps *stack.PushSwapData, context string) {
	DebugLogStackState(ps, context)
}

func DebugBeforeOp(ps *stack.PushSwapData, opName string) {
	functionName := getCallerFunctionName()
	DebugLogBeforeOperation(functionName, 0, ps, opName)
}

func DebugAfterOp(ps *stack.PushSwapData, opName string) {
	functionName := getCallerFunctionName()
	DebugLogAfterOperation(functionName, 0, ps, opName)
}
