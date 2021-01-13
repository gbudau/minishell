/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 21:15:44 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/13 22:27:49 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDEXP_H
# define WORDEXP_H
# include "minishell.h"
# include "lexer.h"
# include "env.h"

int		word_expansion(t_command *cmd, t_list *environ, int *last_status);
int		is_env_format(char c, int flag);
char	*env_or_last_status(char **words, size_t *i,
							t_list *environ, int last_status);
void	remove_quotes(t_list *word_list);
void	variable_expansion(char **words, t_list **word_list,
							t_list *environ, int *last_status);
int		word_exp_io(t_command *cmd, t_list *environ, int *last_status);
void	word_exp_argv(t_command *cmd, t_list *environ, int *last_status);

#endif
