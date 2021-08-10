/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_no_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:47:17 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/12 11:47:23 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_home_variable(char **env, char **path)
{
	char *temp;

	temp = "HOME=";
	while (*env != NULL)
	{
		if ((ft_strncmp(temp, *env, 5)) == 0)
		{
			*path = *env;
			return (0);
		}
		env++;
	}
	g_exit_status = 1;
	ft_putstr("cd: HOME not set\n");
	return (1);
}

char	**try_cd_home(char **env, char *home)
{
	char *s;
	char *test;

	test = get_directory();
	if (test == NULL)
		return (env);
	if (check_path(&home) == 1)
	{
		free(test);
		return (env);
	}
	s = get_directory();
	if (s == NULL)
	{
		free(test);
		return (env);
	}
	env = change_env(env, test, s);
	free(test);
	free(s);
	return (env);
}

char	**cd_home(char **env)
{
	char *home;

	if ((find_home_variable(env, &home)) == 1)
		return (env);
	while (*home != '=')
		home++;
	home++;
	env = try_cd_home(env, home);
	return (env);
}
