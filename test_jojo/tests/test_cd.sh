#!/bin/bash
# Test: cd
# Created: $(date)
# Description: Tests CD command functionality

# Test 1: Basic directory change
cd src/execution
pwd

# Test 2: CD to home with no arguments
cd
pwd

# Test 3: Navigate with relative path
cd ..
pwd

# Test 4: Try a non-existent directory
cd nonexistent_directory_12345
pwd

# Test 5: Create a test file and try to CD to it
touch test_file_for_cd
cd test_file_for_cd
pwd

# Test 6: CD with current directory
cd .
pwd

# Test 7: CD with multiple arguments
cd dir1 dir2
pwd

# Test 8: CD with environment variables
cd $HOME
pwd

# Test 9: CD with spaces in path
mkdir -p "test directory with spaces"
cd "test directory with spaces"
pwd
