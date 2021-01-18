#!/usr/bin/env bash
BLUE='\x1b[1;36m'
RESET='\x1b[0m'
echo -e "${BLUE}Minishell errors${RESET}"
cat minishell_error.txt | sed 's/> />\n/g' | sed '/minishell>/d'
echo
echo -e "${BLUE}Bash errors${RESET}"
cat bash_error.txt | sed "/bash-4.4$ /d"
