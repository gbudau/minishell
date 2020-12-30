/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:35:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/30 18:35:59 by fportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include "command.h"

int		is_builtin(t_command *cmd);
void	do_builtin(t_command *cmd, t_list **environ, int idx, int *last_status);
int		msh_echo(t_command *cmd, t_list **environ, int *last_status);
int		msh_exit(t_command *cmd, t_list **environ, int *last_status);
int		msh_pwd(t_command *cmd, t_list **environ, int *last_status);
int		msh_env(t_command *cmd, t_list **environ, int *last_status);
int		msh_unset(t_command *cmd, t_list **environ, int *last_status);
int		msh_export(t_command *cmd, t_list **environ, int *last_status);
int		msh_cd(t_command *cmd, t_list **environ, int *last_status);
void	mergesort(t_list **alist);


#endif
