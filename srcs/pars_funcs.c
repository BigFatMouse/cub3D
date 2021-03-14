/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:40:52 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/14 22:10:03 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void		skip_simbol(const char **str, char c)
{
	while (**str == c)
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

int			count_params(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != ',' && s[i] != '\t') &&
			(s[i + 1] == ' ' || s[i + 1] == ',' || s[i] == '\t'
			|| s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int			check_params(const char *str, const char *check)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(check, str[i]))
			return (1);
		i++;
	}
	return (0);
}

unsigned	ft_atoi_parce(const char **str, t_all *all)
{
	unsigned num;

	num = 0;
	while (**str == 32)
		(*str)++;
	if (**str == '\0')
		return (0);
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		if (num > 16384)
		{
			if (all->flags->screenshot == 1)
				ft_error(ERR_CODE_11);
				return (6000);
		}
		(*str)++;
	}
	printf("num = %d\n",num);
	printf("flag = %d\n",all->flags->screenshot);
	return (num);
}

int			check_extension(char *name, char *ext)
{
	int	len;

	len = ft_strlen(name);
	if (((ft_strnstr(name, ext, len)) != name + len - 4) || len <= 4)
		return (1);
	return (0);
}
