#!/bin/bash

# cd src
gcc src/main.c src/parsing/*.c utils/*.c -o minishell
./minishell
