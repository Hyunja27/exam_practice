#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_rect
{
	int b_w;
	int	b_h;
	char b_ch;

	char type;
	float x_strt;
	float y_strt;
	float w;
	float h;
	char ch;
}				t_rect;

int ft_strwrt(char *str)
{
	int i = 0;

	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (1);
}

void draw_rect(t_rect t, int cur_x, int cur_y, char **image)
{
	if ( ((float)cur_x >= t.x_strt && (float)cur_x <= t.x_strt + t.w) && \
		((float)cur_y >= t.y_strt && (float)cur_y <= t.y_strt + t.h))
	   (*image)[cur_y * t.b_w + cur_x] = t.ch;	
}

int	main(int ac, char* av[])
{
	t_rect t;
	int cur_x;
	int	cur_y;
	char *image;
	FILE *file;
	int	 read_file;
	float one = 1.00000;

	if (ac != 2)
		return (ft_strwrt("Error: argument\n"));
	if (!(file = fopen(av[1],"r")))
		return (ft_strwrt("Error: Operation file corrupted\n"));
	read_file = fscanf(file,"%d %d %c\n", &t.b_w, &t.b_h, &t.b_ch);
	if (read_file != 3)
		return (ft_strwrt("Error: Operation file corrupted\n"));
	if (!((t.b_w > 0 && t.b_w <= 300) && (t.b_h > 0 && t.b_h <= 300)))
		return (ft_strwrt("Error: Operation file corrupted\n"));
	image = (char*)malloc(sizeof(char) * (t.b_w * t.b_h));
	memset(image, t.b_ch, t.b_w * t.b_h);
	read_file = fscanf(file, "%c %f %f %f %f %c\n", &t.type, &t.x_strt, &t.y_strt, &t.w, &t.h, &t.ch);
	cur_y = 0;
	cur_x = 0;
	while (read_file == 6)
	{
		if ((t.type != 'r' && t.type != 'R') || (t.w <= 0 || t.h <= 0))
		{
			free(image);
			return (ft_strwrt("Error: Operation file corrupted1\n"));
		}
		cur_y = 0;
		while(cur_y < t.b_h)
		{	
			cur_x = 0;
			while(cur_x < t.b_w)
			{
				if (t.type == 'R')
					draw_rect(t, cur_x, cur_y, &image);
				else if(t.type == 'r')
				{
					if ( ((float)cur_x - t.x_strt < one) || (float)cur_x > t.x_strt + t.w - one ||\
						(float)cur_y - t.y_strt < one || (float)cur_y > t.y_strt + t.h - one )
						draw_rect(t, cur_x, cur_y, &image);
				}
				cur_x++;
			}
			cur_y++;
		}
		read_file = fscanf(file, "%c %f %f %f %f %c\n", &t.type, &t.x_strt, &t.y_strt, &t.w, &t.h, &t.ch);
	}
	if (read_file != -1)
	{
		free(image);
		return (ft_strwrt("Error: Operation file corrupted2\n"));
	}
	cur_y = 0;
	while(cur_y < t.b_w * t.b_h)
	{
		write(1, image + cur_y, t.b_w);
		write(1, "\n", 1);
		cur_y += t.b_w;
	}
	free(image);
	fclose(file);
	return (0);
}

