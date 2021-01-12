/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:52:08 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/13 00:45:04 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/command.h"

int			get_last_status(int status)
{
	int	signum;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		if (signum == SIGINT || signum == SIGQUIT)
			ft_putstr_fd("\n", STDERR_FILENO);
		return (128 + signum);
	}
	return (0);
}

static char	*create_env_content(void *content)
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

char		**create_env_array(t_list *environ)
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
		env = create_env_content(environ->content);
		if (env)
		{
			env_array[i] = env;
			i++;
		}
		environ = environ->next;
	}
	return (env_array);
}

char		*build_path_binary(char *dir_name, char *cmd_name)
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
