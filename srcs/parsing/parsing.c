/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/19 22:47:32 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [parsing.c]
// void	init_struct_value(t_parse *parse);
// void	malloc_envp(char **env, t_parse *parse);
// char **parsing(t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	**array_dup(char **array);

void	init_struct_value(t_parse *parse)
{
	parse->var = NULL;
	parse->cmpt_line = 0;
	parse->clean_var = NULL;
	parse->index.j = 0;
	parse->index.i = 0;
	parse->index.len = 0;
	parse->fill_tab = NULL;
}

void	malloc_envp(char **env, t_parse *parse)
{
	int	i;

	i = 0;
	parse->envp = ft_calloc_parsing(sizeof(char *), 4096);
	while (env[i])
	{
		parse->envp[i] = ft_substr_parsing(env[i], 0, ft_strlen(env[i]));
		i++;
	}
	parse->len_envp = i - 1;
	parse->envp[i] = NULL;
}

char	**array_dup_parsing(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (get_len_2d_array(array) + 1));
	while (array[i] != NULL)
	{
		new_array[i] = ft_strdup(array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	new_array[i] = NULL;
	return (new_array);
}

///	else
//	ft_free(parse, TRUE);
//	a la fin de parsing ?
char	**parsing(t_parse *parse)
{
	char	**new_fill_tab;

	new_fill_tab = NULL;
	if (first_parser(parse))
	{
		fill_tab_arg(parse);
		search_path(parse);
		new_fill_tab = array_dup(parse->fill_tab);
		free(parse->line);
		return (new_fill_tab);
	}
	return (NULL);
}
