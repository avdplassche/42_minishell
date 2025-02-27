#!/bin/bash

# cd src
# gcc -Wall -Wextra -Werror src/main.c src/print.c src/parsing/*.c utils/*.c -o minishell
cc src/main.c src/print.c src/init_mini.c src/parsing/*.c utils/*.c -l readline -o minishell
./minishell
