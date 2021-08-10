/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:05:57 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/08 21:39:57 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff_to_out(t_args *x, int fd)
{
	t_vars vars;

	vars.id = fork();
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if ((ft_strncmp("ping", *(x->argv), 4)) == 0)
		signal(SIGQUIT, SIG_IGN);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
		dup2(fd, 0);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		g_exit_status = WEXITSTATUS(vars.ex_res);
	dup2(x->temp_fd_0, 0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	ff_to_pipe(t_args *x, int fdi)
{
	t_vars vars;

	pipe(vars.fd);
	vars.id = fork();
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		dup2(fdi, 0);
		dup2(vars.fd[1], 1);
		close(vars.fd[0]);
		close(vars.fd[1]);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		g_exit_status = WEXITSTATUS(vars.ex_res);
	dup2(vars.fd[0], 0);
	close(vars.fd[1]);
	close(vars.fd[0]);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	ff_to_file(t_args *x, int fdi)
{
	t_vars vars;

	vars.fdd = find_descriptor(x);
	vars.id = fork();
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
		dup2(fdi, 0);
		dup2(vars.fdd, 1);
		close(vars.fdd);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		g_exit_status = WEXITSTATUS(vars.ex_res);
	close(vars.fdd);
	dup2(x->temp_fd_0, 0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

int		open_input_file(t_args *x)
{
	int		fd;
	char	**input_files;

	fd = 0;
	input_files = x->inp_files;
	while (*input_files != NULL)
	{
		if (fd)
			close(fd);
		fd = open(*input_files, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr(*(x->inp_files));
			ft_putstr(": No such file or directory\n");
			g_exit_status = 1;
			return (-1);
		}
		input_files++;
	}
	return (fd);
}

void	from_file(t_args *x)
{
	int fd;

	if ((fd = open_input_file(x)) == -1)
		return ;
	if (x->out_pipe_red == 0)
		ff_to_out(x, fd);
	else if (x->out_pipe_red == 1)
		ff_to_pipe(x, fd);
	else
		ff_to_file(x, fd);
	close(fd);
}
