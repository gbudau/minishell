/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:00:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 16:50:57 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_count_c(const char *s, char c)
{
	size_t i;
	size_t state;

	i = 0;
	state = STATE_OUT_WORD;
	while (*s != '\0')
	{
		if (*s == c)
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
