/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:59:16 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/05 19:08:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_error(char *str, int *last_status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	*last_status = 1;
	return (*last_status);
}

static int	print_cd_error(char *str, int *last_status)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_perror(str);
	*last_status = 1;
	return (*last_status);
}

static void	set_oldpwd_and_pwd(t_list **environ)
{
	char	*old_pwd;
	char	current_pwd[PATH_MAX + 1];
	char	**env_ptr;

	old_pwd = get_env(*environ, "PWD");
	if (old_pwd == NULL)
		error_exit();
	env_ptr = create_env("OLDPWD", old_pwd);
	free(old_pwd);
	if (env_ptr == NULL)
		error_exit();
	set_env(environ, env_ptr);
	if (getcwd(current_pwd, PATH_MAX) == NULL)
		error_exit();
	env_ptr = create_env("PWD", current_pwd);
	if (env_ptr == NULL)
		error_exit();
	set_env(environ, env_ptr);
}

int			msh_cd(t_command *cmd, t_list **environ, int *last_status)
{
	char	*home;

	if (cmd->argc > 2)
		return (print_error("minishell: cd: too many arguments\n",
					last_status));
	else if (cmd->argc == 1)
	{
		home = get_env(*environ, "HOME");
		if (home == NULL)
			return (print_error("minishell: cd: HOME not set\n", last_status));
		if (chdir(home) == -1)
		{
			print_cd_error(home, last_status);
			free(home);
			return (*last_status);
		}
		free(home);
	}
	else if (cmd->argc == 2 && chdir(cmd->argv[1]) == -1)
		return (print_cd_error(cmd->argv[1], last_status));
	set_oldpwd_and_pwd(environ);
	*last_status = 0;
	return (0);
}
