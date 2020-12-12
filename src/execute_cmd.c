/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/12 21:18:17 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void		search_path_and_execute(char **argv, t_list *environ)
{
	// TODO Create and env array that will get passed to execve
	(void)environ;
	// TODO Create a function that search in PATH for the command name
	// TODO If it doesn't start with slash (/)
	// TODO Then use execve
	execvp(argv[0], argv);
	exit(cmd_not_found(argv[0]));
}
