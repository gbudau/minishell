/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:46:36 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 17:43:26 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

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
	return (ft_isblank(c) ||
			ft_strchr(OPERATORS, c) || ft_strchr(QUOTES, c));
}

/*
** https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
** #tag_02_02_03
** Return TRUE if the character is a character considered special
** when a backslash is encountered inside a double quote
** Return FALSE otherwise
*/

int		is_dquote_backslash_special(char c)
{
	return (c == CHAR_DQUOTE || c == CHAR_BACKSLASH || c == CHAR_DOLLAR_SIGN);
}

/*
** Return the state of the current word scan
*/

void	get_state(t_scanner *scanner)
{
	char	c;

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
