package selector

import (
	"testing"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// TestSnapshotStack_Iteration0 tests SnapshotStack with data from PickNearBest1.txt iteration 0
func TestSnapshotStack_Iteration0(t *testing.T) {
	// Arrange - Set up the test data from PickNearBest1.txt iteration 0
	stackA := []int{1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441, 468, 487, 492, 494}
	stackB := []int{367, 380, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61}

	// Create SortingState with the test data
	ps := &ops.SortingState{
		A: stack.InitStack(),
		B: stack.InitStack(),
	}

	// Populate stack A
	stack.FillStack(ps.A, stackA)

	// Populate stack B
	stack.FillStack(ps.B, stackB)

	// Act - Call SnapshotStack on both stacks
	snapshotA := SnapshotStack(ps.A)
	snapshotB := SnapshotStack(ps.B)

	// Assert - Verify basic properties of the results
	if snapshotA == nil {
		t.Error("Expected snapshotA to be non-nil")
		return
	}

	if snapshotB == nil {
		t.Error("Expected snapshotB to be non-nil")
		return
	}

	// Verify we have the expected number of elements
	if len(snapshotA) != len(stackA) {
		t.Errorf("Expected snapshotA length %d, got %d", len(stackA), len(snapshotA))
	}

	if len(snapshotB) != len(stackB) {
		t.Errorf("Expected snapshotB length %d, got %d", len(stackB), len(snapshotB))
	}

	// Verify the elements match the original data
	for i, val := range snapshotA {
		if val != stackA[i] {
			t.Errorf("snapshotA[%d]: expected %d, got %d", i, stackA[i], val)
		}
	}

	for i, val := range snapshotB {
		if val != stackB[i] {
			t.Errorf("snapshotB[%d]: expected %d, got %d", i, stackB[i], val)
		}
	}

	// Print first few elements for inspection
	t.Logf("First 5 elements of snapshotA: %v", snapshotA[:5])
	t.Logf("First 5 elements of snapshotB: %v", snapshotB[:5])
	t.Logf("Last 5 elements of snapshotA: %v", snapshotA[len(snapshotA)-5:])
	t.Logf("Last 5 elements of snapshotB: %v", snapshotB[len(snapshotB)-5:])
}

// TestSnapshotStack_EmptyStack tests SnapshotStack with an empty stack
func TestSnapshotStack_EmptyStack(t *testing.T) {
	// Arrange - Create an empty stack
	emptyStack := stack.InitStack()

	// Act - Call SnapshotStack on empty stack
	snapshot := SnapshotStack(emptyStack)

	// Assert - Verify the result
	if snapshot == nil {
		t.Error("Expected snapshot to be non-nil")
		return
	}

	if len(snapshot) != 0 {
		t.Errorf("Expected empty snapshot, got length %d", len(snapshot))
	}
}

// TestSnapshotStack_SingleElement tests SnapshotStack with a single element
func TestSnapshotStack_SingleElement(t *testing.T) {
	// Arrange - Create a stack with one element
	singleStack := stack.InitStack()
	stack.FillStack(singleStack, []int{42})

	// Act - Call SnapshotStack on single element stack
	snapshot := SnapshotStack(singleStack)

	// Assert - Verify the result
	if snapshot == nil {
		t.Error("Expected snapshot to be non-nil")
		return
	}

	if len(snapshot) != 1 {
		t.Errorf("Expected snapshot length 1, got %d", len(snapshot))
	}

	if snapshot[0] != 42 {
		t.Errorf("Expected snapshot[0] to be 42, got %d", snapshot[0])
	}
}
