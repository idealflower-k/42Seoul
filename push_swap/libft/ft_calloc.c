#include "libft.h"

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	if (count && size > SIZE_MAX / count)
		return ((void *)0);
	temp = malloc(size * count);
	if (temp == 0)
		return ((void *)0);
	ft_bzero(temp, (count * size));
	return (temp);
}
