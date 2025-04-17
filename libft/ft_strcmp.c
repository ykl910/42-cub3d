/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:39:41 by kyang             #+#    #+#             */
/*   Updated: 2025/04/17 10:45:37 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*
int	main(void)
{
	char *s1 = "ABCDFF";
	char *s2 = "ABCDEE";
	char *s3 = "AB";
	char *s4 = "";
	char *s5 = "ABC";
	char *s6 = "ABC";
	int n = 2;

	printf("%d\n",ft_strncmp(s1, s2, 5));
	printf("%d\n",strncmp(s1, s2, 5));

	printf("%d\n",ft_strncmp(s3, s4, n));
	printf("%d\n",strncmp(s3, s4, n));

	printf("%d\n",ft_strncmp(s5, s6, n));
	printf("%d\n",strncmp(s5, s6, n));
	return (0);
}*/
