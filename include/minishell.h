/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/03 20:11:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include "libft.h"
# include "env.h"
# include "command.h"
# include "parser.h"
# include "pipeline.h"
# include "ioredirection.h"
# include "builtins.h"
# include "execute.h"
# include "signalhandlers.h"
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
void			execute_cmds(t_shell *shell);
int				get_last_status(int status);

/*
** TODO: Maybe set the functions prototyes below to a header
** that contain only error functions and include it in here
*/

void			not_a_valid_identifier(char *str);
void			error_exit(void);

#endif
