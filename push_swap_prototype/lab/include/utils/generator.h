#ifndef GENERATOR_H
# define GENERATOR_H

#include <stddef.h>

// Array generation configuration
typedef struct s_generator_config {
    unsigned int seed;           // Random seed for reproducible generation
    int min_value;              // Minimum value in generated array
    int max_value;              // Maximum value in generated array
    int allow_duplicates;        // Whether to allow duplicate values
} t_generator_config;

// Default configuration
extern const t_generator_config DEFAULT_GENERATOR_CONFIG;

// Core generation functions
int *generate_random_array(int size);
int *generate_deterministic_array(int size, unsigned int seed);
int *generate_sequential_array(int size, int start_value);

// Configuration-based generation
int *generate_array_with_config(int size, const t_generator_config *config);

// Utility functions
void set_random_seed(unsigned int seed);
unsigned int get_random_seed(void);
void shuffle_array(int *array, int size, unsigned int seed);

// Memory management
void free_generated_array(int *array);

#endif
