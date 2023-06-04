/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile_permission.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:25:37 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 04:25:38 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_check_all_permission(t_cmd *info_cmd, char *msg, int index,
		int error)
{
	ft_put_str(msg, 2);
	info_cmd[index].possible_excution = -1;
	info_cmd[index].fd.fd_in = -1;
	info_cmd[index].index_error_redirection = -3;
	change_return_value(info_cmd, error, index);
}

void	check_permission_infile(t_cmd *cmd, char *redirection, int index)
{
	int	access_perm;

	access_perm = access(redirection, F_OK);
	if (access_perm == 0)
	{
		ft_put_str(redirection, 2);
		ft_put_str(": Permission denied\n", 2);
		change_return_value(cmd, 1, index);
		return ;
	}
	ft_put_str(redirection, 2);
	ft_put_str(": No such file or directory\n", 2);
	change_return_value(cmd, 1, index);
	return ;
}
