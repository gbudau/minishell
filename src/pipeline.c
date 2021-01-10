/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:31:43 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/06 18:28:05 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"
#include "../include/pipeline.h"
#include "../include/ioredirection.h"
#include "../include/builtins.h"
#include "../include/command.h"

static void	init_pipeline(t_pipeline *p)
{
	ft_bzero(p, sizeof(*p));
	p->havepipe = 1;
	p->lastpipe[STDIN_FILENO] = -1;
	p->lastpipe[STDOUT_FILENO] = -1;
}

void		close_pipe_fds(int *pipefds)
{
	if (pipefds[STDIN_FILENO] != -1)
		close(pipefds[STDIN_FILENO]);
	if (pipefds[STDOUT_FILENO] != -1)
		close(pipefds[STDOUT_FILENO]);
}

void		execute_in_child_process(t_pipeline *p, t_list *environ,
		int *last_status)
{
	int	error;
	int	idx;

	if (p->havepipe)
	{
		dup2(p->lastpipe[STDIN_FILENO], STDIN_FILENO);
		close_pipe_fds(p->lastpipe);
	}
	if (p->cmd->ispipe)
	{
		dup2(p->curpipe[STDOUT_FILENO], STDOUT_FILENO);
		close_pipe_fds(p->curpipe);
	}
	error = set_redirections(p->cmd);
	if (error)
		exit(EXIT_FAILURE);
	if ((idx = is_builtin(p->cmd)) != -1)
	{
		restore_signals_handlers();
		do_builtin(p->cmd, &environ, idx, last_status);
		exit(*last_status);
	}
	search_path_and_execute(p->cmd->argv, environ);
}

void		set_lastpipe_to_curpipe(int *lastpipe, int *curpipe)
{
	lastpipe[STDIN_FILENO] = curpipe[STDIN_FILENO];
	lastpipe[STDOUT_FILENO] = curpipe[STDOUT_FILENO];
}

void		do_pipeline(t_list **commands, t_list *environ, int *last_status)
{
	t_pipeline	p;

	init_pipeline(&p);
	p.trav = *commands;
	while (p.havepipe)
	{
		p.cmd = p.trav->content;
		if (p.cmd->ispipe && pipe(p.curpipe) < 0)
			error_exit();
		if ((p.newpid = fork()) < 0)
			error_exit();
		if (p.newpid == 0)
			execute_in_child_process(&p, environ, last_status);
		p.cmd->pid = p.newpid;
		if (p.havepipe)
			close_pipe_fds(p.lastpipe);
		p.havepipe = p.cmd->ispipe;
		if (p.cmd->ispipe)
			set_lastpipe_to_curpipe(p.lastpipe, p.curpipe);
		p.trav = p.trav->next;
	}
	p.trav = *commands;
	*commands = wait_all_childrens(&p, last_status);
}
