/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:27:01 by jkong             #+#    #+#             */
/*   Updated: 2022/03/16 21:57:36 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <unistd.h>

int	print(const char *buf, size_t n)
{
	return (write(STDOUT_FILENO, buf, n));
}

static int	print_pad(char c, int count)
{
	char		buf[sizeof(long)];
	const int	div = count / sizeof(buf);
	const int	mod = count % sizeof(buf);
	int			i;
	int			result;

	result = 0;
	if (count > 0)
	{
		ft_memset(&buf, c, sizeof(buf));
		i = 0;
		while (i < div)
		{
			result += print(buf, sizeof(buf));
			i++;
		}
		i = 0;
		while (i < mod)
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
		result += print_pad(' ', info->width - (result + n));
	result += print(buf, n);
	if (!left)
		result += print_pad(' ', info->width - result);
	return (result);
}

int	print_integer(t_format_info *info, long number, int radix)
{
	const int	left = !has_flag(info->flags, MINUS);
	const int	zero = has_flag(info->flags, ZERO) && info->precision < 0;
	const int	n = integer_write(number, info->flags, radix, 1);
	int			count;
	int			result;

	result = prepare_integer(info->flags, radix, 1);
	if (left && !zero)
		result = print_pad(' ', info->width - (result + n));
	result = prepare_integer(info->flags, radix, 0);
	count = 0;
	if (left && zero)
		count = info->width - (result + n);
	if (info->precision >= 0 && n < info->precision)
		count = info->precision - n;
	if (count > 0)
		result += print_pad('0', count);
	result += integer_write(number, info->flags, radix, 0);
	if (!left)
		result += print_pad(' ', info->width - result);
	return (result);
}
