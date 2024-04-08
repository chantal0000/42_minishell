/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:36:23 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/08 16:18:13 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
** Creates a new node for the linked list representing an environment
** variable line.
** @param line: The environment variable line to be stored in the node.
** @return: A pointer to the newly created node.
*/
void	*create_env_node(char *line)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->cmd_env = line;
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
void	fill_env_struct(t_cmd *cmd, char **environment)
{
	int		i;
	t_env	*env_head;
	t_cmd	*temp;

	i = 0;
	if (!cmd || !environment)
		return ;
	env_head = NULL;
	temp = cmd;
	while (temp)
	{
		while (environment[i])
		{
			insert_end(&env_head, environment[i]);
			i++;
		}
		temp->m_env = env_head;
//		printf("env: %s\n", temp->m_env->cmd_env);
		temp = temp->next;
	}
	cmd = temp;
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
}


// test main
// int main(int argc, char **argv, char **env)
// {
// 	fill_env_struct(env);
// 	return (0);
// }
