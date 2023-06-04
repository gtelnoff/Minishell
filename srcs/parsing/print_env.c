/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:33:13 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:03:42 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [print_env.c]
// void	change_tab_path(int i, int temp, t_parse *parse);
// int	loop_find_path(char *no_dollar, t_parse *parse);
// int	find_path(int index_i, int index_j, t_parse *parse);
// int	loop_search_path(int i, int j, int temp, t_parse *parse);
// void	search_path(t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	change_tab_path(int i, int temp, t_parse *parse)
{
	char	*str;
	char	*clean;
	int		k;
	int		j;

	str = parse->fill_tab[i];
	k = 0;
	j = 0;
	clean = malloc(sizeof(char *) * ((ft_strlen(parse->clean_var) \
	+ ft_strlen(parse->fill_tab[i]) - ft_strlen(parse->var))));
	while (k < (temp + k - j))
		clean[k++] = str[j++];
	j = 0;
	while (parse->clean_var[j])
		clean[k++] = parse->clean_var[j++];
	free(parse->clean_var);
	j = temp + ft_strlen(parse->var);
	while (str[j])
		clean[k++] = str[j++];
	clean[k] = '\0';
	free(parse->fill_tab[i]);
	parse->fill_tab[i] = clean;
}

int	loop_find_path(char *no_dollar, t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->envp[i])
	{
		if (!ft_strncmp(no_dollar, parse->envp[i], ft_strlen(no_dollar)))
		{
			parse->clean_var = clean_path(parse->envp[i], parse);
			free(no_dollar);
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_path(int index_i, int index_j, t_parse *parse)
{
	int		i;
	int		j;
	char	*no_dollar;

	if (!parse->var || parse->var[1] == '\0')
		return (0);
	no_dollar = ft_calloc_parsing(sizeof(char), ft_strlen(parse->var) + 10);
	i = 1;
	j = 0;
	while (parse->var[i])
		no_dollar[j++] = parse->var[i++];
	no_dollar[i] = '\0';
	if (loop_find_path(no_dollar, parse))
		return (1);
	many_dollar(index_i, index_j, parse);
	free(no_dollar);
	return (0);
}

int	loop_search_path(int i, int j, int temp, t_parse *parse)
{
	int	m;

	m = 0;
	if (parse->fill_tab[i][j + 1] && parse->fill_tab[i][j] == '$'
		&& check_quote(i, '\'', parse) == 1)
	{
		temp = j;
		parse->var = malloc(sizeof(char) * ft_strlen(parse->fill_tab[i]) + 1);
		parse->var[m++] = parse->fill_tab[i][j++];
		while (chech_correct_path_arg(j, parse->fill_tab[i]) == 1)
			parse->var[m++] = parse->fill_tab[i][j++];
		parse->var[m] = '\0';
		if (find_path(i, temp, parse))
			change_tab_path(i, temp, parse);
		free(parse->var);
		parse->var = NULL;
	}
	return (temp);
}

void	search_path(t_parse *parse)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	temp = 0;
	while (parse->fill_tab[i])
	{
		j = 0;
		while (parse->fill_tab[i][j])
		{
			temp = loop_search_path(i, j, temp, parse);
			if (parse->fill_tab[i][j])
				j++;
		}
		if (there_is_character(parse->fill_tab[i], i, parse))
			search_path(parse);
		i++;
	}
}
