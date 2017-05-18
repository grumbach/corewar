/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 03:00:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/19 00:46:06 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

char		*ft_strdup_f(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	str = (char *)ft_memalloc(sizeof(*str) * (i + 1));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	ft_memdel((void **)&s);
	s = NULL;
	return (str);
}

char		*ft_strjoin_f(char const *s1, char const *s2)
{
	char	*s3;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(*s3) * (len + 1));
	if (s3)
	{
		while (s1[i] != '\0')
		{
			s3[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
			s3[i++] = s2[j++];
		s3[i] = '\0';
		ft_memdel((void **)&s1);
		ft_memdel((void **)&s2);
		return (s3);
	}
	else
		return (NULL);
}

char		*ft_strjoin_f1(char const *s1, char const *s2)
{
	char	*s3;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(*s3) * (len + 1));
	if (s3)
	{
		while (s1[i] != '\0')
		{
			s3[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
			s3[i++] = s2[j++];
		s3[i] = '\0';
		ft_memdel((void **)&s1);
		return (s3);
	}
	else
		return (NULL);
}

char		*ft_strtrim_f(char const *s)
{
	size_t b;
	size_t i;
	size_t z;

	b = 0;
	i = 0;
	z = ft_strlen(s);
	b = z;
	if (s == NULL)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i] != '\0')
		i++;
	while ((s[z] == ' ' || s[z] == '\n' || s[z] == '\t'
				|| s[z] == '\0') && z > i)
		z--;
	z++;
	return (ft_strsub_f(s, i, (b - (i + (b - z)))));
}

char		*ft_strsub_f(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *)malloc(sizeof(*s2) * (len + 1));
	if (s2)
	{
		while (i < len)
		{
			s2[i] = s[start + i];
			i++;
		}
		s2[i] = '\0';
		ft_memdel((void **)&s);
		return (s2);
	}
	return (NULL);
}
