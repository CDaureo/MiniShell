/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/02 17:07:22 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

/* ************************************************************************** */
/*                                 DEFINES                                   */
/* ************************************************************************** */
# define E_FAILURE 1
# define E_SUCCESS 0
# define PATH_MAX 4096

/* ************************************************************************** */
/*                                ENUMS                                      */
/* ************************************************************************** */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_APPEND,
	TOKEN_REDIRECT,
	TOKEN_INPUT,
	TOKEN_HEREDOC
}	t_token_type;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_tokens;

/* ************************************************************************** */
/*                              STRUCTURES                                   */
/* ************************************************************************** */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct t_ms
{
	t_env	*env_list;
	char	*input;
	char	*prompt;
	char	*history;

	char	*cmd;
	char	**envp;
	char	**cmd_paths;
	char	**cmd_args;

	int		exit_status;
	int		fd[2];
	int		pid;
}	t_ms;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_ms *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_token					*redirections;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

/* ************************************************************************** */
/*                             SHELL CORE                                    */
/* ************************************************************************** */
void	minishell_init(t_ms *ms);
char	*find_executable(char *cmd, char **paths);
void	error_msg(const char *msg);
void	free_simple_cmds(t_simple_cmds *cmds);
void	setup_signals(void);
/* ************************************************************************** */
/*                          BUILTIN FUNCTIONS                                */
/* ************************************************************************** */
int		handle_builds(char **argv, t_ms *ms);
int		ft_cd(char **args, t_ms *ms);
int		ft_pwd(t_ms *ms);
int		ft_env(t_ms *ms);
int		ft_echo(char **argv);
int		ft_export(char **argv, t_ms *ms);
int		ft_unset(char **argv, t_ms *ms);

/* ************************************************************************** */
/*                          ENVIRONMENT FUNCTIONS                            */
/* ************************************************************************** */
char	**copy_envp(char **envp);
void	update_env_var(t_env *env, const char *key, const char *value);
char	*get_env_value(t_env *env, const char *key);
t_env	*init_env_list(char **envp);

/* ************************************************************************** */
/*                          TOKENIZER FUNCTIONS                              */
/* ************************************************************************** */
t_token	*create_token(t_token_type type, const char *value);
void	append_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *tokens);
t_token	*lexer(const char *input);

/* ************************************************************************** */
/*                          TOKEN HANDLER FUNCTIONS                          */
/* ************************************************************************** */
void	handle_append(t_token **tokens, int type, \
			const char *value, int *i, int increment);
void	handle_pipes(int *i, t_token **tokens);
void	handle_redirections(const char *input, int *i, t_token **tokens);
void	handle_words(const char *input, int *i, t_token **tokens);

/* ************************************************************************** */
/*                            PARSER FUNCTIONS                               */
/* ************************************************************************** */
void	command_types(t_token **tokens, t_simple_cmds **cmds, \
			t_simple_cmds **current_cmd, t_token **current_token, t_ms *ms);
void	parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds, t_ms *ms);
char	**tokens_to_str(t_token *tokens);

/* ************************************************************************** */
/*                            PIPELINE FUNCTIONS                             */
/* ************************************************************************** */
void	pipex(t_ms *ms);
void	execute_pipeline(t_simple_cmds *cmds, char **envp, t_ms *ms);
char	*get_cmd_path(char *cmd, char **envp);
void	free_pathstr(char **arr);
void	apply_redirections(t_simple_cmds *cmd, t_ms *ms);

/* ************************************************************************** */
/*                         LIBFT-STYLE FUNCTIONS                             */
/* ************************************************************************** */
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

#endif
