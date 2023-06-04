/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_utils02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:33:13 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:00:18 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [print_env_utils02.c]
// char	*delete_dollar(char *str, int index);
// int	many_dollar_loop(int index_i, t_parse *parse);
// void	many_dollar(int index_i, int index_j, t_parse *parse);
// int there_is_character(char *str, int index, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	*delete_dollar(char *str, int index)
{
	int		i;
	char	*clean;

	i = 0;
	clean = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (i < index - 1)
	{
		clean[i] = str[i];
		i++;
	}
	index += 1;
	while (str[index])
		clean[i++] = str[index++];
	clean[i] = '\0';
	free(str);
	str = NULL;
	return (clean);
}

int	many_dollar_loop(int index_i, t_parse *parse)
{
	int	j;

	j = 0;
	while (parse->fill_tab[index_i])
	{
		if (parse->fill_tab[index_i][j] == '$')
			return (j);
		j++;
		if (!parse->fill_tab[index_i])
			return (-1);
	}
	return (0);
}

void	many_dollar(int i, int j, t_parse *parse)
{
	int	jbis;
	int	check;

	jbis = many_dollar_loop(i, parse);
	if (jbis == -1)
	{
		parse->fill_tab[i][j] = '\0';
		return ;
	}
	check = strnlen_stop(parse->fill_tab[i], '$', jbis + 1);
	if (!check)
	{
		parse->fill_tab[i][j] = '\0';
		return ;
	}
	while (parse->fill_tab[i][check + jbis] && parse->fill_tab[i][j])
		parse->fill_tab[i][j++] = parse->fill_tab[i][check + jbis++];
	while (parse->fill_tab[i][j])
		parse->fill_tab[i][j++] = '\0';
}

int	there_is_character(char *str, int index, t_parse *parse)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?' || str[i + 1] == ' ' \
			|| str[i + 1] == '\0' || str[i + 1] == '\'' \
			|| (i > 0 && str[i - 1] == '\'') \
			|| check_quote(index, '\'', parse))
				return (FALSE);
			else
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
