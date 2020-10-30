#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# define PROMPT "minishell> "
# define TOKENS "|;><"

enum	e_bool
{
	FALSE,
	TRUE
};

typedef enum	e_tokentype
{
	TOKEN_PIPE, // '|'
	TOKEN_END_COMMAND, // ';'
	TOKEN_QUOTE, // '\''
	TOKEN_DOUBLE_QUOTE, // '\"'
	TOKEN_OUTPUT_REDIRECT, // '>'
	TOKEN_INPUT_REDIRECT, // '<'
	TOKEN_OUTPUT_APPEND, // '>>'
	TOKEN_STRING, // words
	TOKEN_QUOTE_UNFINISHED, // '\'' quote that is not finished
	TOKEN_DOUBLE_QUOTE_UNFINISHED // '\"' double quote that is not finished
}				t_tokentype;

typedef	struct	s_token
{
	t_tokentype	type;
	char		*token;
}				t_token;

typedef struct	s_scanner
{
	t_list	*tokens;
	char	*start;
	char	*current;
	int		error;
}				t_scanner;

/*
typedef struct	s_process
{
	struct process	*next;
	char			**argv;
	char			**env;
	int				status;
}				t_process;
*/

#endif
