int	ft_sqrt(int nb)
{
	long long int	i;

	i = 0;
	if (nb == 1)
		return (1);
	while (i * i <= nb)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
