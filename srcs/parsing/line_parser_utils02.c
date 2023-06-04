/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser_utils02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/13 14:56:13 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [line_parser_utils02.c]
// int	condition_clean_rl(char *str, char *clean, char c, int i);
// char	*clean_read_line(int i, char c, char *str);
// int	strnlen_stop(char *str, char c, int size);
// char	*clean_line(int i, char c, char *str);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	condition_clean_rl(char *str, char *clean, char c, int i)
{
	if (str[i] == ' ' || str[i] == '\'' || str[i] == '\"' \
	|| (c == '\'' && str[i] == '$'))
	{
		free(clean);
		return (TRUE);
	}
	return (FALSE);
}

char	*clean_read_line(int i, char c, char *str)
{
	int		j;
	char	*clean;

	j = 0;
	clean = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (j < i)
	{
		clean[j] = str[j];
		j++;
	}
	i += 1;
	while (str[i] != c)
	{
		if (condition_clean_rl(str, clean, c, i))
			return (str);
		clean[j++] = str[i++];
	}
	i += 1;
	while (str[i])
		clean[j++] = str[i++];
	clean[j] = '\0';
	free(str);
	return (clean);
}

int	strnlen_stop(char *str, char c, int size)
{
	int	tmp;

	tmp = size - 1;
	if (!str)
		return (0);
	while (str[size])
	{
		if (str[size] == c)
			return (size - tmp);
		size++;
	}
	return (0);
}

char	*clean_line(int i, char c, char *str)
{
	int		j;
	char	*clean;

	j = 0;
	clean = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (j < i)
	{
		clean[j] = str[j];
		j++;
	}
	i += 1;
	while (str[i] != c)
		clean[j++] = str[i++];
	i += 1;
	while (str[i])
		clean[j++] = str[i++];
	clean[j] = '\0';
	free(str);
	return (clean);
}
