#!/bin/bash

make re

MINISHELL="./minishell"
TEST_DIR="./test_jojo/tests"
RESULTS_DIR="./test_jojo/results"
LOG_DIR="./test_jojo/logs"
RESET="\033[0m"

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
	local test_file="$TEST_DIR/simple.sh"
	local test_name=$(basename "$test_file")
	local output_dir=./log/$test_name
	local output_standard_file="$output_dir/minishell.log"
	
	mkdir -p $output_dir

	$LEAKS_CMD $MINISHELL $test_file > $output_standard_file
}

run_test

LEAKS_CMD="valgrind"
LEAKS_CMD+=" --leak-check=full"
LEAKS_CMD+=" --track-fds=yes"
LEAKS_CMD+=" --show-leak-kinds=all"
LEAKS_CMD+=" --track-origins=yes"
LEAKS_CMD+=" --log-file=log/leaks.log"
LEAKS_CMD+=" --trace-children=yes"