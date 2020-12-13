/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:31:43 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/13 17:40:10 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipeline.h"
#include "ioredirection.h"
#include "builtins.h"
#include "command.h"

static void	init_pipeline(t_pipeline *p)
{
	ft_bzero(p, sizeof(*p));
	p->havepipe = 1;
	p->lastpipe[0] = -1;
	p->lastpipe[1] = -1;
}

t_list	*wait_all_childrens(t_pipeline *p, int *last_status)
{
	p->havepipe = 1;
	while (p->havepipe)
	{
		p->cmd = p->trav->content;
		waitpid(p->cmd->pid, &p->status, 0);
		*last_status = get_last_status(p->status);
		p->havepipe = p->cmd->ispipe;
		p->trav = p->trav->next;
	}
	return (p->trav);
}

void		close_pipe_fds(int *pipefds)
{
	if (pipefds[0] != -1)
		close(pipefds[0]);
	if (pipefds[1] != -1)
		close(pipefds[1]);
}

void		execute_in_child_process(t_pipeline *p, t_list *environ)
{
	int	error;
	int	idx;

	if (p->havepipe)
	{
		dup2(p->lastpipe[0], STDIN_FILENO);
		close_pipe_fds(p->lastpipe);
	}
	if (p->cmd->ispipe)
	{
		dup2(p->curpipe[1], STDOUT_FILENO);
		close_pipe_fds(p->curpipe);
	}
	error = set_redirections(p->cmd);
	if (error)
		exit(EXIT_FAILURE);
	if ((idx = is_builtin(p->cmd)) != -1)
		exit(do_builtin(p->cmd, &environ, idx));
	search_path_and_execute(p->cmd->argv, environ);
}

void		set_lastpipe_to_curpipe(int *lastpipe, int *curpipe)
{
	lastpipe[0] = curpipe[0];
	lastpipe[1] = curpipe[1];
}

void		do_pipeline(t_list **commands, t_list *environ, int *last_status)
{
	t_pipeline	p;

	init_pipeline(&p);
	p.trav = *commands;
	while (p.newpid != -1 && p.havepipe)
	{
		p.cmd = p.trav->content;
		if (p.cmd->ispipe)
			if (pipe(p.curpipe) != 0)
				error_exit();
		if ((p.newpid = fork()) < 0)
			error_exit();
		if (p.newpid == 0)
			execute_in_child_process(&p, environ);
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
