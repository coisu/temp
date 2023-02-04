#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483648)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (result);
}

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}