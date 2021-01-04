/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:14:13 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/04 19:08:05 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

static char	*create_env(void *content)
{
	char	**str_array;
	char	*env;

	str_array = content;
	if (str_array[ENV_VALUE] == NULL)
		return (NULL);
	env = ft_strjoin(str_array[ENV_NAME], "=");
	if (env == NULL)
		error_exit();
	env = ft_strjoin_free(env, str_array[ENV_VALUE], FREE_FIRST);
	if (env == NULL)
		error_exit();
	return (env);
}

static char	**create_env_array(t_list *environ)
{
	int		list_size;
	char	**env_array;
	size_t	i;
	char	*env;

	list_size = ft_lstsize(environ);
	if (list_size == 0)
		return (NULL);
	env_array = ft_calloc(list_size + 1, sizeof(*env_array));
	if (env_array == NULL)
		return (NULL);
	i = 0;
	while (environ != NULL)
	{
		env = create_env(environ->content);
		if (env)
		{
			env_array[i] = env;
			i++;
		}
		environ = environ->next;
	}
	return (env_array);
}

static char	*build_path_binary(char *dir_name, char *cmd_name)
{
	char	*filename;

	filename = ft_strjoin(dir_name, "/");
	if (filename == NULL)
		error_exit();
	filename = ft_strjoin_free(filename, cmd_name, FREE_FIRST);
	if (filename == NULL)
		error_exit();
	return (filename);
}

static char	*search_and_build_path(char *path, char *cmd_name)
{
	char			**splitted_paths;
	DIR				*dir_ptr;
	struct dirent	*dirent_ptr;
	size_t			i;

	if (path == NULL || *path == '\0')
		return (NULL);
	splitted_paths = ft_split(path, ':');
	if (splitted_paths == NULL)
		return (NULL);
	i = 0;
	while (splitted_paths[i])
	{
		dir_ptr = opendir(splitted_paths[i]);
		while (dir_ptr != NULL && (dirent_ptr = readdir(dir_ptr)) != NULL)
		{
			if (dirent_ptr->d_type == DT_LNK || dirent_ptr->d_type == DT_REG)
			{
				if (ft_strcmp(cmd_name, dirent_ptr->d_name) == 0)
				{
					free(path);
					path = build_path_binary(splitted_paths[i], cmd_name);
					closedir(dir_ptr);
					ft_free_strarr(splitted_paths);
					return (path);
				}
			}
		}
		if (dir_ptr != NULL)
			closedir(dir_ptr);
		i++;
	}
	ft_free_strarr(splitted_paths);
	free(path);
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
