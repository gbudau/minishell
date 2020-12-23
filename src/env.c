/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:38:55 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/23 11:47:19 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_env(t_list **head)
{
	extern char	**environ;
	char		**env;
	t_list		*node;
	size_t		i;
	int			equal_sign_idx;

	i = 0;
	while (environ[i])
	{
		equal_sign_idx = verify_env(environ[i]);
		if (equal_sign_idx == -1)
		{
			not_a_valid_identifier(environ[i]);
			error_exit();
		}
		env = split_env(environ[i++], equal_sign_idx);
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
		if (env[ENV_VALUE] != NULL)
		{
			ft_putstr_fd(env[ENV_NAME], STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env[ENV_VALUE], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		environ = environ->next;
	}
}

char	*get_env(t_list *environ, char *match)
{
	char	**env;
	char	*ret;

	while (environ != NULL)
	{
		env = environ->content;
		if (ft_strcmp(env[ENV_NAME], match) == 0)
		{
			if (env[ENV_VALUE])
				ret = ft_strdup(env[ENV_VALUE]);
			else
				ret = ft_strdup("");
			if (ret == NULL)
				error_exit();
			return (ret);
		}
		environ = environ->next;
	}
	return (NULL);
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

int		unset_env(t_list **environ, char *env_name)
{
	return (ft_lstdelcmp(environ, &compare_env, env_name, &clear_env));
}
