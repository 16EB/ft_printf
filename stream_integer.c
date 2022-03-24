/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:53:02 by jkong             #+#    #+#             */
/*   Updated: 2022/03/24 13:08:56 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_auto(const char *str, int len, int fake)
{
	if (len < 0)
		len = ft_strlen(str);
	if (fake)
		return (len);
	return (print(str, len));
}

static const char	*get_prefix(int flags)
{
	if (has_flag(flags, RADIX_HEX))
	{
		if (has_flag(flags, AFTER_UPPER))
			return ("0X");
		return ("0x");
	}
	return (NULL);
}

int	prepare_integer(int flags, int fake)
{
	int			result;
	const char	*str;

	result = 0;
	if (!has_flag(flags, AFTER_UNSIGNED))
	{
		str = NULL;
		if (has_flag(flags, AFTER_NEGATIVE))
			str = "-";
		else if (has_flag(flags, PLUS))
			str = "+";
		else if (has_flag(flags, SPACE))
			str = " ";
		if (str && !try_inc(&result, print_auto(str, -1, fake)))
			return (-1);
	}
	if (has_flag(flags, AFTER_PREFIX))
	{
		str = get_prefix(flags);
		if (str && !try_inc(&result, print_auto(str, -1, fake)))
			return (-1);
	}
	return (result);
}

static const char	*get_charset(int flags)
{
	if (has_flag(flags, RADIX_DEC))
	{
		return ("0123456789");
	}
	else if (has_flag(flags, RADIX_HEX))
	{
		if (has_flag(flags, AFTER_UPPER))
			return ("0123456789ABCDEF");
		return ("0123456789abcdef");
	}
	return (NULL);
}

int	integer_write(unsigned long number, int n, int flags, int fake)
{
	const char *const	charset = get_charset(flags);
	const int			radix = ft_strlen(charset);
	int					m;
	int					result;

	result = 0;
	if (number != 0 || n != 0)
	{
		if (number >= (unsigned long)radix || n > 0)
		{
			m = integer_write(number / radix, n - (n > 0), flags, fake);
			if (!try_inc(&result, m))
				return (-1);
		}
		m = print_auto(&charset[number % radix], 1, fake);
		if (!try_inc(&result, m))
			return (-1);
	}
	return (result);
}
