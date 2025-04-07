#!/bin/bash
# enter the tests below for the specified command
echo "hello world" | grep hello
ls -l | grep .txt
cat /etc/passwd | head -5
echo "line1\nline2\nline3" | wc -l
ls -la | sort
ls | grep "." | wc -l
cat /etc/passwd | grep sh$ | sort
echo "hello\nworld\nhello\ntest" | sort | uniq
ps aux | grep bash | grep -v grep
cat /etc/passwd | cut -d: -f1,7 | grep bash
ls -l | grep "." > output.txt
ls -l | tee output.txt | grep Apr
cat < /etc/passwd | grep root