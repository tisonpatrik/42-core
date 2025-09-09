/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:50:55 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 20:24:35 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/separator.h"
#include "test_main.h"

// Helper function to check if LIS result matches expected values
int	check_lis_result(t_node_bool_array *result, int *expected_values,
		int expected_count)
{
	if (!result || !result->items || result->count != (size_t)expected_count)
		return (0);
	for (size_t i = 0; i < result->count; i++)
	{
		if (!result->items[i].node
			|| get_content(result->items[i].node) != expected_values[i])
			return (0);
	}
	return (1);
}

// Test LIS with the provided large input
void	test_lis_large_input(void)
{
	int					input_size;
	int					expected_lis[] = {6, 9, 30, 33, 39, 44, 60, 61, 65, 75,
							95, 113, 119, 120, 125, 131, 154, 165, 177, 190,
							193, 232, 242, 249, 253, 281, 315, 334, 343, 366,
							368, 373, 375, 381, 415, 423, 426, 449, 463, 469,
							473, 491};
	int					expected_lis_size;
	t_sorting_state		*state;
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange - Input from user query
	int input[] = {6,   319, 184, 109, 285, 9,  100, 379, 479, 183, 30,  461,
		327, 133, 434, 450, 412, 313, 76, 497, 128, 148, 273, 53,  428, 22,
		 180, 413, 236, 451, 258, 182, 427, 419, 207, 267, 329, 475, 303, 369,
		403, 3,   483, 367, 322, 499, 82,  410, 254, 312, 92, 347, 297, 181,
		395, 397, 127, 94,  153, 84, 416, 482, 43, 195, 200, 141, 74,  302, 208,
		310, 59,  376, 130, 63, 339, 282, 263, 287, 205, 293, 129, 383, 421,
		102, 384, 51,  255, 188, 495, 33,  47,  406, 147, 29,  348, 235, 418,
		194, 78,  166, 137, 328, 447, 454, 23,  401, 455, 298, 289, 11,  1,
		  39,  112, 489, 199, 408, 93,  280, 186, 391, 350, 259, 359, 316, 44,
		 441, 121, 439, 12,  301, 320, 445, 453, 371, 37,  262, 388, 60,  161,
		279, 404, 335, 118, 34,  294, 189, 492, 145, 45,  25,  61,  65,  243,
		465,
					471, 488, 324, 75,  213, 95, 377, 257, 265, 332, 231, 342,
						17,  442, 264, 169, 261, 355, 5,  66,  435, 160, 86,
						 409, 168, 142, 179, 197, 217, 247, 204, 167, 246, 113,
						134, 227, 48,  241, 2,   81,  103, 185, 14,  225, 221,
						459, 277, 119, 292, 305, 87, 361, 370, 31,  120, 440,
						363, 125, 345, 69, 448, 219, 42, 214, 203, 417, 220,
						390, 198, 201, 269, 387, 314, 35, 122, 399, 80,  431,
						456, 296, 88,  306, 13,  400, 191, 407, 480, 494, 108,
						272, 131, 338, 405, 110, 210, 468, 52,  288, 380, 470,
						154, 358, 209, 290, 443, 77,  481, 165, 485, 414, 224,
						276, 330, 97,  386, 446, 321, 486, 177, 392, 79,  477,
						206, 460, 382, 457, 337, 98,  466, 70,  190, 193, 232,
						242, 249, 253, 281, 315, 334, 343, 366, 368, 373, 375,
						381, 415, 423, 426, 449, 463, 469, 473, 491};
	input_size = sizeof(input) / sizeof(input[0]);
	// Expected LIS result from user query
	expected_lis_size = sizeof(expected_lis) / sizeof(expected_lis[0]);
	state = create_sorting_state(input, input_size);
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected_lis, expected_lis_size);
	print_test_result("LIS Large Input Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

// Test LIS with the second large input
void	test_lis_second_large_input(void)
{
	int					input_size;
	int					expected_lis[] = {5, 30, 37, 39, 51, 52, 56, 73, 83, 88,
							99, 101, 103, 109, 113, 129, 186, 218, 235, 244,
							249, 258, 261, 264, 269, 286, 334, 363, 371, 382,
							387, 389, 395, 428, 447, 450, 451, 463, 466, 473};
	int					expected_lis_size;
	t_sorting_state		*state;
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange - Second input from user query
	int input[] = {377, 446, 160, 70,  487, 415, 342, 498, 93,  112, 138, 465,
		54,  5,   228, 431, 390, 318, 401, 456, 423, 89,  47,  223, 283, 331,
		346, 176, 168, 30,  392, 210, 274, 81,  341, 71,  20,  417, 178, 330,
		158, 2,   145, 37,  201, 325, 475, 493, 39,  494, 356, 393, 142, 148,
		280, 305, 320, 62,  310, 51,  289, 72,  296, 220, 420, 10,  294, 391,
		347, 188, 488, 82,  410, 460, 292, 196, 227, 332, 474, 140, 28,  123,
		272, 239, 394, 464, 429, 131, 260, 445, 147, 135, 241, 313, 237, 380,
		214, 339, 301, 151, 164, 358, 425, 52,  408, 127, 25,  326, 173, 90,
		163, 436, 106, 111, 96,  300, 287, 273, 359, 362, 375, 271, 484, 21,
		 405, 78,  128, 56,  404, 110, 115, 4,   379, 48,  33,  444, 16,  259,
		177, 29,  297, 156, 383, 8,   255, 238, 268, 236, 104, 424, 469, 366,
		277, 73,  83,  449, 154, 368, 345, 11,  335, 388, 42,  467, 400, 26,
		 242,
					357, 172, 376, 472, 416, 88,  99,  162, 422, 353, 209, 306,
						134, 80,  59,  455, 203, 317, 490, 13,  303, 352, 398,
						439, 315, 66,  453, 198, 240, 295, 101, 440, 321, 457,
						291, 103, 60,  97,  350, 9,   217, 355, 3,   212, 257,
						18,  15,  309, 338, 126, 109, 298, 438, 293, 432, 169,
						316, 365, 492, 61,  45,  409, 354, 113, 254, 189, 19,
						 329, 270, 129, 186, 497, 218, 322, 137, 452, 235, 107,
						91,  208, 136, 55,  443, 495, 122, 373, 65,  216, 41,
						 324, 75,  302, 244, 433, 199, 435, 284, 249, 479, 419,
						427, 399, 246, 190, 225, 397, 336, 165, 36,  44, 263,
						351, 282, 491, 372, 166, 32,  311, 426, 213, 308, 141,
						35,  402, 418, 481, 258, 76,  95,  250, 230, 117, 153,
						180, 279, 49,  150, 86,  157, 34,  159, 361, 448, 261,
						441, 337, 328, 50,  462, 31,  275, 367, 226, 499, 130,
						386, 224, 40,  132, 193, 139, 414, 14,  384, 245, 171,
						348,
					312, 120, 74,  442, 22,  155, 24,  264, 68,  215, 118, 119,
						413, 206, 340, 421, 248, 269, 262, 486, 286, 385, 124,
						334, 483, 207, 363, 191, 477, 343, 411, 403, 79,  0,
						  205, 253, 371, 382, 412, 364, 461, 349, 63,  69,  489,
						84,  430, 314, 387, 17,  381, 121, 133, 85,  12,  195,
						1,   265, 232, 200, 267, 185, 266, 278, 143, 482, 231,
						58,  98,  202, 496, 184, 105, 454, 471, 114, 116, 299,
						389, 108, 46,  7,   395, 428, 290, 459, 447, 344, 478,
						285, 476, 175, 181, 281, 243, 407, 187, 27,  144, 87,
						 38,  146, 170, 197, 161, 307, 100, 304, 276, 53, 174,
						458, 468, 43,  327, 92,  480, 57,  378, 149, 179, 23,
						 194, 182, 6,   67,  183, 167, 64,  229, 360, 247, 152,
						125, 333, 251, 222, 450, 233, 252, 434, 211, 470, 192,
						369, 451, 77,  219, 221, 406, 396, 319, 437, 485, 94,
						 374, 463, 102, 370, 323, 466, 204, 288, 473, 234, 256};
	input_size = sizeof(input) / sizeof(input[0]);
	// Expected LIS result from user query
	expected_lis_size = sizeof(expected_lis) / sizeof(expected_lis[0]);
	state = create_sorting_state(input, input_size);
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected_lis, expected_lis_size);
	print_test_result("LIS Second Large Input Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

// Test LIS with empty stack
void	test_lis_empty_stack(void)
{
	t_stack				*empty_stack;
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange
	empty_stack = create_stack();
	// Act
	result = get_lis_nodes(empty_stack);
	// Assert
	test_passed = (result != NULL && result->count == 0
			&& result->items == NULL);
	print_test_result("LIS Empty Stack Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	clear_stack(empty_stack);
	free(empty_stack);
}

// Test LIS with single element
void	test_lis_single_element(void)
{
	int					input[] = {42};
	t_sorting_state		*state;
	int					expected[] = {42};
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange
	state = create_sorting_state(input, 1);
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected, 1);
	print_test_result("LIS Single Element Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

// Test LIS with already sorted sequence
void	test_lis_sorted_sequence(void)
{
	int					input[] = {1, 2, 3, 4, 5};
	t_sorting_state		*state;
	int					expected[] = {1, 2, 3, 4, 5};
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange
	state = create_sorting_state(input, 5);
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected, 5);
	print_test_result("LIS Sorted Sequence Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

// Test LIS with reverse sorted sequence
void	test_lis_reverse_sorted(void)
{
	int					input[] = {5, 4, 3, 2, 1};
	t_sorting_state		*state;
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange
	state = create_sorting_state(input, 5);
	int expected[] = {1}; // Only one element in LIS
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected, 1);
	print_test_result("LIS Reverse Sorted Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

// Test LIS with third large input - log line 1
void	test_lis_third_large_input(void)
{
	int					input_size;
	int					expected_lis[] = {6, 35, 48, 50, 77, 81, 96, 111, 123, 126,
							132, 172, 186, 201, 220, 224, 232, 236, 265, 270,
							275, 288, 315, 336, 340, 364, 376, 381, 383, 386,
							413, 423, 425, 438, 444, 452, 457, 458, 461, 467,
							471, 475, 479};
	int					expected_lis_size;
	t_sorting_state		*state;
	t_node_bool_array	*result;
	int					test_passed;

	// Arrange - Third input from user query
	int input[] = {78, 110, 179, 222, 399, 6, 250, 392, 469, 176, 161, 177, 449,
		329, 94, 455, 417, 276, 58, 497, 243, 218, 473, 130, 139, 269, 79, 92,
		35, 187, 237, 354, 429, 145, 278, 390, 64, 464, 162, 460, 416, 12, 48,
		167, 181, 114, 199, 299, 403, 319, 247, 387, 225, 369, 50, 382, 77, 412,
		184, 300, 440, 253, 330, 81, 245, 488, 31, 136, 459, 138, 267, 96, 111,
		59, 36, 305, 418, 103, 385, 373, 196, 75, 149, 123, 451, 292, 126, 215,
		198, 14, 322, 260, 210, 327, 407, 266, 487, 132, 463, 5, 46, 40, 72, 453,
		61, 252, 320, 363, 277, 483, 450, 307, 231, 311, 238, 7, 360, 86, 172,
		271, 166, 489, 186, 476, 201, 261, 437, 1, 9, 308, 284, 220, 205, 375,
		242, 446, 146, 352, 106, 374, 70, 436, 494, 26, 348, 33, 317, 347, 97,
		477, 367, 240, 163, 197, 224, 105, 484, 98, 335, 379, 137, 442, 22, 93,
		251, 301, 38, 357, 362, 44, 323, 84, 212, 325, 16, 498, 56, 49, 95, 148,
		337, 391, 183, 478, 155, 393, 402, 134, 119, 420, 332, 202, 304, 285,
		468, 10, 447, 207, 378, 435, 55, 248, 151, 171, 170, 73, 232, 472, 236,
		90, 211, 353, 355, 30, 265, 180, 433, 400, 52, 443, 405, 257, 326, 270,
		395, 116, 434, 321, 441, 82, 275, 168, 68, 239, 24, 63, 254, 159, 397,
		208, 351, 384, 288, 315, 439, 120, 370, 344, 122, 424, 401, 156, 291,
		262, 18, 462, 124, 482, 51, 411, 336, 368, 193, 194, 365, 206, 160, 480,
		340, 144, 364, 141, 190, 302, 314, 157, 350, 182, 345, 108, 286, 228, 19,
		2, 234, 258, 376, 39, 165, 143, 263, 233, 65, 62, 456, 298, 426, 129,
		431, 388, 91, 23, 32, 334, 229, 11, 495, 398, 281, 109, 219, 381, 203,
		113, 4, 264, 154, 312, 25, 226, 396, 195, 490, 244, 142, 415, 294, 255,
		268, 383, 76, 297, 465, 338, 127, 386, 152, 20, 361, 217, 8, 99, 328,
		496, 499, 107, 174, 377, 445, 486, 324, 491, 69, 221, 287, 371, 29, 112,
		466, 413, 230, 289, 389, 474, 74, 423, 153, 409, 102, 0, 273, 404, 118,
		27, 349, 85, 53, 89, 394, 425, 71, 316, 80, 341, 272, 421, 309, 438, 283,
		246, 444, 279, 150, 339, 310, 54, 204, 164, 282, 406, 34, 88, 147, 333,
		470, 259, 42, 410, 428, 125, 359, 135, 452, 213, 457, 216, 356, 414, 380,
		454, 60, 188, 306, 100, 280, 192, 173, 295, 41, 200, 21, 185, 209, 366,
		115, 131, 485, 3, 15, 47, 17, 303, 104, 43, 83, 274, 175, 191, 432, 249,
		408, 241, 66, 419, 458, 481, 318, 189, 214, 342, 256, 67, 346, 296, 372,
		343, 117, 430, 28, 169, 358, 492, 290, 235, 293, 331, 45, 313, 493, 133,
		461, 223, 467, 178, 37, 448, 471, 128, 13, 140, 87, 101, 475, 121, 427,
		158, 227, 422, 57, 479};
	input_size = sizeof(input) / sizeof(input[0]);
	expected_lis_size = sizeof(expected_lis) / sizeof(expected_lis[0]);
	state = create_sorting_state(input, input_size);
	// Act
	result = get_lis_nodes(state->a);
	// Assert
	test_passed = check_lis_result(result, expected_lis, expected_lis_size);
	print_test_result("LIS Third Large Input Test", test_passed);
	// Cleanup
	if (result)
	{
		free(result->items);
		free(result);
	}
	free_sorting_state(state);
}

void	test_lis_operations(void)
{
	printf("📈 Testing Longest Increasing Subsequence (LIS) Operations\n");
	printf("--------------------------------------------------------\n");
	test_lis_empty_stack();
	test_lis_single_element();
	test_lis_sorted_sequence();
	test_lis_reverse_sorted();
	test_lis_large_input();
	test_lis_second_large_input();
	test_lis_third_large_input();
	printf("\n");
}
