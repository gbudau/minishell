/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:36:53 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/08 18:53:48 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(void)
{
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

int	main(void)
{
	char	*line;
	int		gnl;
	t_list	*tokens;

	line = NULL;
	tokens = NULL;
	gnl = 1;
	while (gnl > 0)
	{
		prompt();
		gnl = get_next_line(STDIN_FILENO, &line);
		tokens = tokenize(line);
		print_tokens(tokens);
		ft_lstclear(&tokens, clear_token);
		free(line);
		line = NULL;
	}
	return (0);
}
