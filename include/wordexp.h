/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 21:15:44 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 17:02:02 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDEXP_H
# define WORDEXP_H
# include "minishell.h"
# include "lexer.h"
# include "env.h"

void	word_expansion(t_list **tokens, t_list *environ, int *last_status);
int		is_env_format(char c, int flag);
char	*env_or_last_status(char **words, size_t *i,
							t_list *environ, int *last_status);
void	remove_quotes(t_list *word_list, char *words, size_t expanded);

#endif
