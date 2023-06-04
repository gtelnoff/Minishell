/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_all_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:06:39 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/14 00:06:51 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


void	define_all_path(t_parse *parse, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		if (parse->cmd[i].cmd_params[0] != NULL)
		{
			parse->cmd[i].cmd_path = strdup(parse->cmd[i].cmd_params[0]);
			check_path(parse->cmd, parse->envp, i);
		}
		else
			parse->cmd[i].possible_excution = -1;
		i++;
	}
}
