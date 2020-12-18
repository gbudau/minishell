/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:46:57 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/18 17:33:35 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signalhandlers.h"

void		signal_handle(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("\b\b", STDIN_FILENO);
		ft_putstr_fd("  ", STDIN_FILENO);
		ft_putstr_fd("\b\b", STDIN_FILENO);
	}
	if (signum == SIGINT || signum == SIGQUIT)
	{
		ft_putstr_fd("\nminishell> ", STDOUT_FILENO);
	}
	signal(signum, signal_handle);
}

void		setup_signals_handlers(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, signal_handle);
}

void		restore_signals_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
** Join the line with the input until it finds a newline in it
** Using this to deal with the case when the user presses CTRL-D
** While in the middle of a input
*/

static void	manage_eof(char **line)
{
	int		gnl;
	char	*input;

	while ((gnl = get_next_line(STDIN_FILENO, &input)) == 0)
		*line = ft_strjoin_free(*line, input, FREE_BOTH);
	if (gnl == -1)
		error_exit();
	*line = ft_strjoin_free(*line, input, FREE_BOTH);
}

/*
** If GNL returns 0 and the input is not empty
** use manage_eof to join new input until it finds a newline
** Return 1 if there was no input and gnl returned 0
** Return 0 in any other cases
*/

int			end_of_input(int gnl, char **input)
{
	if (gnl == 0 && **input != '\0')
		manage_eof(input);
	else if (gnl == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
