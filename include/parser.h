/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:55:58 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 01:34:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../include/minishell.h"
# include "../include/command.h"
# include "../include/lexer.h"

enum	e_parser_errors
{
	NO_PARSER_ERROR,
	ERR_UNEXPECTED_TOKEN_PIPE,
	ERR_UNEXPECTED_TOKEN_SEMICOLON,
	ERR_UNEXPECTED_TOKEN_GREAT,
	ERR_UNEXPECTED_TOKEN_LESS,
	ERR_UNEXPECTED_TOKEN_DGREAT,
	ERR_UNEXPECTED_NEWLINE,
	ERR_REDIRECTION
};

void	clear_command(void *command);
int		add_command(t_list **tokens, t_command *cmd);
int		skip_semicolon_token(t_list **tokens, t_command *cmd);
int		parse_error_token_type(int token_type);

#endif
