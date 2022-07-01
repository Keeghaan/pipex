/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:56:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/04/27 14:02:25 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_commontype.h"
#include "ft_bases_utils.h"

int	get_type(char flag, va_list arg)
{
	int					size;

	size = 0;
	if (flag == 'c')
		size += ft_putchar_p((char)va_arg(arg, int), FD);
	else if (flag == 's')
		size += ft_putstr_p(va_arg(arg, char *), FD);
	else if (flag == 'd' || flag == 'i')
		size += ft_putnbr_p(va_arg(arg, int), FD);
	else if (flag == 'u')
		size += ft_putunsigned(va_arg(arg, unsigned int), "0123456789");
	if (flag == 'x')
		size += ft_putnbr_base(va_arg(arg, unsigned long), HEX);
	else if (flag == 'X')
		size += ft_putnbr_base(va_arg(arg, unsigned long), HEXX);
	else if (flag == 'p')
	{
		ft_putstr_p("0x", FD);
		size += ft_putptr(va_arg(arg, unsigned long long), HEX);
	}
	else if (flag == '%')
		size += ft_putchar_p('%', FD);
	return (size);
}

int	get_blank(const char *format)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == ' ')
			count++;
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		size;

	size = 0;
	if (!format)
		return (0);
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			size += get_type(*format, arg);
		}
		else
		{
			ft_putchar_p(*format, FD);
			size++;
		}
		format++;
	}
	size += get_blank(format);
	va_end(arg);
	return (size);
}
