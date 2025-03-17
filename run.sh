#!/bin/bash

mkdir log
make re
make clean
./minishell test/TESTMODE_DOLLAR_QUOTES 29
# ./minishell test/TESTMODE_MULTIPLE_CMD 14
# ./minishell test/TESTMODE_MULTIPLE_REDIR 15

