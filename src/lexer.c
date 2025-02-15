/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:29:26 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/17 21:23:29 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

/*
** Make a token tokentype with the string between start and current pointers
** And adds the token to the tokens list
*/

static void	make_token(t_tokentype type, t_scanner *scanner)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(*token));
	if (token == NULL)
		error_exit();
	token->type = type;
	token->str = ft_strndup(scanner->start, scanner->current - scanner->start);
	if (token->str == NULL)
		error_exit();
	node = ft_lstnew(token);
	if (node == NULL)
		error_exit();
	ft_lstadd_front(&scanner->tokens, node);
}

static void	make_token_word(t_scanner *scanner)
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
	make_token(TOKEN_WORD, scanner);
}

static void	scan_tokens(t_scanner *scanner)
{
	char		c;

	if ((c = advance(scanner)) == '|')
		make_token(TOKEN_PIPE, scanner);
	else if (c == ';')
	{
		if (match(';', scanner))
			scanner->error = ERR_UNEXPECTED_TOKEN_DOUBLE_SEMICOLON;
		else
			make_token(TOKEN_SEMICOLON, scanner);
	}
	else if (c == '<')
		make_token(TOKEN_LESS, scanner);
	else if (c == '>')
	{
		if (match('>', scanner))
			make_token(TOKEN_DGREAT, scanner);
		else
			make_token(TOKEN_GREAT, scanner);
	}
	else
	{
		regress(scanner);
		make_token_word(scanner);
	}
}

static void	init_scanner(char *line, t_scanner *scanner)
{
	scanner->tokens = NULL;
	scanner->start = line;
	scanner->current = line;
	scanner->state = STATE_GENERAL;
	scanner->error = FALSE;
}

/*
** Split the line into a list of OPERATORS or WORD tokens
*/

t_list		*tokenize(char *line, int *last_status)
{
	t_scanner	scanner;

	if (line == NULL)
		return (NULL);
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
		error_syntax_scanner(scanner.error);
		ft_lstclear(&scanner.tokens, clear_token);
		*last_status = 2;
		return (NULL);
	}
	ft_lstrev(&scanner.tokens);
	return (scanner.tokens);
}
