/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:50:55 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:50:58 by ptison           ###   ########.fr       */
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
	printf("\n");
}
