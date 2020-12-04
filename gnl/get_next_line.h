
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#ifndef OPEN_MAX
# define OPEN_MAX 10240
#endif

int	get_next_line(char **line);

#endif
