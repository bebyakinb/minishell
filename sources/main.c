/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 03:38:28 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/08 21:41:16 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	if (g_line != NULL)
	{
		free(g_line);
		g_line = NULL;
	}
	write(1, "\n> ", 3);
}

void	sigquit(int sig)
{
	(void)sig;
	write(2, "\b\b  \b\b", 6);
}

void	ctrl_d_exit(t_args *args, int i, char *rline)
{
	char	*temp;

	if (i == 0 && *rline == '\0' && g_line == NULL)
	{
		write(1, "\n", 1);
		free_strarr(args->env);
		if (rline)
			free(rline);
		if (g_line)
			free(g_line);
		exit(0);
	}
	if (g_line == NULL)
		g_line = rline;
	else
	{
		temp = g_line;
		g_line = ft_strjoin(g_line, rline);
		free(temp);
		free(rline);
	}
}

int		prompt(t_args *args)
{
	int		i;
	char	*rline;

	while (1)
	{
		if (g_line == NULL)
			write(1, "> ", 2);
		rline = NULL;
		i = get_next_line(0, &rline);
		ctrl_d_exit(args, i, rline);
		if (i == 0)
			continue ;
		if ((*g_line) != '\0')
		{
			if (!(parser(args, g_line)))
				exit(0);
		}
		free(g_line);
		g_line = NULL;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_args	args;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	args.temp_fd_0 = dup(0);
	args.temp_fd_1 = dup(1);
	if (!(args.env = ft_strarrdup(envp)))
		return (0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	g_line = NULL;
	prompt(&args);
}
