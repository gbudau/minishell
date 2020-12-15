/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:52:08 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 21:57:38 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"

int		get_last_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int		cmd_not_found(char *str)
{
	char	*not_found;

	not_found = ft_strjoin(str, ": command not found\n");
	if (not_found == NULL)
		error_exit();
	ft_putstr_fd(not_found, STDERR_FILENO);
	free(not_found);
	return (127);
}
