/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:57:49 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 20:11:04 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		check_cmd_params(t_parse *parse, t_cmd cmd, char *str);
int		check_first_letter(t_parse *parse, t_cmd cmd, char *str);
int		check_all_str(t_parse *parse, t_cmd cmd, char *str);
int		get_index_unset(char **envp, char *unset_var);
char	**array_dup(char **array);

int	ft_strncmp(char *first, char *second, int length)
{
	int	i;
	int	lengthbis;

	i = 0;
	lengthbis = length;
	if (length <= 0)
		return (0);
	while (first[i] && (first[i] == second[i]) && (i < lengthbis - 1))
		i++;
	return (first[i] - second[i]);
}

int	get_index_unset(char **envp, char *unset_var)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(unset_var, envp[i], ft_strlen(unset_var)) == 0)
		{
			free(unset_var);
			return (i);
		}
		i++;
	}
	free(unset_var);
	return (-1);
}

int	get_index_unset_without_egal(char **envp, char *unset_var)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i] != NULL)
	{
		len = ft_strlen(envp[i]);
		if (ft_strncmp(unset_var, envp[i], ft_strlen(unset_var)) == 0)
		{
			if (envp[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	new_envp(char **envp, int index, t_parse *parse)
{
	char	*tmp;
	int		i;

	i = index;
	while (i < parse->len_envp)
	{
		tmp = envp[i];
		envp[i] = envp[i + 1];
		envp[i + 1] = tmp;
		i++;
	}
	parse->len_envp--;
	free(envp[i]);
	envp[i] = NULL;
}

void	unset(char **tab, t_parse *parse, t_cmd cmd)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (!tab[1])
		return ;
	while (tab[i])
	{
		if (check_cmd_params(parse, cmd, tab[i]))
		{
			check = get_index_unset(parse->envp, \
			ft_strjoin_parsing(tab[i], "=\0"));
			if (check == -1)
				check = get_index_unset_without_egal(parse->envp, tab[i]);
			if (check != -1)
				new_envp(parse->envp, check, parse);
		}
		i++;
	}
	if (check == 0)
		change_return_value(parse->cmd, 0, cmd.index_error_redirection);
}
