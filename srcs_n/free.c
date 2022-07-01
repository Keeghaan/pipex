/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:47:46 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 15:52:27 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_file(char **buf)
{
	int	i;

	i = 0;
	if (!buf[i])
		return ;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
	buf = NULL;
}

void	close_parent(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	close_files(t_cmd *cmd)
{
	if (cmd->in > -1)
		close(cmd->in);
	if (cmd->out > -1)
		close(cmd->out);
	return (0);
}

int	close_fd(t_cmd *cmd)
{
	if (cmd->fd[0] > -1)
		close(cmd->fd[0]);
	if (cmd->fd[1] > -1)
		close(cmd->fd[1]);
	return (0);
}

void	free_process(t_cmd *cmd)
{
	if (cmd->fd[0] > -1 || cmd->fd[1] > -1)
		close_fd(cmd);
	if (cmd->in > -1 || cmd->out > -1)
		close_files(cmd);
	close_parent();
}
