/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 22:00:52 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	checksave(char **save, char **line, char **next)
{
	if (*save == NULL)
	{
		*line = ft_strdup("");
		*next = NULL;
		return (*line ? 1 : -1);
	}
	if ((*next = ft_strchr(*save, '\n')))
	{
		*(*next)++ = '\0';
		*line = ft_strdup(*save);
		ft_strcpy(*save, *next);
	}
	else
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	return (*line ? 1 : -1);
}

int				get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*next;
	ssize_t			nbytes;
	static	char	*save;

	if (!line || read(fd, save, 0))
		return (-1);
	nbytes = checksave(&save, line, &next);
	while (nbytes > 0 && !next && (nbytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[nbytes] = '\0';
		if ((next = ft_strchr(buff, '\n')))
		{
			*next++ = '\0';
			save = ft_strdup(next);
		}
		if ((next && !save) ||
				!(*line = ft_strjoin_free(*line, buff, FREE_FIRST)))
			nbytes = -1;
	}
	if (next == NULL || nbytes < 0)
		free(save);
	if (nbytes < 0)
		return (-1);
	return (next ? 1 : 0);
}
