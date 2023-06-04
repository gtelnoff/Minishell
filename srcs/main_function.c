/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:10:11 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 22:10:13 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void);
char	**delete_null_byte(char **array);
void	catch_signal_main(int sig);
void	exit_ctrl_d(t_parse *parse);
void	minishell_exe(t_parse *parse);
void	define_pipe(t_parse *parse);
int		check_all_zero(char **array);

void	minishell_exe(t_parse *parse)
{
	char	**split_cmd;

	define_pipe(parse);
	split_cmd = parsing(parse);
	if (split_cmd == NULL)
	{
		free_2d_array(split_cmd);
		return ;
	}
	if (!check_all_zero(split_cmd) || (split_cmd[0][0] == 0 \
			&& split_cmd[1] == NULL))
	{
		free_2d_array(split_cmd);
		return ;
	}
	split_cmd = delete_null_byte(split_cmd);
	if (split_cmd != NULL)
	{
		if (define_t_cmd(parse, split_cmd) != -1)
		{
			excute_cmds(parse);
			free_all_struct_cmd(parse->cmd);
		}
	}
}

void	exit_ctrl_d(t_parse *parse)
{
	unsigned char	return_value;

	return_value = g_return_status;
	free_2d_array(parse->envp);
	exit(return_value);
}

void	define_pipe(t_parse *parse)
{
	parse->fds1[0] = 0;
	parse->fds1[1] = 0;
	parse->fds2[0] = 0;
	parse->fds2[1] = 0;
}

void	set_signal(void)
{
	signal(SIGINT, catch_signal_main);
	signal(SIGQUIT, SIG_IGN);
}

int	check_all_zero(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] == NULL)
	{
		if (array[0][0] != 0)
			return (0);
		i++;
	}
	return (1);
}
