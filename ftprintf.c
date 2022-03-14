/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:01:47 by jkong             #+#    #+#             */
/*   Updated: 2022/03/14 22:24:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdarg.h>
#include <unistd.h>

static int	write_general_string(char **pfmt)
{
	char *const	format = *pfmt;
	int			i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	if (i == 0)
		return (0);
	*pfmt += i;
	return (write(STDOUT_FILENO, format, i));
}

static int	write_formatted_value(t_format_info *info)
{
	//TODO: make correct function call it
	if (info->type == 'c')
		return (1);
	else if (info->type == 's')
		return (2);
	else if (info->type == 'p')
		return (3);
	else if (info->type == 'd' || info->type == 'i')
		return (4);
	else if (info->type == 'u')
		return (5);
	else if (info->type == 'x' || info->type == 'X')
		return (7);
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
			process_format(&format, &ap, &info);
			result += write_formatted_value(&info);
		}
	}
	va_end(ap);
	return (result);
}
