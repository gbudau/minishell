/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/09 20:33:00 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

void	init_shell(t_shell *shell)
{
	shell->environ = NULL;
	init_env(&shell->environ);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->input = NULL;
}

int		main(void)
{
	t_shell	shell;
	int		gnl;

	gnl = 1;
	init_shell(&shell);
	print_env(shell.environ);
	while (gnl > 0)
	{
		prompt();
		gnl = get_next_line(STDIN_FILENO, &shell.input);
		/* TODO: Move all this into a parsing module */
		shell.tokens = tokenize(shell.input);
		print_tokens(shell.tokens);
		ft_lstclear(&shell.tokens, clear_token);
		free(shell.input);
		shell.input = NULL;
	}
	if (gnl == -1)
		error_exit();
	return (0);
}
