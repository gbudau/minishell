/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:59:16 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/30 18:36:02 by fportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static void	*copy_env(void *content)
{
	char	**new_env;
	char	**env;
	int		i;

	env = content;
	if (env == NULL)
		return (NULL);
	new_env = ft_calloc(sizeof(*new_env), 3);
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env == NULL)
			return (NULL);
		i++;
	}
	return ((void *)new_env);
}

static void	print_exported_env(void *content)
{
	char	**env;

	env = content;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env[ENV_NAME], STDOUT_FILENO);
	if (env[ENV_VALUE] != NULL)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env[ENV_VALUE], STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static int	print_sorted_env(t_list *environ, int *last_status)
{
	t_list	*environ_copy;

	environ_copy = ft_lstmap(environ, &copy_env, &clear_env);
	if (environ_copy == NULL)
		error_exit();
	mergesort(&environ_copy);
	ft_lstiter(environ_copy, &print_exported_env);
	ft_lstclear(&environ_copy, &clear_env);
	*last_status = 0;
	return (0);
}

int			msh_export(t_command *cmd, t_list **environ, int *last_status)
{
	char	**argv;
	char	**str_array;
	int		idx;

	argv = cmd->argv;
	*last_status = 0;
	if (cmd->argc == 1)
		return (print_sorted_env(*environ, last_status));
	while (*(++argv))
	{
		if ((idx = verify_env(*argv)) == -1)
		{
			print_invalid_identifier(*argv);
			*last_status = 1;
		}
		else
		{
			str_array = split_env(*argv, idx);
			if (str_array == NULL)
				error_exit();
			set_env(environ, str_array);
		}
	}
	return (*last_status);
}
