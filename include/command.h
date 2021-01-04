/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:30:34 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/04 21:09:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "minishell.h"

/*
** Command
** argc = number of arguments
** argv = arguments array for execve
** env = environment variables array for execve
** status = status of the command
** ispipe = pipe simbol follow this command
** input = input redirection file
** output = output redirection file
** redirect_type = type of output redirection (normal or append)
** pid = pid running this command
*/

typedef struct	s_command
{
	int		argc;
	char	**argv;
	char	**env;
	char	*input;
	char	*output;
	int		ispipe;
	int		status;
	int		redirect_type;
	pid_t	pid;
}				t_command;

int				get_last_status(int status);

#endif
