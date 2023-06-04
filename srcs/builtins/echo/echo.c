/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:06 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 20:04:18 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [echo.c]
// char	*ft_strjoin_free(char *s1, char *s2, int index);
// char	*double_tab_to_simple(char **array, int n);
// int	verif_arg_echo(char *tab)s;
// void	echo(char **tab);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	*ft_strjoin_free(char *s1, char *s2, int index)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen_parsing(s1) + ft_strlen(s2) + 2));
	if (!dest)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = ' ';
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	if (index >= 2)
		free(s1);
	return (dest);
}

char	*double_tab_to_simple(char **array, int n)
{
	int		i;
	char	*str;

	i = 1 + n;
	str = ft_strdup(array[i++]);
	while (array[i] != NULL)
	{
		str = ft_strjoin_free(str, array[i], i);
		i++;
	}
	return (str);
}

int	verif_first_argument(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (FALSE);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (TRUE);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (FALSE);
			i++;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

void	echo(t_parse *parse, t_cmd cmd, char **tab)
{
	int		verif;
	char	*str;

	verif = 1;
	if (!tab[1])
	{
		printf("\n");
		return ;
	}
	while (verif_first_argument(tab[verif]))
		verif++;
	if (!tab[verif])
		return ;
	str = double_tab_to_simple(tab, verif - 1);
	if (verif != 1)
		printf("%s", str);
	else
		printf("%s\n", str);
	free(str);
	change_return_value(parse->cmd, 0, cmd.index_error_redirection);
}
