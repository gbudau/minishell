/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:38:55 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 20:28:54 by gbudau           ###   ########.fr       */
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
		ft_putstr_fd(env[NAME], 1);
		ft_putchar_fd('=', 1);
		if (env[VALUE] != NULL)
			ft_putstr_fd(env[VALUE], 1);
		ft_putchar_fd('\n', 1);
		environ = environ->next;
	}
}
