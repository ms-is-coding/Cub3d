/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:56:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/31 20:44:13 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

static int	get_digit(char c, int base)
{
	int	d;

	if (c >= '0' && c <= '9')
		d = c - '0';
	else if (c >= 'a' && c <= 'z')
		d = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		d = c - 'A' + 10;
	else
		return (-1);
	if (d >= base)
		return (-1);
	return (d);
}

static int	get_base(const char **s, int base)
{
	if (base == 0)
	{
		if (**s != '0')
			return (10);
		(*s)++;
		if (**s == 'x' || **s == 'X')
		{
			(*s)++;
			return (16);
		}
		return (8);
	}
	if (base == 16 && **s == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X'))
		*s += 2;
	return (base);
}

static long	handle_overflow(const char **s, int base, int neg)
{
	errno = ERANGE;
	while (get_digit(**s, base) >= 0)
		(*s)++;
	if (neg)
		return (LONG_MIN);
	return (LONG_MAX);
}

static long	parse_number(const char **s, int base, int neg)
{
	unsigned long	cutoff;
	unsigned long	acc;
	int				cutlim;
	int				d;

	if (neg)
		cutoff = -(unsigned long)LONG_MIN;
	else
		cutoff = (unsigned long)LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	acc = 0;
	d = get_digit(**s, base);
	while (d >= 0)
	{
		if (acc > cutoff || (acc == cutoff && d > cutlim))
			return (handle_overflow(s, base, neg));
		acc = acc * base + d;
		(*s)++;
		d = get_digit(**s, base);
	}
	if (neg)
		return (-(long)acc);
	return ((long)acc);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*s;
	int			neg;
	long		result;

	s = nptr;
	neg = 0;
	result = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			neg = 1;
		s++;
	}
	base = get_base(&s, base);
	result = parse_number(&s, base, neg);
	if (endptr)
		*endptr = (char *)s;
	return (result);
}
