/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser_utils03.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/19 23:03:11 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [line_parser_utils03.c]
// char	*condition_special_check(char *str, int i, t_parse *parse);
// char	*check_quotes(char *str, int i, t_parse *parse);
// char	*second_parser(char *str, t_parse *parse);
// int	check_dollar_character(char *str);
// int	check_quote_and_char_next_to(int i, char c, char *str);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	*condition_special_check(char *str, int i, t_parse *parse)
{
	if (i >= 2 && str[i] == '$' && str[i + 1] != '\"' && str[i + 1] != ' ')
	{
		if (str[i - 1] == '\"' && str[i - 2] == '\"')
		{
			str = clean_line(i - 2, '\"', str);
			i = 0;
		}
	}
	if (str[i] == '$' && str[i + 1] != '\"' && str[i + 1] != ' ')
	{
		while (str[i] && str[i] != ' ')
		{
			if (str[i + 1] && str[i] == '\"' && str[i + 1] == '\"')
			{
				str = clean_line(i, '\"', str);
				i -= 3;
			}
			i++;
		}
	}
	parse->index.i = i;
	return (str);
}

char	*check_quotes(char *str, int i, t_parse *parse)
{
	char	*tmp;

	if ((str[i] == '\'' || str[i] == '\"'))
	{
		if (check_quote_in_quote(str, str[i], i))
			i += check_quote_in_quote(str, str[i], i);
		else if (check_quote_charactere(str, str[i], i))
		{
			tmp = ft_strdup(str);
			str = clean_read_line(i, str[i], str);
			if (ft_strcmp(str, tmp) == 0)
				i += strnlen_stop(str, str[i], i + 1);
			else if (i > 0)
				i--;
			else
				i = -1;
			free(tmp);
		}
		else if (!check_quote_charactere(str, str[i], i))
			i += strnlen_stop(str, str[i], i + 1);
	}
	parse->index.i = i;
	return (str);
}

char	*second_parser(char *str, t_parse *parse)
{
	parse->index.i = 0;
	while (str[parse->index.i])
	{
		str = check_quotes(str, parse->index.i, parse);
		parse->index.i++;
	}
	parse->index.i = 0;
	return (str);
}

int	check_dollar_character(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && (str[i + 1] == '>' \
			|| str[i + 1] == '<' || str[i + 1] == '|' \
			|| str[i + 1] == '%' || str[i + 1] == '^'))
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_quote_and_char_next_to(int i, char c, char *str)
{
	i += 1;
	while (str[i] != c && str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == c)
			i++;
		else
			return (-1);
	}
	return (1);
}
