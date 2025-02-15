/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:07:44 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/27 21:06:38 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

static char	**create_env(char *env_name, char *env_value)
{
	char	**env;

	env = ft_calloc(3, sizeof(*env));
	if (env == NULL)
		return (NULL);
	env_name = ft_strdup(env_name);
	if (env_name == NULL)
		return (NULL);
	env[ENV_NAME] = env_name;
	if (env_value)
	{
		env_value = ft_strdup(env_value);
		if (env_value == NULL)
			return (NULL);
	}
	env[ENV_VALUE] = env_value;
	return (env);
}

void		create_and_set_env(t_list **environ, char *name, char *value)
{
	char	**env;

	env = create_env(name, value);
	if (env == NULL)
		error_exit();
	set_env(environ, env);
}

char		*double_quoting(const char *str)
{
	int		i;
	int		cont;
	char	*dest;

	i = -1;
	cont = 0;
	while (str[++i])
		if (is_dquote_backslash_special(str[i]))
			cont++;
	if (!(dest = ft_calloc(sizeof(char), i + cont + 1)))
		return (NULL);
	cont = 0;
	i = 0;
	while (str[i])
	{
		if (is_dquote_backslash_special(str[i]))
			dest[cont++] = CHAR_BACKSLASH;
		dest[cont++] = str[i++];
	}
	return (dest);
}

int			compare_env_name(const void *a, const void *b)
{
	const char	**a_str_arr;
	const char	**b_str_arr;

	a_str_arr = (const char **)a;
	b_str_arr = (const char **)b;
	return (ft_strcmp(a_str_arr[ENV_NAME], b_str_arr[ENV_NAME]));
}
