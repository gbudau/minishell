/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:19:57 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/27 21:37:24 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list		*wait_all_childrens(t_pipeline *p, int *last_status)
{
	p->havepipe = 1;
	while (p->havepipe)
	{
		p->cmd = p->trav->content;
		waitpid(p->cmd->pid, &p->wstatus, 0);
		*last_status = get_last_status(p->wstatus);
		p->havepipe = p->cmd->ispipe;
		p->trav = p->trav->next;
	}
	print_interrupt_signal(*last_status);
	return (p->trav);
}
