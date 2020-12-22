/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:17:35 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/22 19:32:20 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	msh_pwd(t_command *cmd, t_list **environ, int *last_status)
{
	char	buf[PATH_MAX];

	(void)environ;
	(void)cmd;
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		*last_status = 1;
		error_exit();
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	*last_status = 0;
	return (0);
}
