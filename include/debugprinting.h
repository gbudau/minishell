/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugprinting.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:49:59 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 19:53:55 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGPRINTING_H
# define DEBUGPRINTING_H
# include "minishell.h"
# include "lexer.h"
# include "command.h"

void	print_commands(t_list *commands);
void	print_tokens(t_list *tokens);

#endif
