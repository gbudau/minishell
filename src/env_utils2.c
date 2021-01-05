/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:07:44 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/05 19:08:24 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_env(char *env_name, char *env_value)
{
	char	**env;

	env = ft_calloc(3, sizeof(*env));
	if (env == NULL)
		return (NULL);
	env_name = ft_strdup(env_name);
	if (env_name == NULL)
		return (NULL);
	env[ENV_NAME] = env_name;
	env_value = ft_strdup(env_value);
	if (env_value == NULL)
		return (NULL);
	env[ENV_VALUE] = env_value;
	return (env);
}
