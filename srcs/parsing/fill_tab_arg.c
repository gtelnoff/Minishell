/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:33:18 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/21 22:54:17 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [fill_tab_arg.c]
// void	fill_tab_arg(t_parse *parse);
// void	find_and_split(t_parse *parse);
// void	find_quote(char c, t_parse *parse);
// void 	split_special_character(int len, t_parse *parse);
// int		find_quote_next_to_char(char c, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	fill_tab_arg(t_parse *parse)
/*	Fill table with arguments (readline)	*/
{
	int	len;

	parse->fill_tab = malloc(sizeof(char *) * \
	cmpt_words((char *)parse->line) + 12);
	len = ft_strlen((char *)parse->line);
	while (parse->index.i < len)
	{
		while (parse->line[parse->index.i] == ' ' \
		&& parse->line[parse->index.i])
			parse->index.i++;
		condition_fill_tab(parse);
		parse->index.i += parse->index.len;
		while (parse->line[parse->index.i] == ' ' \
		&& parse->line[parse->index.i])
			parse->index.i++;
		parse->index.len = 0;
	}
	parse->fill_tab[parse->index.j] = NULL;
}

void	find_and_split(t_parse *parse)
/*	Search special character next to character and split them and
	found if they are 2 simple quote or 2 double quote	*/
{
	while (check_character(parse->index.i, \
	parse->index.len, parse->line, 1))
	{
		if (check_character(parse->index.i, \
		parse->index.len, parse->line, 2))
		{
			if (check_character(parse->index.i, \
			parse->index.len, parse->line, 3))
				split_special_character(2, parse);
			else if (check_character(parse->index.i, \
			parse->index.len, parse->line, 2))
				split_special_character(1, parse);
			break ;
		}
		if (parse->line[parse->index.i + parse->index.len] == '\'')
			if (find_quote_next_to_char('\'', parse))
				break ;
		if (parse->line[parse->index.i + parse->index.len] == '\"')
			if (find_quote_next_to_char('\"', parse))
				break ;
		parse->index.len++;
	}
}

void	find_quote(char c, t_parse *parse)
/* Split character	*/
{
	int		quote;
	int		len_quote;

	len_quote = 0;
	quote = parse->index.i + 1;
	while (parse->line[quote] != c && parse->line[quote])
	{
		quote++;
		len_quote++;
	}
	if (parse->line[quote] == c && parse->line[quote + 1] != '\'' \
	&& parse->line[quote + 1] != '\"')
	{
		parse->fill_tab[parse->index.j] = \
		ft_substr_parsing((const char *)parse->line, \
		parse->index.i, len_quote + 2);
		parse->index.j++;
		parse->index.i = quote + 1;
	}
	else if (parse->line[quote] == c)
		parse->index.i = quote + 1;
}

void	split_special_character(int len, t_parse *parse)
/*	Slit character	*/
{
	if (parse->index.len > 0)
	{
		parse->fill_tab[parse->index.j] \
		= ft_substr_parsing((const char *)parse->line,
			parse->index.i, parse->index.len);
			parse->index.j++;
	}
	parse->fill_tab[parse->index.j] = \
	ft_substr_parsing((const char *)parse->line, \
	(parse->index.i + parse->index.len), len);
	parse->index.j++;
	parse->index.i += parse->index.len + len;
	parse->index.len = 0;
}

int	find_quote_next_to_char(char c, t_parse *parse)
/*	Search character if they are peer	*/
{
	int	quote;

	quote = 0;
	quote = parse->index.i + parse->index.len + 1;
	while (parse->line[quote] != c && parse->line[quote])
		quote++;
	if (parse->line[quote] == c)
		return (TRUE);
	return (FALSE);
}
