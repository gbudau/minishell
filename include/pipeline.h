/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:28:58 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/27 21:35:24 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H
# include "minishell.h"

/*
** Represents a command inside a pipeline
** trav = list of commands
** cmd = pointer to a command struct, defined in command.h
** newpid = the pid of current command
** lastpipe = the pipe of the previous command (if any)
** curpipe = pipe of the current command
** wstatus = the return of waitpid for the current command
*/

typedef struct	s_pipeline
{
	t_list		*trav;
	t_command	*cmd;
	pid_t		newpid;
	int			havepipe;
	int			lastpipe[2];
	int			curpipe[2];
	int			wstatus;
}				t_pipeline;

void			do_pipeline(t_list **commands, t_list *environ,
				int *last_status);
t_list			*wait_all_childrens(t_pipeline *p, int *last_status);

#endif
