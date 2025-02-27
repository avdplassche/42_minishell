#!/bin/bash



cc src/main.c src/print.c src/init_mini.c src/parsing/*.c utils/*.c -l readline -o minishell
./minishell TESTMODE_FILE 8
