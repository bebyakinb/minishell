/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:48:40 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/12 11:48:47 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		keylen(char *key)
{
	int len;

	len = 0;
	while (*key != '=' && *key != '\0')
	{
		len++;
		key++;
	}
	return (len);
}

void	export_arg_error(char *arg)
{
	write(1, "bash: export: '", 15);
	write(1, arg, ft_strlen(arg));
	write(1, "': not a valid identifier\n", 26);
}

int		check_args_export(char *arg)
{
	char *c;

	if (!((*arg > 64 && *arg < 91) || (*arg > 96 && *arg < 123) || *arg == 95))
	{
		export_arg_error(arg);
		g_exit_status = 1;
		return (1);
	}
	c = arg;
	while (*c != '=' && *c != '\0')
	{
		if (!((*c >= '0' && *c <= '9') || (*c >= 'A' && *c <= 'Z') ||
			(*c >= 'a' && *c <= 'z') || *c == '_'))
		{
			export_arg_error(arg);
			g_exit_status = 1;
			return (1);
		}
		c++;
	}
	return (0);
}
