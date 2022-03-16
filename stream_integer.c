/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:53:02 by jkong             #+#    #+#             */
/*   Updated: 2022/03/16 22:04:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_auto(const char *str, int len, int fake)
{
	if (!str)
		return (0);
	if (len < 0)
		len = ft_strlen(str);
	if (fake)
		return (len);
	return (print(str, len));
}

static const char	*get_prefix(int flags, int radix)
{
	if (radix == 16)
	{
		if (has_flag(flags, AFTER_UPPER))
			return ("0X");
		return ("0x");
	}
	return (NULL);
}

int	prepare_integer(int flags, int radix, int fake)
{
	int			result;

	result = 0;
	if (!has_flag(flags, AFTER_UNSIGNED))
	{
		if (has_flag(flags, AFTER_NEGATIVE))
			result += print_auto("-", -1, fake);
		else if (has_flag(flags, PLUS))
			result += print_auto("+", -1, fake);
		else if (has_flag(flags, SPACE))
			result += print_auto(" ", -1, fake);
	}
	if (has_flag(flags, AFTER_PREFIX))
		result += print_auto(get_prefix(flags, radix), -1, fake);
	return (result);
}

static const char	*get_charset(int flags, int radix)
{
	if (radix == 10)
	{
		return ("0123456789");
	}
	else if (radix == 16)
	{
		if (has_flag(flags, AFTER_UPPER))
			return ("0123456789ABCDEF");
		return ("0123456789abcdef");
	}
	return (NULL);
}

int	integer_write(unsigned long number, int flags, int radix, int fake)
{
	const char *const	charset = get_charset(flags, radix);
	int					result;

	if (!number)
		return (print_auto(&charset[0], 1, fake));
	result = 0;
	if (number >= (unsigned long)radix)
		result += integer_write(number / radix, flags, radix, fake);
	result += print_auto(&charset[number % radix], 1, fake);
	return (result);
}
