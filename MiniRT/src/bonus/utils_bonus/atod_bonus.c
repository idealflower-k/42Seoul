#include "defs_bonus.h"

static double	_integer_part(char *str, int len)
{
	double	temp_d;
	char	*temp_s;
	int		i;

	if (len == 0)
		return (0.0);
	i = 0;
	temp_s = ft_malloc(len + 1);
	temp_s[len] = '\0';
	while (i < len)
	{
		temp_s[i] = str[i];
		i++;
	}
	temp_d = (double)ft_atoi(temp_s);
	free(temp_s);
	return (temp_d);
}

static double	_fractional_part(char *str)
{
	double	temp_d;
	int		i;

	temp_d = (double)ft_atoi(str);
	i = ft_strlen(str);
	while (i--)
		temp_d *= 0.1;
	return (temp_d);
}

double	atod(char *str)
{
	double	temp1;
	double	temp2;
	char	*dot;
	int		sign;

	dot = ft_strchr(str, '.');
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	if (dot == NULL || *(dot + 1) == '\0')
		return (_integer_part(str, ft_strlen(str)));
	temp1 = _integer_part(str, dot - str) * sign;
	temp2 = _fractional_part(dot + 1);
	return ((temp1 + temp2) * sign);
}
