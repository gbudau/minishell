/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 23:06:38 by gbudau           ###   ########.fr       */
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
# include "pipeline.h"
# include "ioredirection.h"
# include "builtins.h"
# include "execute.h"
# include "signalhandlers.h"
# include "clear.h"
# include "errors.h"
# define PROMPT "\x1b[1;36mminishell> \x1b[0m"

enum	e_bool
{
	FALSE,
	TRUE
};

/*
** Data used for minishell
** environ = List of environmental variables.
**           The content of a list node is an array of strings
**           where an environmental variable is stored
**           with the format env_array = {"env_name", "env_value", NULL}
** commands = List of commands.
**            The content of a list node is a struct s_command
**            defined in command.h header
** last_status = status of the last executed command
*/

typedef struct	s_shell
{
	t_list	*environ;
	t_list	*commands;
	int		last_status;
}				t_shell;

void			set_shlvl(t_list **environ);
void			parse(t_shell *shell, char *input);
void			execute_cmds(t_shell *shell);

#endif
