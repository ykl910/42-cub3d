/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:06:17 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 15:07:39 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int	main()
{
	printf("%d",ft_isalnum('d'));
	printf("%d",ft_isalnum('1'));
	printf("%d",ft_isalnum('*'));
	printf("%d",ft_isalnum('|'));
}*/