/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:44:17 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 11:26:55 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	have_egal_in_str(char *str);

void	builtins_env(t_parse *parse, t_cmd cmd, char **cmd_params)
{
	int	i;

	i = 0;
	if (get_len_2d_array(cmd_params) != 1)
		return ;
	while (parse->envp[i] != NULL)
	{
		if (have_egal_in_str(parse->envp[i]))
			printf("%s\n", parse->envp[i]);
		i++;
	}
	change_return_value(parse->cmd, 0, cmd.index_error_redirection);
	return ;
}

int	have_egal_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
