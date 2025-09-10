#include "test_main.h"
#include "../include/selector.h"

// TestSnapshotStack_Iteration0 tests SnapshotStack with data from PickNearBest1.txt iteration 0
void test_snapshot_stack_iteration0(void)
{
    printf("Testing SnapshotStack with iteration 0 data...\n");
    
    // Arrange - Set up the test data from PickNearBest1.txt iteration 0
    int stackA[] = {1, 13, 20, 26, 31, 36, 44, 66, 76, 94, 97, 108, 124, 142, 151, 153, 192, 200, 205, 221, 225, 237, 263, 277, 287, 289, 291, 299, 303, 305, 313, 339, 346, 365, 381, 401, 433, 435, 441, 468, 487, 492, 494};
    int stackB[] = {367, 380, 464, 466, 355, 320, 278, 306, 407, 255, 484, 347, 443, 483, 311, 348, 399, 414, 318, 252, 378, 377, 343, 274, 331, 374, 334, 324, 396, 300, 363, 394, 391, 264, 384, 354, 283, 292, 471, 412, 398, 256, 495, 473, 270, 282, 362, 436, 345, 304, 308, 485, 423, 332, 498, 301, 472, 273, 482, 385, 317, 439, 455, 454, 259, 408, 342, 452, 461, 463, 281, 470, 431, 417, 322, 290, 266, 392, 467, 479, 265, 312, 488, 389, 368, 254, 456, 326, 420, 465, 429, 325, 375, 499, 411, 272, 356, 476, 251, 307, 496, 310, 478, 257, 497, 319, 373, 489, 294, 432, 458, 361, 309, 387, 296, 427, 269, 351, 298, 386, 295, 260, 249, 403, 335, 360, 462, 340, 382, 352, 416, 275, 271, 338, 446, 469, 448, 327, 445, 442, 284, 393, 424, 315, 395, 426, 390, 406, 336, 474, 480, 357, 280, 353, 344, 376, 369, 475, 409, 302, 421, 397, 253, 449, 262, 404, 366, 428, 358, 422, 341, 419, 349, 293, 286, 491, 321, 453, 451, 444, 457, 328, 370, 410, 388, 333, 493, 460, 371, 350, 250, 379, 314, 285, 413, 364, 402, 316, 486, 297, 372, 490, 437, 258, 447, 415, 268, 459, 276, 330, 400, 261, 425, 329, 438, 477, 405, 267, 337, 434, 430, 323, 481, 450, 279, 440, 418, 359, 383, 199, 288, 178, 197, 33, 174, 72, 126, 227, 86, 55, 177, 198, 241, 228, 92, 131, 187, 127, 239, 114, 123, 212, 169, 243, 116, 112, 179, 83, 49, 138, 210, 9, 175, 60, 203, 129, 6, 56, 120, 30, 234, 122, 93, 39, 100, 107, 7, 218, 18, 171, 201, 147, 84, 232, 202, 170, 71, 23, 50, 214, 166, 181, 172, 208, 77, 19, 206, 47, 247, 10, 85, 115, 219, 133, 109, 182, 185, 110, 132, 189, 2, 32, 157, 141, 51, 128, 75, 106, 155, 53, 65, 162, 48, 14, 140, 230, 46, 62, 113, 143, 161, 121, 229, 59, 74, 186, 98, 144, 69, 226, 224, 244, 220, 25, 42, 96, 216, 125, 145, 40, 193, 233, 163, 191, 222, 176, 164, 173, 245, 99, 22, 27, 58, 118, 15, 152, 146, 159, 156, 137, 119, 0, 204, 5, 209, 103, 24, 160, 148, 43, 21, 57, 154, 195, 242, 81, 64, 135, 28, 82, 165, 41, 35, 63, 16, 89, 188, 70, 68, 11, 78, 37, 207, 196, 91, 223, 88, 4, 130, 8, 190, 194, 101, 149, 183, 3, 105, 90, 246, 117, 158, 102, 134, 231, 38, 238, 150, 236, 95, 235, 79, 17, 240, 139, 45, 87, 180, 111, 211, 34, 67, 80, 29, 136, 12, 168, 217, 184, 52, 248, 213, 104, 54, 215, 167, 73, 61};
    
    int stackA_size = sizeof(stackA) / sizeof(stackA[0]);
    int stackB_size = sizeof(stackB) / sizeof(stackB[0]);
    
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
    
    // Populate stack A
    for (int i = 0; i < stackA_size; i++) {
        t_node *node = create_node(stackA[i]);
        push_to_stack(ps->a, node);
    }
    
    // Populate stack B
    for (int i = 0; i < stackB_size; i++) {
        t_node *node = create_node(stackB[i]);
        push_to_stack(ps->b, node);
    }
    
    printf("✅ Created sorting state with %d elements in A and %d elements in B\n", 
           get_size(ps->a), get_size(ps->b));
    
    // Act - Call SnapshotStack on both stacks
    int snapshotA_size = 0;
    int *snapshotA = snapshot_stack(ps->a, &snapshotA_size);
    
    int snapshotB_size = 0;
    int *snapshotB = snapshot_stack(ps->b, &snapshotB_size);
    
    // Assert - Verify basic properties of the results
    if (snapshotA == NULL) {
        printf("❌ Expected snapshotA to be non-nil\n");
        free_sorting_state(ps);
        return;
    }
    
    if (snapshotB == NULL) {
        printf("❌ Expected snapshotB to be non-nil\n");
        free(snapshotA);
        free_sorting_state(ps);
        return;
    }
    
    // Verify we have the expected number of elements
    if (snapshotA_size != stackA_size) {
        printf("❌ Expected snapshotA length %d, got %d\n", stackA_size, snapshotA_size);
        free(snapshotA);
        free(snapshotB);
        free_sorting_state(ps);
        return;
    }
    
    if (snapshotB_size != stackB_size) {
        printf("❌ Expected snapshotB length %d, got %d\n", stackB_size, snapshotB_size);
        free(snapshotA);
        free(snapshotB);
        free_sorting_state(ps);
        return;
    }
    
    // Verify the elements match the original data
    int errors = 0;
    for (int i = 0; i < snapshotA_size; i++) {
        if (snapshotA[i] != stackA[i]) {
            printf("❌ snapshotA[%d]: expected %d, got %d\n", i, stackA[i], snapshotA[i]);
            errors++;
        }
    }
    
    for (int i = 0; i < snapshotB_size; i++) {
        if (snapshotB[i] != stackB[i]) {
            printf("❌ snapshotB[%d]: expected %d, got %d\n", i, stackB[i], snapshotB[i]);
            errors++;
        }
    }
    
    if (errors == 0) {
        printf("✅ All snapshot elements match original data\n");
    } else {
        printf("❌ Found %d element mismatches\n", errors);
    }
    
    // Print first few elements for inspection
    printf("First 5 elements of snapshotA: ");
    for (int i = 0; i < 5 && i < snapshotA_size; i++) {
        printf("%d ", snapshotA[i]);
    }
    printf("\n");
    
    printf("First 5 elements of snapshotB: ");
    for (int i = 0; i < 5 && i < snapshotB_size; i++) {
        printf("%d ", snapshotB[i]);
    }
    printf("\n");
    
    printf("Last 5 elements of snapshotA: ");
    for (int i = snapshotA_size - 5; i < snapshotA_size; i++) {
        printf("%d ", snapshotA[i]);
    }
    printf("\n");
    
    printf("Last 5 elements of snapshotB: ");
    for (int i = snapshotB_size - 5; i < snapshotB_size; i++) {
        printf("%d ", snapshotB[i]);
    }
    printf("\n");
    
    // Cleanup
    free(snapshotA);
    free(snapshotB);
    free_sorting_state(ps);
    
    printf("Test completed.\n");
}

// TestSnapshotStack_EmptyStack tests SnapshotStack with an empty stack
void test_snapshot_stack_empty_stack(void)
{
    printf("Testing SnapshotStack with empty stack...\n");
    
    // Arrange - Create an empty stack
    t_stack *empty_stack = create_stack();
    
    // Act - Call SnapshotStack on empty stack
    int size = 0;
    int *snapshot = snapshot_stack(empty_stack, &size);
    
    // Assert - Verify the result
    if (snapshot != NULL) {
        printf("❌ Expected snapshot to be NULL for empty stack\n");
        free(snapshot);
    } else {
        printf("✅ Snapshot is NULL for empty stack (as expected)\n");
    }
    
    if (size != 0) {
        printf("❌ Expected size to be 0, got %d\n", size);
    } else {
        printf("✅ Size is 0 for empty stack\n");
    }
    
    // Cleanup
    clear_stack(empty_stack);
    free(empty_stack);
    
    printf("Test completed.\n");
}

// TestSnapshotStack_SingleElement tests SnapshotStack with a single element
void test_snapshot_stack_single_element(void)
{
    printf("Testing SnapshotStack with single element...\n");
    
    // Arrange - Create a stack with one element
    t_stack *single_stack = create_stack();
    t_node *node = create_node(42);
    push_to_stack(single_stack, node);
    
    // Act - Call SnapshotStack on single element stack
    int size = 0;
    int *snapshot = snapshot_stack(single_stack, &size);
    
    // Assert - Verify the result
    if (snapshot == NULL) {
        printf("❌ Expected snapshot to be non-nil\n");
        clear_stack(single_stack);
        free(single_stack);
        return;
    }
    
    if (size != 1) {
        printf("❌ Expected snapshot length 1, got %d\n", size);
        free(snapshot);
        clear_stack(single_stack);
        free(single_stack);
        return;
    }
    
    if (snapshot[0] != 42) {
        printf("❌ Expected snapshot[0] to be 42, got %d\n", snapshot[0]);
        free(snapshot);
        clear_stack(single_stack);
        free(single_stack);
        return;
    }
    
    printf("✅ Single element snapshot works correctly\n");
    
    // Cleanup
    free(snapshot);
    clear_stack(single_stack);
    free(single_stack);
    
    printf("Test completed.\n");
}
