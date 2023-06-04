/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:14:17 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/13 17:14:18 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int		get_fdin(t_parse *parse, t_cmd cmd, int index);
int		get_fdout(t_parse *parse, t_cmd cmd, int index);
int		make_dup2_out(t_parse *parse, t_cmd cmd, int index, int nb_of_cmd);
int		make_dup2_in(t_parse *parse, t_cmd cmd, int index);
void	close_all_child_fd(t_parse *parse, int nb_of_cmd, int index);
void	write_error_execve(t_cmd *cmd, int index);

void	child(t_parse *parse, pid_t pid, int index, int *all_pid)
{
	int	nb_of_cmd;

	nb_of_cmd = get_nb_of_cmd(parse->cmd);
	if (pid == 0)
	{
		if (!check_builtins_child(parse, 1, index, all_pid))
		{
			make_dup2_in(parse, parse->cmd[index], index);
			make_dup2_out(parse, parse->cmd[index], index, nb_of_cmd);
			close_all_child_fd(parse, nb_of_cmd, index);
			execve(parse->cmd[index].cmd_path, parse->cmd[index].cmd_params,
				parse->envp);
			write_error_execve(parse->cmd, index);
			free_all_struct_cmd(parse->cmd);
			free_2d_array(parse->envp);
			free(all_pid);
			exit(5);
		}
		free_all_struct_cmd(parse->cmd);
		free(all_pid);
		exit(g_return_status);
	}
}

void	write_error_execve(t_cmd *cmd, int index)
{
	if (cmd[index].cmd_params[0][0] == '\0')
	{
		ft_put_str("\'\': command not found\n", 2);
		return ;
	}
	ft_put_str(cmd[index].cmd_params[0], 2);
	ft_put_str(": command not found\n", 2);
}

int	get_fdin(t_parse *parse, t_cmd cmd, int index)
{
	if (cmd.fd.heredoc[0] != 0)
		return (cmd.fd.heredoc[0]);
	if (cmd.fd.fd_in == 0)
	{
		if (index % 2 == 0)
			return (parse->fds2[0]);
		else
			return (parse->fds1[0]);
	}
	return (cmd.fd.fd_in);
}

int	get_fdout(t_parse *parse, t_cmd cmd, int index)
{
	if (cmd.fd.fd_out == 0)
	{
		if (index % 2 == 0)
			return (parse->fds1[1]);
		else
			return (parse->fds2[1]);
	}
	return (cmd.fd.fd_out);
}
