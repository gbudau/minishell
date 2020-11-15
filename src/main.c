/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 21:51:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

void	init_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(*shell));
	init_env(&shell->environ);
}

/*
** Join the line with the input until it finds a newline in it
** Using this to deal with the case when the user presses CTRL-D
** While in the middle of a input
*/

void	manage_eof(char **line)
{
	int		gnl;
	char	*input;

	while ((gnl = get_next_line(STDIN_FILENO, &input)) == 0)
		*line = ft_strjoin_free(*line, input, FREE_BOTH);
	*line = ft_strjoin_free(*line, input, FREE_BOTH);
	if (gnl == -1) 
		error_exit();
}

/*
** Check if GNL returns 0 and the input is not empty
** In that case it uses manage_eof to join new input until it finds a newline
** Return 0 if there was no input and gnl returned 0
** Return 1 in any other cases
*/

int		not_end_of_input(int gnl, char **input)
{
	if (gnl == 0 && **input != '\0')
		manage_eof(input);
	else if (gnl == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

int		main(void)
{
	t_shell	shell;
	char	*input;
	int		gnl;

	init_shell(&shell);
	gnl = 1;
	while (gnl > 0)
	{
		prompt();
		if ((gnl = get_next_line(STDIN_FILENO, &input)) < 0)
			error_exit();
		gnl = not_end_of_input(gnl, &input);
		parse(&shell, input);
		free(input);
	}
	ft_lstclear(&shell.environ, clear_env);
	return (0);
}
