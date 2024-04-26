


#include "../../minishell.h"

/*
** This function turns our linked list env back into array of string
** to use in execve
*/
int	ft_list_size(t_env *head)
{
	int count = 0;
	t_env *current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char **ft_env_list_to_array(t_env *head)
{
	t_env *current;
	int i = 0;
	int count = ft_list_size(head);
	char **env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
	{
		//handle error
	}
	current = head;
	while (current)
	{
		env_array[i] = strdup(current->cmd_env);
		if (env_array[i] == NULL)
		{
			// error
		}
		i++;
		current = current->next;
	}
	env_array[count] = NULL;

	return (env_array);
}


