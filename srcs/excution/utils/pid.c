/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:30:05 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 04:30:06 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_all_pid(t_cmd *cmd)
{
	int	i;
	int	nb_of_cmd;
	int	nb_of_pid;

	i = 0;
	nb_of_cmd = get_nb_of_cmd(cmd);
	nb_of_pid = 0;
	while (i < nb_of_cmd)
	{
		if (cmd[i].possible_excution == 0)
			nb_of_pid++;
		i++;
	}
	return (nb_of_pid);
}

void	make_all_wait_pid(t_parse *parse, pid_t *all_pid)
{
	int	i;
	int	status;
	int	return_status;

	i = 0;
	close_all_main_fd(parse);
	while (i < get_all_pid(parse->cmd))
	{
		waitpid(all_pid[i], &status, 0);
		return_status = status;
		i++;
	}
	print_all_error_cmd(parse->cmd);
	if (i != 0)
		get_return_status(parse->cmd[get_nb_of_cmd(parse->cmd) - 1]. \
			possible_excution, return_status);
	free(all_pid);
}
