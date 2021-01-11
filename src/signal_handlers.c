/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:46:57 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 16:28:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/signalhandlers.h"

static void	signal_handle(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
	}
	signal(signum, signal_handle);
}

void		ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
