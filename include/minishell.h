/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:14:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 00:03:44 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include "lexer.h"
# include "libft.h"
# define PROMPT "minishell> "

enum	e_bool
{
	FALSE,
	TRUE
};

/*
** List of processes
** argv = arguments array for execve
** env = environment variables array for execve
** status = status of the process
*/

typedef struct	s_process
{
	struct process	*next;
	char			**argv;
	char			**env;
	int				status;
}				t_process;

#endif
