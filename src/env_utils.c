/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:31:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/04 19:33:53 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_env(void *content)
{
	ft_free_strarr(content);
}

int		compare_env(const void *content, const void *match)
{
	const char	**env;
	const char	*str;

	env = (const char **)content;
	str = match;
	return (ft_strcmp(env[ENV_NAME], str));
}

void	add_env_front(t_list **environ, char **env)
{
	t_list	*node;

	node = ft_lstnew(env);
	if (node == NULL)
		error_exit();
	ft_lstadd_front(environ, node);
}
