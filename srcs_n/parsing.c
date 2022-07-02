/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:26:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 16:16:31 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_env(t_cmd *cmd, char **envp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (!envp[i])
		return (1);
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

static int	check_digit(char *cmd)
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

static int	ft_more_test(char **en, char *cmd, int msg)
{
	if (!en[0])
		return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(2)), 1);
	if (!ft_strncmp(cmd, "df", ft_strlen(cmd)))
	{
		if (msg)
			ft_printf("%s: %s: %s\n", cmd, DF, strerror(1));
		return (2);
	}
	return (0);
}

char	*get_path(char *cmd, char **en, int msg, int n)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	if (ft_more_test(en, cmd, msg))
		return (NULL);
	while (en[i])
	{
		if (!check_path_cmd(cmd, 0))
			return (cmd);
		tmp = ft_strjoin(en[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
	i++;
	}
	if (en[i])
		msg_error(msg, n, cmd);
	return (NULL);
}
