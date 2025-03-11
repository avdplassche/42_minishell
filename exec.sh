#!/bin/bash


make re
make clean
# ./minishell test/TESTMODE_DOLLAR_QUOTES 26
# ./minishell test/TESTMODE_MULTIPLE_CMD 1
./minishell test/TESTMODE_MULTIPLE_REDIR 3

