#!/bin/bash

make re
make clean

env -i \                # Start with empty environment
valgrind --tool=memcheck \
  --track-origins=yes \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-fds=yes \
  --suppressions=valgrind.supp \
  --log-file=log/valgrind.log \
  ./minishell