#!/bin/bash

# cd src
# gcc -Wall -Wextra -Werror src/main.c src/print.c src/parsing/*.c utils/*.c -o minishell
gcc src/main.c src/print.c src/parsing/*.c utils/*.c -l readline -o minishell
./minishell
