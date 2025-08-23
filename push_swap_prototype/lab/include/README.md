# Include Directory Structure

This directory contains all header files organized by responsibility and purpose.

## Directory Organization

### `core/` - Core Data Structures and Types
- **Purpose**: Contains fundamental data structures and type definitions used across the project
- **Files**:
  - `types.h` - Common type definitions and forward declarations

### `testing/` - Testing Framework Headers
- **Purpose**: Contains all testing-related headers and test structure definitions
- **Files**:
  - `test_runner.h` - Test execution engine and configuration
  - `chunk_utils_tests.h` - Chunk utility test function declarations
  - `chunk_max_value_test.h` - Chunk max value test structure
  - `chunk_value_test.h` - Chunk value test structure
  - `loc_to_stack_test.h` - Location to stack test structure

### `utils/` - Utility Function Headers
- **Purpose**: Contains utility function headers for common operations
- **Files**:
  - `generator.h` - Array generation utilities
  - `json_utils.h` - JSON handling utilities
  - `stack_utils.h` - Stack manipulation utilities
  - `error_utils.h` - Error handling utilities
  - `file_utils.h` - File operation utilities

## Design Principles

1. **Single Responsibility**: Each header has one clear, focused purpose
2. **Logical Grouping**: Related functionality is grouped together
3. **Clear Dependencies**: Dependencies between modules are explicit
4. **Scalability**: Easy to add new functionality without breaking existing structure

## Include Paths

When including headers in source files, use the appropriate relative path:

```c
// For core types
#include "../include/core/types.h"

// For testing framework
#include "../include/testing/test_runner.h"

// For utilities
#include "../include/utils/generator.h"
```

## Adding New Headers

- **Core functionality**: Place in `core/`
- **Testing functionality**: Place in `testing/`
- **Utility functionality**: Place in `utils/`
- **New categories**: Create new subdirectories as needed

## Benefits

- **Maintainability**: Clear organization makes code easier to maintain
- **Readability**: Developers can quickly find relevant headers
- **Scalability**: Structure supports project growth
- **Professional**: Follows industry best practices for C project organization
