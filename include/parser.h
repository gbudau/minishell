/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:55:58 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 23:18:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../include/minishell.h"
# include "../include/command.h"
# include "../include/lexer.h"

void	clear_command(void *command);
int		add_command(t_list **tokens, t_command *cmd);

#endif
