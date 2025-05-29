/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/05/29 19:15:41 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#endif
typedef struct t_minishell
{
	char *input;
	char *prompt;
	char *history;	
	char *cmd;
	char **envp;
	char **cmd_paths;
	char **cmd_args;
	int exit_status;
	int fd[2];
	int pid;
} t_minishell;
