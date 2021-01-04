/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/04 21:46:39 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

static char	*search_inside_directory(char *directory_path, char *cmd_name)
{
	DIR				*dir_ptr;
	struct dirent	*dirent_ptr;
	char			*filename;

	dir_ptr = opendir(directory_path);
	if (dir_ptr == NULL)
		return (NULL);
	while ((dirent_ptr = readdir(dir_ptr)) != NULL)
	{
		if ((dirent_ptr->d_type == DT_LNK || dirent_ptr->d_type == DT_REG) &&
				ft_strcmp(cmd_name, dirent_ptr->d_name) == 0)
		{
			filename = build_path_binary(directory_path, cmd_name);
			closedir(dir_ptr);
			return (filename);
		}
	}
	if (dir_ptr != NULL)
		closedir(dir_ptr);
	return (NULL);
}

static char	*search_and_build_path(char *path, char *cmd_name)
{
	char			**splitted_paths;
	size_t			i;
	char			*filename;

	if (path == NULL || *path == '\0')
		return (NULL);
	splitted_paths = ft_split(path, ':');
	free(path);
	if (splitted_paths == NULL)
		return (NULL);
	i = 0;
	while (splitted_paths[i])
	{
		filename = search_inside_directory(splitted_paths[i], cmd_name);
		if (filename != NULL)
		{
			ft_free_strarr(splitted_paths);
			return (filename);
		}
		i++;
	}
	ft_free_strarr(splitted_paths);
	return (NULL);
}

void		search_path_and_execute(char **argv, t_list *environ)
{
	char	**env_array;
	char	*filename;

	env_array = create_env_array(environ);
	if (env_array == NULL)
		error_exit();
	if (argv[0][0] == '.' || argv[0][0] == '/')
	{
		restore_signals_handlers();
		execve(argv[0], argv, env_array);
	}
	else
	{
		filename = search_and_build_path(get_env(environ, "PATH"), argv[0]);
		restore_signals_handlers();
		if (filename)
			execve(filename, argv, env_array);
	}
	exit(execve_error(argv[0]));
}

void		do_cmd(t_command *cmd, t_list **environ, int *last_status)
{
	int		pid;
	int		status;
	int		idx;
	int		error;

	if ((idx = is_builtin(cmd)) != -1)
	{
		do_builtin(cmd, environ, idx, last_status);
		return ;
	}
	setup_signals_before_fork();
	if ((pid = fork()) == -1)
		error_exit();
	if (pid == 0)
	{
		ignore_signals();
		error = set_redirections(cmd);
		if (error)
			exit(EXIT_FAILURE);
		search_path_and_execute(cmd->argv, *environ);
	}
	if (waitpid(pid, &status, 0) < 0)
		error_exit();
	ignore_signals();
	*last_status = get_last_status(status);
}

void		execute_cmds(t_shell *shell)
{
	t_list		*trav;
	t_command	*cmd;

	trav = shell->commands;
	while (trav != NULL)
	{
		errno = 0;
		cmd = trav->content;
		if (cmd->ispipe)
			do_pipeline(&trav, shell->environ, &shell->last_status);
		else
		{
			do_cmd(cmd, &shell->environ, &shell->last_status);
			trav = trav->next;
		}
	}
}
