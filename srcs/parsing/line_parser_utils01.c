/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser_utils01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/20 18:41:20 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [line_parser_utils01.c]
// int	check_quote_in_quote(char *str, char c, int i);
// int	peer_quote(char *str);
// int	check_quote_charactere(char *str, char c, int i);
// int	check_quoted_string(char *str);
// int	check_unquoted_string(char *str);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	check_quote_in_quote(char *str, char c, int i)
{
	int	tmp;
	int	len_quote_end;
	int	len_quote_start;

	tmp = i;
	len_quote_end = 0;
	len_quote_start = i;
	i += 1;
	if (verif_inside_quote(str, c, i))
		return (TRUE);
	while (str[i] != c && str[i])
	{
		i++;
		if (str[i] == c)
			len_quote_end = i;
	}
	while (len_quote_start < len_quote_end)
	{
		if ((str[len_quote_start] == '\'' && c == '\"') \
		|| (str[len_quote_start] == '\"' && c == '\''))
			return (len_quote_end - tmp);
		len_quote_start++;
	}
	return (0);
}

int	check_quote_charactere(char *str, char c, int i)
{
	i = i + 1;
	if (verif_inside_character(str, c, i))
		return (TRUE);
	while (str[i] != c && str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (FALSE);
		if ((c == '\'' && str[i] == '\"') || (c == '\"' && str[i] == '\''))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	peer_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			if (!str[i])
				return (FALSE);
			while (str[i] != c)
			{
				i++;
				if (!str[i])
					return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

int	check_quoted_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
					return (TRUE);
				if (!str[i])
					return (FALSE);
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}

int	check_unquoted_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] != ' ')
			{
				if (!str[i] || str[i] == '\0')
					return (TRUE);
				if (str[i] == '\"')
					return (TRUE);
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}
