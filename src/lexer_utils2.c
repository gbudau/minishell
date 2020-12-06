/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:54:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/06 19:33:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

/*
** Advance the current pointer until it points at a non-space character
*/

void	skip_space(t_scanner *scanner)
{
	while (ft_isspace(peek(scanner)))
		advance(scanner);
}

/*
** If the current character is the expected one
** advance a character and return TRUE
** Return FALSE otherwise
*/

int		match(char expected, t_scanner *scanner)
{
	if (is_at_end(scanner))
		return (FALSE);
	if (*scanner->current != expected)
		return (FALSE);
	scanner->current++;
	return (TRUE);
}

void	print_tokens(t_list *tokens)
{
	t_token				*token;
	const char			*token_types[] = {"TOKEN_PIPE",
		"TOKEN_SEMICOLON",
		"TOKEN_SINGLE_QUOTE",
		"TOKEN_DOUBLE_QUOTE",
		"TOKEN_GREAT",
		"TOKEN_LESS",
		"TOKEN_DGREAT",
		"TOKEN_WORD"};

	if (tokens == NULL)
		return ;
	while (tokens != NULL)
	{
		token = tokens->content;
		printf("%s = %s\n", token_types[token->type], token->str);
		tokens = tokens->next;
	}
}
