/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:40:39 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/16 19:03:43 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_echo(t_command *cmd, t_list **environ, int *last_status)
{
	char	**argv;
	int		no_trailing_newline;

	(void)environ;
	no_trailing_newline = FALSE;
	argv = cmd->argv;
	if (cmd->argc > 1)
		no_trailing_newline = ft_strcmp(argv[1], "-n") == 0;
	argv++;
	if (no_trailing_newline)
		argv++;
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (*(argv + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		argv++;
	}
	if (no_trailing_newline == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	*last_status = 0;
	return (*last_status);
}
