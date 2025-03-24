#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m"
RESET="\033[0m"

MINISHELL="./minishell"
TEST_DIR="./test_jojo/tests"
RESULTS_DIR="./test_jojo/results"
LOG_DIR="./test_jojo/logs"

mkdir -p "$TEST_DIR" "$RESULTS_DIR" "$LOG_DIR"

info(){
	echo -e "${CYAN}$1${RESET}"
}

success(){
	echo -e "${GREEN}$1${RESET}"
}

error(){
	echo -e "${RED}$1${RESET}"
}

warning(){
	echo -e "${YELLOW}$1${RESET}"
}

print_header() {
	info "\n───────────────────────────────────────────────────"
	info "			$1"
	info "───────────────────────────────────────────────────\n"
}

run_test(){
	local test_file="$1"
	local test_name=$(basename "$test_file" .sh)
	local pass_count=0

	info "TESTING: $test_name"
	
	mkdir -p "$LOG_DIR/$test_name"
	local commands_file="$LOG_DIR/$test_name/commands.txt"
	grep -v '^#' "$test_file" | grep -v '^$' > "$commands_file"
	
	local mini_log="$LOG_DIR/$test_name/mini.log"
	local mini_err="$LOG_DIR/$test_name/mini_error.log"
	local bash_log="$LOG_DIR/$test_name/bash.log"
	local bash_err="$LOG_DIR/$test_name/bash_error.log"
	
	info "Running tests..."
	"$MINISHELL" "$commands_file" $(wc -l < "$commands_file") > "$mini_log" 2> "$mini_err"
	bash "$test_file" > "$bash_log" 2> "$bash_err"
	
	info "\n===== CD COMMAND TESTS ====="
	
	# Test 1: Basic directory change
	echo -e "\n${CYAN}Test 1: Change to a relative directory${RESET}"
	if grep -q "src/execution" "$mini_log"; then
		success "RESULT: OK - Directory change detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No directory change detected"
	fi
	
	# Test 2: CD to home with no arguments
	echo -e "\n${CYAN}Test 2: CD to home directory with no args${RESET}"
	if grep -q "HOME" "$mini_log"; then
		success "RESULT: OK - Home directory change detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No home directory change detected"
	fi
	
	# Test 3: Navigate with relative path
	echo -e "\n${CYAN}Test 3: Navigate with relative path${RESET}"
	if grep -q "\.\." "$mini_log"; then
		success "RESULT: OK - Parent directory navigation detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No parent directory navigation detected"
	fi
	
	# Test 4: CD to nonexistent directory
	echo -e "\n${CYAN}Test 4: CD to nonexistent directory${RESET}"
	if grep -q "nonexistent_directory_12345" "$mini_err" || grep -q "No such file" "$mini_log"; then
		success "RESULT: OK - Error for nonexistent directory detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No error for nonexistent directory"
	fi
	
	# Test 5: CD to a file (not a directory)
	echo -e "\n${CYAN}Test 5: CD to a file (not a directory)${RESET}"
	if grep -q "test_file_for_cd" "$mini_err" || grep -q "Not a directory" "$mini_log"; then
		success "RESULT: OK - Error for file as directory detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No error for file as directory"
	fi
	
	# Test 6: CD with . (current directory)
	echo -e "\n${CYAN}Test 6: CD with . (current directory)${RESET}"
	if grep -q "cd \." "$mini_log"; then
		success "RESULT: OK - Current directory navigation detected"
		((pass_count++))
	else
		error "RESULT: FAILED - Current directory navigation not detected"
	fi
	
	# Test 7: CD with multiple arguments
	echo -e "\n${CYAN}Test 7: CD with multiple arguments${RESET}"
	if grep -q "too many arguments" "$mini_log" || grep -q "too many arguments" "$mini_err"; then
		success "RESULT: OK - Multiple arguments error detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No error for multiple arguments"
	fi
	
	# Test 8: CD with environment variables
	echo -e "\n${CYAN}Test 8: CD with environment variables${RESET}"
	if grep -q "HOME" "$mini_log"; then
		success "RESULT: OK - Environment variable expansion detected"
		((pass_count++))
	else
		error "RESULT: FAILED - No environment variable expansion"
	fi
	
	# Test 9: CD with path containing spaces
	echo -e "\n${CYAN}Test 9: CD with path containing spaces${RESET}"
	if grep -q "test directory with spaces" "$mini_log"; then
		success "RESULT: OK - Path with spaces handled correctly"
		((pass_count++))
	else
		error "RESULT: FAILED - Path with spaces not handled"
	fi
	
	# Show error output if any
	if [ -s "$mini_err" ]; then
		echo -e "\n${YELLOW}Minishell Error Output:${RESET}"
		cat "$mini_err"
	fi
	
	# Overall result
	echo -e "\n${CYAN}Test Summary${RESET}"
	local output=$(grep -c "RESULT: OK" <<< "$(cat "$mini_log")")
	local total_tests=9
	echo -e "Passed: $pass_count/$total_tests tests"
	
	if [ "$pass_count" -eq "$total_tests" ]; then
		success "All tests passed!"
		return 0
	else
		error "Some tests failed"
		return 1
	fi
}

check_leaks() {
	local test_file="$1"
	local test_name=$(basename "$test_file" .sh)
	local leaks_log="$LOG_DIR/$test_name/leaks.log"
	
	local commands_file="$LOG_DIR/$test_name/commands.txt"
	if [ ! -f "$commands_file" ]; then
		grep -v '^#' "$test_file" | grep -v '^$' > "$commands_file"
	fi
	
	local cmd_count=1
	
	info "Checking for memory leaks..."

	if [ $(uname) = "Linux" ]; then
		valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all \
				 --track-origins=yes --log-file="$leaks_log" \
				 "$MINISHELL" "$commands_file" "$cmd_count" >/dev/null 2>&1
		
		local leaks_detected=$(cat "$leaks_log" | grep "ERROR SUMMARY" | awk '{printf "%s", $4}' | tr -d "0")
		if [ -z "$leaks_detected" ]; then
			success "LEAKS\t\tOK"
			return 0
		else
			error "LEAKS\t\tERROR $leaks_log"
			return 1
		fi
	elif [ $(uname) = "Darwin" ]; then
		if command -v leaks >/dev/null; then
			info "Running minishell with leak checker..."
			"$MINISHELL" "$commands_file" "$cmd_count" >/dev/null 2>&1 &
			local pid=$!
			sleep 1
			leaks -quiet "$pid" > "$leaks_log" 2>&1
			kill -9 $pid >/dev/null 2>&1
			
			if grep -q "0 leaks" "$leaks_log"; then
				success "LEAKS\t\tOK"
				return 0
			else
				error "LEAKS\t\tERROR\t$leaks_log"
				return 1
			fi
		else
			warning "LEAKS\t\tSKIPPED (leaks command not available)"
			return 0
		fi
	else
		warning "LEAKS\t\tSKIPPED (unsupported OS)"
		return 0
	fi
}

create_test(){
	local test_name="$1"
	local file_path="$TEST_DIR/test_${test_name}.sh"

	if [ -f "$file_path" ]; then
		error "Test file already exists: $file_path"
		return 1
	fi

	cat > "$file_path" << EOF
#!/bin/bash
# Test: $test_name
# Created: $(date)
# Description: Tests the $test_name builtin command functionality

# Test basic $test_name
echo "Testing $test_name functionality..."
# Add more commands as needed
EOF
	
	chmod +x "$file_path"  # Make it executable
	success "Created test file: $file_path"
	echo "You can now edit it to add your test commands."
}

list_tests() {
	print_header "Available Test Files"
	
	if ls "$TEST_DIR"/test_*.sh &> /dev/null; then
		local total=0
		for file in "$TEST_DIR"/test_*.sh; do
			local test_name=$(basename "$file" .sh | sed 's/^test_//')
			echo -e "${BLUE}$test_name${RESET}"
			# Extract description if it exists
			local description=$(grep "# Description:" "$file" | sed 's/# Description: //')
			if [ -n "$description" ]; then
				echo "  $description"
			fi
			total=$((total+1))
		done
		echo -e "\nTotal test files: $total"
	else
		warning "No test files found."
		echo "Create a new test with: $0 create <test_name>"
	fi
}

if [ "$1" = "create" ] && [ -n "$2" ]; then
	create_test "$2"
elif [ "$1" = "run" ] && [ -n "$2" ]; then
	if [ -f "$TEST_DIR/test_$2.sh" ]; then
		run_test "$TEST_DIR/test_$2.sh"
	else
		error "Test not found: $2"
	fi
elif [ "$1" = "leaks" ] && [ -n "$2" ]; then
	if [ -f "$TEST_DIR/test_$2.sh" ]; then
		check_leaks "$TEST_DIR/test_$2.sh"
	else
		error "Test not found: $2"
	fi
elif [ "$1" = "list" ]; then
	list_tests
else
	echo "Usage: $0 {create|run|leaks|list} [test_name]"
	echo "  create <test_name>: Create a new test file"
	echo "  run <test_name>: Run a specific test"
	echo "  leaks <test_name>: Check for memory leaks in a test"
	echo "  list: List all available tests"
fi