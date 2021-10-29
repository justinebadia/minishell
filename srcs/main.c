/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/29 16:49:56 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct variabl globale
t_msh	g_msh;

void	loop(void)
{
	char	*line;
	char** temp_parsing;
	line = NULL;
	
	while (true)
	{
		if (line != NULL)
			free(line);
		line = readline("\001\e[1;96m\002minishell 1.0$ \001\033[0m\002");
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (*line)
			add_history(line);
		/* ms_parsing(line); */
		temp_parsing = ft_split(line, ' ');
		if (ms_builtins(temp_parsing) == 1)
		{
			g_msh.switch_signal = 1;
			ms_exec(temp_parsing);
			g_msh.switch_signal = 0;
		}
		ft_free_tab(temp_parsing);
	}
	free(line);
}

void	ctrl_c(int var)
{
	(void) var;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_msh.switch_signal == 0)
		rl_redisplay();
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*token;

	(void)argc;
	(void)argv;
	init_shell();
	token = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	loop();
	ft_free_tab(g_msh.env);
	ft_free_tab(g_msh.env_export);
}
