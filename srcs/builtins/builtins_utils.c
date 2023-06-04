/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:40:52 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/29 21:40:53 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_return_value(t_cmd *cmd, int return_status, int index_cmd)
{
	int	nb_of_cmd;

	nb_of_cmd = (get_nb_of_cmd(cmd) - 1);
	if (index_cmd == nb_of_cmd)
	{
		g_return_status = return_status;
		return ;
	}
	return ;
}

int	get_index(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}
