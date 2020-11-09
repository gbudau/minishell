/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:29:26 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 15:37:56 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

/*
** Make a token tokentype with the string between start and current pointers
** And adds the token to the tokens list
** In case of error sets scanner->error to TRUE
*/

static void	make_token(t_tokentype type, t_scanner *scanner)
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
	make_token(WORD, scanner);
}

static void	scan_tokens(t_scanner *scanner)
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

t_list		*tokenize(char *line)
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
		if (errno != 0)
			perror("Error");
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	ft_lstrev(&scanner.tokens);
	return (scanner.tokens);
}
