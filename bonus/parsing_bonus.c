/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:28:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/06 14:02:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_env(t_cmd *cmd, char **envp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (!envp[1])
		cmd->env_i = 1;
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

static void	msg_error(int msg, int n, char *cmd)
{
	int	digit;

	digit = check_digit(cmd);
	if (msg && n > 1 && !ft_strchr(cmd, '/'))
	{
		if (!digit)
			ft_printf("Command '%s' not found\n", cmd);
		else
			ft_printf("%s: command not found\n", cmd);
	}
}

static int	check_path_cmd2(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
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
	if (access(cmd_path, F_OK | X_OK) == 0)
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
	if (more_test(command->env, cmd, msg, command->env_i))
		return (NULL);
	while (command->env[i])
	{
		ret = ret_path(i, cmd, command->env);
		if (ret != NULL)
			return (ret);
		i++;
	}
	if (command->env[0])
		msg_error(msg, n, cmd);
	return (ret);
}
