/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:13:02 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/08 21:39:57 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env)
{
	char **env1;

	env1 = env;
	if (env != NULL)
	{
		while (*env1 != NULL)
		{
			free(*env1);
			env1++;
		}
		free(env);
	}
}

int		check_g_exit_status(char *status)
{
	while (*status != '\0')
	{
		if (*status < '0' || *status > '9')
			return (1);
		status++;
	}
	return (0);
}

void	my_exit(char **arg, char **env)
{
	char **temp;

	temp = arg;
	temp++;
	if (*temp != NULL)
	{
		if (check_g_exit_status(*temp) == 0)
			g_exit_status = ft_atoi(*temp);
	}
	free_array(arg);
	free_array(env);
	exit(g_exit_status);
}
