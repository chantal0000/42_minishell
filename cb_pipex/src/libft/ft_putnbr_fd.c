/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:48:53 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/30 14:22:43 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar_fd('-', fd);
	}
	if (nb > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10 + 48), fd);
	}
	else
		ft_putchar_fd((nb + 48), fd);
}
