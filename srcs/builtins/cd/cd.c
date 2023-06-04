/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:44:36 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 11:29:23 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_old_pwd(t_parse *parse, char *oldpath);
int		get_old_path(char **env);
int		check_chdir(t_parse *parse, t_cmd cmd, char *path);
int		ft_strncmp(char *first, char *second, int length);
int		get_index(char **env);

void	builtins_cd(t_parse *parse, t_cmd cmd, char **cmd_params)
{
	if (get_len_2d_array(cmd_params) >= 3)
	{
		ft_put_str("minishell: cd: too many arguments\n", 2);
		change_return_value(parse->cmd, 1, cmd.index_error_redirection);
		return ;
	}
	else if (get_len_2d_array(cmd_params) == 2)
	{
		if (check_chdir(parse, cmd, cmd_params[1]) == -1)
			return ;
	}
	return ;
}

int	get_old_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] == 'O')
			if (env[i][1] == 'L')
				if (env[i][2] == 'D')
					if (env[i][3] == 'P')
						if (env[i][4] == 'W')
							if (env[i][5] == 'D')
								if (env[i][6] == '=')
									return (i);
		i++;
	}
	return (-1);
}

void	change_old_pwd(t_parse *parse, char *oldpath)
{
	int	index_old_pwd;

	index_old_pwd = get_old_path(parse->envp);
	if (index_old_pwd == -1)
		return ;
	free(parse->envp[index_old_pwd]);
	oldpath = ft_strjoin_no_space("OLDPWD=", oldpath, 0);
	parse->envp[index_old_pwd] = ft_strdup(oldpath);
	free(oldpath);
}

void	change_pwd(t_parse *parse)
{
	char	pwd[4096];
	char	*new_pwd;
	int		index_pwd;

	index_pwd = get_index(parse->envp);
	getcwd(pwd, 4096);
	if (index_pwd == -1)
		return ;
	free(parse->envp[index_pwd]);
	new_pwd = ft_strjoin_no_space("PWD=", pwd, 0);
	parse->envp[index_pwd] = ft_strdup(new_pwd);
	free(new_pwd);
}

int	check_chdir(t_parse *parse, t_cmd cmd, char *path)
{
	char		old_pwd[500];
	static int	i;

	i = 0;
	getcwd(old_pwd, 500);
	if (chdir(path) == -1)
	{
		ft_put_str("cd: No such file or directory\n", 2);
		change_return_value(parse->cmd, 1, cmd.index_error_redirection);
		return (-1);
	}
	change_old_pwd(parse, old_pwd);
	change_pwd(parse);
	change_return_value(parse->cmd, 0, cmd.index_error_redirection);
	i++;
	return (0);
}
