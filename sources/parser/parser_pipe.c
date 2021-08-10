/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:38:05 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/08 21:39:57 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_pipe(t_args *args)
{
	if (!(*(args->argv)))
	{
		ft_putstr("bash: syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		return (2);
	}
	if (args->write_to == 0)
		args->write_to = 1;
	else if (args->write_to == 3 && args->out_pipe_red != 2)
		args->out_pipe_red = 1;
	clean_last_whitespace(args);
	exec_command(args);
	free_arg_struct(args);
	return (init_arg_struct(args));
}
