/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:21:20 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/14 18:21:21 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtins_pwd(t_parse *parse, t_cmd cmd)
{
	char	pwd[4096];

	if (getcwd(pwd, 4096) == NULL)
	{
		write(2, "Cannot get current working directory path\n", 43);
		change_return_value(parse->cmd, 1, cmd.index_error_redirection);
		return ;
	}
	printf("%s\n", pwd);
	return ;
}
