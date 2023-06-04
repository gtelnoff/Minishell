/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:07:52 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [line_parser.c]
// int	verif_inside_character(char *str, char c, int i);
// int	verif_inside_quote(char *str, char c, int i);
// char	*special_check(char *str, t_parse *parse);
// int	first_parser(t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	verif_inside_quote(char *str, char c, int i)
{
	if (i >= 2)
	{
		if (str[i] == c && str[i - 2] != ' ')
			return (FALSE);
		if (str[i] == c && (str[i + 1] != ' ' \
		|| str[i + 1] == '\0'))
			return (FALSE);
	}
	if ((str[i] == '\'' && str[i - 1] == '\'') \
	|| (str[i] == '\"' && str[i - 1] == '\"'))
		return (TRUE);
	return (FALSE);
}

int	verif_inside_character(char *str, char c, int i)
{
	if (i >= 2)
		if (str[i] == c && str[i - 2] == ' ' \
		&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
			return (TRUE);
	return (FALSE);
}

char	*special_check(char *str, t_parse *parse)
{
	parse->index.i = 0;
	while (str[parse->index.i])
	{
		str = condition_special_check(str, parse->index.i, parse);
		if (!str[parse->index.i])
			break ;
		parse->index.i++;
	}
	parse->index.i = 0;
	return (str);
}

int	ft_is_blank(char *line)
{
	char	*tmp;

	tmp = line;
	while (*tmp)
	{
		if (*tmp != ' ' && *tmp != '\t')
			return (0);
		tmp++;
	}
	return (1);
}

int	first_parser(t_parse *parse)
{
	if (ft_is_blank(parse->line))
		return (FALSE);
	if (!peer_quote(parse->line))
	{
		ft_error(NULL, 0x0111, TRUE, parse);
		return (FALSE);
	}
	if (!check_dollar_character(parse->line))
	{
		ft_error(parse->line, 0x0112, TRUE, parse);
		return (FALSE);
	}
	if (check_quoted_string(parse->line) || check_unquoted_string(parse->line))
		parse->line = special_check(parse->line, parse);
	parse->line = second_parser(parse->line, parse);
	return (TRUE);
}
