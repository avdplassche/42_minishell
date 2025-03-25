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
LEAKS_CMD+=" --log-file=log/leaks.log"
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
	local TEST_FILE="$1"
	local TEST_NAME=$(basename "$TEST_FILE")
	local OUTPUT_MINI_LOG="$LOG_DIR/minishell.log"
	local OUTPUT_MINI_ERR_LOG="$LOG_DIR/minishell_error.log"
	local BASH_LOG="$LOG_DIR/bash.log"
	local BASH_ERR="$LOG_DIR/BASH_ERR.log"
	local DIFF_STDOUT="$RESULTS_DIR/${TEST_NAME}_stdout_diff.txt"
	local DIFF_STDERR="$RESULTS_DIR/${TEST_NAME}_stderr_diff.txt"
	
	info "Testing $TEST_NAME"
	
	mkdir -p "$LOG_DIR" "$RESULTS_DIR"

	info "Running tests in Minishell and bash..."
	$LEAKS_CMD $MINISHELL $TEST_FILE > $OUTPUT_MINI_LOG 2> $OUTPUT_MINI_ERR_LOG
	bash $TEST_FILE > "$BASH_LOG" 2> "$BASH_ERR"

	info "Comparing outputs..."

	diff -u "$OUTPUT_MINI_LOG" "$BASH_LOG" > "$DIFF_STDOUT"
	diff -u "$OUTPUT_MINI_ERR_LOG" "$BASH_ERR" > "$DIFF_STDERR"
		if [ -s "$DIFF_STDOUT" ] || [ -s "$DIFF_STDERR" ]; then
		error "Test failed: Differences found"
		[ -s "$DIFF_STDOUT" ] && warning "Standard output differences:" && cat "$DIFF_STDOUT"
		[ -s "$DIFF_STDERR" ] && warning "Standard error differences:" && cat "$DIFF_STDERR"
		return 1
	else
		success "Test passed: No differences found"
		return 0
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

if [ "$1" = "test" ] && [ -n "$2" ]; then
	run_command_test "$2"
else
	if [ -f "$1" ]; then
		run_TEST_FILE "$1"
	else
		error "Usage: $0 [test COMMAND] or $0 [TEST_FILE]"
		exit 1
	fi
fi
