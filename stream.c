/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:27:01 by jkong             #+#    #+#             */
/*   Updated: 2022/03/24 13:07:25 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <unistd.h>

int	print(const char *buf, size_t n)
{
	size_t	i;
	ssize_t	result;

	i = 0;
	while (i < n)
	{
		result = write(STDOUT_FILENO, &buf[i], n - i);
		if (result < 0)
			return (-1);
		i += result;
	}
	return (i);
}

static int	print_pad(char c, int width, int current)
{
	char			buf[4 * sizeof(long)];
	const int		count = width - current;
	unsigned long	i;
	int				result;

	result = 0;
	if (count > 0)
	{
		ft_memset(&buf, c, sizeof(buf));
		i = 0;
		while (i < count / sizeof(buf))
		{
			if (!try_inc(&result, print(buf, sizeof(buf))))
				return (-1);
			i++;
		}
		i = 0;
		while (i < count % sizeof(buf))
		{
			if (!try_inc(&result, print(&c, sizeof(c))))
				return (-1);
			i++;
		}
	}
	return (result);
}

int	print_string(t_format_info *info, char *buf, int n)
{
	const int	left = !has_flag(info->flags, MINUS);
	const int	zero = has_flag(info->flags, ZERO);
	int			result;

	result = 0;
	if (info->precision >= 0 && n > info->precision)
		n = info->precision;
	if (left)
	{
		if (!try_inc(&result, print_pad(" 0"[zero], info->width, result + n)))
			return (-1);
	}
	if (!try_inc(&result, print(buf, n)))
		return (-1);
	if (!left)
	{
		if (!try_inc(&result, print_pad(' ', info->width, result)))
			return (-1);
	}
	return (result);
}

static void	init_radix_flag(int *ptr, int radix)
{
	if (radix == 10)
		set_flag(ptr, RADIX_DEC);
	if (radix == 16)
		set_flag(ptr, RADIX_HEX);
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
		if (!try_inc(&result, print_pad(' ', info->width, result + n + m)))
			return (-1);
	if (!try_inc(&result, prepare_integer(info->flags, 0)))
		return (-1);
	if (left && zero)
		if (!try_inc(&result, print_pad('0', info->width, result + n)))
			return (-1);
	n = info->precision;
	if (!try_inc(&result, integer_write(number, n, info->flags, 0)))
		return (-1);
	if (!left)
		if (!try_inc(&result, print_pad(' ', info->width, result)))
			return (-1);
	return (result);
}
