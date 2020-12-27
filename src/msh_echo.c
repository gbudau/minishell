/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:40:39 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/27 16:00:00 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if the string is "-n" flag
** It can containt multiple "n" characters like "-nnn"
** Return TRUE if it's a "-n" flag or FALSE otherwise
*/

static int	is_no_trailing_newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || str[i + 1] != 'n')
		return (FALSE);
	i += 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Return the numbers of "-n" flags found in the arguments vector
*/

static int	skip_no_trailing_newline_flags(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && is_no_trailing_newline_flag(argv[i]))
		i++;
	return (i);
}

/*
** echo builtin command
**
** Parameters:
** cmd = a command structure containing the command arguments count and
** 		 the command arguments vector
** environ = a list containing the environmental variable (not used here)
** last_status = status of the last command (we use this in the exit builtin)
**
** Return 0 if it was successfully executed, 1 otherwise.
*/

int			msh_echo(t_command *cmd, t_list **environ, int *last_status)
{
	char	**argv;
	int		no_trailing_newline;

	(void)environ;
	no_trailing_newline = FALSE;
	argv = cmd->argv;
	if (cmd->argc > 1)
		no_trailing_newline = is_no_trailing_newline_flag(argv[1]);
	argv++;
	argv += skip_no_trailing_newline_flags(argv);
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
