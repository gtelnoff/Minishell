/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:45:53 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/08 17:45:56 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int		check_env_path_exist(char **env);
char	*ft_delete_path_envp(char **env, int index);
int		ft_get_cmd_w_path(t_cmd *cmd, char **env, int index, int x);
char	*ft_strdup(char *source);

int	check_path(t_cmd *cmd, char **env, int x)
{
	int	index;

	if (cmd[x].cmd_path == NULL)
		return (-1);
	if (access(cmd[x].cmd_path, F_OK) == 0)
		return (0);
	index = check_env_path_exist(env);
	if (index == -1)
		return (-1);
	if (is_builtins(cmd[x].cmd_params[0]))
		return (0);
	ft_get_cmd_w_path(cmd, env, index, x);
	return (0);
}

int	check_env_path_exist(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P')
			if (env[i][1] == 'A')
				if (env[i][2] == 'T')
					if (env[i][3] == 'H')
						if (env[i][4] == '=')
							return (i);
		i++;
	}
	return (-1);
}

char	*get_new_cmd_buf(t_cmd *cmd, char **all_path, int x, int i)
{
	char	*cmd_buf;

	cmd_buf = ft_strdup(cmd[x].cmd_params[0]);
	cmd_buf = ft_strjoin_no_space("/", cmd_buf, 1);
	cmd_buf = ft_strjoin_no_space(all_path[i], cmd_buf, 1);
	return (cmd_buf);
}

int	check_cmd_params_for_path(t_cmd *cmd, int x)
{
	if (cmd[x].cmd_params[0][0] == '\0')
	{
		free(cmd[x].cmd_path);
		cmd[x].cmd_path = ft_strdup(cmd[x].cmd_params[0]);
		return (-1);
	}
	return (0);
}

int	ft_get_cmd_w_path(t_cmd *cmd, char **env, int index, int x)
{
	int		i;
	char	**all_path;
	char	*cmd_buf;

	i = 0;
	if (check_cmd_params_for_path(cmd, x) == -1)
		return (-1);
	all_path = NULL;
	all_path = get_all_path(env, all_path, index);
	while (all_path[i] != NULL)
	{
		cmd_buf = get_new_cmd_buf(cmd, all_path, x, i);
		if (access(cmd_buf, F_OK) == 0)
		{
			free_path(cmd, x, cmd_buf, all_path);
			return (0);
		}
		free(cmd_buf);
		i++;
	}
	free_path_env(cmd, all_path, x);
	return (-1);
}
