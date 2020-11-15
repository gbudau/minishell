/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:18:41 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 16:51:44 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return the number of substrings found in s that are
** separated by any character found in delim
*/

size_t	ft_str_count_s(const char *s, const char *delim)
{
	size_t i;
	size_t state;

	i = 0;
	state = STATE_OUT_WORD;
	while (*s != '\0')
	{
		if (ft_strchr(delim, *s))
			state = STATE_OUT_WORD;
		else if (state == STATE_OUT_WORD)
		{
			state = STATE_IN_WORD;
			i++;
		}
		s++;
	}
	return (i);
}
