/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:00:36 by wheino            #+#    #+#             */
/*   Updated: 2025/05/14 13:59:21 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_str;
	const unsigned char	*src_str;
	size_t				i;

	dest_str = (unsigned char *)dest;
	src_str = (const unsigned char *)src;
	i = 0;
	while (n--)
	{
		dest_str[i] = src_str[i];
		i++;
	}
	return (dest_str);
}

size_t	ft_strlen(const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}


char	*ft_strdup(const char *s)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen((char *)s) + 1;
	new_str = malloc(len * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	return (new_str);
}

char	*ft_strldup(const char *s, size_t len)
{
	char	*new_str;

	new_str = malloc(len * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}

int	count_chars_to_newline(char *str)
{
	int	i;
	int	chars;

	i = 0;
	chars = 1;
	while (str[i] != '\n')
	{
		i++;
		chars++;
	}
	return(chars);
}

char *get_next_line(int fd)
{
	char		*buf;
	static char	*stash;
	char	*temp_stash;
	char		*line;
	int			bytes_read;

	buf = malloc(5 + 1);
	if (stash == NULL)
		stash = ft_strdup("");
	while (1)
	{
		bytes_read = read(fd, buf, 3);
		buf[bytes_read] = '\0';
		temp_stash = ft_strjoin(stash, buf);
		free (stash);
		stash = temp_stash;
		if (ft_strchr(stash, '\n') != NULL || bytes_read <= 0)
			break ;
	}
	if (stash == NULL || *stash == '\0')
	{
		free (buf);
		free (stash);
		stash = NULL;
		return (NULL);
	}
	if (ft_strchr(stash, '\n') != NULL)
	{
		line = ft_strldup(stash, count_chars_to_newline(stash));
		temp_stash = ft_strdup(ft_strchr(stash, '\n') + 1);
		free(stash);
		stash = temp_stash;
	}
	else
	{
		line = ft_strdup(stash);
		free (stash);
		stash = NULL;
	}
	free (buf);
	return (line);
}


int	main()
{
	char *line;
	int	fd;
	int i;

	// List of test files for different edge cases
	const char *test_files[] = {
		"TestTxtFiles/empty_file.txt",
		"TestTxtFiles/no_newline.txt",
		"TestTxtFiles/multiple_lines.txt",
		"TestTxtFiles/newline_at_end.txt",
		"TestTxtFiles/one_line.txt",
		"TestTxtFiles/only_newline.txt"
	};

	// Loop through each test file and process it
	for (i = 0; i < 6; i++)
	{
		printf("\nTesting file: %s\n", test_files[i]);

		// Expected Output for this test case
		if (i == 0)
			printf("Expected Output: (nothing returned - empty file)\n");
		else if (i == 1)
			printf("Expected Output: (only one line, no newline)\n");
		else if (i == 2)
			printf("Expected Output: (multiple lines, each line printed)\n");
		else if (i == 3)
			printf("Expected Output: (newline at the end, last line with newline)\n");
		else if (i == 4)
			printf("Expected Output: (only one line)\n");
		else if (i == 5)
			printf("Expected Output: (only newline)\n");

		// Open the current test file
		fd = open(test_files[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			return (1);
		}

		// Get the next line until we reach the end of the file
		int j = 0;
		printf("Actual Output:\n");
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("Returned line[%d] = %s\n", j, line);
			free(line);
			j++;
		}
		// Check if the final line was NULL (EOF reached)
		if (line == NULL)
			printf("End of file reached for %s\n", test_files[i]);

		close(fd);
	}

	return 0;
}




// int	main()
// {
// 	char *line;
// 	int	fd = open("SomeText.txt", O_RDONLY);
// 	int i;

// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("\nRETURNED LINE[%d] = %s\n",i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	printf("\nRETURNED LINE[%d] = %s\n",i, line);
// 	close(fd);
// 	return 0;
// }