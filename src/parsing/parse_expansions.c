/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/18 21:15:48 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check if variable name is valid
//checks each char is alphanumeric or underscore 
int	valid_name(char *s)
{
	if (!s || !ft_isalpha(*s))
		return (0);
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}
char	*find_var_position(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '$' && valid_name((s + 1)))
			return (s);
		s++;
	}
	return (NULL);
}

// Update the input string with the variable value
void update_string(char **string, char *var_value, char *second_string)
{
	char	*beg_part;
	char	*updated_string;
	size_t	len;

	if (!*string[0] && var_value)
		beg_part = ft_strdup(var_value);
	else if (!*string[0] && !var_value)
		beg_part = ft_strdup("");
	else
		beg_part = ft_strdup(*string);
	len = ft_strlen(beg_part) + ft_strlen(second_string);
	updated_string = ft_calloc((len + 1), sizeof(char));
	if (updated_string) {
		ft_strcpy(updated_string, beg_part);
		ft_strcat(updated_string, second_string);
	}
	free(beg_part);
	free(*string);
	*string = updated_string;
}
//**************************************
//not updated....still copied

// Expand variables in the input string
void expand_variables(char **input, t_env *env) {
	char *var_position;
	char *var_name;
	char *var_value;
	int name_size;

	var_position = find_var_position(*input);
	if (var_position) {
		name_size = 0;
		while (valid_name(&var_position[name_size + 1]))
			name_size++;
		var_name = strndup(var_position + 1, name_size);
		*var_position = '\0';
		var_value = find_substitution(env , var_name);
		update_string(input, var_value, var_position + 1 + name_size);
		free(var_name);
		expand_variables(input, env);
	}
}

// Expand the exit status in the input string
void expand_exit_status(char **input, int exit_status) {
	char *exit_pos;
	char *first_part;
	char *second_part;
	char *status_str;
	char *updated_input;

	while ((exit_pos = strstr(*input, "$?")) != NULL) {
		*exit_pos = '\0';
		first_part = strdup(*input);
		second_part = strdup(exit_pos + 2);
		asprintf(&status_str, "%d", exit_status); // Convert exit status to string

		updated_input = malloc(strlen(first_part) + strlen(status_str) + strlen(second_part) + 1);
		if (updated_input) {
			ft_strcpy(updated_input, first_part);
			ft_strcat(updated_input, status_str);
			ft_strcat(updated_input, second_part);
		}

		free(first_part);
		free(second_part);
		free(status_str);
		free(*input);
		*input = updated_input;
	}
}

// Handle all expansions (variables and exit status) in the input string
void handle_expansions(char **input, t_env *minienv, int exit_status) {
	expand_exit_status(input, exit_status);
	expand_variables(input, minienv);
}

void parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status)
{
	t_cmd *temp;
	int i;

	if (!cmd || !*cmd || !env || !exit_status)
		return;

	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			handle_expansions(&temp->cmd[i], env, *exit_status);
			i++;
		}
		temp = temp->next;
	}
}
