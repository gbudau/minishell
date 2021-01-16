#!/usr/bin/env bash

: '
				💀	WARNING !!!
		DO NOT USE THIS SCRIPT ON YOUR OWN MACHINE
				USE A CONTAINER OR A VM 💀
'

for i in {1..10000}; do
	random="$(head -c100 /dev/urandom | tr -dc "[:space:][:print:]")"
	random+=" ; exit"
	echo "$random" 
	echo ---------------------------------
	./minishell << EOF
$random
EOF
done
