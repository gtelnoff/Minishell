/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part_utils_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:46:00 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/11 14:46:01 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	close_all_heredoc(t_cmd *cmd);

void	open_all_here_doc(t_cmd *cmd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd && g_return_status != -2)
	{
		if (cmd[i].all_redirection != NULL)
		{
			make_here_doc(cmd, cmd[i].all_redirection, i);
			check_here_doc_in(&cmd[i], cmd[i].all_redirection);
		}
		i++;
	}
}

int	check_if_last_rediretion_is_heredoc(char **redirection)
{
	int	len;

	len = get_len_2d_array(redirection);
	if (ft_strcmp(redirection[len - 1], "<<") != 0)
		return (0);
	return (1);
}

void	exit_heredoc(t_cmd *cmd)
{
	close_all_heredoc(cmd);
	free_2d_array(cmd->parse->envp);
	free_all_struct_cmd(cmd);
	exit(0);
}

void	close_all_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < get_nb_of_cmd(cmd))
	{
		if (cmd[i].fd.heredoc[0] > 0)
		{
			close(cmd[i].fd.heredoc[0]);
			close(cmd[i].fd.heredoc[1]);
		}
		i++;
	}
	return ;
}

void	wait_pid_heredoc(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status != 0)
	{
		g_return_status = -2;
		return ;
	}
}
