/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:45 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/07 13:59:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

/*
** Advance a string delimited by quotes
*/

static void	advance_quote(t_scanner *scanner)
{
	advance(scanner);
	while (!is_at_end(scanner) && peek(scanner) != CHAR_QUOTE)
		advance(scanner);
	if (is_at_end(scanner))
		scanner->error = ERR_INCOMPLETE_QUOTE;
	else
		advance(scanner);
}

/*
** Advance a character after a backslash
** If the string ended set error to TRUE
*/

static void	advance_backslash(t_scanner *scanner)
{
	advance(scanner);
	if (!is_at_end(scanner))
		advance(scanner);
	else
		scanner->error = ERR_INCOMPLETE_BACKSLASH;
}

/*
** Advance a string delimited by double quotes
*/

static void	advance_double_quote(t_scanner *scanner)
{
	char	c;
	char	next;

	advance(scanner);
	c = peek(scanner);
	while (!is_at_end(scanner) && c != CHAR_DQUOTE)
	{
		next = peek_next(scanner);
		if (is_backslash(c) && is_dquote_backslash_special(next))
			advance_backslash(scanner);
		else
			advance(scanner);
		if (scanner->error)
			return ;
		c = peek(scanner);
	}
	if (is_at_end(scanner))
		scanner->error = ERR_INCOMPLETE_DQUOTE;
	else
		advance(scanner);
}

/*
** Advance a word that is delimited by spaces, backslash or OPERATORS
** If the current character is a backslash '\\', will advance two characters
*/

static void	advance_general(t_scanner *scanner)
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
** Advance words, quoted strings or backslash
** Advance a word delimited by spaces or OPERATORS
** Advance a quoted string until the end of the quote
*/

int			advance_word(t_scanner *scanner)
{
	char	c;

	c = peek(scanner);
	if (!scanner->state && (ft_isspace(c) || ft_strchr(OPERATORS, c)))
		return (TRUE);
	if (scanner->state == STATE_IN_QUOTE)
		advance_quote(scanner);
	else if (scanner->state == STATE_IN_DQUOTE)
		advance_double_quote(scanner);
	else if (scanner->state == STATE_BACKSLASH)
		advance_backslash(scanner);
	else
		advance_general(scanner);
	return (FALSE);
}
