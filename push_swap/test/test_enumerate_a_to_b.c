#include "test_main.h"
#include "../include/selector.h"

// TestEnumerateAtoB_Iteration0 tests EnumerateAtoB with data from PickNearBest1.txt iteration 0
void test_enumerate_a_to_b_iteration0(void)
{
    printf("Testing EnumerateAtoB with iteration 0 data...\n");
    
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
    
    // Create CandidateEnumerator with default config
    t_selector_config config = default_selector_config();
    t_candidate_enumerator *enumerator = new_candidate_enumerator(config);
    
    if (!enumerator) {
        printf("❌ Failed to create candidate enumerator\n");
        free_sorting_state(ps);
        return;
    }
    
    // Act - Call EnumerateAtoB with the test data
    int candidate_count = 0;
    t_candidate *candidates = enumerate_a_to_b(enumerator, ps->a, ps->b, &candidate_count);
    
    // Assert - Verify basic properties of the result
    if (candidates == NULL) {
        printf("❌ Expected candidates to be non-nil\n");
        free_candidate_enumerator(enumerator);
        free_sorting_state(ps);
        return;
    }
    
    // Verify we have candidates (filtered by cost threshold)
    if (candidate_count == 0) {
        printf("❌ Expected at least one candidate after filtering\n");
        free_candidate_enumerator(enumerator);
        free_sorting_state(ps);
        return;
    }
    
    printf("✅ Got %d candidates after filtering (from %d total)\n", candidate_count, stackA_size);
    
    // Verify each candidate has valid properties
    int errors = 0;
    for (int i = 0; i < candidate_count; i++) {
        t_candidate *candidate = &candidates[i];
        
        // Verify FromIndex is within valid range for stack A
        if (candidate->position.from_index < 0 || candidate->position.from_index >= stackA_size) {
            printf("❌ Candidate %d: FromIndex %d is out of range [0, %d)\n", 
                   i, candidate->position.from_index, stackA_size);
            errors++;
        }
        
        // Verify ToIndex is within valid range for stack B
        if (candidate->position.to_index < 0 || candidate->position.to_index > stackB_size) {
            printf("❌ Candidate %d: ToIndex %d is out of range [0, %d]\n", 
                   i, candidate->position.to_index, stackB_size);
            errors++;
        }
        
        // Verify costs are calculated
        if (candidate->position.cost_a == 0 && candidate->position.cost_b == 0) {
            printf("❌ Candidate %d: both costs are zero, which seems incorrect\n", i);
            errors++;
        }
        
        // Verify Total cost is calculated using MergedCost optimization
        // Note: Total may not equal CostA + CostB due to rotation optimization
        if (candidate->position.total <= 0) {
            printf("❌ Candidate %d: Total cost should be positive, got %d\n", 
                   i, candidate->position.total);
            errors++;
        }
        
        // Verify Score is calculated (includes penalty for AtoB moves)
        if (candidate->score <= 0) {
            printf("❌ Candidate %d: Score should be positive, got %d\n", i, candidate->score);
            errors++;
        }
        
        // For AtoB moves, Score should be >= Total (since it includes penalty)
        if (candidate->score < candidate->position.total) {
            printf("❌ Candidate %d: Score %d should be >= Total %d (Score includes penalty)\n", 
                   i, candidate->score, candidate->position.total);
            errors++;
        }
    }
    
    if (errors == 0) {
        printf("✅ All candidate properties are valid\n");
    } else {
        printf("❌ Found %d property validation errors\n", errors);
    }
    
    // Print first few candidates for inspection (since we don't know expected values yet)
    printf("First 5 candidates:\n");
    for (int i = 0; i < 5 && i < candidate_count; i++) {
        t_candidate *c = &candidates[i];
        printf("  Candidate %d: FromIndex=%d, ToIndex=%d, CostA=%d, CostB=%d, Total=%d, Score=%d\n", 
               i, c->position.from_index, c->position.to_index, c->position.cost_a, c->position.cost_b, c->position.total, c->score);
    }
    
    // Cleanup
    free(candidates);
    free_candidate_enumerator(enumerator);
    free_sorting_state(ps);
    
    printf("Test completed.\n");
}
