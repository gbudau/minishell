/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:22 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/16 19:02:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_exit(t_command *cmd, t_list **environ, int *last_status)
{
	(void)cmd;
	(void)environ;
	exit(*last_status);
	return (0);
}
