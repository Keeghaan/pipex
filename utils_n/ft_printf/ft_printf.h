/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:59:29 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/26 06:43:52 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_commontype.h"
# include "ft_bases_utils.h"

# ifndef FD
#  define FD 1
# endif

# define HEXX "0123456789ABCDEF"
# define HEX "0123456789abcdef"

int				ft_printf(const char *format, ...);
int				ft_putunsigned(unsigned long n, char *base);
int				ft_putptr(unsigned long long addr, char *base);
int				ft_putnbr_base(unsigned int n, char *base);
#endif
