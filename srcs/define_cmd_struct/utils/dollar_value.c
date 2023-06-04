/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:37:27 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 18:46:51 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_len_newstr(char **array);

char	**delete_null_byte(char **array)
{
	char	**newstr;
	int		len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (array == NULL)
		return (NULL);
	len = get_len_newstr(array);
	if (len == -1)
		return (array);
	if (len == 0)
		return (NULL);
	newstr = malloc(sizeof(char *) * (len + 1));
	while (array[i] != NULL)
	{
		if (array[i][0] != '\0')
			newstr[x++] = ft_strdup(array[i]);
		i++;
	}
	newstr[x] = NULL;
	free_2d_array(array);
	return (newstr);
}

char	*make_new_str_with_dollar_value(char *str, char *return_value,
		int index, int len)
{
	char	*new_str;
	int		i;
	int		x;
	int		j;

	i = 0;
	x = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + len + 1));
	while (str[i] != '\0')
	{
		if (i == index)
		{
			while (return_value[x] != '\0')
				new_str[j++] = return_value[x++];
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*change_dollar(char *str, char *return_value)
{
	int	i;
	int	add_len;

	i = 0;
	add_len = (ft_strlen(return_value) - 2);
	while (str[i] != '\0' && str[i] != '\'')
	{
		if (str[i] == '$' && str[i + 1] == '?')
			str = make_new_str_with_dollar_value(str, return_value, i, add_len);
		i++;
	}
	return (str);
}

void	change_dollar_value_in_cmd(t_cmd *cmd, int index)
{
	int		i;
	char	*return_value;

	return_value = ft_itoa(g_return_status);
	i = 0;
	while (cmd[index].cmd_params[i] != NULL)
	{
		cmd[index].cmd_params[i] = change_dollar(cmd[index].cmd_params[i],
				return_value);
		i++;
	}
	free(return_value);
}

void	change_all_dollar_return_value(t_cmd *cmd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		change_dollar_value_in_cmd(cmd, i);
		i++;
	}
}
