/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 19:22:25 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include "env.h"
# include "lexer.h"
# include "libft.h"
# define PROMPT "minishell> "

enum	e_bool
{
	FALSE,
	TRUE
};

/*
** Command
** argc = number of arguments
** argv = arguments array for execve
** env = environment variables array for execve
** status = status of the process
** ispipe = pipe simbol follow this command
** input = input redirection file
** output = output redirection file
*/

typedef struct	s_command
{
	int				argc;
	char			**argv;
	char			**env;
	char			*input;
	char			*output;
	int				ispipe;
	int				status;
}				t_command;

/*
** Data used for minishell
** env = list of environmental variables
** tokens = list of tokens
** commands = list of commands
** line	= line of input from terminal
*/

typedef struct	s_shell
{
	t_list		*environ;
	t_list		*tokens;
	t_list		*commands;
	char		*input;
}				t_shell;

void	error_exit(void);

#endif
