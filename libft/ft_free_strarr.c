/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:29:11 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/05 01:14:17 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_strarr(char **info)
{
	int	i;

	if (info == NULL)
		return (NULL);
	i = 0;
	while (info[i])
	{
		free(info[i]);
		i++;
	}
	free(info);
	return (NULL);
}
