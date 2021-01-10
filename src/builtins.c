/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:34:40 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/06 22:53:38 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_builtin(t_command *cmd)
{
	static const char	*builtins[] = {"echo", "exit", "pwd", "env", "unset",
		"export", "cd", NULL};
	int					i;

	i = 0;
	if (cmd->argv == NULL)
		return (-2);
	while (builtins[i])
	{
		if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
** Save a copy of stdin and stdout file descriptors
*/

void	save_stdin_and_stdout(int *stdin_fd_copy, int *stdout_fd_copy)
{
	*stdin_fd_copy = dup(STDIN_FILENO);
	*stdout_fd_copy = dup(STDOUT_FILENO);
}

/*
** Restore stdin and stdout file descriptors
** From the copies and close the copies
*/

void	restore_and_close_stdin_and_stdout(int stdin_copy, int stdout_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}

void	do_builtin(t_command *cmd, t_list **environ, int idx, int *last_status)
{
	static int	(*const fptr[])(t_command *, t_list **, int *) =
	{msh_echo, msh_exit, msh_pwd, msh_env, msh_unset, msh_export, msh_cd, NULL};
	int			stdin_fd_copy;
	int			stdout_fd_copy;

	save_stdin_and_stdout(&stdin_fd_copy, &stdout_fd_copy);
	*last_status = set_redirections(cmd);
	if (*last_status == 0 && idx != -2)
		fptr[idx](cmd, environ, last_status);
	restore_and_close_stdin_and_stdout(stdin_fd_copy, stdout_fd_copy);
}
