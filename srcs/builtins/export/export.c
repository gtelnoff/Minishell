/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:09:03 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [export.c]
// int	check_same_var(char *tab, t_parse *parse);
// char	*add_arg_witout_more(char *str);
// char	*add_arg_to_var(int index, char *tab, t_parse *parse);
// int	loop_export(char **tab, int i, int j, t_parse *parse);
// void	export(char **tab, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	error_export(t_parse *parse, t_cmd cmd);

int	check_same_var(char *tab, t_parse *parse)
{
	int		i;
	int		len;
	int		len_tmp;
	char	*var;
	char	*tmp;

	i = 0;
	len = strlen_stop(tab, '=');
	len_tmp = strlen_stop(tab, '+');
	if (len_tmp < len)
		len = len_tmp;
	var = ft_strdup(tab);
	var[len] = '\0';
	while (parse->envp[i])
	{
		len = strlen_stop(parse->envp[i], '=');
		tmp = ft_strdup(parse->envp[i]);
		tmp[len] = '\0';
		if (ft_strcmp(tmp, var) == 0)
			return (free(tmp), free(var), i);
		free(tmp);
		i++;
	}
	free(var);
	return (-1);
}

char	*add_arg_witout_more(char *str)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	j = 0;
	clean = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] != '+')
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

char	*add_arg_to_var(int index, char *tab, t_parse *parse)
{
	int		i;
	int		j;
	char	*tmp;
	char	*clean;

	if (is_this_character(tab, '='))
		return (add_arg_witout_more(tab));
	tmp = malloc(sizeof(char) * ft_strlen(tab));
	i = strlen_stop(tab, '=') + 1;
	j = 0;
	while (tab[i])
		tmp[j++] = tab[i++];
	tmp[j] = '\0';
	clean = ft_strjoin_parsing(parse->envp[index], tmp);
	free(tmp);
	return (clean);
}

int	loop_export(char **tab, int i, int j, t_parse *parse)
{
	int		index;
	char	*tmp;

	index = check_same_var(tab[i], parse);
	if (index != -1)
	{
		if (there_is(parse->envp[index], '=', '+') \
		&& !there_is(tab[i], '=', '+'))
			return (j);
		if (verif_var_character(tab[i]))
			tmp = add_arg_to_var(index, tab[i], parse);
		else
			tmp = ft_strdup(tab[i]);
		free(parse->envp[index]);
		parse->envp[index] = tmp;
	}
	else
	{
		free(parse->envp[parse->len_envp + j]);
		if (verif_var_character(tab[i]))
			parse->envp[parse->len_envp + j++] = var_without_no_more(tab[i]);
		else
			parse->envp[parse->len_envp + j++] = ft_strdup(tab[i]);
	}
	return (j);
}

void	export(char **tab, t_parse *parse, t_cmd cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (!tab[1])
	{
		print_export(parse);
		return ;
	}
	while (tab[i])
	{
		if (!check_valid_identifier(tab[i]) && i % 2 != 0)
			error_export(parse, cmd);
		else
			j = loop_export(tab, i, j, parse);
		i++;
	}
	parse->envp[parse->len_envp + j] = NULL;
	parse->len_envp += j - 1;
}
