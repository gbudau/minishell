/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 21:15:44 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/16 19:25:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDEXP_H
# define WORDEXP_H
# include "minishell.h"
# include "lexer.h"
# include "env.h"

void	word_expansion(t_list **tokens, t_list *environ, int *last_status);
int		is_env_format(char c, int flag);
char	*last_status_value(size_t *i, int *last_status);
void	skip_single_quote(char **words, size_t *i);
char	*env_or_last_status(char **words, size_t *i,
							t_list *environ, int *last_status);
void	remove_quotes(t_list *word_list, char *words, size_t expanded);
char	*env_value(char **words, size_t *i, t_list *environ);

#endif
