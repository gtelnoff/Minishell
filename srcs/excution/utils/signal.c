/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 03:37:58 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 03:37:59 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	catch_signal_main(int sig)
{
	if (sig == SIGINT)
	{
		g_return_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	catch_signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		g_return_status = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_return_status = 131;
		write(1, "Quit (core dumped)\n", 20);
	}
}

void	catch_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_return_status = 130;
		close(0);
	}
}

void	write_ctrl_d(void)
{
	ft_put_str("Minishell: warning: here-document ", 2);
	ft_put_str("delimited by end-of-file\n", 2);
}
