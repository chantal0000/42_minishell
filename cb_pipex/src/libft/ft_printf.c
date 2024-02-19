/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:39:27 by chbuerge          #+#    #+#             */
/*   Updated: 2023/07/20 12:33:22 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
1. %c Prints a single character.
2. %s Prints a string (as defined by the common C convention).
3. %p The void * pointer argument has to be printed in hexadecimal format.
4. %d Prints a decimal (base 10) number.
	- prints but does not count
5. %i Prints an integer in base 10.
6. %u Prints an unsigned decimal (base 10) number.
7. %x Prints a number in hexadecimal (base 16) lowercase format.
8. %X Prints a number in hexadecimal (base 16) uppercase format.
9. %% Prints a percent sign.
*/
int	ft_eval_specifier(va_list args, const char specifier)
{
	int	length;

	length = 0;
	if (specifier == 'c')
		length += ft_print_char(va_arg(args, int));
	else if (specifier == 's')
		length += ft_print_str(va_arg(args, char *));
	else if (specifier == 'p')
		length += ft_print_p(va_arg(args, unsigned long int));
	else if (specifier == 'd' || specifier == 'i')
		length += ft_print_nbr(va_arg(args, int));
	else if (specifier == 'u')
		length += ft_print_u_nbr(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		length += ft_print_hex
			((unsigned int)va_arg(args, unsigned long int), specifier);
	else if (specifier == '%')
		length += ft_print_char('%');
	return (length);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	int		i;
	va_list	args;

	length = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length += ft_eval_specifier(args, format[i + 1]);
			i++;
		}
		else
			length += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (length);
}
