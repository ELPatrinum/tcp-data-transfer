#ifndef SFT_H
# define SFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# define SIZE 1024

char	*get_next_line(int fd);
char	*update_remains(char *remains);
char	*get_theline(char *str);
char	*read_from_fd(int fd, char *res);

int		ft_strlen(char *s, int j, char c);
int		new_line_check(char *str);
char	*ft_strjoin(char *s1, char *s2);
//////////////////////////////////////////////
int ft_client(void);
int ft_server(void);

#endif