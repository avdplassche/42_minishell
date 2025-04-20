#!/bin/bash

make re
make clean

valgrind --tool=memcheck \
  --track-origins=yes \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-fds=yes \
  --suppressions=valgrind.supp \
  --log-file=log/valgrind.log \
  ./minishell