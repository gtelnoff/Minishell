/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:45:43 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 04:45:45 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int		check_first_letter(t_parse *parse, t_cmd cmd, char *str);
void	check_first_letter_error_message(t_parse *parse, t_cmd cmd, char *str);
int		check_all_str(t_parse *parse, t_cmd cmd, char *str);

int	check_cmd_params(t_parse *parse, t_cmd cmd, char *str)
{
	if (check_first_letter(parse, cmd, str) == -1)
		return (-1);
	if (check_all_str(parse, cmd, str) == -1)
		return (-1);
	return (1);
}

void	check_first_letter_error_message(t_parse *parse, t_cmd cmd, char *str)
{
	change_return_value(parse->cmd, 1, cmd.index_error_redirection);
	ft_put_str("bash: unset: \'", 2);
	write(2, &str[0], 1);
	ft_put_str("\': not a valid identifier\n", 2);
}

int	check_first_letter(t_parse *parse, t_cmd cmd, char *str)
{
	if (str[0] == '_')
		return (0);
	else if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A'
			&& str[0] <= 'Z'))
		return (0);
	check_first_letter_error_message(parse, cmd, str);
	return (-1);
}

void	put_error_message(char *str)
{
	ft_put_str("bash: unset: \'", 2);
	ft_put_str(str, 2);
	ft_put_str("\': not a valid identifier\n", 2);
}

int	check_all_str(t_parse *parse, t_cmd cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '_')
		{
			if (str[i] < 'a' || str[i] > 'z')
			{
				if (str[i] < 'A' || str[i] > 'Z')
				{
					if (str[i] < '0' || str[i] > '9')
					{
						change_return_value(parse->cmd, 1, \
							cmd.index_error_redirection);
						put_error_message(str);
						return (-1);
					}
				}
			}
		}
		i++;
	}
	return (0);
}
