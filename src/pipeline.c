/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:31:43 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/25 20:46:38 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"
#include "../include/pipeline.h"
#include "../include/ioredirection.h"
#include "../include/builtins.h"
#include "../include/command.h"
#include "../include/wordexp.h"

static void	init_pipeline(t_pipeline *p)
{
	ft_bzero(p, sizeof(*p));
	p->havepipe = 1;
	p->lastpipe[STDIN_FILENO] = -1;
	p->lastpipe[STDOUT_FILENO] = -1;
}

static void	dup2_close_pipe_fds(int *pipefds, int fd)
{
	if (fd != -1 && pipefds[fd] != -1)
		dup2(pipefds[fd], fd);
	if (pipefds[STDIN_FILENO] != -1)
		close(pipefds[STDIN_FILENO]);
	if (pipefds[STDOUT_FILENO] != -1)
		close(pipefds[STDOUT_FILENO]);
}

static void	execute_in_child_process(t_pipeline *p, t_list *environ,
		int *last_status)
{
	int	idx;

	if (word_expansion(p->cmd, environ, last_status) == -1)
		exit(*last_status);
	if (p->cmd->argv)
		create_and_set_env(&environ, "_", p->cmd->argv[p->cmd->argc - 1]);
	if (p->havepipe)
		dup2_close_pipe_fds(p->lastpipe, STDIN_FILENO);
	if (p->cmd->ispipe)
		dup2_close_pipe_fds(p->curpipe, STDOUT_FILENO);
	if (set_redirections(p->cmd))
		exit(EXIT_FAILURE);
	if ((idx = is_builtin(p->cmd)) != -1)
	{
		restore_signals_handlers();
		do_builtin(p->cmd, &environ, idx, last_status);
		exit(*last_status);
	}
	search_path_and_execute(p->cmd->argv, environ);
}

static void	set_lastpipe_to_curpipe(int *lastpipe, int *curpipe)
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
			dup2_close_pipe_fds(p.lastpipe, -1);
		p.havepipe = p.cmd->ispipe;
		if (p.cmd->ispipe)
			set_lastpipe_to_curpipe(p.lastpipe, p.curpipe);
		p.trav = p.trav->next;
	}
	p.trav = *commands;
	*commands = wait_all_childrens(&p, last_status);
}
