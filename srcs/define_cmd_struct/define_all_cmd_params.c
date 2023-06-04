/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_all_cmd_params.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:03:57 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/13 22:03:58 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_cmd_params(t_cmd *cmd, char **array, int x, int index);

void	define_all_cmd_params(t_parse *parse, char **array)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i] != NULL)
	{
		i += get_cmd_params(parse->cmd, array, i, x);
		parse->cmd[x].parse = parse;
		if (array[i - 1] == NULL)
			break ;
		x++;
	}
}

int	get_len_of_cmd_params(char **array, int index)
{
	int	i;

	i = 0;
	while (array[index] != NULL)
	{
		if (array[index][0] == '|' && array[index][1] == '\0')
			break ;
		i++;
		index++;
	}
	return (i);
}

int	get_cmd_params(t_cmd *cmd, char **array, int x, int index)
{
	int	i;
	int	len_2d_tab;

	i = 0;
	len_2d_tab = get_len_of_cmd_params(array, x);
	cmd[index].cmd_params = malloc(sizeof(char *) * (len_2d_tab + 1));
	while (i < len_2d_tab)
	{
		cmd[index].cmd_params[i] = ft_strdup(array[x]);
		x++;
		i++;
	}
	cmd[index].cmd_params[i] = NULL;
	return (len_2d_tab + 1);
}
