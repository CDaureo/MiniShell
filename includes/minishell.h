/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:51:17 by cdaureo-         ###   ########.fr       */
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
#include <sys/types.h>
#endif

#define E_FAILURE 1
#define E_SUCCESS 0
typedef struct t_ms
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
} t_ms;

void minishell_init(t_ms *ms);
char *find_executable(char *cmd, char **paths);
/* ************************************************************************** */
/* ************************LIBRARY FUNCTIONS********************************* */
/* ************************************************************************** */
char *ft_strdup(const char *s);
int ft_strlen(const char *str);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strchr(const char *s, int c);
