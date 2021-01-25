/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:07:44 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/22 00:55:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (str[i] == '\"' || str[i] == '$' || str[i] == '\\')
			cont++;
	dest = ft_calloc(sizeof(char), i + cont + 1);
	cont = 0;
	i = 0;
	while (str[i])
	{
		dest[cont++] = str[i++];
		if (str[i] == '"' || str[i] == '$' || str[i] == '\\')
			dest[cont++] = '\\';
	}
	return (dest);
}
