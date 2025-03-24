#!/bin/bash
# Create a troubleshooting test script

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
YELLOW="\033[0;33m"
RESET="\033[0m"

MINISHELL="./minishell"
TEST_DIR="./tests"
RESULTS_DIR="./results"

mkdir -p "$TEST_DIR" "$RESULTS_DIR"

debug_test() {
    local test_name="$1"
    local test_file="$TEST_DIR/${test_name}.commands"
    
    echo -e "${BLUE}Debugging test: ${test_name}${RESET}"
    
    # Read commands line by line and test individually
    while IFS= read -r cmd; do
        # Skip comments and empty lines
        [[ "$cmd" =~ ^#.*$ || -z "$cmd" ]] && continue
        
        echo -e "${YELLOW}Testing command: ${cmd}${RESET}"
        
        # Run single command to isolate issues
        echo "$cmd" > /tmp/single_command.txt
        "$MINISHELL" "/tmp/single_command.txt" "1" 
        
        echo -e "${BLUE}Exit status: $?${RESET}"
        echo "----------------------------------------"
    done < "$test_file"
    
    rm -f /tmp/single_command.txt
}

# Run in debug mode
debug_test "basic_commands"