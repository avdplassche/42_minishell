export REDIR=">"
echo YO $REDIR log/hard/a_out.txt
export OUT_FILE="out.txt"
echo HAHA $REDIR log/hard/b_$OUT_FILE
echo HAHA > log/hard/c_$OUT_FILE
grep . log/redirect/b_$OUT_FILE
grep . log/redirect/c_$OUT_FILE
export FOO="BAR" && echo "$FOO"

export VAR=TEST
export $VAR=YOLO
echo $TEST

export VAR=TEST
export $VAR=ls
$TEST

export VAR='$VAR'
echo $VAR

export VAR="$HOME"
echo "$VAR/dev"

export VAR=PROUT | echo $VAR
echo $VARtodo