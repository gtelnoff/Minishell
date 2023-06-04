/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_all_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:29:22 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/13 23:29:23 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int		is_redirection_in(char *array);
int		is_redirection_out(char *array);
char	**make_2d_array_redirection(t_cmd *cmd, char **array, int index, int x);
char	**delete_redirection(char **array, int delete);
char	**get_all_redirection(t_cmd *cmd, char **array, int x);
char	**set_all_redirection(char **new_all_redirection, char **array, \
			int x, int i);

void	define_all_redirection(t_parse *parse, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		parse->cmd[i].cmd_params = get_all_redirection(parse->cmd,
				parse->cmd[i].cmd_params, i);
		i++;
	}
}

char	**make_2d_array_redirection(t_cmd *cmd, char **array, int index, int x)
{
	int		i;
	char	**new_all_redirection;

	i = 0;
	if (cmd[index].all_redirection == NULL)
	{
		cmd[index].all_redirection = malloc(sizeof(char *) * 3);
		cmd[index].all_redirection[0] = ft_strdup(array[x]);
		cmd[index].all_redirection[1] = ft_strdup(array[x + 1]);
		cmd[index].all_redirection[2] = NULL;
		return (array);
	}
	else
		new_all_redirection = malloc(sizeof(char *)
				* (get_len_2d_array(cmd[index].all_redirection) + 3));
	while (cmd[index].all_redirection[i] != NULL)
	{
		new_all_redirection[i] = ft_strdup(cmd[index].all_redirection[i]);
		i++;
	}
	new_all_redirection = set_all_redirection(new_all_redirection, array, x, i);
	free_2d_array(cmd[index].all_redirection);
	cmd[index].all_redirection = new_all_redirection;
	return (cmd[index].all_redirection);
}

char	**delete_redirection(char **array, int delete)
{
	char	**new_array;
	int		x;
	int		i;

	i = 0;
	x = 0;
	new_array = malloc(sizeof(char *) * (get_len_2d_array(array)));
	while (array[i] != NULL)
	{
		if (i == delete)
			i += 2;
		new_array[x] = ft_strdup(array[i]);
		x++;
		if (array[i] == NULL)
			break ;
		i++;
	}
	new_array[x] = NULL;
	free_2d_array(array);
	return (new_array);
}

char	**get_all_redirection(t_cmd *cmd, char **array, int x)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (array[i] != NULL)
	{
		if (is_redirection_in(array[i]) || is_redirection_out(array[i]))
		{
			make_2d_array_redirection(cmd, array, x, i);
			array = delete_redirection(array, i);
			flag++;
		}
		else
			i++;
	}
	if (flag == 0)
		cmd[x].all_redirection = NULL;
	return (array);
}
