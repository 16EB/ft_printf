/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:27:01 by jkong             #+#    #+#             */
/*   Updated: 2022/03/17 14:37:45 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <unistd.h>

int	print(const char *buf, size_t n)
{
	return (write(STDOUT_FILENO, buf, n));
}

static int	print_pad(char c, int width, int current)
{
	char		buf[sizeof(long)];
	const int	count = width - current;
	int			i;
	int			result;

	result = 0;
	if (count > 0)
	{
		ft_memset(&buf, c, sizeof(buf));
		i = 0;
		while (i < count / sizeof(buf))
		{
			result += print(buf, sizeof(buf));
			i++;
		}
		i = 0;
		while (i < count % sizeof(buf))
		{
			result += print(&c, sizeof(c));
			i++;
		}
	}
	return (result);
}

int	print_string(t_format_info *info, char *buf, int n)
{
	const int	left = !has_flag(info->flags, MINUS);
	int			result;

	result = 0;
	if (info->precision >= 0 && n > info->precision)
		n = info->precision;
	if (left)
		result += print_pad(' ', info->width, result + n);
	result += print(buf, n);
	if (!left)
		result += print_pad(' ', info->width, result);
	return (result);
}

static void	init_radix_flag(int *ptr, int radix)
{
	if (radix == 10)
		set_flag(ptr, RADIX_DEC);
	else
		reset_flag(ptr, RADIX_DEC);
	if (radix == 16)
		set_flag(ptr, RADIX_HEX);
	else
		reset_flag(ptr, RADIX_HEX);
}

int	print_integer(t_format_info *info, long number, int radix)
{
	const int	left = !has_flag(info->flags, MINUS);
	const int	zero = has_flag(info->flags, ZERO) && info->precision < 0;
	int			n;
	int			m;
	int			result;

	init_radix_flag(&info->flags, radix);
	result = 0;
	m = prepare_integer(info->flags, 1);
	n = integer_write(number, info->precision, info->flags, 1);
	if (left && !zero)
		result += print_pad(' ', info->width, result + n + m);
	result += prepare_integer(info->flags, 0);
	if (left && zero)
		result += print_pad('0', info->width, result + n);
	result += integer_write(number, info->precision, info->flags, 0);
	if (!left)
		result += print_pad(' ', info->width, result);
	return (result);
}
