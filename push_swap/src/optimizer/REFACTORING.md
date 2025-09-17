# Optimizer Module Refactoring Plan

## Overview

The current optimizer module suffers from significant architectural and code quality issues that make it difficult to maintain, extend, and debug. This document outlines a comprehensive refactoring plan to transform the optimizer into a clean, modular, and maintainable system following the same high-quality patterns used in the selector and separator modules.

## Current Issues Analysis

### 1. Architecture Problems

#### Poor Separation of Concerns
- All optimization logic is mixed together in a single monolithic approach
- No clear boundaries between different optimization strategies
- Direct manipulation of linked lists throughout the codebase
- Tight coupling between optimization functions

#### Inconsistent Design Patterns
- Arena is created/destroyed per function instead of being reused efficiently
- No proper abstraction layer for operation manipulation
- Missing strategy pattern for different optimization types
- Inconsistent error handling patterns

### 2. Memory Management Issues

#### Inefficient Allocation Patterns
- Creating new lists for every optimization step
- Multiple malloc/free calls instead of arena-based allocation
- Potential memory leaks with complex cleanup logic
- Arena created but not properly utilized for memory management

#### Memory Leak Risks
- Complex cleanup logic with goto statements
- Inconsistent error handling that may skip cleanup
- Manual memory management instead of RAII patterns

### 3. Code Quality Violations

#### Function Length Issues
- Many functions exceed 50 lines (violates coding standards)
- Complex nested loops and conditional logic
- Missing proper function decomposition

#### Magic Numbers and Hardcoded Values
- Hardcoded `max_gap = 4` in bubble operations
- Magic numbers throughout the codebase
- No configuration system for optimization parameters

#### Poor Control Flow
- goto statements in `cancel_across_other_stack_*` functions
- Complex nested loops that are hard to follow
- Inconsistent error handling patterns

### 4. Maintainability Problems

#### Code Duplication
- `copy_operation` function duplicated across files
- `add_operation_to_list` pattern repeated everywhere
- Similar validation logic scattered throughout

#### Lack of Modularity
- No clear interfaces between components
- Public functions expose internal implementation details
- Missing abstractions for common operations

## Refactoring Strategy

### Phase 1: Foundation (High Priority)

#### 1.1 Enhanced Arena Management
Create a proper arena system similar to selector/separator modules:

```c
typedef struct s_optimizer_arena {
    t_operation     *operations;
    t_list         **temp_lists;
    int            *indices;
    bool           *flags;
    size_t         capacity;
    size_t         used;
    void           *arena_memory;
    size_t         arena_size;
} t_optimizer_arena;
```

**Benefits:**
- Single allocation for all temporary data
- Automatic cleanup on arena destruction
- Better memory locality and performance
- Consistent with other modules

#### 1.2 Operation Builder Pattern
Implement a safe operation list manipulation system:

```c
typedef struct s_operation_builder {
    t_optimizer_arena   *arena;
    t_list             *result;
    bool               changed;
    t_optimizer_error  error;
} t_operation_builder;
```

**Benefits:**
- Encapsulates list manipulation logic
- Provides safe operation building
- Consistent error handling
- Reduces code duplication

### Phase 2: Architecture Redesign (High Priority)

#### 2.1 Strategy Pattern Implementation
Create a strategy pattern for different optimization types:

```c
typedef struct s_optimization_strategy {
    char            *name;
    bool            (*can_apply)(t_list *seq);
    t_list*         (*apply)(t_list *seq, t_optimizer_arena *arena, bool *changed);
    int             priority;
} t_optimization_strategy;
```

**Strategies to implement:**
- Bubble Strategy: Move operations across barriers
- Merge Strategy: Combine neighboring operations
- Cancel Strategy: Remove inverse operation pairs

#### 2.2 Configuration System
Add a configuration system for optimization parameters:

```c
typedef struct s_optimizer_config {
    int     max_bubble_gap;
    bool    enable_merge_neighbors;
    bool    enable_cancel_pairs;
    bool    enable_cancel_across;
    int     max_iterations;
} t_optimizer_config;
```

**Benefits:**
- Eliminates magic numbers
- Makes optimization behavior configurable
- Easier testing with different configurations

### Phase 3: Module Restructuring (Medium Priority)

#### 3.1 Core Modules
- **`optimizer_core.c`**: Main optimization engine
- **`optimization_strategies.c`**: Strategy registry and management
- **`operation_builder.c`**: Safe operation list manipulation
- **`optimizer_arena.c`**: Enhanced arena management

#### 3.2 Strategy Modules
- **`bubble_strategy.c`**: Bubble operations optimization
- **`merge_strategy.c`**: Neighbor merging optimization  
- **`cancel_strategy.c`**: Operation cancellation optimization

#### 3.3 Utility Modules
- **`operation_properties.c`**: Operation classification utilities
- **`optimizer_utils.c`**: Common utility functions

### Phase 4: Code Quality Improvements (Medium Priority)

#### 4.1 Function Decomposition
- Break down functions > 50 lines into smaller, focused functions
- Extract common patterns into utility functions
- Implement proper validation functions

#### 4.2 Error Handling
```c
typedef enum e_optimizer_error {
    OPTIMIZER_SUCCESS = 0,
    OPTIMIZER_INVALID_INPUT,
    OPTIMIZER_MEMORY_ERROR,
    OPTIMIZER_ARENA_FULL,
    OPTIMIZER_INVALID_CONFIG
} t_optimizer_error;
```

#### 4.3 Memory Management
- Use arena for all temporary allocations
- Implement proper cleanup patterns
- Add memory usage tracking and validation

### Phase 5: API Redesign (Low Priority)

#### 5.1 Clean Public Interface
```c
// New public API
t_optimizer_result optimize_operations(t_list *operations, t_optimizer_config *config);
void              free_optimizer_result(t_optimizer_result *result);
t_optimizer_arena* create_optimizer_arena(size_t capacity);
void              destroy_optimizer_arena(t_optimizer_arena *arena);
```

#### 5.2 Configuration Management
```c
t_optimizer_config* create_default_optimizer_config(void);
t_optimizer_config* create_custom_optimizer_config(int max_gap, bool enable_merge, ...);
void               free_optimizer_config(t_optimizer_config *config);
```

## Implementation Roadmap

### Week 1: Foundation
- [ ] Implement enhanced arena management
- [ ] Create operation builder pattern
- [ ] Add basic error handling system

### Week 2: Architecture
- [ ] Implement strategy pattern
- [ ] Create configuration system
- [ ] Refactor main optimization loop

### Week 3: Strategies
- [ ] Implement bubble strategy
- [ ] Implement merge strategy
- [ ] Implement cancel strategy

### Week 4: Quality & Testing
- [ ] Add comprehensive unit tests
- [ ] Performance optimization
- [ ] Documentation updates

## Migration Strategy

### Backward Compatibility
- Keep existing public API during transition
- Implement new API alongside old API
- Gradual migration of callers to new API

### Testing Strategy
- Unit tests for each strategy
- Integration tests for full optimization pipeline
- Performance benchmarks
- Memory leak detection

### Rollout Plan
1. Implement new architecture in parallel
2. Add comprehensive tests
3. Performance validation
4. Gradual replacement of old implementation
5. Remove deprecated code

## Success Metrics

### Code Quality
- All functions under 50 lines
- No magic numbers
- Consistent error handling
- Comprehensive test coverage

### Performance
- Reduced memory allocations
- Better cache locality
- Maintained or improved optimization quality
- Faster execution times

### Maintainability
- Clear separation of concerns
- Easy to add new optimization strategies
- Comprehensive documentation
- Consistent coding patterns

## Risk Mitigation

### Testing Risks
- Implement comprehensive test suite before refactoring
- Use property-based testing for optimization correctness
- Performance regression testing

### Migration Risks
- Gradual migration approach
- Keep old implementation as fallback
- Extensive integration testing

### Performance Risks
- Benchmark current implementation
- Monitor performance during refactoring
- Optimize critical paths

## Conclusion

This refactoring will transform the optimizer from a monolithic, hard-to-maintain module into a clean, modular, and extensible system that follows the same high-quality patterns used in the selector and separator modules. The new architecture will be more maintainable, testable, and performant while providing a solid foundation for future enhancements.

The refactoring follows clean code principles and coding standards, ensuring that the resulting code is professional, maintainable, and follows best practices for C development.