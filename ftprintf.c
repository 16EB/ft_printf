/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:01:47 by jkong             #+#    #+#             */
/*   Updated: 2022/03/14 20:41:51 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdarg.h>

int	ft_printf(char const *format, ...)
{
	va_list			ap;
	size_t			i;
	t_format_info	info;

	va_start(ap, format);
	while (*format)
	{
		i = 0;
		while (format[i] && format[i] != '%')
			i++;
		if (i != 0)
		{
			//general string
			format += i;
		}
		if (*format == '%')
		{
			format++;
			process_format(&format, &ap, &info);
			//formatted value
		}
	}
	va_end(ap);
	return (0);
}
