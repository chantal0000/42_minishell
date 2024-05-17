/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/17 16:51:53 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_memory(char **arr)
{
	size_t	i;

	i = 0;
	if (!*arr || !arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
//	free (arr);
}

/* free the array of env, in every loop*/

void	free_env(char **env)
{
// THIS IS ACTUALLY JUST A FREE ARRAY FUNCTION SO MAYBE CHANGE NAME CHANTAL
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i] != NULL)
	{
		// IMPORTANT!!!!!!!!!
		free(env[i]);
		i++;
	}
	free (env);
}


/*chantal added functions
** free the linked list of environment
** needs to be freed only at the very end of the program vs the array that needs to be freed in every loop
*/

// void	ft_free_env_list(t_env **env_list)
// {
// 	t_env	*next;

// 	if (!env_list)
// 		return ;
// 	while (env_list != NULL)
// 	{
// 		next = (*env_list)->next;
// 		free((*env_list)->cmd_env);
// 		free(*env_list);
// 		env_list = &next;
// 	}
// }
void	ft_free_env_list(t_env **env_list)
{
	t_env	*next;

	if (!env_list || !*env_list) // Check if env_list or *env_list is NULL
		return ;
	while (*env_list != NULL) // Check if the value pointed to by env_list is not NULL
	{
		next = (*env_list)->next;
		free((*env_list)->cmd_env);
		free(*env_list);
		*env_list = next; // Update the value pointed to by env_list
	}
}

/*
** free cmd_struct after every loop
*/
void	ft_free_cmd_struct(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_memory(current->cmd);
		if (current->file_name)
		{
			if (ft_strcmp(current->file_name, "/tmp/tempfile21008") == 0)
				unlink("/tmp/tempfile21008");
		}
		free(current);
		current = next;
	}
}
