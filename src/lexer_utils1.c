/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:51:27 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 00:11:05 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
** Advance the current pointer
** Return the previous character
*/

char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (*(scanner->current - 1));
}

/*
** Return the character pointed by current pointer
*/

char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}


/*
** Return the character after the character pointed by current pointer
*/

char	peek_next(t_scanner *scanner)
{
	return (*(scanner->current + 1));
}
