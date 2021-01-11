/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:35:25 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 17:00:16 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/env.h"

static void		skip_single_quote(char **words, size_t *i)
{
	(*i)++;
	while ((*words)[*i] && (*words)[*i] != '\'')
		(*i)++;
	if ((*words)[*i])
		(*i)++;
}

static size_t	substitute_env(char **words, size_t *i,
						t_list *environ, int *last_status)
{
	char	*beginning;
	char	*middle;
	char	*end;

	if ((*words)[*i + 1] == '\0' || (!is_env_format((*words)[*i + 1], 0) &&
			(*words)[*i + 1] != '?'))
	{
		(*i)++;
		return (0);
	}
	if ((beginning = ft_strndup(*words, *i)) == NULL)
		error_exit();
	middle = env_or_last_status(words, i, environ, last_status);
	if ((end = ft_strndup(*words + *i, ft_strlen(*words + *i))) == NULL)
		error_exit();
	*i = ft_strlen(beginning) + ft_strlen(middle);
	free(*words);
	if ((*words = ft_strjoin_free(beginning, middle, FREE_BOTH)) == NULL)
		error_exit();
	if ((*words = ft_strjoin_free(*words, end, FREE_BOTH)) == NULL)
		error_exit();
	return (1);
}

static size_t	parse_double_quotes(char **words, size_t *i,
							t_list *environ, int *last_status)
{
	size_t	expanded;

	expanded = 0;
	(*i)++;
	while ((*words)[*i] != '\0' && (*words)[*i] != '"')
	{
		if ((*words)[*i] == '\\')
			*i += 2;
		else if ((*words)[*i] == '$')
			expanded = substitute_env(words, i, environ, last_status);
		else if ((*words)[*i])
			(*i)++;
	}
	return (expanded);
}

static int		variable_expansion(char **words, t_list **word_list,
							t_list *environ, int *last_status)
{
	size_t	expanded;
	size_t	i;

	expanded = 0;
	i = 0;
	while ((*words)[i])
	{
		if ((*words)[i] == '\'')
			skip_single_quote(words, &i);
		else if ((*words)[i] == '"')
			expanded = parse_double_quotes(words, &i, environ, last_status);
		else if ((*words)[i] == '\\')
			i += 2;
		else if ((*words)[i] == '$')
			expanded = substitute_env(words, &i, environ, last_status);
		else if ((*words)[i])
			i++;
	}
	if (expanded)
		*word_list = tokenize(*words, last_status);
	remove_quotes(*word_list, *words, expanded);
	return (expanded);
}

void			word_expansion(t_list **tokens, t_list *environ,
												int *last_status)
{
	t_list	*trav;
	t_list	*sublist;
	t_list	*tmp;
	t_token	*token;

	while ((trav = *tokens))
	{
		token = trav->content;
		tmp = trav->next;
		if (token->type == TOKEN_WORD &&
			variable_expansion(&token->str, &sublist, environ, last_status) &&
			sublist != NULL)
		{
			*tokens = sublist;
			sublist = ft_lstlast(*tokens);
			sublist->next = tmp;
			tokens = &sublist->next;
			ft_lstdelone(trav, clear_token);
		}
		else
			tokens = &trav->next;
	}
}
