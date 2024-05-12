/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/12 14:29:27 by chbuerge         ###   ########.fr       */
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
//		free(arr[i]);
		i++;
	}
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
		// store the next node before freeing the current one
		next = current->next;
		// free cmd string
		//if (current->cmd)
		free_memory(current->cmd);
		if (current->file_name && ft_strcmp(current->file_name, "/tmp/tempfile21008") != 0)
			free(current->file_name);
//	**this causes IOT Instruction error and invalid freeing to free delimiter

//		if (current->heredoc_delimiter)
//			free(current->heredoc_delimiter);
		// if (current->heredoc_content)
		// free_memory(current->heredoc_content);
		free(current);
		current = next;
	}
}
