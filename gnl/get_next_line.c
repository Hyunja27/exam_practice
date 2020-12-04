
#include "get_next_line.h"

static int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

static char		*ft_strjoin(char *str1, char *str2)
{
	int 	i;
	int		j;
	int		len;
	char	*tmp;
	
	i = 0;
	j = 0;
	len = ft_strlen(str1) + ft_strlen(str2);
	if (!(tmp = malloc(sizeof(char) * (len + 1))))
		return (0);
	tmp[len] = 0;
	while(str1[i])
	{
		tmp[i] = str1[i];
		i++;
	}
	while(str2[j])
	{
		tmp[i] = str2[j];
		i++;
		j++;
	}
	return (tmp);
}


static char		*ft_strdup(char *str)
{
	int 	i;
	char	*tmp;
	
	i = 0;
	i = ft_strlen(str);
	if (!(tmp = malloc(sizeof(char) * (i + 1))))
		return (0);
	tmp[i] = 0;
	i = 0;
	while(str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

char	*ft_strchr(char	*str, int tg)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == tg)
			return (&str[i]);
		i++;
	}
	return (0);
}

static void	rt_n_store(char **room, char **line, int *rt)
{
	char	*tmp;
	char	*anchor;

	anchor = ft_strchr(*room, '\n');
	*anchor = 0;
	*line = ft_strdup(*room);
	tmp = ft_strdup(anchor + 1);
	free(*room);
	*room = ft_strdup(tmp);
	free(tmp);
	*rt = 1;
}

static void	rt_room(char **room, char **line, int *rt)
{
	if (ft_strchr(*room, '\n'))
		rt_n_store(room, line, rt);
	else
	{
		*line = ft_strdup(*room);
		free(*room);
		*room = 0;
		*rt = 0;
	}
}

int				get_next_line (char **line)
{
	int 		rt;
	static char	*room[1];
	char 		buff[10000];
	char 		*tmp;

	rt = 0;
	if (!line)
		return (-1);
	while ((rt = read(0, buff, 1)) >= 0)
	{
		buff[rt] = 0;
		printf("\n![%d]!\n",rt);
		tmp = !room[0] ? ft_strdup(buff) : ft_strjoin(room[0], buff);
		free(room[0]);
		room[0] = tmp;
		if (rt == 0)
		{
			printf("!!");
			rt_room(&room[0], line, &rt);
			if (rt == 0)
				break ;
		}
		else if (ft_strchr(room[0], '\n'))
		{
			rt_n_store(&room[0], line, &rt);
			break ;
		}
	}
	return (rt);
}
