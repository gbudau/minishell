/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/12 23:19:56 by gbudau           ###   ########.fr       */
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

int		is_builtin(t_command *cmd)
{
	static const char	*builtins[] = {"echo", "exit", NULL};
	int					i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		msh_echo(t_command *cmd, t_list **environ)
{
	char	**argv;
	int		no_trailing_newline;

	(void)environ;
	no_trailing_newline = FALSE;
	argv = cmd->argv;
	if (cmd->argc > 1)
		no_trailing_newline = ft_strcmp(argv[1], "-n") == 0;
	argv++;
	if (no_trailing_newline)
		argv++;
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (argv + 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		argv++;
	}
	if (no_trailing_newline == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

// TODO: Write this function
int		msh_exit(t_command *cmd, t_list **environ)
{
	(void)cmd;
	(void)environ;
	ft_putstr_fd("Executing exit builtin\n", STDOUT_FILENO);
	return (0);
}

/*
** Save a copy of stdin and stdout file descriptors
*/

void	save_stdin_and_stdout(int *stdin_fd_copy, int *stdout_fd_copy)
{
	*stdin_fd_copy = dup(STDIN_FILENO);
	*stdout_fd_copy = dup(STDOUT_FILENO);
}

/*
** Restore stdin and stdout file descriptors
** From the copies and close the copies
*/

void	restore_and_close_stdin_and_stdout(int stdin_fd_copy, int stdout_fd_copy)
{
	dup2(stdin_fd_copy, STDIN_FILENO);
	dup2(stdout_fd_copy, STDOUT_FILENO);
	close(stdin_fd_copy);
	close(stdout_fd_copy);
}

int		do_builtin(t_command *cmd, t_list **environ, int idx)
{
	static int	(*fptr[3])(t_command *, t_list **) =
								{ msh_echo, msh_exit, NULL };
	int			status;
	int			stdin_fd_copy;
	int			stdout_fd_copy;
	
	save_stdin_and_stdout(&stdin_fd_copy, &stdout_fd_copy);
	status = set_redirections(cmd);
	if (status == 0)
		status = fptr[idx](cmd, environ);
	restore_and_close_stdin_and_stdout(stdin_fd_copy, stdout_fd_copy);
	return(status);
}

int		get_last_status(int status)
{
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
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
