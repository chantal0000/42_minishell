/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:25 by chbuerge          #+#    #+#             */
/*   Updated: 2023/12/29 17:54:09 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Write a function that returns a line read from a
file descriptor
*/

#include "../libft.h"

/*
joins the existing stash string with the buffer string
and updates the stash pointer. frees the old stash string.
*/
static void	ft_join(char **stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin_gnl(*stash, buffer);
	free(*stash);
	*stash = temp;
}

/*
reading lines from the file descriptor,
appends (anhaengen)them to the existing
    1. buffer check...
    2. read data from the file into the buffer,
    BUFFER_SIZE -> max number of bytes read at
	 a time (returns number of bytes read - >int)
    3. while bytes_read > 0 meaning, there was
	a successful read operation
    4. set last character of the buffer to
	'\0' to terminate the string in the buffer
    5. if !stash call strjoin with "" and buffer
    6. join stash and buffer
    7. search for new line
    8. repeat if not found
    9. finished reading from the file so we can free buffer
*/
char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read_counter;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read_counter = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read_counter > 0)
	{
		buffer[bytes_read_counter] = '\0';
		if (!stash)
			stash = ft_strjoin("", buffer);
		else
			ft_join(&stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes_read_counter = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read_counter == -1 && stash != 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

/*  1. if
fd is < 0 means invalid fd or closed fd
    2. passing extracted_str as an argument
    to allow the ft_read function to update the
    value of extracted_str based on the data read from the
    file. The function receives the current value of
    static_str and appends the new data read from the
    file to it.
    3. checks if two conditions are true, a) !extracted_str:
	checking if the pointer is NULL,
    meaning check if extracted_str does not point to any
	valid memory location.
    b) !*extracted_line: check if the value at the memory
	ocation pointed to by extracted_line
    is NULL meaning checking if the first character of the s
	tring extracted_line points to is '\0'
    -> if this is the case: ....function
	free_str(&extracted_line) and return NULL
    4. calls extract line function and passes stash,
	line from stash is extracted and
    returns it as extracted_line var.
    5. after

*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	extracted_line = ft_extract_line(stash);
	stash = ft_remove_extracted_line_from_stash(stash);
	return (extracted_line);
}
/*
RETURN VALUE: Read line: correct behavior
NULL: there is nothing else to read, or an error
*/

/*test main function*/
/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	char	*temp;
	int	fd;

	fd = open("map.ber", O_RDONLY);
	if (fd > 0)
//        printf("%d\n", fd);
	while(1)
	{
		temp = get_next_line(fd);
		if (!temp)
		    break ;
		printf("%s", temp);
//         printf("%d\n", fd);
		free(temp);
	}
	return (0);
}
*/
