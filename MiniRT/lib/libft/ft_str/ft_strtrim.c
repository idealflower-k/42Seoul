#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && start < end)
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (str)
		ft_strlcpy(str, &s1[start], end - start + 1);
	else
		return (NULL);
	return (str);
}
