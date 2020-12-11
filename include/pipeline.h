/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:28:58 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/11 21:29:15 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H
# include "minishell.h"

typedef struct	s_pipeline
{
	t_list		*trav;
	t_command	*cmd;
	pid_t		newpid;
	int			havepipe;
	int			lastpipe[2];
	int			curpipe[2];
	int			status;
}				t_pipeline;

void	do_pipeline(t_list **commands, t_list *environ, int *last_status);

#endif
