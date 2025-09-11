#include "test_main.h"
#include "../include/solver.h"

// Helper function to create test data from arrays
static void create_test_data_from_arrays(t_sorting_state *state, int *stack_a, int stack_a_size, int *stack_b, int stack_b_size)
{
    // Clear existing stacks
    clear_stack(state->a);
    clear_stack(state->b);
    
    // Fill stack A
    for (int i = 0; i < stack_a_size; i++) {
        t_node *node = create_node(stack_a[i]);
        push_to_stack(state->a, node);
    }
    
    // Fill stack B
    for (int i = 0; i < stack_b_size; i++) {
        t_node *node = create_node(stack_b[i]);
        push_to_stack(state->b, node);
    }
}

// Helper function to get stack size
static int get_stack_size(t_stack *stack)
{
    return get_size(stack);
}

// Helper function to create position
static t_position create_position(int from_index, int to_index, int cost_a, int cost_b, int total)
{
    t_position pos = {0};
    pos.from_index = from_index;
    pos.to_index = to_index;
    pos.cost_a = cost_a;
    pos.cost_b = cost_b;
    pos.total = total;
    return pos;
}

// TestApplyCombined_Iteration0 tests ApplyCombined with data from PickNearBest1.txt iteration 0
void test_apply_combined_iteration0(void)
{
    printf("Running TestApplyCombined_Iteration0... ");
    
    // Arrange - Set up the test data from PickNearBest1.txt iteration 0
    int stackA[] = {1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441, 468, 487, 492, 494};
    int stackB[] = {367, 380, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61};
    
    int stackA_size = sizeof(stackA) / sizeof(stackA[0]);
    int stackB_size = sizeof(stackB) / sizeof(stackB[0]);
    
    t_position position = create_position(2, 39, -4, 2, 6);
    bool pushToB = true;
    
    // Create SortingState with the test data
    t_sorting_state *ps = malloc(sizeof(t_sorting_state));
    if (!ps) {
        printf("❌ Failed to allocate memory for sorting state\n");
        return;
    }
    ps->a = create_stack();
    ps->b = create_stack();
    ps->operations = NULL;
    if (!ps->a || !ps->b) {
        printf("❌ Failed to create stacks\n");
        if (ps->a) free(ps->a);
        if (ps->b) free(ps->b);
        free(ps);
        return;
    }
    
    // Populate stacks with test data
    create_test_data_from_arrays(ps, stackA, stackA_size, stackB, stackB_size);
    
    // Act - Call ApplyCombined with the test data
    apply_combined(ps, position, pushToB);
    
    // Assert - Verify the result
    // Expected lengths from Go test: PickNearBest1.txt iteration 0
    int expectedStackASize = 42;
    int expectedStackBSize = 458;
    
    int finalStackASize = get_stack_size(ps->a);
    int finalStackBSize = get_stack_size(ps->b);
    
    bool test_passed = true;
    if (finalStackASize != expectedStackASize) {
        printf("❌ Stack A length: expected %d, got %d\n", expectedStackASize, finalStackASize);
        test_passed = false;
    }
    if (finalStackBSize != expectedStackBSize) {
        printf("❌ Stack B length: expected %d, got %d\n", expectedStackBSize, finalStackBSize);
        test_passed = false;
    }
    
    if (test_passed) {
        printf("✅ passed\n");
    }
    
    // Cleanup
    free_sorting_state(ps);
}

// TestApplyCombined_Iteration1 tests ApplyCombined with data from PickNearBest1.txt iteration 1
void test_apply_combined_iteration1(void)
{
    printf("Running TestApplyCombined_Iteration1... ");
    
    // Arrange - Set up the test data from PickNearBest1.txt iteration 1
    int stackA[] = {487, 492, 494, 1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441};
    int stackB[] = {468, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380};
    
    int stackA_size = sizeof(stackA) / sizeof(stackA[0]);
    int stackB_size = sizeof(stackB) / sizeof(stackB[0]);
    
    t_position position = create_position(0, 0, 0, 0, 0);
    bool pushToB = true;
    
    // Create SortingState with the test data
    t_sorting_state *ps = malloc(sizeof(t_sorting_state));
    if (!ps) {
        printf("❌ Failed to allocate memory for sorting state\n");
        return;
    }
    ps->a = create_stack();
    ps->b = create_stack();
    ps->operations = NULL;
    if (!ps->a || !ps->b) {
        printf("❌ Failed to create stacks\n");
        if (ps->a) free(ps->a);
        if (ps->b) free(ps->b);
        free(ps);
        return;
    }
    
    // Populate stacks with test data
    create_test_data_from_arrays(ps, stackA, stackA_size, stackB, stackB_size);
    
    // Act - Call ApplyCombined with the test data
    apply_combined(ps, position, pushToB);
    
    // Assert - Verify the result
    // Expected lengths from Go test: PickNearBest1.txt iteration 1
    int expectedStackASize = 41;
    int expectedStackBSize = 459;
    
    int finalStackASize = get_stack_size(ps->a);
    int finalStackBSize = get_stack_size(ps->b);
    
    bool test_passed = true;
    if (finalStackASize != expectedStackASize) {
        printf("❌ Stack A length: expected %d, got %d\n", expectedStackASize, finalStackASize);
        test_passed = false;
    }
    if (finalStackBSize != expectedStackBSize) {
        printf("❌ Stack B length: expected %d, got %d\n", expectedStackBSize, finalStackBSize);
        test_passed = false;
    }
    
    if (test_passed) {
        printf("✅ passed\n");
    }
    
    // Cleanup
    free_sorting_state(ps);
}

// TestApplyCombined_Iteration2 tests ApplyCombined with data from PickNearBest1.txt iteration 2
void test_apply_combined_iteration2(void)
{
    printf("Running TestApplyCombined_Iteration2... ");
    
    // Arrange - Set up the test data from PickNearBest1.txt iteration 2
    int stackA[] = {468, 487, 492, 494, 1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441};
    int stackB[] = {464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61, 367, 380};
    
    int stackA_size = sizeof(stackA) / sizeof(stackA[0]);
    int stackB_size = sizeof(stackB) / sizeof(stackB[0]);
    
    t_position position = create_position(0, 0, 0, 0, 0);
    bool pushToB = true;
    
    // Create SortingState with the test data
    t_sorting_state *ps = malloc(sizeof(t_sorting_state));
    if (!ps) {
        printf("❌ Failed to allocate memory for sorting state\n");
        return;
    }
    ps->a = create_stack();
    ps->b = create_stack();
    ps->operations = NULL;
    if (!ps->a || !ps->b) {
        printf("❌ Failed to create stacks\n");
        if (ps->a) free(ps->a);
        if (ps->b) free(ps->b);
        free(ps);
        return;
    }
    
    // Populate stacks with test data
    create_test_data_from_arrays(ps, stackA, stackA_size, stackB, stackB_size);
    
    // Act - Call ApplyCombined with the test data
    apply_combined(ps, position, pushToB);
    
    // Assert - Verify the result
    // Expected lengths from Go test: PickNearBest1.txt iteration 2
    int expectedStackASize = 42;
    int expectedStackBSize = 458;
    
    int finalStackASize = get_stack_size(ps->a);
    int finalStackBSize = get_stack_size(ps->b);
    
    bool test_passed = true;
    if (finalStackASize != expectedStackASize) {
        printf("❌ Stack A length: expected %d, got %d\n", expectedStackASize, finalStackASize);
        test_passed = false;
    }
    if (finalStackBSize != expectedStackBSize) {
        printf("❌ Stack B length: expected %d, got %d\n", expectedStackBSize, finalStackBSize);
        test_passed = false;
    }
    
    if (test_passed) {
        printf("✅ passed\n");
    }

    // Cleanup
    free_sorting_state(ps);
}

// TestApplyCombined_PushToA tests ApplyCombined with pushToB=false (push from B to A)
void test_apply_combined_push_to_a(void)
{
    printf("Running TestApplyCombined_PushToA... ");
    
    // Arrange - Set up test data
    int stackA[] = {1, 13, 20, 26, 31, 36, 44, 66, 76, 94};
    int stackB[] = {367, 380, 464, 466, 355, 320, 278, 306, 407, 255};
    
    int stackA_size = sizeof(stackA) / sizeof(stackA[0]);
    int stackB_size = sizeof(stackB) / sizeof(stackB[0]);
    
    t_position position = create_position(2, 5, 3, -2, 5);
    bool pushToB = false; // Push from B to A
    
    // Create SortingState with the test data
    t_sorting_state *ps = malloc(sizeof(t_sorting_state));
    if (!ps) {
        printf("❌ Failed to allocate memory for sorting state\n");
        return;
    }
    ps->a = create_stack();
    ps->b = create_stack();
    ps->operations = NULL;
    if (!ps->a || !ps->b) {
        printf("❌ Failed to create stacks\n");
        if (ps->a) free(ps->a);
        if (ps->b) free(ps->b);
        free(ps);
        return;
    }
    
    // Populate stacks with test data
    create_test_data_from_arrays(ps, stackA, stackA_size, stackB, stackB_size);
    
    // Act - Call ApplyCombined with the test data
    apply_combined(ps, position, pushToB);
    
    // Assert - Verify the result
    // Expected lengths from Go test: PushToA test
    int expectedStackASize = 11;
    int expectedStackBSize = 9;
    
    int finalStackASize = get_stack_size(ps->a);
    int finalStackBSize = get_stack_size(ps->b);
    
    bool test_passed = true;
    if (finalStackASize != expectedStackASize) {
        printf("❌ Stack A length: expected %d, got %d\n", expectedStackASize, finalStackASize);
        test_passed = false;
    }
    if (finalStackBSize != expectedStackBSize) {
        printf("❌ Stack B length: expected %d, got %d\n", expectedStackBSize, finalStackBSize);
        test_passed = false;
    }
    
    if (test_passed) {
        printf("✅ passed\n");
    }

    // Cleanup
    free_sorting_state(ps);
}