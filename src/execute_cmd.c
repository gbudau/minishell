/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/12 23:13:54 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void		search_path_and_execute(char **argv, t_list *environ)
{
	// TODO Create an env array that will get passed to execve
	// TODO Or make environ an array of strings and create functions
	// TODO That can modify it (add/delete/print/etc...) like the ones in env.c

	(void)environ;

	// TODO If the command name start with a slash (/) character
	// TODO Use execve directly
	// TODO Else
	// TODO Create a function that search in PATH for the command name
	// TODO Then use execve
	execvp(argv[0], argv);
	exit(cmd_not_found(argv[0]));
}
