#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "../include/push_swap.h"


typedef struct s_parser_result
{
	int*	input;
	int	count;
}			t_parser_result;

t_parser_result parse_args(int argc, char *argv[]) {
    if (argc < 2) {
        ft_printf("Error\n");
        return 1;
    }
	int out_index = 0;
    
    for (int i = 1; i < argc; i++) {
        // Check if the argument contains spaces
        if (ft_strchr(argv[i], ' ') != NULL) {
            // Split the argument by spaces
            char **split_nums = ft_split(argv[i], ' ');
            if (!split_nums) {
                printf("Error\n");
                return -1;
            }
            
            // Process each split number
            int j = 0;
            while (split_nums[j] != NULL) {
                char *endptr;
                errno = 0;
                int val = ft_strtoi10(split_nums[j], &endptr);
                
                if (*endptr != '\0') {
                    // Free allocated memory before returning error
                    for (int k = 0; split_nums[k] != NULL; k++) {
                        free(split_nums[k]);
                    }
                    free(split_nums);
                    printf("Error\n");
                    return -1;
                }
                
                if (errno == ERANGE) {
                    // Free allocated memory before returning error
                    for (int k = 0; split_nums[k] != NULL; k++) {
                        free(split_nums[k]);
                    }
                    free(split_nums);
                    printf("Error\n");
                    return -1;
                }
                
                out[out_index++] = val;
                j++;
            }
            
            // Free the split array
            for (int k = 0; split_nums[k] != NULL; k++) {
                free(split_nums[k]);
            }
            free(split_nums);
        } else {
            // Single number argument
            char *endptr;
            errno = 0;
            int val = ft_strtoi10(argv[i], &endptr);
            
            if (*endptr != '\0') {
                printf("Error\n");
                return -1;
            }
            
            if (errno == ERANGE) {
                printf("Error\n");
                return -1;
            }
            
            out[out_index++] = val;
        }
    }
    
    return out_index;
}

int main(int argc, char *argv[]) {

	t_parser_result result;
    result = parse_args(argc, argv);

    for (int i = 0; i < result.count; i++) {
        printf("%d ", result.input[i]);
    }
    printf("\n");

    return 0;
}
