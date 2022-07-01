/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:44:17 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/04/27 14:10:53 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nbase_len(unsigned long long n, char *base)
{
	unsigned long long	i;

	i = 0;
	while (n != 0)
	{
		n /= ft_strlen_p(base);
		i++;
	}
	return (i);
}

int	ft_putnbr_base(unsigned int n, char *base)
{
	if (!(check_base(base)))
	{
		ft_putstr_p("(null)", FD);
		return (6);
	}
	if (n < 1)
	{
		ft_putchar_p('0', FD);
		return (1);
	}
	if (n == 0)
	{
		ft_putchar_p('0', FD);
		return (1);
	}
	if (n / ft_strlen_p(base) > 0)
		ft_putnbr_base(n / ft_strlen_p(base), base);
	ft_putchar_p(base[n % ft_strlen_p(base)], FD);
	return (nbase_len(n, base));
}

int	ft_putptr(unsigned long long address, char *base)
{
	if (!(check_base(base)))
	{
		ft_putchar_p('0', FD);
		return (3);
	}
	if (address == 0)
	{
		ft_putchar_p('0', FD);
		return (3);
	}
	if (address < 1)
		address *= -1;
	if (address / ft_strlen_p(base) > 0)
		ft_putptr(address / ft_strlen_p(base), base);
	ft_putchar_p(base[address % ft_strlen_p(base)], FD);
	return (nbase_len(address, base) + 2);
}

int	ft_putunsigned(unsigned long n, char *base)
{
	if (!(check_base(base)))
	{
		ft_putstr_p("(null)", FD);
		return (ft_strlen_p("(null)"));
	}
	if (n == 0)
	{
		ft_putchar_p('0', FD);
		return (1);
	}
	if (n / ft_strlen_p(base) > 0)
		ft_putunsigned(n / ft_strlen_p(base), base);
	ft_putchar_p(base[n % ft_strlen_p(base)], FD);
	return (unsigned_size(n));
}
