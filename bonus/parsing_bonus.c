/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:28:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/04 13:21:43 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_env(t_cmd *cmd, char **envp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
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

int	check_digit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	msg_error(int msg, int n, char *cmd)
{
	int	digit;

	digit = check_digit(cmd);
	if (msg && n > 1)
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
		if (access(cmd, 0) == 0)
			return (0);
		return (1);
	}
	return (2);
}

char	*get_path(char	*cmd, char **en, int msg, int n)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	if (more_test(cmd, msg))
		return (NULL);
	while (en[i])
	{
		if (!check_path_cmd2(cmd))
			return (cmd);
		if (check_path_cmd2(cmd) == 1)
			break ;
		tmp = ft_strjoin(en[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	msg_error(msg, n, cmd);
	return (NULL);
}
