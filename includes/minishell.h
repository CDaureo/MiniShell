/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:46 by cdaureo-         ###   ########.fr       */
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
#include <sys/wait.h>
#include "libft.h"
#endif

#define E_FAILURE 1
#define E_SUCCESS 0

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_APPEND,
    TOKEN_REDIRECT
} t_token_type;	

typedef enum s_tokens
{
    PIPE = 1,
    GREAT,
    GREAT_GREAT,
    LESS,
    LESS_LESS,
} t_tokens;

typedef struct s_token
{
    t_token_type type;
    t_tokens specific;
    char *value;
	struct s_token *next;
} t_token;

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
void error_msg(const char *msg);
/* ************************************************************************** */
/* ************************LIBRARY FUNCTIONS********************************* */
/* ************************************************************************** */
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
/* ************************************************************************** */
/* **************************TOKEN FUNCTIONS********************************* */
/* ************************************************************************** */
t_token	*create_token(t_token_type type, t_tokens specific, const char *value);
void	append_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *tokens);
t_token	*lexer(const char *input);
/* ************************************************************************** */
/* ***************************HANDLER FUNCTIONS****************************** */
/* ************************************************************************** */
void	handle_append(t_token **tokens, int type, int subtype, \
	const char *value, int *i, int increment);
void	handle_pipes(int *i, t_token **tokens);
void	handle_redirections(const char *input, int *i, t_token **tokens);
void	handle_words(const char *input, int *i, t_token **tokens);
/* ************************************************************************** */
/* ***************************PIPE FUNCTIONS********************************* */
/* ************************************************************************** */
void	pipex(t_ms *ms);
void	free_pathstr(char **arr);
char *get_cmd_path(char *cmd, char **envp);
void execute_pipeline(t_token *tokens, char **envp);
