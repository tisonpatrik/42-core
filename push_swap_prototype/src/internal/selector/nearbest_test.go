package selector

import (
	"testing"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// TestPickNearBest_FirstIteration tests PickNearBest with the exact data from PickNearBest1.txt log line 1
func TestPickNearBest_FirstIteration(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt
	stackA := []int{14, 18, 19, 42, 74, 86, 90, 142, 144, 166, 169, 182, 186, 207, 216, 227, 253, 257, 270, 305, 313, 321, 325, 337, 347, 355, 358, 361, 404, 421, 435, 440, 443, 445, 450, 467, 470, 478, 487, 491}
	stackB := []int{284, 451, 480, 381, 380, 426, 462, 448, 345, 327, 394, 368, 486, 308, 473, 377, 431, 328, 293, 441, 382, 432, 373, 412, 457, 436, 403, 342, 317, 367, 401, 366, 356, 267, 297, 405, 269, 485, 496, 319, 326, 309, 260, 335, 362, 266, 307, 353, 261, 254, 334, 425, 333, 489, 336, 409, 348, 265, 329, 350, 374, 494, 447, 389, 399, 460, 433, 263, 359, 271, 315, 268, 411, 477, 279, 492, 452, 338, 384, 277, 331, 281, 256, 259, 300, 332, 493, 282, 296, 437, 304, 310, 287, 323, 302, 264, 455, 311, 352, 286, 369, 466, 320, 427, 375, 396, 499, 459, 402, 439, 357, 474, 416, 295, 360, 372, 424, 276, 469, 482, 468, 429, 275, 285, 370, 476, 252, 371, 490, 318, 390, 349, 391, 408, 454, 471, 420, 344, 400, 472, 453, 322, 446, 306, 407, 324, 272, 498, 340, 341, 289, 314, 464, 385, 414, 479, 291, 465, 483, 351, 316, 294, 365, 278, 475, 406, 434, 280, 458, 301, 339, 312, 392, 290, 444, 364, 330, 274, 463, 378, 497, 461, 413, 273, 262, 363, 346, 288, 481, 388, 393, 354, 255, 376, 418, 423, 417, 422, 398, 428, 258, 456, 419, 410, 415, 343, 387, 442, 484, 292, 298, 438, 488, 430, 303, 299, 397, 495, 383, 379, 395, 449, 386, 283, 218, 157, 151, 97, 54, 32, 92, 73, 34, 226, 174, 11, 220, 246, 43, 111, 15, 93, 245, 243, 110, 123, 251, 249, 31, 156, 215, 202, 225, 250, 119, 239, 154, 203, 83, 63, 237, 20, 188, 132, 98, 62, 69, 178, 195, 134, 131, 65, 148, 122, 163, 217, 29, 234, 23, 162, 117, 91, 71, 106, 36, 84, 107, 37, 87, 139, 27, 116, 77, 199, 130, 189, 76, 95, 89, 180, 13, 165, 104, 113, 52, 2, 153, 197, 112, 56, 66, 78, 26, 198, 103, 1, 200, 185, 35, 8, 247, 121, 28, 210, 221, 129, 204, 179, 125, 81, 38, 236, 205, 4, 46, 17, 85, 167, 184, 192, 53, 6, 138, 146, 120, 41, 99, 241, 147, 72, 114, 21, 94, 159, 109, 140, 7, 235, 136, 40, 79, 196, 238, 30, 190, 150, 208, 128, 193, 161, 181, 100, 51, 213, 233, 152, 16, 145, 173, 175, 187, 171, 47, 219, 118, 244, 232, 48, 59, 101, 209, 57, 102, 49, 0, 39, 137, 224, 105, 9, 248, 172, 240, 168, 45, 158, 222, 60, 12, 67, 164, 24, 50, 80, 194, 124, 3, 143, 55, 155, 177, 214, 201, 58, 191, 127, 88, 10, 133, 22, 135, 229, 33, 25, 75, 228, 160, 206, 176, 126, 64, 183, 68, 231, 5, 149, 211, 242, 141, 223, 115, 82, 212, 61, 170, 230, 44, 108, 96, 70}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 2, ToIndex: 38, CostA: -2, CostB: 2, Total: 4}

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

// TestPickNearBest_PickNearBest1Data tests PickNearBest with the exact data from PickNearBest1.txt log line 1
func TestPickNearBest_PickNearBest1Data(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt
	stackA := []int{20, 52, 68, 73, 75, 105, 107, 126, 133, 136, 144, 150, 154, 165, 172, 174, 189, 206, 234, 237, 260, 273, 287, 294, 298, 305, 321, 331, 354, 356, 360, 377, 386, 420, 442, 449, 486, 488}
	stackB := []int{446, 370, 425, 347, 480, 409, 271, 374, 426, 411, 344, 308, 445, 283, 476, 272, 251, 268, 396, 358, 252, 285, 329, 413, 423, 301, 490, 325, 339, 474, 459, 276, 319, 470, 340, 357, 284, 261, 415, 481, 314, 391, 262, 472, 366, 492, 483, 478, 477, 318, 274, 263, 335, 296, 270, 484, 463, 258, 267, 491, 390, 389, 424, 380, 401, 441, 398, 300, 406, 364, 385, 363, 439, 316, 475, 293, 315, 352, 428, 432, 264, 399, 498, 355, 265, 444, 418, 371, 282, 496, 482, 309, 455, 376, 467, 291, 403, 289, 438, 427, 400, 495, 312, 394, 397, 435, 302, 443, 456, 384, 419, 465, 359, 430, 254, 337, 326, 279, 451, 286, 457, 387, 433, 454, 452, 255, 466, 311, 342, 290, 368, 367, 479, 485, 412, 275, 320, 392, 494, 348, 250, 373, 375, 487, 468, 292, 436, 448, 410, 408, 280, 429, 338, 369, 464, 379, 393, 303, 416, 431, 383, 310, 253, 334, 351, 417, 422, 497, 493, 402, 471, 362, 323, 421, 469, 489, 453, 365, 353, 462, 330, 461, 381, 297, 333, 256, 307, 332, 378, 328, 440, 437, 306, 343, 458, 499, 313, 382, 295, 388, 404, 299, 361, 277, 473, 317, 327, 395, 434, 405, 304, 350, 450, 259, 241, 257, 281, 244, 324, 322, 336, 407, 278, 447, 288, 460, 372, 346, 345, 266, 349, 269, 414, 341, 175, 97, 210, 219, 184, 243, 19, 31, 94, 26, 115, 138, 190, 142, 187, 236, 228, 42, 183, 129, 181, 51, 179, 132, 188, 235, 131, 199, 47, 195, 22, 57, 1, 40, 119, 38, 33, 4, 207, 211, 182, 197, 164, 217, 163, 221, 108, 35, 32, 196, 6, 70, 65, 249, 13, 91, 16, 60, 111, 200, 203, 161, 173, 58, 84, 170, 204, 21, 213, 224, 110, 53, 72, 12, 151, 17, 130, 102, 140, 88, 128, 64, 201, 147, 248, 125, 9, 83, 59, 145, 155, 113, 46, 109, 44, 63, 137, 15, 167, 242, 79, 230, 98, 74, 239, 238, 28, 157, 85, 0, 120, 143, 176, 62, 118, 139, 169, 159, 202, 122, 55, 89, 123, 95, 77, 86, 25, 124, 166, 246, 101, 148, 225, 23, 80, 218, 24, 153, 82, 191, 177, 231, 103, 30, 149, 87, 222, 232, 247, 81, 114, 223, 14, 245, 192, 43, 104, 208, 156, 93, 5, 198, 54, 49, 116, 67, 158, 205, 69, 7, 121, 220, 127, 215, 11, 48, 117, 214, 160, 233, 194, 76, 100, 186, 71, 162, 212, 3, 66, 209, 96, 178, 99, 229, 146, 152, 8, 41, 36, 10, 185, 227, 39, 18, 134, 34, 50, 106, 45, 2, 92, 141, 226, 61, 78, 90, 112, 27, 180, 193, 56, 135, 240, 168, 29, 171, 216, 37}
	maxCandidates := 30
	expectedPosition := Position{FromIndex: 461, ToIndex: 1, CostA: 1, CostB: -1, Total: 2}

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

func TestPickNearBest_PickNearBest2Data(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt
	stackA := []int{70, 85, 86, 90, 92, 106, 132, 173, 185, 192, 214, 215, 220, 226, 237, 242, 250, 263, 273, 293, 314, 329, 353, 364, 377, 385, 386, 416, 419, 446, 468, 497, 499}
	stackB := []int{427, 347, 346, 344, 370, 259, 408, 391, 390, 326, 389, 300, 498, 292, 414, 290, 480, 487, 378, 334, 409, 433, 462, 444, 281, 297, 256, 393, 345, 340, 394, 467, 348, 315, 484, 322, 469, 474, 248, 369, 489, 286, 298, 359, 379, 490, 441, 304, 351, 374, 448, 283, 317, 426, 331, 276, 258, 342, 253, 254, 343, 387, 296, 475, 267, 324, 482, 316, 336, 447, 455, 431, 457, 445, 430, 288, 438, 449, 420, 295, 472, 454, 260, 407, 421, 440, 312, 495, 461, 442, 305, 251, 335, 352, 464, 341, 399, 373, 363, 413, 425, 410, 396, 398, 380, 417, 423, 291, 299, 494, 405, 301, 384, 491, 424, 429, 401, 313, 479, 483, 488, 354, 358, 470, 473, 388, 406, 422, 456, 402, 481, 303, 321, 437, 252, 477, 404, 306, 485, 349, 460, 275, 279, 289, 381, 338, 274, 320, 412, 330, 478, 365, 318, 372, 307, 308, 350, 271, 261, 458, 395, 255, 451, 432, 339, 453, 415, 411, 466, 436, 418, 465, 337, 282, 268, 459, 310, 435, 383, 376, 434, 428, 328, 264, 269, 284, 463, 356, 280, 361, 471, 450, 382, 249, 360, 392, 486, 262, 362, 332, 452, 403, 325, 257, 368, 272, 476, 355, 265, 492, 287, 367, 397, 309, 323, 400, 371, 266, 270, 333, 278, 375, 302, 319, 493, 443, 366, 439, 327, 311, 496, 357, 285, 108, 153, 152, 213, 100, 205, 201, 217, 294, 235, 178, 277, 216, 28, 196, 183, 204, 17, 58, 145, 42, 189, 133, 93, 195, 55, 39, 54, 12, 233, 118, 150, 1, 143, 24, 186, 45, 175, 187, 56, 194, 246, 241, 240, 87, 71, 8, 59, 134, 32, 7, 95, 122, 115, 11, 232, 224, 176, 77, 75, 21, 48, 137, 209, 207, 84, 157, 23, 172, 40, 159, 33, 113, 177, 117, 81, 30, 244, 221, 20, 80, 65, 138, 50, 191, 169, 239, 199, 37, 110, 72, 107, 236, 13, 174, 230, 27, 229, 167, 193, 123, 98, 180, 31, 2, 99, 114, 102, 60, 140, 154, 197, 78, 222, 126, 67, 9, 53, 144, 89, 206, 73, 136, 147, 104, 142, 148, 141, 129, 182, 125, 41, 105, 200, 14, 156, 19, 190, 66, 162, 227, 61, 151, 124, 83, 74, 131, 82, 135, 155, 121, 181, 103, 170, 88, 36, 158, 69, 44, 225, 165, 68, 119, 166, 160, 243, 34, 223, 51, 146, 210, 76, 35, 38, 164, 234, 91, 130, 202, 62, 139, 198, 6, 127, 47, 0, 25, 149, 116, 18, 94, 112, 228, 179, 111, 163, 43, 211, 63, 3, 64, 4, 120, 203, 22, 29, 15, 247, 16, 26, 188, 219, 96, 184, 5, 218, 101, 52, 168, 10, 208, 79, 128, 238, 161, 97, 109, 245, 46, 57, 171, 49, 212, 231}
	maxCandidates := 30

	expectedPosition := Position{FromIndex: 464, ToIndex: 0, CostA: 0, CostB: -3, Total: 3}

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
