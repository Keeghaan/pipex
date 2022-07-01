/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bases_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:59:26 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/04/27 14:11:24 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bases_utils.h"

int	check_double(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_base(char *base)
{
	int	i;
	int	size_base;

	i = 0;
	size_base = ft_strlen_p(base);
	if (base[i] == 0)
		return (0);
	if (size_base < 2)
		return (0);
	while (base[i])
	{
		if (base[i] < 48 || base[i] > 122)
			return (0);
		i++;
	}
	if (check_double(base))
		return (0);
	return (1);
}

int	unsigned_size(long int n)
{
	int	count;

	count = 0;
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	if (n < 10)
		count++;
	return (count);
}
