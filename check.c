#include "stdio.h"

void		skip_coma(const char **str)
{
	if (**str == ',')
		(*str)++;
}

void		skip_spaces(const char **str)
{
	while (**str == ' ')
		(*str)++;
}

int		count_coma(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i] != '\0')
		if(str[i] == ',')
			count++;
	return (count);	
}

int	main(void)
{
	char *str = ",,,defg,hij,,,k";
	printf("%d\n", count_coma(str));
}