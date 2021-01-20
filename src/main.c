/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/20 23:45:15 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDERR_FILENO);
}

static void	init_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(*shell));
	init_env(&shell->environ);
	create_and_set_env(&shell->environ, "_", "PATH");
	set_shlvl(&shell->environ);
}

int			run_once(t_shell shell, int argc, char **argv)
{
	if (argc < 3)
	{
		ft_putstr_fd("minishell: -c: option requires an argument\n",
																STDERR_FILENO);
		return (2);
	}
	ignore_signals();
	parse(&shell, argv[2]);
	execute_cmds(&shell);
	ft_lstclear(&shell.commands, clear_command);
	ft_lstclear(&shell.environ, clear_env);
	return (shell.last_status);
}

int			main(int argc, char **argv)
{
	t_shell	shell;
	char	*input;
	int		gnl;

	setup_signals_handlers();
	init_shell(&shell);
	if (argc > 1 && ft_strcmp(argv[1], "-c") == 0)
		return (run_once(shell, argc, argv));
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
	return (shell.last_status);
}
