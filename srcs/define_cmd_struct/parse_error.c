/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:13:07 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 18:47:11 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_check_pipe(char **array);
int	error_check_redirection(char **array);

int	have_parse_error(char **array)
{
	if (error_check_pipe(array) == 1)
	{
		ft_put_str("minishell: syntax error ", 2);
		ft_put_str("near unexpected token `|\'\n", 2);
		g_return_status = 2;
		return (1);
	}
	if (error_check_redirection(array) == 1)
	{
		ft_put_str("minishell: syntax", 2);
		ft_put_str(" error near unexpected token `newline\'\n", 2);
		g_return_status = 2;
		return (1);
	}
	return (0);
}

int	error_check_pipe(char **array)
{
	int	len;

	len = get_len_2d_array(array);
	if (ft_strlen(array[0]) == 1 && array[0][0] == '|')
		return (1);
	if (ft_strlen(array[len - 1]) == 1 && array[len - 1][0] == '|')
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (str == NULL)
		return (-1);
	if (str[0] == '|' && (str[1] == '\0'))
		return (-2);
	if ((str[0] == '<') && (str[1] == '\0'))
		return (1);
	if ((str[0] == '>') && str[1] == '\0')
		return (1);
	if ((str[0] == '>') && (str[1] == '>' && str[2] == '\0'))
		return (1);
	if ((str[0] == '<') && (str[1] == '<' && str[2] == '\0'))
		return (1);
	return (0);
}

int	error_check_redirection(char **array)
{
	int	i;
	int	len_array;

	i = 0;
	len_array = get_len_2d_array(array);
	if ((array[0][0] == '<' && array[1] == NULL) \
		|| (array[0][0] == '>' && array[1] == NULL))
		return (1);
	else if ((array[len_array - 1][0] == '<' && array[len_array] == NULL) \
		|| (array[len_array - 1][0] == '>' && array[len_array] == NULL))
		return (1);
	while (i < len_array - 1)
	{
		if (is_redirection(array[i]) == 1 && is_redirection(array[i + 1]) == 1)
			return (1);
		if (is_redirection(array[i]) == 1 && is_redirection(array[i + 1]) == -2)
			return (1);
		i++;
	}
	return (0);
}
