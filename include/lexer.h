/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:01:02 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/16 19:15:16 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# define OPERATORS "|;><"
# define QUOTES "\'\"\\"

enum	e_special_chars
{
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_BACKSLASH = '\\',
	CHAR_DOLLAR_SIGN = '$'
};

/*
** Enumeration of tokens that can be an OPERATOR or a WORD token
** TOKEN_WORD is a command, command argument, file or directory names
*/

typedef enum	e_tokentype
{
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_GREAT,
	TOKEN_LESS,
	TOKEN_DGREAT,
	TOKEN_WORD
}				t_tokentype;

/*
** State machine for quotes and backslash escape in WORD tokens
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
	char		*str;
}				t_token;

/*
** Variables used for splitting the line into tokens
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

t_list			*tokenize(char *line, int *last_status);
int				advance_word(t_scanner *scanner);
void			get_state(t_scanner *scanner);
int				is_at_end(t_scanner *scanner);
int				is_backslash(char c);
int				is_general_delimiter(char c);
int				is_dquote_backslash_special(char c);
int				is_dquote_backslash_special(char c);
void			regress(t_scanner *scanner);
char			advance(t_scanner *scanner);
char			peek(t_scanner *scanner);
char			peek_next(t_scanner *scanner);
void			skip_space(t_scanner *scanner);
int				match(char expected, t_scanner *scanner);
void			clear_token(void *node);
void			print_tokens(t_list *tokens);

#endif
