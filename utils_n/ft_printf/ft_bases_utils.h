/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bases_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:01:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/26 06:10:44 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASES_UTILS_H
# define FT_BASES_UTILS_H

# include "ft_printf.h"

int	check_double(char *str);
int	check_base(char *base);
int	unsigned_size(long int n);
int	hex_len(unsigned long long n);

#endif
