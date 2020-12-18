/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:36:05 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/18 22:57:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

void	copy_inside_squotes(char *words, size_t *i, size_t *j)
{
	(*i)++;
	while (words[*i] && words[*i] != '\'')
		words[(*j)++] = words[(*i)++];
	if (words[*i])
		(*i)++;
}

void	copy_backslash(char *words, size_t *i, size_t *j)
{
	(*i)++;
	words[(*j)++] = words[(*i)++];
}

void	copy_inside_dquotes(char *words, size_t *i, size_t *j)
{
	(*i)++;
	while (words[*i] && words[*i] != '"')
	{
		if (words[*i] == '\\' && words[*i + 1] == '"')
			copy_backslash(words, i, j);
		else
			words[(*j)++] = words[(*i)++];
	}
	if (words[*i])
		(*i)++;
}

void	copy_without_quotes(char *words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (words[i])
	{
		if (words[i] == '\'')
			copy_inside_squotes(words, &i, &j);
		else if (words[i] == '"')
			copy_inside_dquotes(words, &i, &j);
		else if (words[i] == '\\')
			copy_backslash(words, &i, &j);
		else
			words[j++] = words[i++];
	}
	words[j] = '\0';
}

void	remove_quotes(t_list *word_list, char *words, size_t expanded)
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
