/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part_utils_three.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:56:56 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/12 15:56:57 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int		check_permission_outfile(t_cmd *cmd, char *file_name, int fd,
			int index);
void	close_fd_in_out(t_cmd cmd);

void	close_all_child_fd(t_parse *parse, int nb_of_cmd, int index)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		close_fd_in_out(parse->cmd[i]);
		i++;
	}
	if (index == 0)
	{
		close(parse->fds1[0]);
		close(parse->fds1[1]);
		return ;
	}
	close(parse->fds1[0]);
	close(parse->fds1[1]);
	close(parse->fds2[0]);
	close(parse->fds2[1]);
}

void	close_all_child_end(t_parse *parse, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		close_fd_in_out(parse->cmd[i]);
		i++;
	}
}

int	check_permission_outfile(t_cmd *cmd, char *file_name, int fd, int index)
{
	if (fd != -1)
		return (0);
	cmd[index].possible_excution = -1;
	cmd[index].index_error_redirection = 1;
	ft_put_str(file_name, 2);
	ft_put_str(": Permission denied\n", 2);
	change_return_value(cmd, 1, index);
	return (-1);
}
