/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:29:50 by jkong             #+#    #+#             */
/*   Updated: 2022/03/17 14:23:44 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdarg.h>

static int	load_flag(char const **pfmt)
{
	int	flags;

	flags = 0;
	while (**pfmt)
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
		else
			break ;
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

static char	get_value(char const **pfmt, va_list *ap, t_variant *value)
{
	char	type;

	type = *(*pfmt);
	if (type)
	{
		(*pfmt)++;
		if (type == 'c')
			value->c = va_arg(*ap, int);
		else if (type == 's')
		{
			value->s = va_arg(*ap, char *);
			if (!value->s)
				value->s = "(null)";
		}
		else if (type == 'p')
			value->p = va_arg(*ap, void *);
		else if (type == 'd' || type == 'i')
			value->n = va_arg(*ap, int);
		else if (type == 'u' || type == 'x' || type == 'X')
			value->u = va_arg(*ap, unsigned int);
	}
	return (type);
}

void	process_format(char const **pfmt, va_list *ap, t_format_info *info)
{
	info->flags = load_flag(pfmt);
	info->width = load_number(pfmt);
	if (**pfmt == '.')
	{
		(*pfmt)++;
		info->precision = load_number(pfmt);
	}
	else
		info->precision = -1;
	info->type = get_value(pfmt, ap, &info->value);
	if (info->type == '%')
	{
		info->type = 'c';
		info->value.c = '%';
	}
}
