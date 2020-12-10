/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/10 23:32:03 by gbudau           ###   ########.fr       */
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

// TODO: Write this function
int		msh_echo(t_command *cmd, t_list **environ, int *last_status)
{
	(void)cmd;
	(void)environ;
	(void)last_status;
	ft_putstr_fd("Executing echo builtin\n", STDOUT_FILENO);
	return (0);
}

// TODO: Write this function
int		msh_exit(t_command *cmd, t_list **environ, int *last_status)
{
	(void)cmd;
	(void)environ;
	(void)last_status;
	ft_putstr_fd("Executing exit builtin\n", STDOUT_FILENO);
	return (0);
}

void	do_builtin(t_command *cmd, t_list **environ, int *last_status, int idx)
{
	static int	(*fptr[3])(t_command *, t_list **, int *) =
								{ msh_echo, msh_exit, NULL };
	*last_status = fptr[idx](cmd, environ, last_status);
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

	if ((idx = is_builtin(cmd)) != -1)
	{
		do_builtin(cmd, environ, last_status, idx);
		return ;
	}
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		// TODO change this to execve
		execvp(cmd->argv[0], cmd->argv);
		exit(cmd_not_found(cmd->argv[0]));
	}
	if (waitpid(pid, &status, 0) < 0)
		error_exit();
	*last_status = get_last_status(status);
}

// TODO Refactor this function
void	do_pipeline(t_list **commands, t_list *environ, int *last_status)
{
	pid_t		newpid = 0;
	int			havepipe = 1;
	int			lastpipe[2] = {-1, -1};
	int			curpipe[2];
	t_list		*trav;
	t_command	*cmd;
	int			status;

	(void)environ;
	trav = *commands;
	while (newpid != -1 && havepipe)
	{
		cmd = trav->content;
		if (cmd->ispipe)
			if (pipe(curpipe) != 0)
				error_exit();
		if ((newpid = fork()) < 0)
			error_exit();
		if (newpid == 0)
		{
			if (havepipe)
			{
				close(lastpipe[1]);
				dup2(lastpipe[0], STDIN_FILENO);
				close(lastpipe[0]);
			}
			if (cmd->ispipe)
			{
				close(curpipe[0]);
				dup2(curpipe[1], STDOUT_FILENO);
				close(curpipe[1]);
			}
			// TODO Change this to execve
			execvp(cmd->argv[0], cmd->argv);
			exit(cmd_not_found(cmd->argv[0]));
		}
		if (havepipe)
		{
			close(lastpipe[0]);
			close(lastpipe[1]);
		}
		havepipe = cmd->ispipe;
		if (cmd->ispipe)
		{
			lastpipe[0] = curpipe[0];
			lastpipe[1] = curpipe[1];
		}
		cmd->pid = newpid;
		trav = trav->next;
	}

	trav = *commands;
	havepipe = 1;
	while (havepipe)
	{
		cmd = trav->content;
		waitpid(cmd->pid, &status, 0);
		*last_status = get_last_status(status);
		havepipe = cmd->ispipe;
		trav = trav->next;
	}

	*commands = trav;
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
