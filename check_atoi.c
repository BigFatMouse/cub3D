#include "stdio.h"

unsigned	ft_atoi_parce(const char **str)
{
	unsigned num;

	num = 0;
	if (**str == '\0')
		return (0);
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		//printf("%d\n", num);
		// if (num > 6000)
		// 	return (0);
		(*str)++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int i;
	int minus;
	int num;

	i = 0;
	minus = 0;
	num = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == 32)
		i++;
	if (str[i] == '-')
		minus = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (minus == 1)
		num = -num;
	return (num);
}

int	main(void)
{
	printf("%d", ft_atoi_parce("12"));
}