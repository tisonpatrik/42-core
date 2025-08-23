# Push Swap Lab - Smoke Testing & JSON Generation

## 🎯 **What it is**

This lab project serves for **partial smoke testing** of functions from the push_swap project. The main goal is to generate JSON files with test results that can then be used as basic unit tests in another project.

## 🚀 **Purpose**

### **Main goals:**
- **Smoke test** chunk utility functions from push_swap
- **Generate JSON files** with test data
- **Validate** basic functionality before integration
- **Create test datasets** for further use

### **Why it exists:**
- Push_swap has complex chunk-based algorithms
- We need to verify that basic functions work
- JSON outputs can be used elsewhere as unit tests
- Quick testing without full push_swap complexity

## 🏗️ **Structure**

```
lab/
├── src/
│   ├── utils/                    # Utility functions
│   │   ├── generator.c          # Generate test data
│   │   ├── json_utils.c         # JSON export
│   │   ├── file_utils.c         # File I/O
│   │   └── stack_utils.c        # Stack management
│   ├── tasks/                   # Test logic
│   │   └── chunk_utils_tasks/   # Chunk tests
│   │       ├── loc_to_stack/            # Test loc_to_stack
│   │       │   ├── loc_to_stack_test_utils.c
│   │       │   └── run_loc_to_stack_tests.c
│   │       ├── chunk_max_value/         # Test chunk_max_value
│   │       │   ├── chunk_max_value_test_utils.c
│   │       │   └── run_chunk_max_value_tests.c
│   │       └── chunk_value/             # Test chunk_value
│   │           ├── chunk_value_test_utils.c
│   │           └── run_chunk_value_tests.c
│   └── main.c                   # Test runner
├── include/                     # Header files
├── libs/                        # Libraries
│   ├── push_swap/              # Push swap source
│   └── cJSON/                  # JSON library
├── data/                       # Generated JSON files
└── bin/                        # Compiled files
```

## 🔧 **What we test**

### **Chunk utility functions from push_swap:**
- `chunk_value()` - Value at specific position in chunk
- `chunk_max_value()` - Maximum in chunk
- `loc_to_stack()` - Convert location to stack reference

### **Test scenarios:**
- Different chunk sizes (3, 4, 5 elements)
- Different locations (TOP_A, BOTTOM_A, TOP_B, BOTTOM_B)
- Different offsets in chunks

## 📊 **Output**

### **JSON files in `data/chunk_utils/`:**
- `loc_to_stack.json` - Results of loc_to_stack tests
- `chunk_max_value.json` - Results of chunk_max_value tests  
- `chunk_value.json` - Results of chunk_value tests

### **JSON content:**
- Input arrays (test data)
- Expected vs. actual results
- Test parameters (size, location, offset)
- Metadata for each test

## 🚀 **Usage**

### **Build:**
```bash
make        # Build and run tests (default)
make build  # Only compile
make clean  # Clean
make re     # Rebuild and run
```

### **Run tests:**
```bash
make        # Build and run all tests (recommended)
make build  # Only build without running
./bin/main  # Run tests manually (if already built)
```

### **Makefile targets:**
- `make` or `make all` - Build and run tests (default)
- `make build` - Only compile without running
- `make clean` - Clean compiled files
- `make re` - Clean, recompile and run tests

### **Results:**
Tests run automatically and generate JSON files in the `data/chunk_utils/` directory.

## 🔍 **How it works**

### **Test flow:**
1. **Generate test data** - Random arrays of different sizes
2. **Run chunk functions** - Call push_swap functions with test data
3. **Collect results** - Store input/output in test cases
4. **JSON export** - Serialize to structured JSON files

### **Test framework:**
- `create_test_data()` - Creates test stacks
- `create_test_case()` - Creates individual test case
- `add_test_to_batch()` - Adds test to batch
- `save_test_batch_to_json()` - Exports to JSON

## 📈 **What it gives us**

### **For this lab:**
- ✅ Verification that chunk functions work
- ✅ Generation of test datasets
- ✅ Quick testing without full push_swap

### **For other projects:**
- **JSON test data** for unit tests
- **Validated input/output** pairs
- **Test scenarios** for chunk algorithms
- **Reference data** for debugging

## 🧪 **Testing strategy**

### **Test types:**
- **Smoke tests** - Basic functionality
- **Edge cases** - Empty, small, large arrays
- **Different configurations** - Different sizes and locations

### **Test data:**
- Random arrays (5-100 elements)
- Different chunk sizes (3-5 elements)
- All locations (TOP_A, BOTTOM_A, TOP_B, BOTTOM_B)

## 🔧 **Development**

### **Adding new test:**
1. Create test logic in `tasks/`
2. Use utility functions from `utils/`
3. Export results to JSON
4. Run `make && ./bin/main`

### **Modifying utility functions:**
1. Edit file in `utils/`
2. Ensure function has single responsibility
3. Test with existing tests
4. Run `make clean && make`

## 📋 **Current status**

### **✅ Done:**
- All chunk utility functions tested
- JSON export works
- Test framework is complete
- Code is clean and optimized

### **🎯 Goal:**
Generate quality JSON test data that we can use as unit tests in another project for validating push_swap chunk algorithms.

---

**💡 This lab is a tool for quick testing and generating test data. It's not a full push_swap project, but its testing foundation.**
