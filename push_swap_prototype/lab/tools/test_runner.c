/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 1000

// Generate random numbers without duplicates
void generate_random_numbers(int *numbers, int count) {
    int used[MAX_VALUE + 1] = {0};  // Track used numbers
    int generated = 0;
    
    // Use microsecond precision for better randomness
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    srand(ts.tv_nsec);  // Use nanoseconds for better randomness
    
    while (generated < count) {
        int num = rand() % MAX_VALUE + 1;  // 1 to MAX_VALUE
        
        if (!used[num]) {
            numbers[generated] = num;
            used[num] = 1;
            generated++;
        }
    }
}

// Print numbers to console
void print_numbers(int *numbers, int count) {
    printf("Generated %d random numbers:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d", numbers[i]);
        if (i < count - 1) printf(" ");
    }
    printf("\n\n");
}

// Run push_swap with the generated numbers
void run_push_swap(int *numbers, int count) {
    char command[4096];
    char numbers_str[4096];
    
    // Convert numbers array to space-separated string
    numbers_str[0] = '\0';
    for (int i = 0; i < count; i++) {
        char temp[32];
        snprintf(temp, sizeof(temp), "%d", numbers[i]);
        
        if (i > 0) strcat(numbers_str, " ");
        strcat(numbers_str, temp);
    }
    
    // Build command: ./bin/push_swap <numbers>
    snprintf(command, sizeof(command), "./bin/push_swap %s", numbers_str);
    
    printf("Running: %s\n", command);
    printf("Output:\n");
    printf("----------------------------------------\n");
    
    // Execute the command
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error executing push_swap");
        return;
    }
    
    char buffer[256];
    int operation_count = 0;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
        operation_count++;
    }
    
    pclose(fp);
    
    printf("----------------------------------------\n");
    printf("Total operations: %d\n", operation_count);
}

// Run push_swap and count operations
int count_operations(int *numbers, int count) {
    char command[4096];
    char numbers_str[4096];
    
    // Convert numbers array to space-separated string
    numbers_str[0] = '\0';
    for (int i = 0; i < count; i++) {
        char temp[32];
        snprintf(temp, sizeof(temp), "%d", numbers[i]);
        
        if (i > 0) strcat(numbers_str, " ");
        strcat(numbers_str, temp);
    }
    
    // Build command: ./bin/push_swap <numbers> | wc -l
    snprintf(command, sizeof(command), "./bin/push_swap %s | wc -l", numbers_str);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }
    
    char buffer[32];
    int operations = 0;
    
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        operations = atoi(buffer);
    }
    
    pclose(fp);
    return operations;
}

// Run multiple tests and show statistics
void run_multiple_tests(int test_count) {
    printf("Running %d tests with 100 random numbers each...\n\n", test_count);
    
    int total_operations = 0;
    int min_operations = INT_MAX;
    int max_operations = 0;
    
    for (int test = 1; test <= test_count; test++) {
        int numbers[MAX_NUMBERS];
        generate_random_numbers(numbers, MAX_NUMBERS);
        
        printf("Test %d/%d: ", test, test_count);
        
        int operations = count_operations(numbers, MAX_NUMBERS);
        if (operations >= 0) {
            printf("%d operations\n", operations);
            total_operations += operations;
            
            if (operations < min_operations) min_operations = operations;
            if (operations > max_operations) max_operations = operations;
        } else {
            printf("ERROR\n");
        }
    }
    
    printf("\nStatistics:\n");
    printf("Total tests: %d\n", test_count);
    printf("Average operations: %.2f\n", (double)total_operations / test_count);
    printf("Min operations: %d\n", min_operations);
    printf("Max operations: %d\n", max_operations);
}

int main(int argc, char *argv[]) {
    int numbers[MAX_NUMBERS];
    
    printf("=== Push Swap Test Runner ===\n\n");
    
    if (argc > 1) {
        if (strcmp(argv[1], "stats") == 0) {
            int test_count = (argc > 2) ? atoi(argv[2]) : 10;
            run_multiple_tests(test_count);
        } else if (strcmp(argv[1], "help") == 0) {
            printf("Usage:\n");
            printf("  %s                    - Run single test with 100 numbers\n", argv[0]);
            printf("  %s stats [count]      - Run multiple tests and show statistics\n", argv[0]);
            printf("  %s help               - Show this help\n", argv[0]);
            printf("\nExamples:\n");
            printf("  %s                    - Single test\n", argv[0]);
            printf("  %s stats              - 10 tests with statistics\n", argv[0]);
            printf("  %s stats 50           - 50 tests with statistics\n", argv[0]);
        } else {
            printf("Unknown option: %s\n", argv[1]);
            printf("Use '%s help' for usage information\n", argv[0]);
            return 1;
        }
    } else {
        // Single test mode
        printf("Generating 100 random numbers...\n");
        generate_random_numbers(numbers, MAX_NUMBERS);
        
        print_numbers(numbers, MAX_NUMBERS);
        run_push_swap(numbers, MAX_NUMBERS);
    }
    
    return 0;
}
