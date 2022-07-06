/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:46:07 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/06 13:03:49 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child_process_one(t_cmd *cmd, char **av)
{
	if (dup2(cmd->fd[1], STDOUT_FILENO) < 0)
		return (close_fd(cmd), 1);
	close_fd(cmd);
	if (dup2(cmd->in, STDIN_FILENO) < 0)
		return (close_files(cmd), 2);
	close_files(cmd);
	if (ft_strlen(av[2]) < 1)
		return (close_parent(), 3);
	cmd->cmd = ft_split(av[2], ' ');
	if (!cmd->cmd)
		return (free_process(cmd), 2);
	cmd->path = get_path(cmd->cmd[0], cmd, 0, 5);
	if (!cmd->path)
		return (free_file(cmd->cmd), free_process(cmd), 3);
	execve(cmd->path, cmd->cmd, cmd->env);
	return (free(cmd->path), free_file(cmd->cmd), free_process(cmd), 4);
}

int	open_out(t_cmd *cmd, char **av)
{
	cmd->out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->out == -1)
	{
		ft_printf("%s: %s: %s\n", SH, av[4], strerror(errno));
		return (1);
	}
	return (0);
}

int	child_process_two(t_cmd *cmd, char **av)
{
	if (dup2(cmd->fd[0], STDIN_FILENO) < 0)
		return (close_fd(cmd), 1);
	close_fd(cmd);
	if (dup2(cmd->out, STDOUT_FILENO) < 0)
		return (close_files(cmd), 2);
	close_files(cmd);
	if (ft_strlen(av[3]) < 1)
		return (close_parent(), 3);
	cmd->cmd = ft_split(av[3], ' ');
	if (!cmd->cmd)
		return (free_process(cmd), 2);
	cmd->path = get_path(cmd->cmd[0], cmd, 0, 5);
	if (!cmd->path)
		return (free_file(cmd->cmd), free_process(cmd), 3);
	execve(cmd->path, cmd->cmd, cmd->env);
	return (free(cmd->path), free_file(cmd->cmd), free_process(cmd), 4);
}
