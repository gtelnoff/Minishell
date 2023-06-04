/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:08:48 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/11 14:08:49 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int		check_return_status(t_parse *parse);
void	catch_signal_cmd(int sig);
void	close_all_child_end(t_parse *parse, int nb_of_cmd);

void	excute_cmds(t_parse *parse)
{
	pid_t	*all_pid;
	int		i;
	int		x;

	i = 0;
	x = 0;
	open_all_redirection(parse->cmd);
	if (check_return_status(parse) == 1)
		return ;
	all_pid = malloc(sizeof(pid_t) * get_all_pid(parse->cmd));
	pipe(parse->fds1);
	while (i < get_nb_of_cmd(parse->cmd))
	{
		open_pipe(parse, i + 1);
		if (parse->cmd[i].possible_excution >= 0)
		{
			all_pid[x] = fork();
			parse->cmd[i].index_error_redirection = i;
			child(parse, all_pid[x], i, all_pid);
			x++;
		}
		close_pipe(parse, i + 1);
		i++;
	}
	make_all_wait_pid(parse, all_pid);
}

int	check_return_status(t_parse *parse)
{
	if (g_return_status == -2)
	{
		close_all_child_end(parse, get_nb_of_cmd(parse->cmd));
		g_return_status = 130;
		return (1);
	}
	signal(SIGINT, catch_signal_cmd);
	signal(SIGQUIT, catch_signal_cmd);
	if (check_builtins(parse))
		return (1);
	return (0);
}

void	open_pipe(t_parse *parse, int index)
{
	if (index == 1)
		return ;
	else if (index % 2 == 0)
		pipe(parse->fds2);
	else
		pipe(parse->fds1);
}

void	close_pipe(t_parse *parse, int index)
{
	if (index == 1)
		return ;
	else if (index % 2 == 0)
	{
		close(parse->fds1[0]);
		close(parse->fds1[1]);
	}
	else
	{
		close(parse->fds2[0]);
		close(parse->fds2[1]);
	}
}

void	close_all_pipe(t_cmd *cmd)
{
	int	i;
	int	nb_of_cmd;

	i = 0;
	nb_of_cmd = get_nb_of_cmd(cmd);
	while (i < nb_of_cmd)
	{
		if (cmd[i].fd.heredoc[0] != 0)
		{
			close(cmd[i].fd.heredoc[0]);
			close(cmd[i].fd.heredoc[1]);
		}
		i++;
	}
	return ;
}
