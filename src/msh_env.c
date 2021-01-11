/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:44:53 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 16:18:08 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	msh_env(t_command *cmd, t_list **environ, int *last_status)
{
	if (cmd->argc != 1)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		*last_status = 1;
	}
	else
	{
		print_env(*environ);
		*last_status = 0;
	}
	return (*last_status);
}
