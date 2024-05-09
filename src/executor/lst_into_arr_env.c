/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_into_arr_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:32:58 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/09 14:40:08 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** This function turns our linked list env back into array of string
** to use in execve
*/
int	ft_list_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**ft_env_list_to_array(t_env *head)
{
	t_env	*current;
	int		i;
	int		count;
	char	**env_array;

	i = 0;
	count = ft_list_size(head);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	current = head;
	while (current)
	{
		env_array[i] = strdup(current->cmd_env);
		if (env_array[i] == NULL)
			return (NULL);
		i++;
		current = current->next;
	}
	env_array[count] = NULL;
	return (env_array);
}
