#!/bin/bash

mkdir log
make re
make clean
valgrind --leak-check=full --show-leak-kinds=all --log-file=log/valgrind.log ./minishell test/TESTMODE_INVALID_CMD 15

