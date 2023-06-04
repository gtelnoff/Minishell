/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:22:37 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 18:58:18 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_status;
void	set_signal(void);
char	**delete_null_byte(char **array);
void	catch_signal_main(int sig);
void	exit_ctrl_d(t_parse *parse);
void	minishell_exe(t_parse *parse);
void	define_pipe(t_parse *parse);

int	main(int ac, char **av, char **env)
{
	t_parse	parse;

	(void)ac;
	(void)av;
	parse.env = env;
	g_return_status = 0;
	malloc_envp(env, &parse);
	while (1)
	{
		set_signal();
		init_struct_value(&parse);
		parse.line = readline("🔥👹\033[1;31m Minihell \033[0m👹🔥➜ ");
		if (!parse.line)
			exit_ctrl_d(&parse);
		if (parse.line[0] != '\0')
		{
			add_history(parse.line);
			minishell_exe(&parse);
		}
	}
	return (0);
}
