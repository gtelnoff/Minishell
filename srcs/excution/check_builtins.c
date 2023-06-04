/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:23:47 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 11:22:08 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd_path);

void	excute_builtins(t_parse *parse, t_cmd cmd, int builtins_numbers,
		int *fds_one_zero)
{
	if (builtins_numbers == ECHO)
	{
		echo(parse, cmd, cmd.cmd_params);
	}
	else if (builtins_numbers == CD)
		builtins_cd(parse, cmd, cmd.cmd_params);
	else if (builtins_numbers == PWD)
		builtins_pwd(parse, cmd);
	else if (builtins_numbers == EXPORT)
		export(cmd.cmd_params, parse, cmd);
	else if (builtins_numbers == UNSET)
		unset(cmd.cmd_params, parse, cmd);
	else if (builtins_numbers == ENV)
		builtins_env(parse, cmd, cmd.cmd_params);
	else if (builtins_numbers == EXIT)
	{
		if (get_nb_of_cmd(parse->cmd) == 1)
		{
			close(fds_one_zero[0]);
			close(fds_one_zero[1]);
		}
		exit_function(cmd.cmd_params, parse, cmd);
	}
	return ;
}

int	check_builtins(t_parse *parse)
{
	int	builtins_numbers;
	int	nb_of_cmd;
	int	fds_one_zero[2];

	builtins_numbers = is_builtins(parse->cmd[0].cmd_path);
	nb_of_cmd = get_nb_of_cmd(parse->cmd);
	if (nb_of_cmd != 1 || builtins_numbers == 0
		|| parse->cmd[0].possible_excution < 0)
		return (0);
	fds_one_zero[0] = dup(0);
	fds_one_zero[1] = dup(1);
	make_dup2_in(parse, parse->cmd[0], 0);
	make_dup2_out(parse, parse->cmd[0], 0, get_nb_of_cmd(parse->cmd));
	parse->cmd[0].index_error_redirection = 0;
	excute_builtins(parse, parse->cmd[0], builtins_numbers, fds_one_zero);
	if (parse->cmd[0].fd.fd_in != 0)
		close(parse->cmd[0].fd.fd_in);
	if (parse->cmd[0].fd.fd_out != 0)
		close(parse->cmd[0].fd.fd_out);
	dup2(fds_one_zero[0], 0);
	dup2(fds_one_zero[1], 1);
	close(fds_one_zero[0]);
	close(fds_one_zero[1]);
	return (1);
}

int	check_builtins_child(t_parse *parse, int is_child, int index, int *all_pid)
{
	int	builtins_numbers;
	int	nb_of_cmd;
	int	*fds;

	fds = NULL;
	builtins_numbers = is_builtins(parse->cmd[index].cmd_path);
	nb_of_cmd = get_nb_of_cmd(parse->cmd);
	if ((is_child == 1 && builtins_numbers == 0)
		|| (parse->cmd[index].possible_excution < 0))
		return (0);
	make_dup2_in(parse, parse->cmd[index], index);
	make_dup2_out(parse, parse->cmd[index], index, nb_of_cmd);
	if (ft_strcmp(parse->cmd[index].cmd_path, "exit") == 0)
	{
		close_all_child_fd(parse, nb_of_cmd, index);
		free(all_pid);
	}
	excute_builtins(parse, parse->cmd[index], builtins_numbers, fds);
	free_2d_array(parse->envp);
	close_all_child_fd(parse, nb_of_cmd, index);
	return (1);
}

int	is_builtins(char *cmd_path)
{
	if (cmd_path == NULL)
		return (-1);
	else if (ft_strcmp(cmd_path, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_path, "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd_path, "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd_path, "export") == 0)
		return (4);
	else if (ft_strcmp(cmd_path, "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd_path, "env") == 0)
		return (6);
	else if (ft_strcmp(cmd_path, "exit") == 0)
		return (7);
	return (0);
}
