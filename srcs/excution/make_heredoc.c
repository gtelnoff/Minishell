/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_part_utils_four.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:50:36 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/05 17:50:37 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	catch_signal_heredoc(int sig);
void	write_ctrl_d(void);

void	make_here_doc(t_cmd *cmd, char **redirection, int index)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	signal(SIGINT, SIG_IGN);
	while (redirection[i] != NULL && g_return_status != -2)
	{
		if (is_here_doc(redirection[i]))
		{
			if (counter != 0)
			{
				close(cmd[index].fd.heredoc[0]);
				close(cmd[index].fd.heredoc[1]);
			}
			pipe(cmd[index].fd.heredoc);
			here_doc_child(cmd, redirection, index, i);
			counter++;
		}
		i += 2;
	}
	signal(SIGINT, catch_signal_main);
}

int	is_here_doc(char *str)
{
	if (ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}

void	check_here_doc_in(t_cmd *cmd, char **redirection)
{
	int	i;

	i = 0;
	while (redirection[i] != NULL)
		i++;
	if (ft_strlen(redirection[i - 2]) == 1)
	{
		if (cmd->fd.heredoc[0] > 0)
		{
			close(cmd->fd.heredoc[0]);
			close(cmd->fd.heredoc[1]);
		}
		cmd->fd.heredoc[0] = 0;
		cmd->fd.heredoc[1] = 0;
	}
}

void	free_here_doc(t_cmd *cmd, int index, char *str)
{
	if (cmd[index].fd.heredoc[0] > 0)
	{
		close(cmd[index].fd.heredoc[0]);
		close(cmd[index].fd.heredoc[1]);
	}
	free(str);
	free_2d_array(cmd->parse->envp);
	free_all_struct_cmd(cmd);
	if (g_return_status == 130)
		exit(1);
	exit(0);
}

void	here_doc_child(t_cmd *cmd, char **redirection, int index, int i)
{
	char	*str;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, catch_signal_heredoc);
		while (1)
		{
			str = readline("> ");
			if (!str || g_return_status == 130)
			{
				if (!str && g_return_status != 130)
					write_ctrl_d();
				free_here_doc(cmd, index, str);
			}
			if (!ft_strcmp(str, redirection[i + 1]))
				break ;
			ft_putchar_fd(cmd[index].fd.heredoc[1], str);
			free(str);
		}
		exit_heredoc(cmd);
	}
	wait_pid_heredoc(pid);
}
