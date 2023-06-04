/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_all_no_parse_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:06:30 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/13 23:06:31 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_no_parse_cmd(t_cmd *cmd, int index);

void	define_all_no_parse_cmd(t_parse *parse, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		make_no_parse_cmd(parse->cmd, i);
		i++;
	}
	parse->cmd[i].fd.fd_in = -50;
}

void	make_no_parse_cmd(t_cmd *cmd, int index)
{
	int	i;

	i = 0;
	while (cmd[index].cmd_params[i] != NULL)
	{
		if (cmd[index].no_parse_cmd == NULL)
			cmd[index].no_parse_cmd = ft_strdup(cmd[index].cmd_params[i]);
		else
			cmd[index].no_parse_cmd = ft_strjoin(cmd[index].no_parse_cmd, \
				cmd[index].cmd_params[i], 2);
		i++;
	}
}
