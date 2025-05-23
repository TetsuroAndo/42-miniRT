/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:28:51 by teando            #+#    #+#             */
/*   Updated: 2024/11/10 11:08:55 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_stdio.h"
# include "ft_string.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
int	dprintf_format_string(int fd, const char *format, va_list ap);
int	type_putbase(int fd, long long nbr, char *base);
int	type_putchar(int fd, int c);
int	type_putptr(int fd, uintptr_t nbr, char *base);
int	type_putstr(int fd, char *str);

#endif