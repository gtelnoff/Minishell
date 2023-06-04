/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:05:52 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 11:25:25 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [print_export.c]
// char	*add_quote2(char *tmp, int count, int i, int j);
// char	*add_quote(char *str);
// void	add_argument_into_export(t_parse *parse);
// void	sort_loop(t_parse *parse);
// void	print_export(t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	*add_quote2(char *tmp, int count, int i, int j)
{
	if (count == 1)
	{
		tmp[j++] = '\"';
		tmp[j] = '\0';
	}
	else
		tmp[j] = '\0';
	i = ft_strlen(tmp);
	if (i > 2)
	{
		if (tmp[i - 1] == '\"' && tmp[i - 2] == '=')
		{
			tmp[i] = '\"';
			tmp[i + 1] = '\0';
		}
	}
	return (tmp);
}

char	*add_quote(char *str)
{
	int		i;
	int		j;
	int		len;
	int		count;
	char	*tmp;

	j = 0;
	i = 0;
	count = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 4);
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '=' && count == 0)
		{
			tmp[j++] = '=';
			i++;
			tmp[j++] = '\"';
			count = 1;
		}
		tmp[j++] = str[i++];
	}
	free(str);
	return (add_quote2(tmp, count, i, j));
}

void	add_argument_into_export(t_parse *parse)
{
	int		i;
	char	*tmp;

	i = 0;
	while (parse->env[i])
	{
		if (parse->env[i][0] != '_' && parse->env[i][0] != '=')
		{
			tmp = ft_strjoin_parsing("declare -x ", parse->env[i]);
			tmp = add_quote(tmp);
			free(parse->env[i]);
			parse->env[i] = tmp;
			printf("%s\n", parse->env[i]);
			free(parse->env[i]);
		}
		else
			free(parse->env[i]);
		i++;
	}
	free(parse->env);
}

void	sort_loop(t_parse *parse)
{
	int		i;
	int		j;
	char	*temp;

	j = 1;
	i = 0;
	while (parse->env[j])
	{
		i = 0;
		while (parse->env[i])
		{
			if (ft_strcmp(parse->env[i], parse->env[j]) > 0)
			{
				temp = parse->env[i];
				parse->env[i] = parse->env[j];
				parse->env[j] = temp;
			}
			i++;
		}
		j++;
	}
}

void	print_export(t_parse *parse)
{
	int	i;

	i = 0;
	parse->env = malloc(sizeof(char *) * 4096);
	while (parse->envp[i])
	{
		parse->env[i] = ft_substr_parsing(parse->envp[i], 0, \
			ft_strlen(parse->envp[i]));
		i++;
	}
	parse->env[i] = NULL;
	sort_loop(parse);
	add_argument_into_export(parse);
}
