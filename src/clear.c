/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 19:28:58 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/06 19:34:05 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clear.h"

void	clear_env(void *content)
{
	ft_free_strarr(content);
}

void	clear_command(void *command)
{
	t_command	*cmd;

	cmd = command;
	cmd->argv = ft_free_strarr(cmd->argv);
	cmd->env = ft_free_strarr(cmd->env);
	free(cmd->input);
	free(cmd->output);
	free(command);
}

/*
** Free one token node from the list of tokens
*/

void	clear_token(void *node)
{
	free(((t_token *)node)->str);
	free(node);
}
