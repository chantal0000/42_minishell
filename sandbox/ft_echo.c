#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char	**ft_echo(char *s)
{
	int		i;
	int		len;
	char	*str;
	char	**temp;
	char	*arg_start;

	i = 1;
	len = 0;
	str = s;
	temp = (char**)malloc(sizeof(char *) * 100);
	temp[0] = strdup("echo");
//	arg_start = s;
	while (str[len] != '|' && str[len - 1] != '\\' && str[len] != '\0')
	{
		if (str[len] == '-' && str[len + 1] == 'n' && str[len + 2] == ' ')
		{
			while (str[len] != ' ' && str[len] != '\0')
				len++;
			temp[i] = strndup(s, len);
			str += len + 1;
			i++;
			len = 0;
		}
		len++;
	}
	arg_start = str;
	temp[i] = strndup(arg_start, len);
	str += len;
	temp[i + 1] = NULL;
	s = str;
	return (temp);
}


int	main()
{
	char	**line;
	int		i = 0;
	char 	*s = "-n this is";

	line = ft_echo(s);
	while (line[i]) 
	{
		printf("line[i] = %s\n", line[i]);
		i++;
	}
	return (0);
}