/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:35:49 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/25 19:35:50 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_all_arrays_struct_cmd(t_cmd *cmd);
void	free_all_double_arrays_struct_cmd(t_cmd *cmd);

void	free_all_struct_cmd(t_cmd *cmd)
{
	free_all_arrays_struct_cmd(cmd);
	free_all_double_arrays_struct_cmd(cmd);
	free(cmd);
	return ;
}

void	free_all_arrays_struct_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].fd.fd_in != -50)
	{
		free(cmd[i].no_parse_cmd);
		free(cmd[i].cmd_path);
		i++;
	}
	return ;
}

void	free_all_double_arrays_struct_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].fd.fd_in != -50)
	{
		free_2d_array(cmd[i].cmd_params);
		free_2d_array(cmd[i].all_redirection);
		i++;
	}
	return ;
}

char	**set_all_redirection(char **new_all_redirection, char **array, \
			int x, int i)
{
	new_all_redirection[i] = ft_strdup(array[x]);
	new_all_redirection[i + 1] = ft_strdup(array[x + 1]);
	new_all_redirection[i + 2] = NULL;
	return (new_all_redirection);
}
