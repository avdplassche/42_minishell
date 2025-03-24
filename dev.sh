#!/bin/bash

make re
LEAKS_CMD="valgrind"
LEAKS_CMD+=" --leak-check=full"
LEAKS_CMD+=" --track-fds=yes"
LEAKS_CMD+=" --show-leak-kinds=all"
LEAKS_CMD+=" --track-origins=yes"
LEAKS_CMD+=" --log-file=log/leaks.log"
LEAKS_CMD+=" --trace-children=yes"

$LEAKS_CMD ./minishell ./test_jojo/tests/simple.sh