/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/18 17:33:41 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

/*
** TODO:
** Create an env array that will get passed to execve
** Or make environ an array of strings and create functions
** That can modify it (add/delete/print/etc...) like the ones in env.c
**
** TODO:
** If the command name start with a slash (/) character
** Use execve directly
** Else
** Create a function that search in PATH for the command name
** Then use execve
**
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/
** V3_chap02.html#tag_18_09_01_01
*/

void	search_path_and_execute(char **argv, t_list *environ)
{
	(void)environ;
	execvp(argv[0], argv);
	exit(cmd_not_found(argv[0]));
}

void	do_cmd(t_command *cmd, t_list **environ, int *last_status)
{
	int		pid;
	int		status;
	int		idx;
	int		error;

	if ((idx = is_builtin(cmd)) != -1)
	{
		do_builtin(cmd, environ, idx, last_status);
		return ;
	}
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		restore_signals_handlers();
		error = set_redirections(cmd);
		if (error)
			exit(EXIT_FAILURE);
		search_path_and_execute(cmd->argv, *environ);
	}
	if (waitpid(pid, &status, 0) < 0)
		error_exit();
	*last_status = get_last_status(status);
}

void	execute_cmds(t_shell *shell)
{
	t_list		*trav;
	t_command	*cmd;

	trav = shell->commands;
	while (trav != NULL)
	{
		cmd = trav->content;
		if (cmd->ispipe)
			do_pipeline(&trav, shell->environ, &shell->last_status);
		else
		{
			do_cmd(cmd, &shell->environ, &shell->last_status);
			trav = trav->next;
		}
	}
}
