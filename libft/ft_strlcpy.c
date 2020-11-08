/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:39:35 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/08 01:13:14 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char *start;

	if (size == 0)
		return (ft_strlen(src));
	start = src;
	while (*src && size-- > 1)
		*dst++ = *src++;
	*dst = '\0';
	while (*src)
		src++;
	return (src - start);
}
