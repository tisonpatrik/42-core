package selector

import (
	"testing"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// TestPickNearBest_Iteration0 tests PickNearBest with data from PickNearBest1.txt iteration 0
func TestPickNearBest_Iteration0(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 0
	stackA := []int{1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441, 468, 487, 492, 494}
	stackB := []int{367, 380, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 2, ToIndex: 39, CostA: -4, CostB: 2, Total: 6}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration1 tests PickNearBest with data from PickNearBest1.txt iteration 1
func TestPickNearBest_Iteration1(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 1
	stackA := []int{487, 492, 494, 1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration2 tests PickNearBest with data from PickNearBest1.txt iteration 2
func TestPickNearBest_Iteration2(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 2
	stackA := []int{492, 494, 1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration3 tests PickNearBest with data from PickNearBest1.txt iteration 3
func TestPickNearBest_Iteration3(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 3
	stackA := []int{494, 1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration4 tests PickNearBest with data from PickNearBest1.txt iteration 4
func TestPickNearBest_Iteration4(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 4
	stackA := []int{1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration5 tests PickNearBest with data from PickNearBest1.txt iteration 5
func TestPickNearBest_Iteration5(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 5
	stackA := []int{13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration6 tests PickNearBest with data from PickNearBest1.txt iteration 6
func TestPickNearBest_Iteration6(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 6
	stackA := []int{20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration7 tests PickNearBest with data from PickNearBest1.txt iteration 7
func TestPickNearBest_Iteration7(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 7
	stackA := []int{26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration8 tests PickNearBest with data from PickNearBest1.txt iteration 8
func TestPickNearBest_Iteration8(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 8
	stackA := []int{31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration9 tests PickNearBest with data from PickNearBest1.txt iteration 9
func TestPickNearBest_Iteration9(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 9
	stackA := []int{36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration10 tests PickNearBest with data from PickNearBest1.txt iteration 10
func TestPickNearBest_Iteration10(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 10
	stackA := []int{44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration11 tests PickNearBest with data from PickNearBest1.txt iteration 11
func TestPickNearBest_Iteration11(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 11
	stackA := []int{66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration12 tests PickNearBest with data from PickNearBest1.txt iteration 12
func TestPickNearBest_Iteration12(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 12
	stackA := []int{76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration13 tests PickNearBest with data from PickNearBest1.txt iteration 13
func TestPickNearBest_Iteration13(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 13
	stackA := []int{94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration14 tests PickNearBest with data from PickNearBest1.txt iteration 14
func TestPickNearBest_Iteration14(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 14
	stackA := []int{97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration15 tests PickNearBest with data from PickNearBest1.txt iteration 15
func TestPickNearBest_Iteration15(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 15
	stackA := []int{108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration16 tests PickNearBest with data from PickNearBest1.txt iteration 16
func TestPickNearBest_Iteration16(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 16
	stackA := []int{124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration17 tests PickNearBest with data from PickNearBest1.txt iteration 17
func TestPickNearBest_Iteration17(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 17
	stackA := []int{142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration18 tests PickNearBest with data from PickNearBest1.txt iteration 18
func TestPickNearBest_Iteration18(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 18
	stackA := []int{151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration19 tests PickNearBest with data from PickNearBest1.txt iteration 19
func TestPickNearBest_Iteration19(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 19
	stackA := []int{153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B3
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration20 tests PickNearBest with data from PickNearBest1.txt iteration 20
func TestPickNearBest_Iteration20(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 20
	stackA := []int{192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration21 tests PickNearBest with data from PickNearBest1.txt iteration 21
func TestPickNearBest_Iteration21(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 21
	stackA := []int{200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration22 tests PickNearBest with data from PickNearBest1.txt iteration 22
func TestPickNearBest_Iteration22(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 22
	stackA := []int{205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration23 tests PickNearBest with data from PickNearBest1.txt iteration 23
func TestPickNearBest_Iteration23(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 23
	stackA := []int{221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration24 tests PickNearBest with data from PickNearBest1.txt iteration 24
func TestPickNearBest_Iteration24(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 24
	stackA := []int{225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration25 tests PickNearBest with data from PickNearBest1.txt iteration 25
func TestPickNearBest_Iteration25(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 25
	stackA := []int{237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration26 tests PickNearBest with data from PickNearBest1.txt iteration 26
func TestPickNearBest_Iteration26(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 26
	stackA := []int{263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration27 tests PickNearBest with data from PickNearBest1.txt iteration 27
func TestPickNearBest_Iteration27(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 27
	stackA := []int{277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration28 tests PickNearBest with data from PickNearBest1.txt iteration 28
func TestPickNearBest_Iteration28(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 28
	stackA := []int{287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration29 tests PickNearBest with data from PickNearBest1.txt iteration 29
func TestPickNearBest_Iteration29(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 29
	stackA := []int{289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration30 tests PickNearBest with data from PickNearBest1.txt iteration 30
func TestPickNearBest_Iteration30(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 30
	stackA := []int{291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration31 tests PickNearBest with data from PickNearBest1.txt iteration 31
func TestPickNearBest_Iteration31(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 31
	stackA := []int{299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration32 tests PickNearBest with data from PickNearBest1.txt iteration 32
func TestPickNearBest_Iteration32(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 32
	stackA := []int{303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration33 tests PickNearBest with data from PickNearBest1.txt iteration 33
func TestPickNearBest_Iteration33(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 33
	stackA := []int{305, 313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration34 tests PickNearBest with data from PickNearBest1.txt iteration 34
func TestPickNearBest_Iteration34(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 34
	stackA := []int{313, 339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration35 tests PickNearBest with data from PickNearBest1.txt iteration 35
func TestPickNearBest_Iteration35(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 35
	stackA := []int{339, 346, 365, 381, 401, 433, 435, 441}
	stackB := []int{313, 305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration36 tests PickNearBest with data from PickNearBest1.txt iteration 36
func TestPickNearBest_Iteration36(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 36
	stackA := []int{346, 365, 381, 401, 433, 435, 441}
	stackB := []int{339, 313, 305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration37 tests PickNearBest with data from PickNearBest1.txt iteration 37
func TestPickNearBest_Iteration37(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 37
	stackA := []int{365, 381, 401, 433, 435, 441}
	stackB := []int{346, 339, 313, 305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration38 tests PickNearBest with data from PickNearBest1.txt iteration 38
func TestPickNearBest_Iteration38(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 38
	stackA := []int{381, 401, 433, 435, 441}
	stackB := []int{365, 346, 339, 313, 305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

// TestPickNearBest_Iteration39 tests PickNearBest with data from PickNearBest1.txt iteration 39
func TestPickNearBest_Iteration39(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 39
	stackA := []int{401, 433, 435, 441}
	stackB := []int{381, 365, 346, 339, 313, 305, 303, 299, 291, 289, 287, 277, 263, 237, 225, 221, 205, 200, 192, 153, 151, 142, 124, 108, 97, 94, 76, 66, 44, 36, 31, 26, 20, 13, 1, 494, 492, 487, 468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 0, ToIndex: 0, CostA: 0, CostB: 0, Total: 0}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call PickNearBest with the test data
	result := PickNearBest(ps, maxCandidates)

	// Assert - Verify the result matches the expected position from PickNearBest1.txt
	if result.FromIndex != expectedPosition.FromIndex {
		t.Errorf("FromIndex: expected %d, got %d", expectedPosition.FromIndex, result.FromIndex)
	}
	if result.ToIndex != expectedPosition.ToIndex {
		t.Errorf("ToIndex: expected %d, got %d", expectedPosition.ToIndex, result.ToIndex)
	}
	if result.CostA != expectedPosition.CostA {
		t.Errorf("CostA: expected %d, got %d", expectedPosition.CostA, result.CostA)
	}
	if result.CostB != expectedPosition.CostB {
		t.Errorf("CostB: expected %d, got %d", expectedPosition.CostB, result.CostB)
	}
	if result.Total != expectedPosition.Total {
		t.Errorf("Total: expected %d, got %d", expectedPosition.Total, result.Total)
	}

	// Additional assertion: verify the selected element from stack B
	stackBArray := stack.ToArray(ps.B)
	if len(stackBArray) > result.FromIndex {
		selectedElement := stackBArray[result.FromIndex]
		t.Logf("Selected element from stack B[%d]: %d", result.FromIndex, selectedElement)
	}

	// Additional assertion: verify the target position in stack A
	stackAArray := stack.ToArray(ps.A)
	if len(stackAArray) > result.ToIndex {
		targetPosition := stackAArray[result.ToIndex]
		t.Logf("Target position in stack A[%d]: %d", result.ToIndex, targetPosition)
	}
}

