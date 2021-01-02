/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:03:19 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/02 17:11:25 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *s)
{
	char *err;

	if (s && *s)
	{
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	err = strerror(errno);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
