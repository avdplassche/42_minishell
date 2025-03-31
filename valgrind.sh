#!/bin/bash

mkdir log
make re
make clean
valgrind --leak-check=full --show-leak-kinds=all ./minishell test/TESTMODE_WILDCARDS 17

