#include "libft.h"

static size_t	cal_num_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	tmp;
	char			*num;
	int				len;
	int				for_minus;

	for_minus = 0;
	len = cal_num_len(n);
	num = malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		num[0] = '-';
		for_minus++;
	}
	num[len] = '\0';
	while (len-- > for_minus)
	{
		num[len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (num);
}
