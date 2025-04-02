#!/bin/bash
# enter the tests below for the specified command

ls -l
ls | wc -l
echo "Hello World" | tr ' ' '\n' | sort | uniq -c
ls | nonexistentcommand | wc -l
ls | ./sigsegv | wc -l
echo 12345 | ./conduit --count 2 | ./conduit --count 3 | ./conduit --count 2 | wc -l
sleep 3 | sleep 3 | sleep 3

