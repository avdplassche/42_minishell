#!/bin/bash

mkdir log
make re
make clean
valgrind --leak-check=full --show-leak-kinds=all --log-file=log/valgrind.log ./minishell test/TESTMODE_DOLLAR 2
# valgrind --leak-check=full --show-leak-kinds=all --log-file=log/valgrind.log ./minishell test/TESTMODE_WILDCARDS 19