/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:36:05 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 16:27:09 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

static void	copy_inside_squotes(char *words, size_t *src_idx, size_t *dst_idx)
{
	(*src_idx)++;
	while (words[*src_idx] && words[*src_idx] != '\'')
		words[(*dst_idx)++] = words[(*src_idx)++];
	if (words[*src_idx])
		(*src_idx)++;
}

static void	copy_backslash(char *words, size_t *src_idx, size_t *dst_idx)
{
	(*src_idx)++;
	words[(*dst_idx)++] = words[(*src_idx)++];
}

static void	copy_inside_dquotes(char *words, size_t *src_idx, size_t *dst_idx)
{
	(*src_idx)++;
	while (words[*src_idx] && words[*src_idx] != '"')
	{
		if (words[*src_idx] == '\\' &&
				(words[*src_idx + 1] == '"' || words[*src_idx + 1] == '\\'))
			copy_backslash(words, src_idx, dst_idx);
		else
			words[(*dst_idx)++] = words[(*src_idx)++];
	}
	if (words[*src_idx])
		(*src_idx)++;
}

static void	copy_without_quotes(char *words)
{
	size_t	src_idx;
	size_t	dst_idx;

	src_idx = 0;
	dst_idx = 0;
	while (words[src_idx])
	{
		if (words[src_idx] == '\'')
			copy_inside_squotes(words, &src_idx, &dst_idx);
		else if (words[src_idx] == '"')
			copy_inside_dquotes(words, &src_idx, &dst_idx);
		else if (words[src_idx] == '\\')
			copy_backslash(words, &src_idx, &dst_idx);
		else
			words[dst_idx++] = words[src_idx++];
	}
	words[dst_idx] = '\0';
}

void		remove_quotes(t_list *word_list, char *words, size_t expanded)
{
	if (!expanded)
		copy_without_quotes(words);
	else
	{
		while (word_list != NULL)
		{
			copy_without_quotes(word_list->content);
			word_list = word_list->next;
		}
	}
}
