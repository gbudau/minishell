## Minishell roadmap/progress status

[Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

[Bash Beginners Guide](https://tldp.org/LDP/Bash-Beginners-Guide/html/chap_01.html)

[The Architecture of Open Source Applications: The Bourne-Again Shell](https://www.aosabook.org/en/bash.html)

- [x] Lexical analysis and parsing
  
  - [x] Split the line into tokens
  
  - [ ] Parse (analyze and substitute) the tokens into simple commands

- [ ] Expansion
  
  - [ ] Parameter expansion
    
    - [ ] Environmental variables
  
  - [ ] Word splitting

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
  
      
