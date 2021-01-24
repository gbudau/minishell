/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:30:34 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 00:43:22 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "minishell.h"

enum	e_redirection_type
{
	REDIRECTION_NONE,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_APPEND
};

enum	e_redirection_order
{
	REDIRECT_INPUT_FIRST,
	REDIRECT_OUTPUT_FIRST
};

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
** redirection_order = which redirection is first(from left to right)
** pid = pid running this command
** redirection_error = if there is no redirection error this flag is FALSE
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
	int		redirection_order;
	pid_t	pid;
	int		redirection_error;
}				t_command;

int				get_last_status(int status);
void			print_interrupt_signal(int last_status);

#endif
