/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/05 19:51:40 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDERR_FILENO);
}

static void	init_shell(t_shell *shell)
{
	char	**env;

	ft_bzero(shell, sizeof(*shell));
	init_env(&shell->environ);
	env = create_env("_", "PATH");
	if (env == NULL)
		error_exit();
	set_env(&shell->environ, env);
}

int			main(void)
{
	t_shell	shell;
	char	*input;
	int		gnl;

	setup_signals_handlers();
	init_shell(&shell);
	gnl = 1;
	while (gnl > 0)
	{
		prompt();
		setup_signals_handlers();
		gnl = get_next_line(STDIN_FILENO, &input);
		if (gnl < 0)
			error_exit();
		gnl = !end_of_input(gnl, &input);
		ignore_signals();
		parse(&shell, input);
		free(input);
		execute_cmds(&shell);
		ft_lstclear(&shell.commands, clear_command);
	}
	ft_lstclear(&shell.environ, clear_env);
	return (0);
}
