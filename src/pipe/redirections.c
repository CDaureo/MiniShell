/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   redirections.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/12 16:20:04 by cdaureo-		  #+#	#+#			 */
/*   Updated: 2025/07/04 17:28:26 by cdaureo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_outfile_trunc(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_outfile_append(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_infile(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	apply_redirections(t_simple_cmds *cmd, t_ms *ms)
{
	int	ret;

	while (cmd->redirections)
	{
		if (cmd->redirections->type == TOKEN_REDIRECT)
		{
			ret = open_outfile_trunc(cmd->redirections->value, ms);
			if (ret < 0)
				return ;
		}
		else if (cmd->redirections->type == TOKEN_APPEND)
		{
			ret = open_outfile_append(cmd->redirections->value, ms);
			if (ret < 0)
				return ;
		}
		else if (cmd->redirections->type == TOKEN_INPUT
			|| cmd->redirections->type == TOKEN_HEREDOC)
		{
			ret = open_infile(cmd->redirections->value, ms);
			if (ret < 0)
				return ;
		}
		cmd->redirections = cmd->redirections->next;
	}
}
