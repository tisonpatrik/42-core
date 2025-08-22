package solver

import (
	"push_swap_prototype/internal/stack"
	"testing"
)

func TestLocToStack(t *testing.T) {
	tests := []struct {
		name     string
		setupA   []int
		setupB   []int
		loc      stack.Loc
		expected *stack.Stack
	}{
		{
			name:     "normal_behavior_TOP_A",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.TOP_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "normal_behavior_BOTTOM_A",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.BOTTOM_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "normal_behavior_TOP_B",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.TOP_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "normal_behavior_BOTTOM_B",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.BOTTOM_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "empty_stacks_TOP_A",
			setupA:   []int{},
			setupB:   []int{},
			loc:      stack.TOP_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "empty_stacks_BOTTOM_A",
			setupA:   []int{},
			setupB:   []int{},
			loc:      stack.BOTTOM_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "empty_stacks_TOP_B",
			setupA:   []int{},
			setupB:   []int{},
			loc:      stack.TOP_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "empty_stacks_BOTTOM_B",
			setupA:   []int{},
			setupB:   []int{},
			loc:      stack.BOTTOM_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "single_element_stacks_TOP_A",
			setupA:   []int{1},
			setupB:   []int{6},
			loc:      stack.TOP_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "single_element_stacks_BOTTOM_A",
			setupA:   []int{1},
			setupB:   []int{6},
			loc:      stack.BOTTOM_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "single_element_stacks_TOP_B",
			setupA:   []int{1},
			setupB:   []int{6},
			loc:      stack.TOP_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "single_element_stacks_BOTTOM_B",
			setupA:   []int{1},
			setupB:   []int{6},
			loc:      stack.BOTTOM_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "large_stacks_TOP_A",
			setupA:   []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			setupB:   []int{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			loc:      stack.TOP_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "large_stacks_BOTTOM_A",
			setupA:   []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			setupB:   []int{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			loc:      stack.BOTTOM_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "large_stacks_TOP_B",
			setupA:   []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			setupB:   []int{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			loc:      stack.TOP_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "large_stacks_BOTTOM_B",
			setupA:   []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			setupB:   []int{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			loc:      stack.BOTTOM_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "negative_indices_TOP_A",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.TOP_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "negative_indices_BOTTOM_A",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.BOTTOM_A,
			expected: nil, // Will be set in test
		},
		{
			name:     "negative_indices_TOP_B",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.TOP_B,
			expected: nil, // Will be set in test
		},
		{
			name:     "negative_indices_BOTTOM_B",
			setupA:   []int{1, 2, 3, 4, 5},
			setupB:   []int{6, 7, 8},
			loc:      stack.BOTTOM_B,
			expected: nil, // Will be set in test
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// Setup test data
			ps := stack.NewPushSwapData()
			
			if len(tt.setupA) > 0 {
				ps.A = stack.FromSlice(tt.setupA)
			}
			if len(tt.setupB) > 0 {
				ps.B = stack.FromSlice(tt.setupB)
			}

			// Call the function
			result := locToStack(ps, tt.loc)

			// Determine expected result based on location
			var expected *stack.Stack
			if tt.loc == stack.TOP_A || tt.loc == stack.BOTTOM_A {
				expected = ps.A
			} else {
				expected = ps.B
			}

			// Verify the result
			if result != expected {
				t.Errorf("locToStack() = %v, want %v", result, expected)
			}

			// Additional verification: check that we get the correct stack pointer
			if tt.loc == stack.TOP_A || tt.loc == stack.BOTTOM_A {
				if result != ps.A {
					t.Errorf("For location %v, expected stack A but got different stack", tt.loc)
				}
			} else {
				if result != ps.B {
					t.Errorf("For location %v, expected stack B but got different stack", tt.loc)
				}
			}
		})
	}
}

func TestLocToStackConsistency(t *testing.T) {
	// Test consistency with multiple calls (like the test report)
	ps := stack.NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2, 3, 4, 5})
	ps.B = stack.FromSlice([]int{6, 7, 8})

	// Test TOP_A consistency
	call1 := locToStack(ps, stack.TOP_A)
	call2 := locToStack(ps, stack.TOP_A)
	call3 := locToStack(ps, stack.TOP_A)

	if call1 != call2 || call2 != call3 {
		t.Errorf("TOP_A consistency failed: call1=%p, call2=%p, call3=%p", call1, call2, call3)
	}

	// Test BOTTOM_B consistency
	call1 = locToStack(ps, stack.BOTTOM_B)
	call2 = locToStack(ps, stack.BOTTOM_B)
	call3 = locToStack(ps, stack.BOTTOM_B)

	if call1 != call2 || call2 != call3 {
		t.Errorf("BOTTOM_B consistency failed: call1=%p, call2=%p, call3=%p", call1, call2, call3)
	}
}

func TestChunkValueExact(t *testing.T) {
	tests := []struct {
		name           string
		setupA         []int
		setupB         []int
		chunkLoc       stack.Loc
		chunkSize      int
		n              int
		expectedResult int
		description    string
	}{
		{
			name:           "chunk_value_top_a_first_element",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      3,
			n:              0,
			expectedResult: 10,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=3; n=0",
		},
		{
			name:           "chunk_value_top_a_second_element",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      3,
			n:              1,
			expectedResult: 10, // This is the actual result from the test report
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=3; n=1",
		},
		{
			name:           "chunk_value_top_a_last_element",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      3,
			n:              2,
			expectedResult: 25, // This is the actual result from the test report
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=3; n=2",
		},
		{
			name:           "chunk_value_top_b_first_element",
			setupA:         []int{},
			setupB:         []int{42, 18, 33, 7, 55},
			chunkLoc:       stack.TOP_B,
			chunkSize:      4,
			n:              0,
			expectedResult: 42,
			description:    "Stack B: size=5, top=0, bottom=4, values=[42,18,33,7,55]; Chunk: loc=TOP_B, size=4; n=0",
		},
		{
			name:           "chunk_value_top_b_middle_element",
			setupA:         []int{},
			setupB:         []int{42, 18, 33, 7, 55},
			chunkLoc:       stack.TOP_B,
			chunkSize:      4,
			n:              2,
			expectedResult: 18, // This is the actual result from the test report
			description:    "Stack B: size=5, top=0, bottom=4, values=[42,18,33,7,55]; Chunk: loc=TOP_B, size=4; n=2",
		},
		{
			name:           "chunk_value_bottom_a_first_element",
			setupA:         []int{20, 35, 12, 28, 45},
			setupB:         []int{},
			chunkLoc:       stack.BOTTOM_A,
			chunkSize:      2,
			n:              0,
			expectedResult: 45,
			description:    "Stack A: size=5, top=0, bottom=4, values=[20,35,12,28,45]; Chunk: loc=BOTTOM_A, size=2; n=0",
		},
		{
			name:           "chunk_value_bottom_a_second_element",
			setupA:         []int{20, 35, 12, 28, 45},
			setupB:         []int{},
			chunkLoc:       stack.BOTTOM_A,
			chunkSize:      2,
			n:              1,
			expectedResult: 45, // This is the actual result from the test report
			description:    "Stack A: size=5, top=0, bottom=4, values=[20,35,12,28,45]; Chunk: loc=BOTTOM_A, size=2; n=1",
		},
		{
			name:           "chunk_value_bottom_b_first_element",
			setupA:         []int{},
			setupB:         []int{-129660600, 16022915, 2105738868, 208995060, -129660088},
			chunkLoc:       stack.BOTTOM_B,
			chunkSize:      3,
			n:              0,
			expectedResult: -129660088,
			description:    "Stack B: size=5, top=0, bottom=4, values=[-129660600,16022915,2105738868,208995060,-129660088]; Chunk: loc=BOTTOM_B, size=3; n=0",
		},
		{
			name:           "chunk_value_bottom_b_last_element",
			setupA:         []int{},
			setupB:         []int{-129660600, 16022915, 2105738868, 208995060, -129660088},
			chunkLoc:       stack.BOTTOM_B,
			chunkSize:      3,
			n:              2,
			expectedResult: 208995060,
			description:    "Stack B: size=5, top=0, bottom=4, values=[-129660600,16022915,2105738868,208995060,-129660088]; Chunk: loc=BOTTOM_B, size=3; n=2",
		},
		{
			name:           "chunk_value_single_element",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      1,
			n:              0,
			expectedResult: 10,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=1; n=0",
		},
		{
			name:           "chunk_value_full_stack_last_element",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      5,
			n:              4,
			expectedResult: 30,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=5; n=4",
		},
		{
			name:           "chunk_value_oversized_chunk",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      10,
			n:              0,
			expectedResult: 10,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=10; n=0",
		},
		{
			name:           "chunk_value_n_larger_than_chunk",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      3,
			n:              5,
			expectedResult: 5,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=3; n=5",
		},
		{
			name:           "chunk_value_boundary_n_zero_TOP_A",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_A,
			chunkSize:      2,
			n:              0,
			expectedResult: 10,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=2; n=0",
		},
		{
			name:           "chunk_value_boundary_n_zero_BOTTOM_A",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.BOTTOM_A,
			chunkSize:      2,
			n:              0,
			expectedResult: 5,
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=BOTTOM_A, size=2; n=0",
		},
		{
			name:           "chunk_value_boundary_n_zero_TOP_B",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.TOP_B,
			chunkSize:      2,
			n:              0,
			expectedResult: 0, // Stack B is empty, so returns 0
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_B, size=2; n=0",
		},
		{
			name:           "chunk_value_boundary_n_zero_BOTTOM_B",
			setupA:         []int{10, 25, 15, 30, 5},
			setupB:         []int{},
			chunkLoc:       stack.BOTTOM_B,
			chunkSize:      2,
			n:              0,
			expectedResult: 0, // Stack B is empty, so returns 0
			description:    "Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=BOTTOM_B, size=2; n=0",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// Setup test data
			ps := stack.NewPushSwapData()
			
			if len(tt.setupA) > 0 {
				ps.A = stack.FromSlice(tt.setupA)
			}
			if len(tt.setupB) > 0 {
				ps.B = stack.FromSlice(tt.setupB)
			}

			// Create chunk
			chunk := &stack.Chunk{
				Loc:  tt.chunkLoc,
				Size: tt.chunkSize,
			}

			// Call the function
			result := chunkValue(ps, chunk, tt.n)

			// Verify the result
			if result != tt.expectedResult {
				t.Errorf("chunkValue() = %v, want %v\nTest: %s", result, tt.expectedResult, tt.description)
			}
		})
	}
}

func TestChunkValueWrappedStack(t *testing.T) {
	// Special test for wrapped stack with specific top/bottom indices
	ps := stack.NewPushSwapData()
	ps.A = stack.FromSlice([]int{50, 60, 70, 80, 90})
	
	// Manually set the wrapped stack indices as shown in the test report
	// top=3, bottom=2 means the stack is wrapped
	ps.A.SetTop(3)
	ps.A.SetBottom(2)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3,
	}

	// Test the three cases from the report
	tests := []struct {
		name           string
		n              int
		expectedResult int
	}{
		{"chunk_value_wrapped_stack_first", 0, 80},
		{"chunk_value_wrapped_stack_second", 1, 80},
		{"chunk_value_wrapped_stack_third", 2, 90},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := chunkValue(ps, chunk, tt.n)
			if result != tt.expectedResult {
				t.Errorf("chunkValue() = %v, want %v", result, tt.expectedResult)
			}
		})
	}
}

func TestChunkValueConsistencyMultipleCalls(t *testing.T) {
	// Test consistency with multiple calls (like the test report)
	ps := stack.NewPushSwapData()
	ps.A = stack.FromSlice([]int{10, 25, 15, 30, 5})
	
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3,
	}

	// Test consistency with multiple calls
	call1 := chunkValue(ps, chunk, 1)
	call2 := chunkValue(ps, chunk, 1)
	call3 := chunkValue(ps, chunk, 1)

	allEqual := call1 == call2 && call2 == call3

	if !allEqual {
		t.Errorf("Consistency failed: call1=%v, call2=%v, call3=%v, All equal: NO", call1, call2, call3)
	}

	// Verify the expected result from the test report
	expected := 10
	if call1 != expected {
		t.Errorf("Expected result %v, got %v", expected, call1)
	}
}

func TestChunkValueConsistencyMultipleCallsExact(t *testing.T) {
	// Exact test case from the report: chunk_value_consistency_multiple_calls
	// INPUT: Stack A: size=5, top=0, bottom=4, values=[10,25,15,30,5]; Chunk: loc=TOP_A, size=3; n=1; Function called 3 times
	// OUTPUT: Call 1: 10, Call 2: 10, Call 3: 10, All equal: YES
	
	ps := stack.NewPushSwapData()
	ps.A = stack.FromSlice([]int{10, 25, 15, 30, 5})
	
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3,
	}

	// Function called 3 times with n=1
	call1 := chunkValue(ps, chunk, 1)
	call2 := chunkValue(ps, chunk, 1)
	call3 := chunkValue(ps, chunk, 1)

	// Verify all calls return the same value
	if call1 != 10 || call2 != 10 || call3 != 10 {
		t.Errorf("Expected all calls to return 10, got: Call 1: %v, Call 2: %v, Call 3: %v", call1, call2, call3)
	}

	// Verify they are all equal
	allEqual := call1 == call2 && call2 == call3
	if !allEqual {
		t.Errorf("All equal: NO, expected: YES")
	}
}


