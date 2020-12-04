#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	printf("===================================================\n");
	while ((r = get_next_line(&line)) > 0)
	{	
		printf("%s\n", line);
	printf("\n[%d]\n", r);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	printf("\n[%d]\n", r);
	free(line);
	line = NULL;
	printf("===================================================\n");
}
