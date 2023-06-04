/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:45:07 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/05 19:45:08 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_path(t_cmd *cmd, int index, char *cmd_buf, char **all_path)
{
	free(cmd[index].cmd_path);
	cmd[index].cmd_path = ft_strdup(cmd_buf);
	free(cmd_buf);
	free_2d_array(all_path);
}

char	**get_all_path(char **env, char **all_path, int index)
{
	char	*path;

	path = ft_delete_path_envp(env, index);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

void	free_path_env(t_cmd *cmd, char **all_path, int x)
{
	free(cmd[x].cmd_path);
	cmd[x].cmd_path = ft_strdup(cmd[x].cmd_params[0]);
	free_2d_array(all_path);
}

char	*ft_delete_path_envp(char **env, int index)
{
	int		i;
	int		start;
	int		len_path;
	char	*paths;

	i = 0;
	start = 0;
	while (env[index][start] != '/')
		start++;
	len_path = (ft_strlen(env[index]) - start);
	paths = malloc(sizeof(char) * len_path + 2);
	while (i < len_path)
	{
		paths[i] = env[index][start];
		i++;
		start++;
	}
	paths[i] = '\0';
	return (paths);
}
