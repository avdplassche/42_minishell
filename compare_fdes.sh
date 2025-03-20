#!/bin/bash

rm test/comp1 test/comp2
./minishell test/TESTMODE_DOLLAR 12
cat "log/debug.log" > test/comp1.log
make re
make clean
./minishell test/TESTMODE_DOLLAR 12
cat "log/debug.log" > test/comp2.log
./test/compare_fd test/comp1.log test/comp2.log
