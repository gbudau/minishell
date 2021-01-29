/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:35:25 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/29 14:50:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/env.h"

static size_t	skip_single_quote(char *str, size_t i)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i])
		i++;
	return (i);
}

static char		*substitute_env(char *str, size_t *i,
											t_list *environ, int last_status)
{
	char	*beginning;
	char	*middle;
	char	*end;

	if (str[*i + 1] == '\0' || (!is_env_format(str[*i + 1], 0) &&
			str[*i + 1] != '?'))
	{
		(*i)++;
		return (str);
	}
	if ((beginning = ft_strndup(str, *i)) == NULL)
		error_exit();
	middle = env_or_last_status(str, i, environ, last_status);
	if ((end = ft_strndup(str + *i, ft_strlen(str + *i))) == NULL)
		error_exit();
	*i = ft_strlen(beginning) + ft_strlen(middle);
	free(str);
	if ((str = ft_strjoin_free(beginning, middle, FREE_BOTH)) == NULL)
		error_exit();
	if ((str = ft_strjoin_free(str, end, FREE_BOTH)) == NULL)
		error_exit();
	return (str);
}

static char		*parse_double_quotes(char *str, size_t *i,
											t_list *environ, int last_status)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '"')
	{
		if (str[*i] == '\\')
			*i += 2;
		else if (str[*i] == '$')
			str = substitute_env(str, i, environ, last_status);
		else if (str[*i])
			(*i)++;
	}
	if (str[*i])
		(*i)++;
	return (str);
}

t_list			*variable_expansion(char **words, t_list *environ,
															int *last_status)
{
	size_t	i;
	t_list	*word_list;
	char	*str;

	i = 0;
	str = *words;
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_single_quote(str, i);
		else if (str[i] == '"')
			str = parse_double_quotes(str, &i, environ, *last_status);
		else if (str[i] == '\\')
			i += 2;
		else if (str[i] == '$')
			str = substitute_env(str, &i, environ, *last_status);
		else if (str[i])
			i++;
	}
	word_list = tokenize(str, last_status);
	remove_quotes(word_list);
	*words = str;
	return (word_list);
}

int				word_expansion(t_command *cmd, t_list *environ,
															int *last_status)
{
	if (cmd->redirection_error == TRUE)
	{
		*last_status = 1;
		return (-1);
	}
	word_exp_argv(cmd, environ, last_status);
	return (0);
}
