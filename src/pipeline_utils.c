/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:19:57 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 23:20:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list		*wait_all_childrens(t_pipeline *p, int *last_status)
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
