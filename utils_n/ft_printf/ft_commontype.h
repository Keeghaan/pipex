/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commontype.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:53:50 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/04/27 14:01:52 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMONTYPE_H
# define FT_COMMONTYPE_H

# include "ft_printf.h"

int	ft_putchar_p(char c, int fd);
int	ft_putstr_p(char *s, int fd);
int	ft_strlen_p(char *s);
int	ft_putnbr_p(int n, int fd);

#endif
