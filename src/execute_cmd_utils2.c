/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 22:54:42 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/28 23:22:46 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
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

int		is_absolute_cmd(char *str)
{
	return (str[0] == '/' || !ft_strncmp(str, "./", 2)
							|| !ft_strncmp(str, "../", 3));
}

void	exec_file(char *filename, char **env_array)
{
	char	*argv[3];

	argv[0] = "/bin/bash";
	argv[1] = filename;
	argv[2] = NULL;
	execve(argv[0], argv, env_array);
}
