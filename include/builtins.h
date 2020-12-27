/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:35:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/27 19:49:17 by gbudau           ###   ########.fr       */
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
int		msh_unset(t_command *cmd, t_list **environ, int *last_status);

#endif
