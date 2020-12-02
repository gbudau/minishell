## References

[Shell](https://pubs.opengroup.org/onlinepubs/9699919799/idx/shell.html)

[Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)

[The Architecture of Open Source Applications: The Bourne-Again Shell](https://www.aosabook.org/en/bash.html)

## Minishell roadmap/progress status

- [x] Save the environment variables

- [x] Lexical analysis
  
  - [x] Split the line into tokens

- [ ] Expansion
  
  - [x] Environment variables substitution
  
  - [ ] Field splitting
  
  - [ ] Quote removal

- [ ] Parse (analyze and substitute) the tokens into commands

- [ ] Command Execution
  
  - [ ] Redirection of IO
  
  - [ ] Pipelines
  
  - [ ] Built-in commands
    
    - [ ] echo with option '-n'
    
    - [ ] cd with relative or absolute path
    
    - [ ] pwd
    
    - [ ] export
    
    - [ ] unset
    
    - [ ] env without arguments
    
    - [ ] exit
  
  - [ ] Execute nonbuilt-in commands
  
  - [ ] Exit status
  
  - [ ] Signals SIGINT (CTRL-C), SIGQUIT \(CTRL-\\\) and EOF \(CTRL-D\)
  
    
