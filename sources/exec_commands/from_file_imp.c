/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file_imp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:03:06 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/08 19:05:05 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff_to_out_imp(t_args *x, int fd)
{
	dup2(fd, 0);
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_0, 0);
}

void	ff_to_pipe_imp(t_args *x, int fdi)
{
	int fd[2];

	pipe(fd);
	dup2(fdi, 0);
	dup2(fd[1], 1);
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void	ff_to_file_imp(t_args *x, int fdi)
{
	int fd;

	fd = find_descriptor(x);
	dup2(fdi, 0);
	dup2(fd, 1);
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	close(fd);
	dup2(x->temp_fd_0, 0);
}

void	from_file_imp(t_args *x)
{
	int fd;

	if ((fd = open_input_file(x)) == -1)
		return ;
	if (x->out_pipe_red == 0)
		ff_to_out_imp(x, fd);
	else if (x->out_pipe_red == 1)
		ff_to_pipe_imp(x, fd);
	else
		ff_to_file_imp(x, fd);
	close(fd);
}
