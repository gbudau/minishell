/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 22:54:42 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/31 01:28:32 by gbudau           ###   ########.fr       */
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

char		*add_curr_dir_to_path(char *path)
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

int			is_absolute_cmd(char *str)
{
	return (str[0] == '/' || !ft_strncmp(str, "./", 2)
							|| !ft_strncmp(str, "../", 3));
}

static void	init_subshell(t_shell *shell, t_list *environ)
{
	char	curr_dir[PATH_MAX + 1];

	ft_bzero(shell, sizeof(*shell));
	shell->environ = environ;
	create_and_set_env(&shell->environ, "_", "PATH");
	set_shlvl(&shell->environ);
	if (getcwd(curr_dir, PATH_MAX) == NULL)
		error_exit();
	create_and_set_env(&shell->environ, "PWD", curr_dir);
}

static int	open_error(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_perror(filename);
	return (127);
}

int			exec_file(char *filename, t_list *environ)
{
	t_shell	shell;
	char	*line;
	int		gnl;
	int		fd;

	ignore_signals();
	if ((fd = open(filename, O_RDONLY)) == -1)
		open_error(filename);
	init_subshell(&shell, environ);
	gnl = 1;
	while (gnl > 0)
	{
		if ((gnl = get_next_line(fd, &line)) < 0)
			error_exit();
		parse(&shell, line);
		free(line);
		signal(SIGINT, SIG_DFL);
		execute_cmds(&shell);
		signal(SIGINT, SIG_IGN);
		ft_lstclear(&shell.commands, clear_command);
	}
	ft_lstclear(&shell.environ, clear_env);
	close(fd);
	return (shell.last_status);
}
