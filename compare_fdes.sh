#!/bin/bash

rm test/comp1 test/comp2
./minishell test/TESTMODE_DOLLAR 12 > test/comp1
# ./minishell test/TESTMODE_DOLLAR_QUOTES 26 > test/comp1
make re
make clean
# ./minishell test/TESTMODE_DOLLAR_QUOTES 26
# ./minishell test/TESTMODE_MULTIPLE_CMD 14
./minishell test/TESTMODE_DOLLAR 12 > test/comp2
# ./minishell test/TESTMODE_DOLLAR_QUOTES 26 > test/comp2
# diff test/comp1 test/comp2
./test/compare_fd test/comp1 test/comp2
