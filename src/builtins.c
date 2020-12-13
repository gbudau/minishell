/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:34:40 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/13 17:42:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(t_command *cmd)
{
	static const char	*builtins[] = {"echo", "exit", NULL};
	int					i;

	i = 0;
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

void	restore_and_close_stdin_and_stdout(int stdin_fd_copy, int stdout_fd_copy)
{
	dup2(stdin_fd_copy, STDIN_FILENO);
	dup2(stdout_fd_copy, STDOUT_FILENO);
	close(stdin_fd_copy);
	close(stdout_fd_copy);
}

int		do_builtin(t_command *cmd, t_list **environ, int idx)
{
	static int	(*fptr[3])(t_command *, t_list **) =
								{ msh_echo, msh_exit, NULL };
	int			status;
	int			stdin_fd_copy;
	int			stdout_fd_copy;
	
	save_stdin_and_stdout(&stdin_fd_copy, &stdout_fd_copy);
	status = set_redirections(cmd);
	if (status == 0)
		status = fptr[idx](cmd, environ);
	restore_and_close_stdin_and_stdout(stdin_fd_copy, stdout_fd_copy);
	return(status);
}
