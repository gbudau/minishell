/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 16:08:04 by gbudau           ###   ########.fr       */
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
# include "lexer.h"
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
	t_list		*commands;
}				t_shell;


void	parse(t_shell *shell, char *input);
void	error_exit(void);

#endif
