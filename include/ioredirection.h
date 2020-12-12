/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredirection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:04:08 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/12 21:06:49 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOREDIRECTION_H
# define IOREDIRECTION_H
# include "minishell.h"
# include "command.h"

int			set_redirections(t_command *cmd);

#endif
