/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:26:57 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/05 15:36:37 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	close_fileno(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (1);
}

void	close_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->no - 1)
	{
		close(cmd->fd[i][0]);
		close(cmd->fd[i][1]);
		i++;
	}
}

int	free_file(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		free(file[i]);
		i++;
	}
	free(file);
	file = NULL;
	return (2);
}

int	free_parent(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->no - 1)
		free(cmd->fd[i++]);
	free(cmd->fd);
	if (cmd->env[0])
		free_file(cmd->env);
	if (cmd->here_doc)
		unlink(".here_doc");
	close_files(cmd);
	close_fileno();
	return (3);
}

int	free_process(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->here_doc)
		unlink(".here_doc");
	if (cmd->cmd)
		free_file(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	while (i < cmd->no - 1)
		free(cmd->fd[i++]);
	free(cmd->fd);
	if (cmd->env[0])
		free_file(cmd->env);
	close_files(cmd);
	close_fileno();
	return (4);
}
