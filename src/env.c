/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:38:55 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/27 16:18:24 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_env(t_list **head)
{
	extern char	**environ;
	char		**env;
	t_list		*node;
	size_t		i;

	i = 0;
	while (environ[i])
	{
		env = ft_split(environ[i++], '=');
		if (env == NULL)
			error_exit();
		node = ft_lstnew(env);
		if (node == NULL)
			error_exit();
		ft_lstadd_front(head, node);
	}
	ft_lstrev(head);
}

void	print_env(t_list *environ)
{
	char	**env;

	while (environ != NULL)
	{
		env = environ->content;
		ft_putstr_fd(env[ENV_NAME], STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		if (env[ENV_VALUE] != NULL)
			ft_putstr_fd(env[ENV_VALUE], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		environ = environ->next;
	}
}

char	*get_env(t_list *environ, char *match)
{
	char	**env;

	while (environ != NULL)
	{
		env = environ->content;
		if (ft_strcmp(env[ENV_NAME], match) == 0)
		{
			return (env[ENV_VALUE]);
		}
		environ = environ->next;
	}
	return (NULL);
}

void	add_env_front(t_list **environ, char **env)
{
	t_list	*node;

	node = ft_lstnew(env);
	if (node == NULL)
		error_exit();
	ft_lstadd_front(environ, node);
}

void	set_env(t_list **environ, char **newenv)
{
	t_list	*node;
	char	**env;

	if (*environ == NULL)
		add_env_front(environ, newenv);
	else
	{
		node = *environ;
		while (node != NULL)
		{
			env = node->content;
			if (ft_strcmp(env[ENV_NAME], newenv[ENV_NAME]) == 0)
				break ;
			node = node->next;
		}
		if (node == NULL)
			add_env_front(environ, newenv);
		else
		{
			ft_free_strarr(env);
			node->content = newenv;
		}
	}
}

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

int		unset_env(t_list **environ, char *env_name)
{
	return (ft_lstdelcmp(environ, &compare_env, env_name, &clear_env));
}
