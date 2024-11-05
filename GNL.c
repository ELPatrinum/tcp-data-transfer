# include "SFT.h"

int	ft_strlen(char *str, int j, char c)
{
	int	i;

	i = j;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c && c != '\0')
		i++;
	return (i);
}

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*cpy_str(char *s1, char *s2, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
		{
			free(s1);
			return (NULL);
		}
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	res = malloc(ft_strlen(s1, 0, '\0') + ft_strlen(s2, 0, '\0') + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	cpy_str(s1, s2, res);
	free(s1);
	return (res);
}

char	*read_from_fd(int fd, char *remains)
{
	char		*buff;
	long long	size;

	size = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(remains), NULL);
	while (size > 0 && !new_line_check(remains))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == 0)
			break ;
		if (size == -1)
		{
			free(buff);
			free(remains);
			return (NULL);
		}
		buff[size] = '\0';
		remains = ft_strjoin(remains, buff);
	}
	free(buff);
	return (remains);
}

char	*get_theline(char *str)
{
	int		i;
	char	*line;

	if (!*str)
		return (NULL);
	line = malloc((ft_strlen(str, 0, '\n') + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remains(char *remains)
{
	char	*new_remains;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!remains)
		return (free(remains), NULL);
	while (remains[i] != '\0' && remains[i] != '\n')
		i++;
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	new_remains = malloc((ft_strlen(remains, i, '\0')) * sizeof(char));
	if (!new_remains)
		return (free(remains), NULL);
	i++;
	while (remains[i])
		new_remains[j++] = remains[i++];
	new_remains[j] = '\0';
	free(remains);
	return (new_remains);
}

char	*get_next_line(int fd)
{
	static char	*remains;
	char		*theline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remains = read_from_fd(fd, remains);
	if (!remains)
		return (NULL);
	theline = get_theline(remains);
	if (!theline)
	{
		free(remains);
		remains = NULL;
		return (NULL);
	}
	remains = update_remains(remains);
	return (theline);
}