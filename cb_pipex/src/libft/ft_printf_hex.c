/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:50 by chbuerge          #+#    #+#             */
/*   Updated: 2023/07/20 10:27:24 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* hexadecimal %x
255 = ff or FF
f = 15 -> (15 * 16(base of hex)^1(the leftmost position))
(15 * 16^1) + (15 * 16^0) = (15 * 16) + (15 * 1) = 240 + 15 = 255

10 - 15 -> ABCDEF
calculates ASCII value of the character to be printed on the numeric value of
hex digit (nb)
nb -> numeric value of the dex digit
nb - 10 -> offset of A from 0
ft_putchar_fd((nb - 10 + 'A'), 1);
*/

int	ft_print_hex(unsigned long int nb, char specifier)
{
	int	length;

	length = 0;
	if (nb > 15)
	{
		length += ft_print_hex(nb / 16, specifier);
		length += ft_print_hex(nb % 16, specifier);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + 48), 1);
		else
		{
			if (specifier == 'X')
				ft_putchar_fd((nb - 10 + 'A'), 1);
			else if (specifier == 'x')
				ft_putchar_fd((nb - 10 + 'a'), 1);
		}
		length++;
	}
	return (length);
}
