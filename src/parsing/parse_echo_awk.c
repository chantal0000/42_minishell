/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/22 17:21:48 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*t_cmd	*ft_parse_echo(t_cmd *cmd_tree, char **str)
{
	int		i;
	char	*arg_start;
	char	*s;
	t_cmd	*temp;

	i = 0;
	s = *str;
	temp = cmd_tree;
	temp->cmd[i++] = ft_strdup("echo");
	while (*s && *s != '|')
	{
		if (*s == '-' && *(s + 1) == 'n' && *(s + 2) == ' ')
		{
			temp->token = 'n';
			s += 3;
		}
		else
		{
			arg_start = s;
			while (*s && (*s != '|' && *(s - 1) != '\\') && *s != '\0')
				s++;
			temp->cmd[i++] = ft_strndup(arg_start, s - arg_start);
		}
	}
	temp->cmd[i] = NULL;
	*str = s;
	return (temp);
}*/
int	ft_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_echo(t_cmd *cmd)
{
	t_cmd	*temp;
	int		index;
	int		i;

	i = ft_count(cmd->cmd);
	temp = cmd;
	if (!ft_strcmp(temp->cmd[0], "echo") && !ft_strcmp(temp->cmd[1], "-n"))
	{
		index = 2;
		while (index < i)
		{
			printf("%s ", temp->cmd[index]);
			index++;
		}
		printf("%s", temp->cmd[index]);
	}
	else
	{
		index = 1;
		while (index < i)
		{
			printf("%s ", temp->cmd[index]);
			index++;
		}
		printf("%s\n", temp->cmd[index]);
	}
}
//parse through if no quotes

/*		parse_for_pipe(&temp->cmd[1], &temp, 0, &index);
		update_fd(*cmd);
		// fill_env_struct(*cmd, env);
		while (&temp->cmd[1] != '\0' && is_whitespace(&temp->cmd[1]))
			(*temp->cmd[1])++;
		if (*temp != '\0')
		{
			printf("check syntax\n");//check what bash returns
			return ;
		}
		restore_pipes_and_spaces(*cmd);
		if (cmd->token == 'e')
			printf("\n");
	}*/


/*t_cmd	*ft_echo(t_cmd *cmd_tree, char **str)
{
	int		i;
	int		len;
	char	*arg_start;
	char	*s;
	t_cmd	*temp;

	i = 1;
	len = 0;
	s = *str;
	arg_start = s;
	temp = cmd_tree;
	temp->cmd[0] = ft_strdup("echo");
	while (s[len] != '|' && s[len - 1] != '\\' && s[len] != '\0')
	{
		if (s[len] == '-' && s[len + 1] == 'n' && s[len + 2] == ' ')
		{
			while (s[len] != ' ' && s[len] != '\0')
				len++;
			temp->cmd[i] = ft_strndup(arg_start, len);
			s += len + 1;
			i++;
			len = 0;
		}
		len++;
	}
	arg_start = s;
	temp->cmd[i] = ft_strndup(arg_start, len);
	temp->cmd[3] = NULL;
	*str = s + len;
	cmd_tree = temp;
	return (cmd_tree);
}*/

/*char	*parse_line_echo(char *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0' && (arr[i] != '\'' && arr[i - 1] != '\\'))
		i++;
	arr[i] = '\0';
	return (arr);
}*/

