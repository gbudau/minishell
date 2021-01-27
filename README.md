## 

![norminette](https://github.com/gbudau/minishell/workflows/norminette/badge.svg)

## References

[Shell](https://pubs.opengroup.org/onlinepubs/9699919799/idx/shell.html)

[Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)

[The Architecture of Open Source Applications: The Bourne-Again Shell](https://www.aosabook.org/en/bash.html)

## Minishell progress status

- [x] Environment variables

- [x] Lexical analysis
  
  - [x] Split input into tokens

- [x] Parse (analyze and substitute) the tokens into commands

- [x] Command Execution
  
  - [x] Word expansion
    
    - [x] Environment variables substitution
    
    - [x] Field splitting
    
    - [x] Quote removal
  
  - [x] Redirection of I/O
  
  - [x] Pipelines
  
  - [x] Built-in commands
    
    - [x] echo with option '-n'
    
    - [x] cd with relative or absolute path
    
    - [x] pwd
    
    - [x] export
    
    - [x] unset
    
    - [x] env without arguments
    
    - [x] exit
  
  - [x] Execution of non-built-in commands
  
  - [x] Exit status of last command
  
  - [x] Signals: SIGINT (CTRL-C), SIGQUIT \(CTRL-\\\) and EOF \(CTRL-D\)
