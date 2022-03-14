/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:29:50 by jkong             #+#    #+#             */
/*   Updated: 2022/03/14 20:41:23 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdarg.h>

static int	load_flag(char const **pfmt)
{
	int	flags;

	flags = 0;
	while (ft_strchr("-0# +", **pfmt))
	{
		if (**pfmt == '-')
			set_flag(&flags, MINUS);
		else if (**pfmt == '0')
			set_flag(&flags, ZERO);
		else if (**pfmt == '#')
			set_flag(&flags, HASH);
		else if (**pfmt == ' ')
			set_flag(&flags, SPACE);
		else if (**pfmt == '+')
			set_flag(&flags, PLUS);
		(*pfmt)++;
	}
	return (flags);
}

static int	load_number(char const **pfmt)
{
	int	number;

	number = 0;
	while (ft_isdigit(**pfmt))
	{
		number *= 10;
		number += **pfmt - '0';
		(*pfmt)++;
	}
	return (number);
}

static int	try_load_precision(char const **pfmt, int *result)
{
	*result = 0;
	if (**pfmt == '.')
	{
		(*pfmt)++;
		*result = load_number(pfmt);
		return (1);
	}
	return (0);
}

static char	get_value(char const **pfmt, va_list *ap, t_variant *value)
{
	char	type;

	type = *(*pfmt)++;
	if (type == 'c')
		value->c = va_arg(*ap, char);
	else if (type == 's')
		value->s = va_arg(*ap, char *);
	else if (type == 'p')
		value->p = va_arg(*ap, void *);
	else if (type == 'd' || type == 'i')
		value->n = va_arg(*ap, int);
	else if (type == 'u' || type == 'x' || type == 'X')
		value->u = va_arg(*ap, unsigned int);
	else if (type == '%')
	{
		type = 'c';
		value->c = '%';
	}
	else
		type = 0;
	return (type);
}

void	process_format(char const **pfmt, va_list *ap, t_format_info *info)
{
	info->flags = load_flag(pfmt);
	info->width = load_number(pfmt);
	info->has_precision = try_load_precision(pfmt, &info->precision);
	info->type = get_value(pfmt, ap, &info->value);
}
