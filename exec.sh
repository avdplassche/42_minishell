#!/bin/bash


make re
make clean
# cc src/main.c src/print.c src/init_mini.c src/parsing/*.c utils/*.c -l readline -o minishell
./minishell test/TESTMODE_ECHO_DOLLAR 26
# cc -Wall -Wextra -Werror src/main.c src/print.c src/init_mini.c src/parsing/*.c utils/*.c -l readline -o minishell
# ./minishell
