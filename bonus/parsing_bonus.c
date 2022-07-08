/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:28:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/08 13:15:13 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_env(t_cmd *cmd, char **envp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (!envp[0])
		cmd->env_i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp[i] = ft_strchr(envp[i], '/');
			found = 1;
			break ;
		}
		i++;
	}
	if (path_not_found(found, cmd))
		return (0);
	cmd->env = ft_split(envp[i], ':');
	if (!cmd->env)
		return (3);
	return (0);
}

int	check_cmd(int n, char *av, t_cmd *cmd)
{
	if (ft_strlen(av) > 0)
	{
		cmd->cmd = ft_split(av, ' ');
		if (!cmd->cmd)
			return (2);
		if (n == 1)
			cmd->path = get_path(cmd->cmd[0], cmd, 0, n);
		else
			cmd->path = get_path(cmd->cmd[0], cmd, 1, n);
		if (!cmd->path)
			return (free_file(cmd->cmd), 4);
		free(cmd->path);
		free_file(cmd->cmd);
		return (0);
	}
	return (0);
}

static int	check_path_cmd2(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (0);
		return (1);
	}
	return (2);
}

char	*ret_path(int i, char *cmd, char **en)
{
	char	*tmp;
	char	*cmd_path;

	cmd_path = NULL;
	tmp = NULL;
	if (!check_path_cmd2(cmd))
		cmd_path = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin(en[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*get_path(char	*cmd, t_cmd *command, int msg, int n)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (more_test(command, cmd, msg, n))
		return (NULL);
	while (command->env[i])
	{
		ret = ret_path(i, cmd, command->env);
		if (ret != NULL)
			return (ret);
		i++;
	}
	if (command->env[0])
	{
		if (msg && n > 1 && !ft_strchr(cmd, '/'))
			ft_printf("%s: command not found\n", cmd);
	}
	return (ret);
}
