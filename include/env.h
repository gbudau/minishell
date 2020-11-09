/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:54:37 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 19:26:08 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "minishell.h"
# include "libft.h"

enum	e_environ
{
	NAME,
	VALUE
};

void	init_env(t_list **environ);
void	print_env(t_list *environ);

#endif
