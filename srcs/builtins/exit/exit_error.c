/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 03:11:54 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 03:11:55 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_exit_tma(t_parse *parse, t_cmd cmd)
{
	unsigned char	c;

	c = 1;
	ft_put_str("exit\n", 1);
	ft_put_str("minishell: exit: too many arguments\n", 2);
	change_return_value(parse->cmd, 1, cmd.index_error_redirection);
	free_2d_array(parse->envp);
	free_all_struct_cmd(parse->cmd);
	exit(c);
}

void	error_exit_nar(t_parse *parse, t_cmd cmd)
{
	unsigned char	c;

	c = 2;
	ft_put_str("exit\n", 1);
	ft_put_str("minishell: numeric argument required\n", 2);
	change_return_value(parse->cmd, 1, cmd.index_error_redirection);
	free_2d_array(parse->envp);
	free_all_struct_cmd(parse->cmd);
	exit(c);
}

void	error_exit_nr(t_parse *parse, t_cmd cmd)
{
	unsigned char	c;

	c = 2;
	ft_put_str("exit\n", 1);
	ft_put_str("minishell: numeric argument required\n", 2);
	change_return_value(parse->cmd, 1, cmd.index_error_redirection);
	free_2d_array(parse->envp);
	free_all_struct_cmd(parse->cmd);
	exit(c);
}
