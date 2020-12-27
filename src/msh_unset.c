/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:50:50 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/27 20:30:04 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_proper_env_name(char *str)
{
	int	i;

	i = 0;
	while (is_env_format(str[i], i > 0))
		i++;
	return (i != 0 && str[i] == '\0');
}

static void	print_invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int			msh_unset(t_command *cmd, t_list **environ, int *last_status)
{
	char	**argv;
	
	argv = cmd->argv;
	argv++;
	*last_status = 0;
	while (*argv)
	{
		if (!is_proper_env_name(*argv))
		{
			print_invalid_identifier(*argv);
			*last_status = 1;
		}
		else
			unset_env(environ, *argv);
		argv++;
	}
	return (*last_status);
}
