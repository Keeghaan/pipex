/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:33:40 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 11:30:01 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_dup2(int n, t_cmd *cmd)
{
	if (n == 0)
	{
		if ((dup2(cmd->in, STDIN_FILENO) < 0)
			|| (dup2(cmd->fd[n][1], STDOUT_FILENO) < 0))
			return (ft_printf("%s\n", strerror(errno))
				, close_pipes(cmd), 1);
	}	
	else if (n == cmd->no - 1)
	{
		if (cmd->in)
			close(cmd->in);
		if ((dup2(cmd->fd[n - 1][0], STDIN_FILENO) < 0)
			|| (dup2(cmd->out, STDOUT_FILENO) < 0))
			return (ft_printf("%s\n", strerror(errno))
				, close_pipes(cmd), 2);
	}
	else
	{
		if ((dup2(cmd->fd[n - 1][0], STDIN_FILENO) < 0)
			|| (dup2(cmd->fd[n][1], STDOUT_FILENO) < 0))
			return (ft_printf("%s\n", strerror(errno))
				, close_pipes(cmd), 3);
	}
	return (0);
}

static int	ft_process(char **av, t_cmd *cmd, int n)
{
	cmd->cmd = ft_split(av[2 + cmd->here_doc + n], ' ');
	if (!cmd->cmd)
	{
		close_pipes(cmd);
		close_files(cmd);
		if (cmd->here_doc)
			unlink(".here_doc");
		return (1);
	}
	cmd->path = get_path(cmd->cmd[0], cmd->env, 0, 5);
	if (!cmd->path)
	{
		free_file(cmd->cmd);
		close_files(cmd);
		close_pipes(cmd);
		if (cmd->here_doc)
			unlink(".here_doc");
		return (2);
	}
	return (0);
}

int	child_process(int n, char **av, char **en, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	else if (cmd->pid == 0)
	{
		if (ft_process(av, cmd, n))
			return (1);
		if (ft_dup2(n, cmd))
			return (close_pipes(cmd), close_files(cmd)
				, free(cmd->path), free_file(cmd->cmd), 2);
		close_pipes(cmd);
		close_files(cmd);
		execve(cmd->path, cmd->cmd, en);
		close_pipes(cmd);
		free_process(cmd);
		return (3);
	}
	return (0);
}
