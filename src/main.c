/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:51:33 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:51:52 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_prompt_and_line(t_ms *ms, char **line)
{
	t_prompt_data	data;

	data.user = NULL;
	data.display_cwd = NULL;
	get_user_and_host_data(&data.user, data.hostname);
	get_cwd_display(data.cwd, ms, &data.display_cwd, &data.display_malloced);
	data.prompt = build_prompt(data.user, data.hostname, data.display_cwd);
	*line = readline(data.prompt);
	free(data.prompt);
	if (data.display_malloced)
		free(data.display_cwd);
}

static void	process_cmd_line(char *line, t_ms *ms)
{
	t_token			*tokens;
	t_simple_cmds	*cmds;

	tokens = NULL;
	cmds = NULL;
	if (*line)
	{
		add_history(line);
		tokens = lexer(line);
		if (tokens)
		{
			parse_simple_cmds(&tokens, &cmds, ms);
			execute_cmds(cmds, ms, line);
			free_simple_cmds(cmds);
		}
	}
}

static void	main_loop(t_ms *ms)
{
	char	*line;

	line = NULL;
	while (1)
	{
		get_prompt_and_line(ms, &line);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		process_cmd_line(line, ms);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	ms.exit_status = 0;
	ms.envp = copy_envp(envp);
	ms.env_list = init_env_list(envp);
	setup_signals();
	main_loop(&ms);
	return (0);
}
