#include <stdio.h>
#include "../include/minishell.h"

void	init_scanner(char *line, t_scanner *scanner)
{
	scanner->tokens = NULL;
	scanner->error = FALSE;
	scanner->start = line;
	scanner->current = line;
}

int		is_at_end(t_scanner *scanner)
{
	return (*scanner->current == '\0');
}

char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (*(scanner->current - 1));
}

int		match(char expected, t_scanner *scanner)
{
	if (is_at_end(scanner))
		return FALSE;
	if (*(scanner->current) != expected)
		return FALSE;
	scanner->current++;
	return TRUE;
}

char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}

void	skip_space(t_scanner *scanner)
{
	while (ft_isspace(peek(scanner)))
		advance(scanner);
}

void	make_token(int tokentype, t_scanner *scanner)
{
	t_token	*new;
	t_list	*node;
	
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		scanner->error = TRUE;
		return ;
	}
	new->type = tokentype;
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

void	make_token_quote(char c, int tokentype, t_scanner *scanner)
{
	while (peek(scanner) != c && !is_at_end(scanner))
		advance(scanner);
	if (is_at_end(scanner))
	{
		if (c == '\'')
			make_token(TOKEN_QUOTE_UNFINISHED, scanner);
		else
			make_token(TOKEN_DOUBLE_QUOTE_UNFINISHED, scanner);
		return ;
	}
	advance(scanner);
	make_token(tokentype, scanner);
}

void	make_token_string(int tokentype, t_scanner *scanner)
{
	char	c;

	c = peek(scanner);
	while (!ft_isspace(c) && !ft_strchr(TOKENS, c) && !is_at_end(scanner))
	{
		advance(scanner);
		c = peek(scanner);
	}
	make_token(tokentype, scanner);
}

void	scan_tokens(t_scanner *scanner)
{
	char		c;

	c = advance(scanner);
	if (c == '\'')
		make_token_quote('\'', TOKEN_QUOTE, scanner);
	else if (c == '\"')
		make_token_quote('\"', TOKEN_DOUBLE_QUOTE, scanner);
	else if (c == '>')
	{
		if (match('>', scanner))
			make_token(TOKEN_OUTPUT_APPEND, scanner);
		else
			make_token(TOKEN_OUTPUT_REDIRECT, scanner);
	}
	else if (c == '<')
		make_token(TOKEN_INPUT_REDIRECT, scanner);
	else if (c == ';')
		make_token(TOKEN_END_COMMAND, scanner);
	else if (c == '|')
		make_token(TOKEN_PIPE, scanner);
	else
		make_token_string(TOKEN_STRING, scanner);
}

t_list	*tokenize(char *line)
{
	t_scanner	scanner;

	init_scanner(line, &scanner);
	while (!is_at_end(&scanner) && !scanner.error)
	{
		skip_space(&scanner);
		scanner.start = scanner.current;
		scan_tokens(&scanner);
	}
	ft_lstrev(&scanner.tokens);
	return (scanner.tokens);
}

void	print_tokens(t_list *tokens)
{
	static char *tok[] = {"TOKEN_PIPE",
		"TOKEN_END_COMMAND",
		"TOKEN_QUOTE",
		"TOKEN_DOUBLE_QUOTE",
		"TOKEN_OUTPUT_REDIRECT",
		"TOKEN_INPUT_REDIRECT",
		"TOKEN_OUTPUT_APPEND",
		"TOKEN_STRING",
		"TOKEN_QUOTE_UNFINISHED",
		"TOKEN_DOUBLE_QUOTE_UNFINISHED"};
	while (tokens != NULL)
	{
		t_token *token = tokens->content;
		printf("%s = %s\n", tok[token->type], token->token);
		tokens = tokens->next;
	}
}

void	clear_token(void *content)
{
	t_token *token;

	token = content;
	free(token->token);
	free(content);
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
