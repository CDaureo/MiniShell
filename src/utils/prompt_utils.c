/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:53:40 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:55:50 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_user_and_host_data(char **user, char *hostname)
{
	struct passwd	*pw;

	*user = NULL;
	pw = getpwuid(getuid());
	if (pw && pw->pw_name)
		*user = pw->pw_name;
	else
		*user = "user";
	if (gethostname(hostname, 256) != 0)
		ft_strcpy(hostname, "minishell");
}

void	set_home_display(char *cwd, char *home,
		char **display_cwd, int *display_malloced)
{
	size_t	home_len;
	size_t	new_len;
	char	*tmp;

	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0 && cwd[home_len] == '/')
	{
		new_len = ft_strlen(cwd) - home_len + 2;
		tmp = malloc(new_len);
		if (tmp)
		{
			tmp[0] = '~';
			ft_strcpy(tmp + 1, cwd + home_len);
			*display_cwd = tmp;
			*display_malloced = 1;
		}
	}
}

void	get_cwd_display(char *cwd, t_ms *ms, char **display_cwd,
		int *display_malloced)
{
	char	*pwd_env;
	char	*home;

	pwd_env = get_env_value(ms->env_list, "PWD");
	home = getenv("HOME");
	*display_cwd = cwd;
	*display_malloced = 0;
	if (pwd_env)
		ft_strlcpy(cwd, pwd_env, 4096);
	else if (!getcwd(cwd, 4096))
		ft_strcpy(cwd, "~");
	if (home && ft_strcmp(cwd, home) == 0)
	{
		*display_cwd = "~";
		*display_malloced = 0;
	}
	else if (home)
		set_home_display(cwd, home, display_cwd, display_malloced);
}

char	*build_prompt(char *user, char *hostname, char *display_cwd)
{
	size_t	prompt_len;
	char	*prompt;

	prompt_len = ft_strlen(user) + 1 + ft_strlen(hostname) + 1
		+ ft_strlen(display_cwd) + 3;
	prompt = malloc(prompt_len);
	if (!prompt)
		return (ft_strdup("$ "));
	snprintf(prompt, prompt_len, "%s@%s:%s$ ", user, hostname, display_cwd);
	return (prompt);
}
