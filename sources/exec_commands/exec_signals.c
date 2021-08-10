/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:58 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/08 21:39:57 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_skip(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	sigquit_skip(int signum)
{
	(void)signum;
	ft_putstr("Quit (core dumped)\n");
	g_exit_status = 131;
}

void	sigint_child(int signum)
{
	(void)signum;
	exit(130);
}

void	sigquit_child(int signum)
{
	(void)signum;
	exit(131);
}
