/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/11 21:34:49 by gbudau           ###   ########.fr       */
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
# include "command.h"
# include "parser.h"
# include "pipeline.h"
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

void	parse(t_shell *shell, char *input);
void	error_exit(void);
int		get_last_status(int status);
int		cmd_not_found(char *str);

#endif
