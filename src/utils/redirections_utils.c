/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:17:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 17:20:07 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

int	open_outfile_trunc(char *filename, t_ms *ms)
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

int	open_outfile_append(char *filename, t_ms *ms)
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

int	open_infile(char *filename, t_ms *ms)
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
