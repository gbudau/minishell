/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:39:23 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/04 19:52:15 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"

/*
** The flag variable control if ft_isdigit is used or not
** This is because POSIX specifies that
** environmental variables don't begin with a digit
** https://pubs.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html
*/

int		is_env_format(char c, int flag)
{
	return (ft_isalpha(c) || c == '_' || c == '?' || (flag && ft_isdigit(c)));
}

char	*last_status_value(size_t *i, int last_status)
{
	char	*status;

	*i += 2;
	status = ft_itoa(last_status);
	if (status == NULL)
		error_exit();
	return (status);
}

void	skip_single_quote(char **words, size_t *i)
{
	(*i)++;
	while ((*words)[*i] && (*words)[*i] != '\'')
		(*i)++;
	if ((*words)[*i])
		(*i)++;
}

char	*env_or_last_status(char **words, size_t *i,
							t_list *environ, int last_status)
{
	if ((*words)[*i + 1] == '?')
		return (last_status_value(i, last_status));
	else
		return (env_value(words, i, environ));
}
