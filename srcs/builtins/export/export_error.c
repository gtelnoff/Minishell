/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 03:13:19 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 18:41:08 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_export(t_parse *parse, t_cmd cmd)
{
	ft_put_str(" not a valid identifier\n", 2);
	change_return_value(parse->cmd, 1, cmd.index_error_redirection);
}
