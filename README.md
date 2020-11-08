## Minishell roadmap/progress status

[Shell](https://pubs.opengroup.org/onlinepubs/9699919799/idx/shell.html)

[Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)

[The Architecture of Open Source Applications: The Bourne-Again Shell](https://www.aosabook.org/en/bash.html)

- [x] Lexical analysis
  
  - [x] Split the line into token

- [ ] Expansion 
  
  - [ ] Environmental variables substitution
  
  - [ ] Field splitting
  
  - [ ] Quote removal

- [ ] Parse (analyze and substitute) the tokens into simple commands

- [ ] Command Execution
  
  - [ ] Builtin commands
    
    - [ ] echo with option '-n'
    
    - [ ] cd with relative or absolute path
    
    - [ ] pwd
    
    - [ ] export
    
    - [ ] unset
    
    - [ ] env without arguments
    
    - [ ] exit
  
  - [ ] Simple commands
  
  - [ ] Redirection of IO
  
  - [ ] Pipelines
  
  - [ ] Job control
  
  - [ ] Exit status
  
  - [ ] Signals (CTRL-C, CTRL-\\) and EOF (CTRL-D)
  
      
