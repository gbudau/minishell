/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/14 15:12:33 by gbudau           ###   ########.fr       */
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
	if (gnl == -1)
		error_exit();
	*line = ft_strjoin_free(*line, input, FREE_BOTH);
}

/*
** If GNL returns 0 and the input is not empty
** use manage_eof to join new input until it finds a newline
** Return 1 if there was no input and gnl returned 0
** Return 0 in any other cases
*/

int		end_of_input(int gnl, char **input)
{
	if (gnl == 0 && **input != '\0')
		manage_eof(input);
	else if (gnl == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int		cmd_not_found(char *str)
{
	char	*not_found;

	not_found = ft_strjoin(str, ": command not found\n");
	if (not_found == NULL)
		error_exit();
	ft_putstr_fd(not_found, STDERR_FILENO);
	free(not_found);
	return (127);
}

int		get_last_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	do_cmd(t_command *cmd, t_list **environ, int *last_status)
{
	int		pid;
	int		status;
	int		idx;
	int		error;

	if ((idx = is_builtin(cmd)) != -1)
	{
		*last_status = do_builtin(cmd, environ, idx);
		return ;
	}
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		error = set_redirections(cmd);
		if (error)
			error_exit();
		search_path_and_execute(cmd->argv, *environ);
	}
	if (waitpid(pid, &status, 0) < 0)
		error_exit();
	*last_status = get_last_status(status);
}

void	execute_cmds(t_shell *shell)
{
	t_list		*trav;
	t_command	*cmd;

	trav = shell->commands;
	while (trav != NULL)
	{
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
		gnl = !end_of_input(gnl, &input);
		parse(&shell, input);
		free(input);
		execute_cmds(&shell);
		ft_lstclear(&shell.commands, clear_command);
	}
	ft_lstclear(&shell.environ, clear_env);
	return (0);
}
