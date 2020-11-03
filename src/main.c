#include <stdio.h>
#include "../include/minishell.h"

void	init_scanner(char *line, t_scanner *scanner)
{
	scanner->tokens = NULL;
	scanner->start = line;
	scanner->current = line;
	scanner->state = STATE_GENERAL;
	scanner->error = FALSE;
}

/*
** Return TRUE if the current pointer is at the end of the string
** False otherwise
*/
int		is_at_end(t_scanner *scanner)
{
	return (*scanner->current == '\0');
}

/*
** Regress the current pointer
*/
void	regress(t_scanner *scanner)
{
	scanner->current--;
}

/*
** Advance the current pointer and returns the previous character
*/
char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (*(scanner->current - 1));
}

/*
** If the current character is the expected one advance a character and return TRUE
** Return FALSE otherwise
*/
int		match(char expected, t_scanner *scanner)
{
	if (is_at_end(scanner))
		return FALSE;
	if (*scanner->current != expected)
		return FALSE;
	scanner->current++;
	return TRUE;
}

/*
** Return the character pointed by current pointer
*/
char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}

/*
** Advance the pointer until it points at a non-space character
*/
void	skip_space(t_scanner *scanner)
{
	while (ft_isspace(peek(scanner)))
		advance(scanner);
}

/*
** Make a token tokentype with the string between start and current pointers
** And adds the token to the tokens list
** In case of error sets scanner->error to TRUE
*/
void	make_token(t_tokentype type, t_scanner *scanner)
{
	t_token	*new;
	t_list	*node;
	
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		scanner->error = TRUE;
		return ;
	}
	new->type = type;
	new->token = ft_strndup(scanner->start, scanner->current - scanner->start);
	if (new->token == NULL)
	{
		scanner->error = TRUE;
		return ;
	}
	node = ft_lstnew(new);
	if (node == NULL)
	{
		scanner->error = TRUE;
		return ;
	}
	ft_lstadd_front(&scanner->tokens, node);
}

/*
** Return the state of the current word scan
*/
void		get_state(t_scanner *scanner)
{
	char			c;

	c = peek(scanner);
	if (c == CHAR_BACKSLASH)
		scanner->state = STATE_BACKSLASH;
	else if (c == CHAR_QUOTE)
		scanner->state = STATE_IN_QUOTE;
	else if (c == CHAR_DQUOTE)
		scanner->state = STATE_IN_DQUOTE;
	else
		scanner->state = STATE_GENERAL;
}

/*
** Advance a character after a backslash
** If the string ended set error to TRUE
*/
void	advance_backslash(t_scanner *scanner)
{
	advance(scanner);
	if (!is_at_end(scanner))
		advance(scanner);
	else
		scanner->error = TRUE;
}

int		is_backslash(char c)
{
	return (c == CHAR_BACKSLASH);
}

/*
** Return TRUE if char is a backslash, space, OPERATOR or quote
** Return FALSE otherwise
*/
int		is_general_delimiter(char c)
{
	return (is_backslash(c) || ft_isspace(c) ||
			ft_strchr(OPERATORS, c) || ft_strchr(QUOTES, c));
}

/*
** Advance a word that is delimited by spaces, backslash or OPERATORS
** If the current character is a backslash '\\', will advance two characters
*/
void	advance_general(t_scanner *scanner)
{
	char	c;

	c = peek(scanner);
	while (!is_at_end(scanner) && !is_general_delimiter(c))
	{
		advance(scanner);
		c = peek(scanner);
	}
}

/*
** Advance a string delimited by quotes
*/
void	advance_quote(char c, t_scanner *scanner)
{
	advance(scanner);
	while (!is_at_end(scanner) && peek(scanner) != c)
		advance(scanner);
	if (is_at_end(scanner))
		scanner->error = TRUE;
	else
		advance(scanner);
}

/*
** Advance words, quoted strings or backslash
** Advance a word delimited by spaces or OPERATORS
** Advance a quoted string until the end of the quote
*/
int		advance_word(t_scanner *scanner)
{
	char	c;

	c = peek(scanner);
	if (!scanner->state && (ft_isspace(c) || ft_strchr(OPERATORS, c)))
		return (TRUE);
	if (scanner->state == STATE_IN_QUOTE)
		advance_quote(CHAR_QUOTE, scanner);
	else if (scanner->state == STATE_IN_DQUOTE)
		advance_quote(CHAR_DQUOTE, scanner);
	else if (scanner->state == STATE_BACKSLASH)
		advance_backslash(scanner);
	else
		advance_general(scanner);
	return (FALSE);
}

void	make_token_word(t_scanner *scanner)
{
	int		done;

	done = FALSE;
	get_state(scanner);
	while (!done && !scanner->error)
	{
		done = advance_word(scanner);
		get_state(scanner);
	}
	if (scanner->error)
		return ;
	make_token(WORD, scanner);
}

void	scan_tokens(t_scanner *scanner)
{
	char		c;

	c = advance(scanner);
	if (c == '|')
		make_token(PIPE, scanner);
	else if (c == ';')
		make_token(SEMICOLON, scanner);
	else if (c == '<')
		make_token(LESS, scanner);
	else if (c == '>')
	{
		if (match('>', scanner))
			make_token(DGREAT, scanner);
		else
			make_token(GREAT, scanner);
	}
	else
	{
		regress(scanner);
		make_token_word(scanner);
	}
}

/*
** Tokenize the line into OPERATORS or WORD tokens
*/
t_list	*tokenize(char *line)
{
	t_scanner	scanner;

	init_scanner(line, &scanner);
	while (!is_at_end(&scanner) && !scanner.error)
	{
		skip_space(&scanner);
		if (is_at_end(&scanner))
			break ;
		scanner.start = scanner.current;
		scan_tokens(&scanner);
	}
	if (scanner.error)
	{
		if (errno != 0)
			perror("Error:");
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	ft_lstrev(&scanner.tokens);
	return (scanner.tokens);
}

void	print_tokens(t_list *tokens)
{
	static char *tok[] = {"PIPE",
		"SEMICOLON",
		"SINGLE_QUOTE",
		"DOUBLE_QUOTE",
		"GREAT",
		"LESS",
		"DGREAT",
		"WORD",};

	while (tokens != NULL)
	{
		t_token *token = tokens->content;
		printf("%s = %s\n", tok[token->type], token->token);
		tokens = tokens->next;
	}
}

/*
** Free one token node from the list of tokens
*/
void	clear_token(void *node)
{
	free(((t_token *)node)->token);
	free(node);
}

void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

int	main(void)
{
	char	*line;
	ssize_t	nread;
	t_list	*tokens;

	line = NULL;
	tokens = NULL;
	while (1)
	{
		prompt();
		nread = get_next_line(STDIN_FILENO, &line);
		if (nread == -1)
			break;
		tokens = tokenize(line);
		print_tokens(tokens);
		ft_lstclear(&tokens, clear_token);
		free(line);
		line = NULL;
		if (nread == 0)
			break;
	}
	return (0);
}
