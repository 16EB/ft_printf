/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:01:47 by jkong             #+#    #+#             */
/*   Updated: 2022/03/17 12:05:42 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdarg.h>

static int	write_general_string(const char **pfmt)
{
	const char *const	format = *pfmt;
	int					i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	if (i == 0)
		return (0);
	*pfmt += i;
	return (print(format, i));
}

/*
** 
**	if (has_flag(info->flags, PLUS))
**		reset_flag(&info->flags, SPACE);
**	if (has_flag(info->flags, MINUS))
**		reset_flag(&info->flags, ZERO);
*/
static int	write_formatted_value(t_format_info *info)
{
	if (info->type == 'c')
		return (print_string(info, &info->value.c, sizeof(info->value.c)));
	else if (info->type == 's')
		return (print_string(info, info->value.s, ft_strlen(info->value.s)));
	else if (info->type == 'p' || info->type == 'x' || info->type == 'X')
	{
		if (info->type == 'p' || has_flag(info->flags, HASH))
			set_flag(&info->flags, AFTER_PREFIX);
		if (info->type == 'X')
			set_flag(&info->flags, AFTER_UPPER);
		set_flag(&info->flags, AFTER_UNSIGNED);
		return (print_integer(info, info->value.l, 16));
	}
	else if (info->type == 'd' || info->type == 'i' || info->type == 'u')
	{
		if (info->type == 'u')
			set_flag(&info->flags, AFTER_UNSIGNED);
		else if (info->value.n < 0)
		{
			set_flag(&info->flags, AFTER_NEGATIVE);
			info->value.n = -info->value.n;
		}
		return (print_integer(info, info->value.l, 10));
	}
	return (0);
}

int	ft_printf(char const *format, ...)
{
	int				result;
	va_list			ap;
	t_format_info	info;

	result = 0;
	va_start(ap, format);
	while (*format)
	{
		result += write_general_string(&format);
		if (*format == '%')
		{
			format++;
			ft_memset(&info, 0, sizeof(info));
			process_format(&format, &ap, &info);
			result += write_formatted_value(&info);
		}
	}
	va_end(ap);
	return (result);
}
