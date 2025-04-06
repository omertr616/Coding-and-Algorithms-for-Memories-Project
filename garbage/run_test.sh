#!/bin/bash

# Files containing the different implementations of `scs`
FILES=("regular_dp.cpp" "BFS_0-1_2strings.cpp" "BFS_0-1_3strings+not_works.cpp" "BFS_0-1_kstrings")

# Path to the test cases
TEST_DIR="tests"

# Get a list of all input files
TESTS=$(ls ${TEST_DIR}/*.in)

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Loop through each file (each version of scs)
for file in "${FILES[@]}"; do
    # Extract the base name (e.g., scs1 from scs1.cpp)
    NAME=$(basename "$file" .cpp)
    echo "Testing ${NAME}..."

    # Compile the current file and link it with test.cpp
    g++ test.cpp "$file" -o "test_exec"
    if [ $? -ne 0 ]; then
        echo -e "${RED} Compilation failed for $file${NC}"
        continue
    fi

    # Loop through all the test cases
    for input in $TESTS; do
        # Get the base name for input and output files (e.g., 1)
        base=$(basename "$input" .in)
        expected="${TEST_DIR}/${base}.out"
        output="temp.out"

        # Time the execution of the test case
        START=$(date +%s%N)
        ./test_exec < "$input" > "$output"
        END=$(date +%s%N)
        TIME=$(( (END - START)/1000000 )) # in ms

        # Compare the output with the expected result
        if diff -q "$output" "$expected" > /dev/null; then
            echo -e "${GREEN} Test $base passed [${TIME}ms]${NC}"
        else
            echo -e "${RED} Test $base failed [${TIME}ms]${NC}"
            echo "Expected:"
            cat "$expected"
            echo "Got:"
            cat "$output"
        fi

        # Clean up the temporary output file
        rm "$output"
    done

    echo ""
done