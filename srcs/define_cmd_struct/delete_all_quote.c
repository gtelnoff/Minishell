/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:14:35 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/14 00:14:37 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**delete_first_and_last_quote(char **array);
char	*make_newstr_wtih_no_quote(char *str);
int		is_quote(char *str);

void	delete_all_quote(t_parse *parse, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		parse->cmd[i].cmd_params = delete_first_and_last_quote(parse-> \
			cmd[i].cmd_params);
		parse->cmd[i].all_redirection = delete_first_and_last_quote(parse-> \
			cmd[i].all_redirection);
		i++;
	}
}

int	is_quote(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		return (1);
	return (0);
}

char	*make_newstr_wtih_no_quote(char *str)
{
	char	*new_str;
	int		len_str;
	int		i;

	i = 0;
	len_str = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len_str - 1));
	while (i < (len_str - 1))
	{
		new_str[i] = str[i + 1];
		i++;
	}
	new_str[i - 1] = '\0';
	return (new_str);
}

char	**delete_first_and_last_quote(char **array)
{
	char	**new_array;
	int		nb_of_str;
	int		i;

	if (array == NULL)
		return (NULL);
	nb_of_str = get_len_2d_array(array);
	i = 0;
	new_array = malloc(sizeof(char *) * (nb_of_str + 1));
	while (i < nb_of_str)
	{
		if (is_quote(array[i]))
			new_array[i] = make_newstr_wtih_no_quote(array[i]);
		else
			new_array[i] = strdup(array[i]);
		i++;
	}
	free_2d_array(array);
	new_array[i] = NULL;
	return (new_array);
}
