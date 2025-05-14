#include "get_next_line.h"

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
		printf("\nTEST NUMBER %d\nTesting file: %s\n", i, test_files[i]);

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