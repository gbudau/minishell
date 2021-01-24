/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredirection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:04:08 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 01:18:06 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOREDIRECTION_H
# define IOREDIRECTION_H
# include "minishell.h"
# include "command.h"

int			set_redirections(t_command *cmd);
int			print_error_io(char *str);

#endif
