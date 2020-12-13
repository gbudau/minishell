/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:22 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/13 17:41:46 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Write this function
int		msh_exit(t_command *cmd, t_list **environ)
{
	(void)cmd;
	(void)environ;
	ft_putstr_fd("Executing exit builtin\n", STDOUT_FILENO);
	return (0);
}
