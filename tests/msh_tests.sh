#!/usr/bin/env bash
make -C ..
cp ../minishell .
./minishell < tests.file 2> minishell_error.txt 1> minishell_output.txt
echo $? >> minishell_output.txt
bash --norc -i < tests.file 2> bash_error.txt 1> bash_output.txt
echo $? >> bash_output.txt
git --no-pager diff --no-index --unified=0 minishell_output.txt bash_output.txt
./error_output.sh
rm minishell minishell_output.txt bash_output.txt minishell_error.txt bash_error.txt
