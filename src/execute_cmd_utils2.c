/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 22:54:42 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/24 23:08:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/errors.h"

/*
** If the path is not NULL
** Adds current directory '.' to path if path is an empty string
** Or if the path starts or ends with ':'
**
** path = NULL      -> path = NULL
** path = ""        -> path = "."
** path = ":/bin"   -> path = ".:/bin"
** path = "/bin:"   -> path = "/bin:."
** path = ":/bin:"  -> path = ".:/bin:."
*/

char	*add_curr_dir_to_path(char *path)
{
	if (path && (*path == '\0' || *path == ':'))
	{
		path = ft_strjoin_free(".", path, FREE_SECOND);
		if (path == NULL)
			error_exit();
	}
	if (path && path[ft_strlen(path) - 1] == ':')
	{
		path = ft_strjoin_free(path, ".", FREE_FIRST);
		if (path == NULL)
			error_exit();
	}
	return (path);
}
