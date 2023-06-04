/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:19:27 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/11 21:19:28 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_str(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	get_nb_of_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].fd.fd_in != -50)
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int index)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
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
	if (index > 1)
		free(s1);
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
	{
		printf("(null)\n");
		return ;
	}
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
