/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:35:25 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/19 19:26:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/env.h"

static void	skip_single_quote(char **words, size_t *i)
{
	(*i)++;
	while ((*words)[*i] && (*words)[*i] != '\'')
		(*i)++;
	if ((*words)[*i])
		(*i)++;
}

static void	substitute_env(char **words, size_t *i,
						t_list *environ, int last_status)
{
	char	*beginning;
	char	*middle;
	char	*end;

	if ((*words)[*i + 1] == '\0' || (!is_env_format((*words)[*i + 1], 0) &&
			(*words)[*i + 1] != '?'))
	{
		(*i)++;
		return ;
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
}

static void	parse_double_quotes(char **words, size_t *i,
							t_list *environ, int last_status)
{
	(*i)++;
	while ((*words)[*i] != '\0' && (*words)[*i] != '"')
	{
		if ((*words)[*i] == '\\')
			*i += 2;
		else if ((*words)[*i] == '$')
			substitute_env(words, i, environ, last_status);
		else if ((*words)[*i])
			(*i)++;
	}
	if ((*words)[*i])
		(*i)++;
}

void		variable_expansion(char **words, t_list **word_list,
							t_list *environ, int *last_status)
{
	size_t	i;

	i = 0;
	while ((*words)[i])
	{
		if ((*words)[i] == '\'')
			skip_single_quote(words, &i);
		else if ((*words)[i] == '"')
			parse_double_quotes(words, &i, environ, *last_status);
		else if ((*words)[i] == '\\')
			i += 2;
		else if ((*words)[i] == '$')
			substitute_env(words, &i, environ, *last_status);
		else if ((*words)[i])
			i++;
	}
	*word_list = tokenize(*words, last_status);
	remove_quotes(*word_list);
}

int			word_expansion(t_command *cmd, t_list *environ, int *last_status)
{
	if (word_exp_io(cmd, environ, last_status) == -1)
		return (-1);
	word_exp_argv(cmd, environ, last_status);
	return (0);
}
