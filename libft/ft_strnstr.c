/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:40:47 by gbudau            #+#    #+#             */
/*   Updated: 2020/09/12 15:20:46 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_str(const char *hay, const char *need, size_t len)
{
	size_t	i;

	i = 0;
	while (hay[i] && need[i] && i < len)
	{
		if (hay[i] != need[i])
			return (0);
		i++;
	}
	if (need[i] == '\0')
		return (1);
	return (0);
}

char		*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;

	if (*need == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i])
	{
		if (find_str(&hay[i], need, len))
			return ((char *)&hay[i]);
		i++;
	}
	return (NULL);
}
