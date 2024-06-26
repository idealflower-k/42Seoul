#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*temp;
	int		size;

	size = 0;
	while (src[size])
		size++;
	temp = (char *)malloc(sizeof(char) * size + 1);
	if (temp == 0)
		return (0);
	size = 0;
	while (*src)
	{
		temp[size] = *src;
		size++;
		src++;
	}
	temp[size] = 0;
	return (temp);
}
