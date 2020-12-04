/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:54:37 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/04 19:34:21 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "minishell.h"
# include "libft.h"

enum	e_environ
{
	ENV_NAME,
	ENV_VALUE
};

void	init_env(t_list **environ);
void	print_env(t_list *environ);
char	*get_env(t_list *environ, char *match);
void	set_env(t_list **environ, char **newenv);
void	clear_env(void *content);
int		compare_env(const void *content, const void *match);
int		unset_env(t_list **environ, char *env);
void	add_env_front(t_list **environ, char **env);

#endif
