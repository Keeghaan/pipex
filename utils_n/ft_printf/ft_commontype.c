/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commontype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:51:58 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/04/27 14:01:35 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_commontype.h"

int	ft_putstr_p(char *s, int fd)
{
	if (!s)
	{
		ft_putstr_p("(null)", FD);
		return (ft_strlen_p("(null)"));
	}
	write(fd, s, ft_strlen_p(s));
	return (ft_strlen_p(s));
}

int	ft_putchar_p(char c, int fd)
{
	write(fd, &c, sizeof(c));
	return (1);
}

int	ft_strlen_p(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	int_size(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	if (n < 10)
		count++;
	return (count);
}

int	ft_putnbr_p(int nb, int fd)
{
	int			len;
	long int	n;

	len = 0;
	n = (long int)nb;
	if (n < 0)
	{
		n = n * -1;
		ft_putchar_p('-', fd);
		len++;
	}
	if (n < 10)
	{
		ft_putchar_p(n + '0', fd);
		return (len + 1);
	}
	ft_putnbr_p(n / 10, fd);
	ft_putchar_p((n % 10) + '0', fd);
	len += int_size(n);
	return (len);
}
