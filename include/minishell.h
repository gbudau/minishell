#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# define PROMPT "minishell> "
# define OPERATORS "|;><"
# define QUOTES "\'\""

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_special_chars
{
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_BACKSLASH = '\\'
};

/*
** Enumeration of tokens that can be an OPERATOR or a WORD
** WORD is a command, command argument, file or directory names
*/
typedef enum	e_tokentype
{
	PIPE,
	SEMICOLON,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	GREAT,
	LESS,
	DGREAT,
	WORD
}				t_tokentype;

/*
** State machine to deal with quotes
*/
typedef enum	e_scan_state
{
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_BACKSLASH
}				t_scan_state;

/*
** Struct containing the type of the token (OPERATORS or WORD)
** And the token itself
*/
typedef	struct	s_token
{
	t_tokentype	type;
	char		*token;
}				t_token;

/*
** *tokens = list of tokens for the current line
** *start = start of the token
** *current = current character that is being analyzed
** state = current state of the WORD token
** error = malloc or syntax errors while lexing
*/
typedef struct	s_scanner
{
	t_list			*tokens;
	char			*start;
	char			*current;
	t_scan_state	state;
	int				error;
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
