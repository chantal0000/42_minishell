/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/08 18:12:45 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	free_cmdtree(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	while (tree)
	{
		temp = tree;
		// if (temp->fd_in)
		// 	close(temp->fd_in);
		// if (temp->fd_out)
		// 	close(temp->fd_out);
		// if (temp->pid)
		// 	close(temp->pid)
		temp = tree->next;
		if (tree->fd_in)
			close(tree->fd_in);
		if (tree->fd_out)
			close(tree->fd_out);
		if (tree->pid)
		{
			close(tree->pid);
//			kill(tree->pid, SIGKILL); should I use this?
		}
		// if (temp->m_env)
		// 	free_env(&temp->m_env);
		if (tree->file_name)
			free(tree->file_name);
		free_memory(tree->cmd);
		if (tree->heredoc_delimiter)
			free (tree->heredoc_delimiter);
		free_memory(tree->heredoc_content);
		free(tree);
		tree = temp;
	}
	free(tree);
}*/

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
	// free(arr);
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

void ft_free_env_list(t_env *env_list)
{
	t_env *next;
	if (!env_list)
		return ;
	while (env_list != NULL)
	{
			next = env_list->next;
			free(env_list);
			env_list = next;
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
		// if (current->cmd)
		free_memory(current->cmd);
		if (current->file_name && ft_strcmp(current->file_name, "/tmp/tempfile21008") != 0)
			free(current->file_name);
		if (current->heredoc_delimiter)
			free(current->heredoc_delimiter);
		// if (current->heredoc_content)
		// free_memory(current->heredoc_content);
		free(current);
		current = next;
	}
}


void free_exp(t_exp **exp)
{
	t_exp *current = *exp;
	t_exp *next;

	while (current != NULL)
	{
		next = current->next;

		if (current->exp_name)
			free(current->exp_name);
		if (current->exp_value)
			free(current->exp_value);
		free(current);

		current = next;
	}
	*exp = NULL; // Set the original pointer to NULL after freeing all nodes
}
