#!/bin/bash

mkdir log
make re
make clean

# ./minishell test/TESTMODE_WILDCARDS 19
# ./minishell test/TESTMODE_DOLLAR 19
# ./minishell test/TESTMODE_QUOTES 16
# ./minishell test/TESTMODE_MULTIPLE_CMD 14
# ./minishell test/TESTMODE_MULTIPLE_REDIR 16
# ./minishell test/TESTMODE_INVALID_CMD 2
./minishell test/TESTMODE_BUILTINS 8
# ./minishell test/TESTMODE_DOLLAR_WILDCARDS 3
