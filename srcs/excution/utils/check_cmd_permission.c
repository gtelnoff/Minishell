/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_permission.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:08:13 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 20:01:46 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_check_all_permission(t_cmd *info_cmd, char *msg, int index,
			int error);
void	check_all_permission(t_cmd *info_cmd, int index);
int		no_file_or_directory(char *cmd);
int		is_directory(char *cmd);
int		have_no_permission(char *cmd);

void	check_command_permission(t_cmd *cmd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		check_all_permission(cmd, i);
		i++;
	}
}

void	check_all_permission(t_cmd *info_cmd, int index)
{
	struct stat	buf;
	char		*cmd;

	if (info_cmd[index].cmd_path == NULL)
		return ;
	cmd = info_cmd[index].cmd_path;
	stat(cmd, &buf);
	if ((cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '/'))
	{
		if (no_file_or_directory(cmd))
		{
			error_check_all_permission(info_cmd, \
				"Minishell: No such file or directory\n", index, 127);
		}
		else if (S_ISDIR(buf.st_mode))
		{
			error_check_all_permission(info_cmd, \
				"Minishell: Is a directory\n", index, 126);
		}
		else if (have_no_permission(cmd))
		{
			error_check_all_permission(info_cmd, \
				"Minishell: Permission denied\n", index, 126);
		}
	}
}

int	no_file_or_directory(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		if (access(cmd, X_OK) == -1)
			if (access(cmd, W_OK) == -1)
				if (access(cmd, R_OK) == -1)
					return (1);
	return (0);
}

int	is_directory(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		if (access(cmd, X_OK) == 0)
			if (access(cmd, W_OK) == 0)
				if (access(cmd, R_OK) == 0)
					return (1);
	return (0);
}

int	have_no_permission(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		if (access(cmd, X_OK) == -1)
			if (access(cmd, W_OK) == -1)
				if (access(cmd, R_OK) == -1)
					return (1);
	return (0);
}
