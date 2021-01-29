/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:18:58 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/29 11:04:05 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

void	search_path_and_execute(char **argv, t_list *environ);
char	*build_path_binary(char *dir_name, char *cmd_name);
char	**create_env_array(t_list *environ);
char	*add_curr_dir_to_path(char *path);
int		is_absolute_cmd(char *str);
int		exec_file(char *filename, t_list *environ);

#endif
