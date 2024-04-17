/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:36:23 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/17 13:12:19 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/// ENV utils

// int	ft_split_env_line(char *line, char **env_name, char **env_value)
// {
// 	char	*delimiter;

// 	delimiter = ft_strchr(line, '=');
// 	if (!delimiter)
// 		return (0);
// 	*env_name = (char *)malloc((delimiter - line + 1) * sizeof(char));
// 	if (!(*env_name)) {
// 	return (0); // Return failure
// 	ft_strncmp(*env_name, line, delimiter - line);
// 	 (*env_name)[delimiter - line] = '\0';
// 	     // Allocate memory for env_value
//     *env_value = strdup(delimiter + 1);
//     if (!(*env_value)) {
//         free(*env_name); // Free previously allocated memory
//         return 0; // Return failure
//     }

//     }
// 	    return 1; // Return success

// }


/*
** Creates a new node for the linked list representing an environment
** variable line.
** @param line: The environment variable line to be stored in the node.
** @return: A pointer to the newly created node.
*/
void	*create_env_node(char *line)
{
	t_env	*new_node;
	// char	*env_name;
	// char	*env_value;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	    // Split the line into env_name and env_value
    // if (!ft_split_env_line(line, &env_name, &env_value)) {
    //     // Splitting failed
    //     free(new_node); // Free the allocated memory for the new node
    //     return NULL; // Return NULL
    // }
	new_node->cmd_env = strdup(line);
	// new_node->env_name = env_name;
	// new_node->env_value = env_value;
	new_node->next = NULL;

	return (new_node);
}

/*
** Inserts a new node at the end of the linked list representing the environment.
** If the list is empty, creates a new list with the provided node.
** @param head: A pointer to the head of the environment linked list.
** @param line: The environment variable line to be stored in the new node.
*/
void	insert_end(t_env **head, char *line)
{
	t_env	*new_node;
	t_env	*temp;

	temp = NULL;
	new_node = create_env_node(line);
	if (!new_node)
	{
//		free_env(head->cmd_env);
		return ;
	}
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
//	free (new_node);
}

/*
** Fills a linked list with environment variable lines.
** @param environment: The array of strings containing environment variable lines.
**                     The last element of the array must be NULL.
*/
t_env	*fill_env_struct(char **environment)
{
	int		i;
	t_env	*env_head;

	i = 0;
	if (!environment)
		return (NULL);
	env_head = NULL;
		while (environment[i])
		{
			insert_end(&env_head, environment[i]);
			i++;
		}
//	free (temp);
/*	 (environment[i])
	{
		insert_end(&env_head, environment[i]);
		i++;
	}*/
	// while (env_head)
	// {
	// 	printf("%s\n", env_head->env_line);
	// 	env_head = env_head->next;
	// }
	return(env_head);
}


// test main
// int main(int argc, char **argv, char **env)
// {
// 	fill_env_struct(env);
// 	return (0);
// }
