ls /not_dir && ls /usr || ls /not_dir || ls /usr (ls /not_dir && ls /usr || ls /not_dir) || ls /usr
ls /not_dir && ls /usr || (ls /not_dir && ls /not_dir || ls /etc) && ls /usr
(export VAR=TOTO && echo "var in subshell = '$VAR'") && echo "var out subshell = '$VAR'"
export VAR=TOTO && echo "var = '$VAR'"
