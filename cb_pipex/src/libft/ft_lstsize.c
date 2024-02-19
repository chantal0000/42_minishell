/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:51:23 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/01 17:02:01 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Counts the number of nodes in a list.*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
