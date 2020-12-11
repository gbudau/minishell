/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:31:43 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/11 23:29:52 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipeline.h"
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

void		execute_in_child_process(t_pipeline *p)
{
	if (p->havepipe)
	{
		close(p->lastpipe[1]);
		dup2(p->lastpipe[0], STDIN_FILENO);
		close(p->lastpipe[0]);
	}
	if (p->cmd->ispipe)
	{
		close(p->curpipe[0]);
		dup2(p->curpipe[1], STDOUT_FILENO);
		close(p->curpipe[1]);
	}
	// TODO Change this to execve
	execvp(p->cmd->argv[0], p->cmd->argv);
	exit(cmd_not_found(p->cmd->argv[0]));
}

void		close_lastpipe(int *lastpipe)
{
	close(lastpipe[0]);
	close(lastpipe[1]);
}

void		set_lastpipe_to_curpipe(int *lastpipe, int *curpipe)
{
	lastpipe[0] = curpipe[0];
	lastpipe[1] = curpipe[1];
}

void		do_pipeline(t_list **commands, t_list *environ, int *last_status)
{
	t_pipeline	p;

	(void)environ;
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
			execute_in_child_process(&p);
		if (p.havepipe)
			close_lastpipe(p.lastpipe);
		p.havepipe = p.cmd->ispipe;
		p.cmd->pid = p.newpid;
		if (p.cmd->ispipe)
			set_lastpipe_to_curpipe(p.lastpipe, p.curpipe);
		p.trav = p.trav->next;
	}
	p.trav = *commands;
	*commands = wait_all_childrens(&p, last_status);
}
