#!/bin/bash

# cd src
gcc src/*.c utils/*.c gnl/*.c -o minishell
./minishell
