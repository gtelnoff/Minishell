/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_part_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:07:19 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/11 21:07:20 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	get_return_status(int last_cmd_status, int return_status)
{
	if (last_cmd_status == -1)
	{
		g_return_status = 1;
		return ;
	}
	g_return_status = WEXITSTATUS(return_status);
	if (g_return_status == 5)
		g_return_status = 127;
	return ;
}
