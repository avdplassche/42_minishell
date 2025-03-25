#!/bin/bash

MINISHELL="./minishell"
TEST_DIR="./test_jojo/tests"
RESULTS_DIR="./test_jojo/results"
LOG_DIR="./test_jojo/logs"
RESET="\033[0m"

LEAKS_CMD="valgrind"
LEAKS_CMD+=" --leak-check=full"
LEAKS_CMD+=" --track-fds=yes"
LEAKS_CMD+=" --show-leak-kinds=all"
LEAKS_CMD+=" --track-origins=yes"
LEAKS_CMD+=" --log-file=./test_jojo/logs/leaks.log"
LEAKS_CMD+=" --trace-children=yes"

mkdir -p "$TEST_DIR" "$RESULTS_DIR" "$LOG_DIR"

info(){
	echo -e "\033[0;36m$1${RESET}"
}

success(){
	echo -e "\033[0;32m$1${RESET}"
}

error(){
	echo -e "\033[0;31m$1${RESET}"
}

warning(){
	echo -e "\033[0;33m$1${RESET}"
}

run_test() {
    local test_file="$1"
    local test_name=$(basename "$test_file")
    local output_standard_file="$LOG_DIR/minishell.log"
    local erroroutput_standard_file="$LOG_DIR/minishell_error.log"
    local bash_log="$LOG_DIR/bash.log"
    local bash_err="$LOG_DIR/bash_err.log"
    local diff_stdout="$RESULTS_DIR/${test_name}_stdout_diff.txt"
    local diff_stderr="$RESULTS_DIR/${test_name}_stderr_diff.txt"
    
    info "Testing $test_name"
    
    mkdir -p "$LOG_DIR" "$RESULTS_DIR"

    info "Running tests in Minishell and bash..."
    $LEAKS_CMD $MINISHELL $test_file > $output_standard_file 2> $erroroutput_standard_file
    bash $test_file > "$bash_log" 2> "$bash_err"
    
    sed -i -r "s/ line [0-9]+://" "$bash_err"

    info "Comparing outputs..."

    local stdout_diff=$(diff -U 1 "$bash_log" "$output_standard_file")
    local stderr_diff=$(diff -U 1 "$bash_err" "$erroroutput_standard_file")
    
    echo "$stdout_diff" > "$diff_stdout"
    echo "$stderr_diff" > "$diff_stderr"

    if [[ -z "$stdout_diff" ]]; then
        success "✓ Standard output matches"
    else
        error "STDOUT DIFFERENCES DETECTED:"
        echo ""
        echo "=== MINISHELL OUTPUT ==="
        cat "$output_standard_file"
        echo ""
        echo "=== BASH OUTPUT ==="
        cat "$bash_log"
        echo ""
    fi
    
    if [[ -z "$stderr_diff" ]]; then
        success "✓ Standard error output matches"
    else
        warning "STDERR DIFFERENCES DETECTED (Warning only):"
        echo ""
        echo "=== MINISHELL ERROR OUTPUT ==="
        cat "$erroroutput_standard_file"
        echo ""
        echo "=== BASH ERROR OUTPUT (normalized) ==="
        cat "$bash_err"
        echo ""
    fi

    info "Test commands executed:"
    cat "$test_file" | grep -v "^#" | sed '/^$/d' | sed 's/^/  /'
    
    if [[ -z "$stdout_diff" ]]; then
        success "✓ Test passed: Standard output matches"
        return 0
    else
        error "✗ Test failed: Differences found in standard output"
        return 1
    fi
}

run_command_test() {
	local command="$1"
	local TEST_FILE="$TEST_DIR/${command}_test.sh"
	
	if [ ! -f "$TEST_FILE" ]; then
		info "Creating test file for $command..."
		case "$command" in
			"cd")
				cat > "$TEST_FILE" << 'EOF'
#!/bin/bash
# enter the tests below for the specified command
EOF
				;;
			"echo")
				;;
			*)
				error "No template available for $command"
				return 1
				;;
		esac
		chmod +x "$TEST_FILE"
	fi
	

	run_test "$TEST_FILE"
}

make re

run_command_test $@
