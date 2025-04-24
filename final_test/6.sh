# # **************************************************************************** #
# #                                  CORRECTION                                  #
# # **************************************************************************** #

rm -rf ./tmp
mkdir -p ./tmp
cd ./tmp

mkdir tmp_path_test1 tmp_path_test2
echo '#include <unistd.h>' > tmp_path_test1/test1.c
echo 'int main(){write(1, "1\n", 2);}' >> tmp_path_test1/test1.c
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
echo '#include <unistd.h>' > tmp_path_test2/test2.c
echo 'int main(){write(1, "2\n", 2);}' >> tmp_path_test2/test2.c
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
export PATH=tmp_path_test1:tmp_path_test2
a.out
export PATH=tmp_path_test2:tmp_path_test1
a.out
/bin/chmod -x tmp_path_test2/a.out
a.out
echo $?
cd ..
/bin/rm -rf ./tmp

/bin/echo
/bin/echo 1
/bin/cat 42

""

"   "

"    "

/bin/echo hello 42

/bin/sleep 0

/bin/echo -n 1

echo

echo hello world

echo -n 42

echo -n 42 -n

echo 42 -n

echo -n -n -n 42

echo -n -n -n -n 42

/bin/echo 42
echo $?

/bin/cat 42
echo $?

/bin/exe42 42
echo $?

42 42

/bin/echo 42
expr $? + $?

/bin/cat 42
expr $? + $?

echo "Hello World"

echo "  ""Hello World"

echo "  "Hello "World "

"echo" 42

"echo 42"

echo " cat ' lol.c"

/bin/echo @World"42"Hello

echo 'Hello World'

echo '  ' Hello World

echo '  'Hello 'World '

'echo' 42

'e'cho 42

echo 'cat lol.c << cat > lol.c'

echo @World'42'Hello

echo "" ''

echo """"''""''""

echo " "" " ' ' " " ' ' " "

echo 1 '|' echo 2

echo 1 '&&' echo 2

echo 1 '||' echo 2

echo 1 '>' echo 2

echo 1 '>>' file 2

'<<' lim echo 1 >>/dev/null

echo "$USER"

echo "   $   "

echo '$USER'

echo '   $   '

echo "$HO ME"

echo '$HO ME'

echo $"HOME"

echo $'HOME'

echo ""$PWD""

echo ''$PWD''

echo $USE"R"$HOME

echo $"HOME"$USER

echo $"HOM"E$USER

echo $"'HOM'E"$USER

echo $'HOM'E$USER

echo $"HOME"

echo $'HOME'

echo $

echo "$"

echo '$='

echo "$""$"

echo $"$"

echo $"42$"

echo "$"$

echo $'$'

echo '$'$

export USER="@?/"
echo $USER
echo "$USER"

export NEW="4 2"
echo $NEW
echo "$NEW"

export NEW="4=2"
echo $NEW
echo "$NEW"

export NEW=4=2
echo $NEW
echo "$NEW"

export =

export ''=''

export ""=""

export export

export =============123

export echo

unset

unset env

unset PATH
echo $PATH
unset PATH
echo $PATH
unset HOME
echo $HOME

export NEW=42
echo $NEW
echo "$NEW"
unset NEW
echo $NEW
echo "$NEW"
unset NEW
unset NEW
unset NEW
unset NEW
unset NEW
echo $NEW
echo "$NEW"

cd .
/bin/ls

cd ..
/bin/ls

cd /notsuchdir
/bin/ls

cd /////
/bin/ls

cd "cmds/"
/bin/ls

cd cmds/
/bin/ls

cd ./cmds/
/bin/ls

pwd

cd $HOME
pwd

pwd pwd

pwd hello

unset PATH
pwd

unset PATH
cd /bin
ls

unset PATH
cd /bin/../bin/
ls

unset PATH
cd /bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/
../bin/../bin/ls

unset PATH
cd /bin/
sleep 2
