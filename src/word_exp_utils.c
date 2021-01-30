/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:39:23 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/29 14:28:02 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"

static char	*env_value(char *str, size_t *i, t_list *environ)
{
	size_t	len;
	char	*env_name;
	char	*tmp;

	(*i)++;
	len = *i;
	while (is_env_format(str[len], 1))
		len++;
	if ((env_name = ft_strndup(str + *i, len - *i)) == NULL)
		error_exit();
	tmp = env_name;
	env_name = get_env(environ, env_name);
	free(tmp);
	if (env_name == NULL)
	{
		env_name = ft_strdup("");
		if (env_name == NULL)
			error_exit();
	}
	*i += (len - *i);
	return (env_name);
}

static char	*last_status_value(size_t *i, int last_status)
{
	char	*status;

	*i += 2;
	status = ft_itoa(last_status);
	if (status == NULL)
		error_exit();
	return (status);
}

char		*env_or_last_status(char *str, size_t *i,
							t_list *environ, int last_status)
{
	if (str[*i + 1] == '?')
		return (last_status_value(i, last_status));
	return (env_value(str, i, environ));
}
