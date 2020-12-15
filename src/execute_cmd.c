/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 19:46:27 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

/*
** TODO:
** Create an env array that will get passed to execve
** Or make environ an array of strings and create functions
** That can modify it (add/delete/print/etc...) like the ones in env.c
**
** TODO:
** If the command name start with a slash (/) character
** Use execve directly
** Else
** Create a function that search in PATH for the command name
** Then use execve
**
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/
** V3_chap02.html#tag_18_09_01_01
*/

void		search_path_and_execute(char **argv, t_list *environ)
{
	(void)environ;
	execvp(argv[0], argv);
	exit(cmd_not_found(argv[0]));
}
