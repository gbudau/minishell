/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:59:16 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/01 19:35:27 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_error(char *str, int *last_status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	*last_status = 1;
	return (*last_status);
}

static int	print_cd_error(char *str, int *last_status)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	*last_status = 1;
	errno = 0;
	return (*last_status);
}

int			msh_cd(t_command *cmd, t_list **environ, int *last_status)
{
	char	*home;

	errno = 0;
	if (cmd->argc == 1)
	{
		home = get_env(*environ, "HOME");
		if (home == NULL)
			return (print_error("minishell: cd: HOME not set\n", last_status));
		if (chdir(home) == -1)
			return (print_cd_error(home, last_status));
	}
	else if (cmd->argc > 2)
		return (print_error("minishell: cd: too many arguments\n",
					last_status));
	else
	{
		if (chdir(cmd->argv[1]) == -1)
			return (print_cd_error(cmd->argv[1], last_status));
	}
	*last_status = 0;
	return (0);
}
