/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:48:36 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/02 20:39:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALHANDLERS_H
# define SIGNALHANDLERS_H
# include "minishell.h"
# include <signal.h>

void	setup_signals_handlers(void);
void	setup_signals_before_fork(void);
void	ignore_signals(void);
void	restore_signals_handlers(void);
int		end_of_input(int gnl, char **input);

#endif
