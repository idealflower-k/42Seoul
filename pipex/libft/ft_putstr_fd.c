#include "libft.h"

void	ft_putstr_fd(char *s, int fd);

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i++], 1);
	}
}
