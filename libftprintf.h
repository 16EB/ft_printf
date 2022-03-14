/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:50:39 by jkong             #+#    #+#             */
/*   Updated: 2022/03/14 22:07:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stddef.h>
# include <stdarg.h>

typedef enum e_flag
{
	MINUS,
	ZERO,
	HASH,
	SPACE,
	PLUS
}	t_flag;

typedef union u_variant
{
	char			c;
	char			*s;
	void			*p;
	int				n;
	unsigned int	u;
	long			l;
}	t_variant;

typedef struct s_format_info
{
	int			flags;
	int			width;
	int			has_precision;
	int			precision;
	char		type;
	t_variant	value;
}	t_format_info;

/*
**
** Standard C Library functions (libft.c)
**
*/
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);

/*
**
** Flag manipulate utility functions (util_flag.c)
**
*/
void	set_flag(int *ptr, int index);
void	reset_flag(int *ptr, int index);
int		has_flag(int flags, int index);

/*
**
** Formatting function (format.c)
**
*/
void	process_format(char const **pfmt, va_list *ap, t_format_info *info);

/*
**
** Main function (ftprintf.c)
**
*/
int		ft_printf(char const *format, ...);

#endif
