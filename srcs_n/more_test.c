/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:29:08 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 17:27:46 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	r_ok(char *file)
{
	if (access(file, R_OK) != 0)
		return (0);
	return (1);
}

int	w_ok(char *file)
{
	if (access(file, W_OK) != 0)
		return (0);
	return (2);
}

int	x_ok(char *file)
{
	if (access(file, X_OK) != 0)
		return (0);
	return (3);

}

int	file_ok(char **av)
{
		if (!r_ok(av[1]) && !w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[4], strerror(13));
			ft_printf("%s: %s: %s\n", SH, av[1], strerror(13));
			return (3);
		}
		if (!r_ok(av[1]) && w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[1], strerror(13));
			return (1);
		}
		if (r_ok(av[1]) && !w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[4], strerror(13));
			return (2);
		}

	return (0);	
}
/*
int	file_ok_outfile(char **av)
{
	if (access(av[4], F_OK) == 0)
	{
		if (!r_ok(av[1]) && !w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[4], strerror(13));
			ft_printf("%s: %s: %s\n", SH, av[1], strerror(13));
			return (3);
		}
		if (!r_ok(av[1]) && w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[1], strerror(13));
			return (1);
		}
		if (r_ok(av[1]) && !w_ok(av[4]))
		{
			ft_printf("%s: %s: %s\n", SH, av[4], strerror(13));
			return (2);
		}
	}
	return (0);	
}a*/
