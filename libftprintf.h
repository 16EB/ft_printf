/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:50:39 by jkong             #+#    #+#             */
/*   Updated: 2022/03/16 21:57:56 by jkong            ###   ########.fr       */
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
	PLUS,
	AFTER_UPPER,
	AFTER_PREFIX,
	AFTER_UNSIGNED,
	AFTER_NEGATIVE
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
	int			precision;
	char		type;
	t_variant	value;
}	t_format_info;

/*
**
** Standard C Library functions (libft.c)
**
*/
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);

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
** Output stream function (stream.c)
**
*/
int		print(const char *buf, size_t n);
int		print_string(t_format_info *info, char *buf, int n);
int		print_integer(t_format_info *info, long number, int radix);

/*
**
** Integer output stream function (stream_integer.c)
**
*/
int		prepare_integer(int flags, int radix, int fake);
int		integer_length(unsigned long number, int radix);
int		integer_write(unsigned long number, int flags, int radix, int fake);

/*
**
** Main function (ftprintf.c)
**
*/
int		ft_printf(char const *format, ...);

#endif
