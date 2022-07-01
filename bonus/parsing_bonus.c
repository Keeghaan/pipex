/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:28:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 11:27:07 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_env(char **envp)
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
	if (!found)
		return (NULL);
	envp = ft_split(envp[i], ':');
	if (!envp)
		return (NULL);
	return (envp);
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

char	*get_path(char	*cmd, char **en, int msg, int n)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	if (!ft_strncmp(cmd, "df", ft_strlen(cmd)))
	{
		if (msg)
			ft_printf("%s: %s: %s\n", cmd, DF, strerror(1));
		return (NULL);
	}
	while (en[i])
	{
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
