## 

![norminette](https://github.com/gbudau/minishell/workflows/norminette/badge.svg)

## References

[Shell](https://pubs.opengroup.org/onlinepubs/9699919799/idx/shell.html)

[Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)

[The Architecture of Open Source Applications: The Bourne-Again Shell](https://www.aosabook.org/en/bash.html)

## Minishell roadmap/progress status

- [x] Save the environment variables

- [x] Lexical analysis
  
  - [x] Split the line into tokens

- [x] Expansion
  
  - [x] Environment variables substitution
  
  - [x] Field splitting
  
  - [x] Quote removal

- [x] Parse (analyze and substitute) the tokens into commands

- [ ] Command Execution
  
  - [x] Redirection of IO
  
  - [x] Pipelines
  
  - [ ] Built-in commands
    
    - [x] echo with option '-n'
    
    - [ ] cd with relative or absolute path
    
    - [ ] pwd
    
    - [ ] export
    
    - [ ] unset
    
    - [ ] env without arguments
    
    - [ ] exit
  
  - [ ] Execute nonbuilt-in commands
  
  - [x] Exit status
  
  - [ ] Signals SIGINT (CTRL-C), SIGQUIT \(CTRL-\\\) and EOF \(CTRL-D\)
  
    
