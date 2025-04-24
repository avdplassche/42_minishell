#!/bin/bash

SRC_DIR="./src"
LOG_DIR="log"
PROG="./minishell"
LEAKS_CHECK=true

make re

if [ $(uname) = "Linux" ]; then
	LEAKS_CMD="valgrind"
	LEAKS_CMD+=" --leak-check=full"
	#LEAKS_CMD+=" --track-fds=yes"
	LEAKS_CMD+=" --show-leak-kinds=all"
	LEAKS_CMD+=" --track-origins=yes"
	LEAKS_CMD+=" --log-file=log/leaks.log"
	#LEAKS_CMD+=" --trace-children=yes"
else
	LEAKS_CMD="leaks -quiet --atExit --"
	LEAKS_CMD=""
fi

watch() {
	STATE_A=""
	PROG_PID=""
	TEST_DIR="final_test"
	if [[ $2 != "" ]] ; then
		TEST_DIR=$2
	fi

	while [[ true ]]
	do
		STATE_B=$(get_state)
		if [[ $STATE_A != $STATE_B ]]; then
			STATE_A=$STATE_B
			clear
			info "───────── $(date) ─────────"
			norminette_pretty "$SRC_DIR lib"
			rm -f "$PROG"
			make
			if [ ! -f "$PROG" ]; then
				error "COMPILATION\ERROR"
			else
				success "COMPILATION\tOK\n"
				info "───────────────────────────────────────────────────\n"

				if [[ $1 != "" ]] ; then
					run_test "$TEST_DIR/$1.sh"
				else
					for TEST_FILE in $TEST_DIR/*.sh ; do 
						run_test "$TEST_FILE"
					done
				fi
			fi
		fi
		sleep 0.1
	done
}

run_test() {
	local TEST_FILE=$1
	local COMMAND="$PROG $TEST_FILE"
	if [[ ! -f $TEST_FILE ]] ; then
		error "404 NOT FOUND\t$TEST_FILE\n"
		exit 1
	fi
	if $LEAKS_CHECK ; then
		COMMAND="$LEAKS_CMD $COMMAND"
	fi
	local TEST_NAME="$(basename $TEST_FILE .sh)"
	mkdir -p "$LOG_DIR/$TEST_NAME"
	local LOG_FILE="$LOG_DIR/$TEST_NAME/mini.log"
	local LOG_FILE_ERR="$LOG_DIR/$TEST_NAME/mini_error.log"
	$COMMAND > "$LOG_FILE" 2> "$LOG_FILE_ERR"
	info "$TEST_NAME \t$TEST_FILE"
	echo -e "mini\t\t$LOG_FILE\t\t$LOG_FILE_ERR"
	get_diff $TEST_FILE $LOG_FILE $LOG_FILE_ERR
	check_leaks
	echo
}
 
get_diff() {
	TEST_FILE=$1
	LOG_FILE_MINI=$2
	LOG_FILE_MINI_ERR=$3
	local TEST_NAME="$(basename $TEST_FILE .sh)"
	local LOG_FILE="$LOG_DIR/$TEST_NAME/bash.log"
	local LOG_FILE_ERR="$LOG_DIR/$TEST_NAME/bash_error.log"
	local DIFF_FILE="$LOG_DIR/$TEST_NAME/diff.diff"
	local DIFF_FILE_ERR="$LOG_DIR/$TEST_NAME/diff_error.diff"
	bash $TEST_FILE > $LOG_FILE 2> $LOG_FILE_ERR
	sed -i -r "s/ line [0-9]+://" $LOG_FILE_ERR
	local DIFF=$(diff -U 1 $LOG_FILE $LOG_FILE_MINI)
	local DIFF_ERR=$(diff -U 1 $LOG_FILE_ERR $LOG_FILE_MINI_ERR)
	echo "$DIFF" > "$DIFF_FILE"
	echo "$DIFF_ERR" > "$DIFF_FILE_ERR"
	echo -e "bash\t\t$LOG_FILE\t$LOG_FILE_ERR"
	if [[ $DIFF == "" ]] ; then
		success "DIFF\t\tOK"
	else
		error "DIFF\t\tERROR\t$DIFF_FILE"
	fi
	if [[ $DIFF_ERR == "" ]] ; then
		success "DIFF_ERR\tOK"
	else
		warning "DIFF_ERR\tWARNING\t$DIFF_FILE_ERR"
	fi
}

get_state() {
	if [[ $(uname) == "Linux" ]];  then
		MD5="md5sum"
	else
		MD5="md5"
	fi
	SRC_STATE=$(find -L $SRC_DIR -type f -name "*.[ch]" -exec $MD5 {} \;)
	TEST_STATE=$(find -L ./final_test -type f -name "*.sh" -exec $MD5 {} \;)
	echo "$SRC_STATE $TEST_STATE"
}

norminette_pretty() {
	NORM_ERROR=$(sed -e '/.*: OK!/d' <(norminette $1))
	if [[ $NORM_ERROR == "" ]] ; then
		success "\nNORMINETTE\tOK\n"
	else
		error "\nNORMINETTE\tERROR"
		AWK_SCRIPT='{
			if ($2 == "Error!") {
				filename = $1;
				sub(/^\.\//, "", filename);
				print "";
			} else if (filename != "./src/debug.h:") {
				printf "[%s%d:%d]\t", filename, $4, $6;
				for(i = 7; i <= NF; i++) {
					printf "%s ", $i;
				};
				printf "\n";
			}
		}'
		echo "$NORM_ERROR" | awk "$AWK_SCRIPT"
		echo -e "\n"
	fi
}

check_leaks() {
	LEAKS_DETECTED=$(cat ./log/leaks.log | grep "ERROR SUMMARY" | awk '{printf "%s", $4}' | tr -d "0")
	if [[ $LEAKS_DETECTED == "" ]] ; then
		success "LEAKS\t\tOK"
	else
		error "LEAKS\t\tERROR\t./log/leaks.log"
	fi
}

info() {
	echo -e "\033[36m$1\033[0m"
}
error() {
	echo -e "\033[31m$1\033[0m"
}
success() {
	echo -e "\033[32m$1\033[0m"
}
warning() {
	echo -e "\033[33m$1\033[0m"
}

watch "$@"