/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:40:37 by chbuerge          #+#    #+#             */
/*   Updated: 2023/07/20 10:30:12 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//6. %u Prints an unsigned decimal (base 10) number.

/* %u */
void	ft_putnbr_u(unsigned int n)
{
	long int	nb;

	nb = n;
	if (nb > 9)
	{
		ft_putnbr_u(nb / 10);
		ft_putchar_fd((nb % 10 + 48), 1);
	}
	else
		ft_putchar_fd((nb + 48), 1);
}

size_t	ft_print_u_nbr(unsigned int nb)
{
	size_t	length;

	length = 0;
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putnbr_u(nb);
	while (nb > 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}
