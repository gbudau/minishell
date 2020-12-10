/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/10 17:21:26 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft.h"
# include "env.h"
# include "parser.h"
# include "clear.h"
# define PROMPT "minishell> "

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_redirection_type
{
	REDIRECTION_NONE,
	REDIRECTION_OUTPUT,
	REDIRECTION_INPUT,
	REDIRECTION_APPEND
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

/*
** Data used for minishell
** env = list of environmental variables
** tokens = list of tokens
** commands = list of commands
** line	= line of input from terminal
** last_status = status of the last executed command
*/

typedef struct	s_shell
{
	t_list	*environ;
	t_list	*commands;
	int		last_status;
}				t_shell;

void			parse(t_shell *shell, char *input);
void			error_exit(void);

#endif
