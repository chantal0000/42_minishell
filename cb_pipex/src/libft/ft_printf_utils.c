/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:25:41 by chbuerge          #+#    #+#             */
/*   Updated: 2023/07/20 10:27:58 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
cases to handle:
1. %c Prints a single character.
2. %s Prints a string (as defined by the common C convention).
3. %p The void * pointer argument has to be printed in hexadecimal format.
4. %d Prints a decimal (base 10) number.
5. %i Prints an integer in base 10.
*/

/* %c */
int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

/* %s */
int	ft_print_str(char *s)
{
	int	length;

	length = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[length])
	{
		ft_print_char(s[length]);
		length++;
	}
	return (length);
}

/* %p */

int	ft_print_p(unsigned long long ptr)
{
	int	length;

	length = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	length = length + write(1, "0x", 2);
	length = length + ft_print_hex(ptr, 'x');
	return (length);
}

/* %i and %d */
int	ft_print_nbr(int nb)
{
	int		length;
	char	*s;

	length = 0;
	s = ft_itoa(nb);
	length = ft_strlen(s);
	ft_putnbr_fd(nb, 1);
	free (s);
	return (length);
}
