/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 03:44:47 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 03:44:48 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

void	open_all_here_doc(t_cmd *cmd, int nb_of_cmd);
void	open_redirection_in_out(t_cmd *cmd, int nb_of_cmd);
void	open_redirection(t_cmd *cmd, int index);
int		open_simple_redirection_in(t_cmd *cmd, char *redirection, int index);
int		open_simple_redirection_out(t_cmd *cmd, char *redirection_type,
			char *redirection, int index);
void	check_permission_infile(t_cmd *cmd, char *redirection, int index);
void	close_all_pipe(t_cmd *cmd);
void	check_command_permission(t_cmd *cmd, int nb_of_cmd);

void	open_all_redirection(t_cmd *cmd)
{
	int	nb_of_cmd;

	nb_of_cmd = get_nb_of_cmd(cmd);
	open_all_here_doc(cmd, nb_of_cmd);
	open_redirection_in_out(cmd, nb_of_cmd);
	check_command_permission(cmd, nb_of_cmd);
	if (g_return_status == -2)
		close_all_pipe(cmd);
}

void	open_redirection_in_out(t_cmd *cmd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		open_redirection(cmd, i);
		i++;
	}
}

void	open_redirection(t_cmd *cmd, int index)
{
	int	i;

	i = 0;
	if (cmd[index].all_redirection == NULL)
		return ;
	while (cmd[index].all_redirection[i] != NULL)
	{
		if (is_simple_redirection_in(cmd[index].all_redirection[i]))
		{
			if (open_simple_redirection_in(cmd,
					cmd[index].all_redirection[i + 1], index) == -1)
				return ;
		}
		if (is_redirection_out(cmd[index].all_redirection[i]) == 1)
		{
			if (open_simple_redirection_out(cmd, cmd[index].all_redirection[i],
					cmd[index].all_redirection[i + 1], index) == -1)
				return ;
		}
		if (cmd[index].all_redirection[i] == NULL)
			break ;
		i += 2;
	}
}

int	open_simple_redirection_in(t_cmd *cmd, char *redirection, int index)
{
	if (cmd[index].fd.fd_in != 0)
		close(cmd[index].fd.fd_in);
	cmd[index].fd.fd_in = open(redirection, O_RDONLY);
	if (cmd[index].fd.fd_in == -1)
	{
		cmd[index].possible_excution = -1;
		cmd[index].index_error_redirection = 2;
		check_permission_infile(cmd, redirection, index);
		return (-1);
	}
	return (0);
}

int	open_simple_redirection_out(t_cmd *cmd, char *redirection_type,
		char *redirection, int index)
{
	if (cmd[index].fd.fd_out != 0)
		close(cmd[index].fd.fd_out);
	if (ft_strlen(redirection_type) == 2)
		cmd[index].fd.fd_out = open(redirection, O_WRONLY | O_APPEND | O_CREAT,
				0644);
	else
		cmd[index].fd.fd_out = open(redirection, O_WRONLY | O_TRUNC | O_CREAT,
				0644);
	if (cmd[index].fd.fd_out == -1)
	{
		cmd[index].possible_excution = -1;
		cmd[index].index_error_redirection = 2;
		ft_put_str(redirection, 2);
		ft_put_str(": Permission denied\n", 2);
		change_return_value(cmd, 1, index);
		return (-1);
	}
	return (0);
}
