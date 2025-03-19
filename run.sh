#!/bin/bash

mkdir log
make re
make clean
# ./minishell test/TESTMODE_DOLLAR 14
# ./minishell test/TESTMODE_QUOTES 14
# ./minishell test/TESTMODE_MULTIPLE_CMD 14
./minishell test/TESTMODE_MULTIPLE_REDIR 15
# ./minishell test/TESTMODE_ECHOTYPE 4

