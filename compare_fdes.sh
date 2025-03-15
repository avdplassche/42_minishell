#!/bin/bash


make re
make clean
# ./minishell test/TESTMODE_DOLLAR_QUOTES 26
# ./minishell test/TESTMODE_MULTIPLE_CMD 14
./minishell test/TESTMODE_MULTIPLE_REDIR 11 > test/comp2
diff
# ./test/compare_fd test/comp1 test/comp2
