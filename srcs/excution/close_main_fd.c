/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part_two_utils_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:14:05 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/15 16:14:06 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	close_fd_in_out(t_cmd cmd);

void	close_all_main_fd(t_parse *parse)
{
	int	i;

	i = 0;
	while (i < get_nb_of_cmd(parse->cmd))
	{
		close_fd_in_out(parse->cmd[i]);
		i++;
	}
	if (get_nb_of_cmd(parse->cmd) % 2 != 0)
	{
		close(parse->fds1[0]);
		close(parse->fds1[1]);
	}
	else if (get_nb_of_cmd(parse->cmd) % 2 == 0)
	{
		close(parse->fds2[0]);
		close(parse->fds2[1]);
	}
}

void	close_fd_in_out(t_cmd cmd)
{
	t_fd	fd;

	fd = cmd.fd;
	if (fd.fd_in > 0)
		close(fd.fd_in);
	if (fd.fd_out > 0)
		close(fd.fd_out);
	if (fd.heredoc[0] > 0)
	{
		close(fd.heredoc[0]);
		close(fd.heredoc[1]);
	}
}

void	print_all_error_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd[i].cmd_params[0] == NULL)
		return ;
	while (i < get_nb_of_cmd(cmd))
	{
		if (cmd[i].possible_excution == -1 \
			&& cmd[i].index_error_redirection == -1)
		{
			ft_put_str(cmd[i].cmd_params[0], 2);
			ft_put_str(": acommand not found\n", 2);
		}
		i++;
	}
}
