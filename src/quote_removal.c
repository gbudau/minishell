/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:36:05 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/14 18:07:23 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"

static void	copy_inside_squotes(struct s_unquote *u)
{
	u->src_idx++;
	while (u->str[u->src_idx] && u->str[u->src_idx] != '\'')
		u->str[u->dst_idx++] = u->str[u->src_idx++];
	if (u->str[u->src_idx])
		u->src_idx++;
}

static void	copy_inside_dquotes(struct s_unquote *u)
{
	u->src_idx++;
	while (u->str[u->src_idx] && u->str[u->src_idx] != '"')
	{
		if (u->str[u->src_idx] == '\\' &&
			(u->str[u->src_idx] == '"' || u->str[u->src_idx + 1] == '\\'))
		{
			u->src_idx++;
		}
		u->str[u->dst_idx++] = u->str[u->src_idx++];
	}
	if (u->str[u->src_idx])
		u->src_idx++;
}

/*
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
** #tag_18_06_07
** Removing the quotes by copying the string in place without the quotes
** Using two indexes, one for the copy and one to traverse the string
*/

static void	copy_without_quotes(char *str)
{
	struct s_unquote	u;

	u.str = str;
	u.dst_idx = 0;
	u.src_idx = 0;
	while (u.str[u.src_idx])
	{
		if (u.str[u.src_idx] == '\'')
			copy_inside_squotes(&u);
		else if (u.str[u.src_idx] == '"')
			copy_inside_dquotes(&u);
		else if (u.str[u.src_idx] == '\\')
		{
			u.src_idx++;
			u.str[u.dst_idx++] = u.str[u.src_idx++];
		}
		else
			u.str[u.dst_idx++] = u.str[u.src_idx++];
	}
	u.str[u.dst_idx] = '\0';
}

void		remove_quotes(t_list *word_token_list)
{
	t_token	*token;

	while (word_token_list != NULL)
	{
		token = word_token_list->content;
		copy_without_quotes(token->str);
		word_token_list = word_token_list->next;
	}
}
