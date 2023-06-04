/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:02:53 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/13 14:53:07 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [error.c]
// void    ft_error_exit(char *str, int code);
// void    ft_error_export(int code);
// void    ft_error_parse(char *str, int code);
// void    ft_error(char *str, int code, int free, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	ft_error_exit(char *str, int code)
{
	if (code == 0x01)
		printf("minishell: exit: %s: numeric argument required\n", str);
	if (code == 0x02)
		printf("minishell: exit: too many arguments\n");
	if (code == 0x03)
		printf("minishell: exit: %s: numeric required\n", str);
}

void	ft_error_export(int code)
{
	if (code == 0x011)
		printf("minishell: export: `: not a valid identifier\n");
}

void	ft_error_parse(char *str, int code)
{
	if (code == 0x0111)
	{
		printf("minishell: syntax error near unexpected token\n");
		g_return_status = 2;
	}
	if (code == 0x0112)
		printf("%s:command not found\n", str);
}

void	ft_error(char *str, int code, int free, t_parse *parse)
{
	ft_error_export(code);
	ft_error_exit(str, code);
	ft_error_parse(str, code);
	if (free == FALSE)
		ft_free(parse, TRUE);
}
